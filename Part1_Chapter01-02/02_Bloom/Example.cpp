#include "Example.h"

#include <cmath>
#include <cstdint>
#include <omp.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

void Image::ReadFromFile(const char* filename)
{
	int sourceChannels = 0;
	unsigned char* img = stbi_load(filename, &width, &height, &sourceChannels, 4);

	if (!img)
	{
		std::cout << "Warning: " << filename << " not found. Using synthetic fallback image." << std::endl;
		CreateSyntheticTestImage(640, 360);
		return;
	}

	channels = 4;
	pixels.resize(width * height);

	for (int i = 0; i < width * height; i++)
	{
		pixels[i].v[0] = img[i * channels] / 255.0f;
		pixels[i].v[1] = img[i * channels + 1] / 255.0f;
		pixels[i].v[2] = img[i * channels + 2] / 255.0f;
		pixels[i].v[3] = img[i * channels + 3] / 255.0f;
	}

	stbi_image_free(img);

	std::cout << "Image loaded: " << width << " x " << height << " channels=" << channels << std::endl;
}

void Image::CreateSyntheticTestImage(int imageWidth, int imageHeight)
{
	width = imageWidth;
	height = imageHeight;
	channels = 4;
	pixels.assign(width * height, Vec4{ 0.02f, 0.025f, 0.035f, 1.0f });

	const struct Light
	{
		float x, y, radius;
		Vec4 color;
	} lights[] = {
		{ 0.25f, 0.45f, 0.16f, Vec4{ 1.0f, 0.45f, 0.18f, 1.0f } },
		{ 0.55f, 0.35f, 0.12f, Vec4{ 0.28f, 0.70f, 1.0f, 1.0f } },
		{ 0.76f, 0.62f, 0.18f, Vec4{ 0.95f, 0.80f, 0.30f, 1.0f } },
	};

	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			const float u = float(i) / float(width - 1);
			const float v = float(j) / float(height - 1);
			Vec4& c = GetPixel(i, j);

			c.v[0] += 0.05f * u;
			c.v[1] += 0.04f * v;
			c.v[2] += 0.08f * (1.0f - u);

			for (const Light& light : lights)
			{
				const float dx = u - light.x;
				const float dy = v - light.y;
				const float d = std::sqrt(dx * dx + dy * dy);
				const float t = std::clamp(1.0f - d / light.radius, 0.0f, 1.0f);
				const float falloff = t * t * t;

				c.v[0] = std::clamp(c.v[0] + light.color.v[0] * falloff, 0.0f, 1.0f);
				c.v[1] = std::clamp(c.v[1] + light.color.v[1] * falloff, 0.0f, 1.0f);
				c.v[2] = std::clamp(c.v[2] + light.color.v[2] * falloff, 0.0f, 1.0f);
			}
		}
	}
}

void Image::WritePNG(const char* filename)
{
	std::vector<unsigned char> img(width * height * channels, 0);

	for (int i = 0; i < width * height; i++)
	{
		img[i * channels] = uint8_t(std::clamp(pixels[i].v[0], 0.0f, 1.0f) * 255.0f);
		img[i * channels + 1] = uint8_t(std::clamp(pixels[i].v[1], 0.0f, 1.0f) * 255.0f);
		img[i * channels + 2] = uint8_t(std::clamp(pixels[i].v[2], 0.0f, 1.0f) * 255.0f);
		img[i * channels + 3] = uint8_t(std::clamp(pixels[i].v[3], 0.0f, 1.0f) * 255.0f);
	}

	stbi_write_png(filename, width, height, channels, img.data(), width * channels);
}

Vec4& Image::GetPixel(int i, int j)
{
	i = std::clamp(i, 0, width - 1);
	j = std::clamp(j, 0, height - 1);

	return pixels[i + width * j];
}

void Image::BoxBlur5()
{
	std::vector<Vec4> pixelsBuffer(pixels.size());

	// Separable blur: horizontal pass followed by vertical pass.
#pragma omp parallel for
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			Vec4 neighborColorSum{ 0.0f, 0.0f, 0.0f, 1.0f };

			for (int k = 0; k < 5; k++)
			{
				neighborColorSum.v[0] += GetPixel(i + (k - 2), j).v[0];
				neighborColorSum.v[1] += GetPixel(i + (k - 2), j).v[1];
				neighborColorSum.v[2] += GetPixel(i + (k - 2), j).v[2];
			}

			pixelsBuffer[i + (j * width)].v[0] = neighborColorSum.v[0] * 0.2f;
			pixelsBuffer[i + (j * width)].v[1] = neighborColorSum.v[1] * 0.2f;
			pixelsBuffer[i + (j * width)].v[2] = neighborColorSum.v[2] * 0.2f;
			pixelsBuffer[i + (j * width)].v[3] = 1.0f;
		}
	}

	std::swap(pixels, pixelsBuffer);

#pragma omp parallel for
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			Vec4 neighborColorSum{ 0.0f, 0.0f, 0.0f, 1.0f };

			for (int k = 0; k < 5; k++)
			{
				neighborColorSum.v[0] += GetPixel(i, j + (k - 2)).v[0];
				neighborColorSum.v[1] += GetPixel(i, j + (k - 2)).v[1];
				neighborColorSum.v[2] += GetPixel(i, j + (k - 2)).v[2];
			}

			pixelsBuffer[i + (j * width)].v[0] = neighborColorSum.v[0] * 0.2f;
			pixelsBuffer[i + (j * width)].v[1] = neighborColorSum.v[1] * 0.2f;
			pixelsBuffer[i + (j * width)].v[2] = neighborColorSum.v[2] * 0.2f;
			pixelsBuffer[i + (j * width)].v[3] = 1.0f;
		}
	}

	std::swap(pixels, pixelsBuffer);
}

void Image::GaussianBlur5()
{
	std::vector<Vec4> pixelsBuffer(pixels.size());
	const float weights[5] = { 0.0545f, 0.2442f, 0.4026f, 0.2442f, 0.0545f };

#pragma omp parallel for
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			Vec4 neighborColorSum{ 0.0f, 0.0f, 0.0f, 1.0f };

			for (int k = 0; k < 5; k++)
			{
				neighborColorSum.v[0] += GetPixel(i + (k - 2), j).v[0] * weights[k];
				neighborColorSum.v[1] += GetPixel(i + (k - 2), j).v[1] * weights[k];
				neighborColorSum.v[2] += GetPixel(i + (k - 2), j).v[2] * weights[k];
			}

			pixelsBuffer[i + (j * width)].v[0] = neighborColorSum.v[0];
			pixelsBuffer[i + (j * width)].v[1] = neighborColorSum.v[1];
			pixelsBuffer[i + (j * width)].v[2] = neighborColorSum.v[2];
			pixelsBuffer[i + (j * width)].v[3] = 1.0f;
		}
	}

	std::swap(pixels, pixelsBuffer);

#pragma omp parallel for
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			Vec4 neighborColorSum{ 0.0f, 0.0f, 0.0f, 1.0f };

			for (int k = 0; k < 5; k++)
			{
				neighborColorSum.v[0] += GetPixel(i, j + (k - 2)).v[0] * weights[k];
				neighborColorSum.v[1] += GetPixel(i, j + (k - 2)).v[1] * weights[k];
				neighborColorSum.v[2] += GetPixel(i, j + (k - 2)).v[2] * weights[k];
			}

			pixelsBuffer[i + (j * width)].v[0] = neighborColorSum.v[0];
			pixelsBuffer[i + (j * width)].v[1] = neighborColorSum.v[1];
			pixelsBuffer[i + (j * width)].v[2] = neighborColorSum.v[2];
			pixelsBuffer[i + (j * width)].v[3] = 1.0f;
		}
	}

	std::swap(pixels, pixelsBuffer);
}

void Image::Bloom(float threshold, int repeatCount, float weight)
{
	const std::vector<Vec4> originalPixels = pixels;
	const float luminanceWeights[3] = { 0.2126f, 0.7152f, 0.0722f };

	// Extract bright pixels using relative luminance.
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			Vec4& c = GetPixel(i, j);
			const float relativeLuminance =
				c.v[0] * luminanceWeights[0] +
				c.v[1] * luminanceWeights[1] +
				c.v[2] * luminanceWeights[2];

			if (relativeLuminance < threshold)
			{
				c.v[0] = 0.0f;
				c.v[1] = 0.0f;
				c.v[2] = 0.0f;
			}
		}
	}

	for (int i = 0; i < repeatCount; i++)
	{
		GaussianBlur5();
	}

	// Add blurred highlights back to the original image.
	for (size_t i = 0; i < originalPixels.size(); i++)
	{
		pixels[i].v[0] = std::clamp(originalPixels[i].v[0] + pixels[i].v[0] * weight, 0.0f, 1.0f);
		pixels[i].v[1] = std::clamp(originalPixels[i].v[1] + pixels[i].v[1] * weight, 0.0f, 1.0f);
		pixels[i].v[2] = std::clamp(originalPixels[i].v[2] + pixels[i].v[2] * weight, 0.0f, 1.0f);
		pixels[i].v[3] = originalPixels[i].v[3];
	}
}
