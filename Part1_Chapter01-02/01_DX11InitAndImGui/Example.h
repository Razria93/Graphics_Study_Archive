#pragma once

#include <windows.h>
#include <memory>
#include <iostream>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <vector>

struct Vec4
{
	float v[4];
};

struct Vec2
{
	float v[2];
};

struct Vertex 
{
	Vec4 pos;
	Vec2 uv;
};

class Example
{
public:
	Example(HWND window, int width, int height, int canvasWidth, int canvasHeight)
	{
		Initialize(window, width, height, canvasWidth, canvasHeight);
	}

	void InitShaders()
	{
		ID3DBlob* vertexBlob = nullptr;
		ID3DBlob* pixelBlob = nullptr;
		ID3DBlob* errorBlob = nullptr;

		if (FAILED(D3DCompileFromFile(L"VS.hlsl", 0, 0, "main", "vs_5_0", 0, 0, &vertexBlob, &errorBlob)))
		{
			if (errorBlob) {
				std::cout << "Vertex shader compile error\n" << (char*)errorBlob->GetBufferPointer() << std::endl;
			}
		}

		if (FAILED(D3DCompileFromFile(L"PS.hlsl", 0, 0, "main", "ps_5_0", 0, 0, &pixelBlob, &errorBlob)))
		{
			if (errorBlob) {
				std::cout << "Pixel shader compile error\n" << (char*)errorBlob->GetBufferPointer() << std::endl;
			}
		}

		device->CreateVertexShader(vertexBlob->GetBufferPointer(), vertexBlob->GetBufferSize(), NULL, &vertexShader);
		device->CreatePixelShader(pixelBlob->GetBufferPointer(), pixelBlob->GetBufferSize(), NULL, &pixelShader);

		D3D11_INPUT_ELEMENT_DESC ied[] =
		{
			{"POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};

		device->CreateInputLayout(ied, 2, vertexBlob->GetBufferPointer(), vertexBlob->GetBufferSize(), &layout);
		deviceContext->IASetInputLayout(layout);

		if (vertexBlob) { vertexBlob->Release(); }
		if (pixelBlob) { pixelBlob->Release(); }
		if (errorBlob) { errorBlob->Release(); }
	}

	void Initialize(HWND window, int width, int height, int canvasWidth, int canvasHeight)
	{
		this->canvasWidth = canvasWidth;
		this->canvasHeight = canvasHeight;

		// Device and swap chain setup.
		DXGI_SWAP_CHAIN_DESC swapChainDesc;
		ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
		swapChainDesc.BufferDesc.Width = width;
		swapChainDesc.BufferDesc.Height = height;
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.BufferCount = 2;
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.OutputWindow = window;
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.Windowed = TRUE;
		swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		UINT createDeviceFlags = 0;

		const D3D_FEATURE_LEVEL featureLevelArray[1] = { D3D_FEATURE_LEVEL_11_0};
		if (FAILED(D3D11CreateDeviceAndSwapChain(NULL,
			D3D_DRIVER_TYPE_HARDWARE,
			NULL,
			createDeviceFlags,
			featureLevelArray,
			1,
			D3D11_SDK_VERSION,
			&swapChainDesc,
			&swapChain,
			&device,
			NULL,
			&deviceContext)))
		{
			std::cout << "D3D11CreateDeviceAndSwapChain() error" << std::endl;
		}

		// Back buffer render target.
		ID3D11Texture2D* pBackBuffer; 		
		swapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
		if (pBackBuffer)
		{
			device->CreateRenderTargetView(pBackBuffer, NULL, &renderTargetView);
			pBackBuffer->Release();
		}
		else
		{
			std::cout << "CreateRenderTargetView() error" << std::endl;
			exit(-1);
		}

		ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));
		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		viewport.Width = float(width);
		viewport.Height = float(height);
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;
		deviceContext->RSSetViewports(1, &viewport);

		// Shader and input layout setup.
		InitShaders();

		// CPU-updated canvas texture exposed to the pixel shader through SRV.
		D3D11_SAMPLER_DESC sampDesc;
		ZeroMemory(&sampDesc, sizeof(sampDesc));
		sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
		sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		sampDesc.MinLOD = 0;
		sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

		device->CreateSamplerState(&sampDesc, &colorSampler);

		D3D11_TEXTURE2D_DESC textureDesc;
		ZeroMemory(&textureDesc, sizeof(textureDesc));
		textureDesc.MipLevels = textureDesc.ArraySize = 1;
		textureDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		textureDesc.SampleDesc.Count = 1;
		textureDesc.Usage = D3D11_USAGE_DYNAMIC;
		textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		textureDesc.MiscFlags = 0;
		textureDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		textureDesc.Width = canvasWidth;
		textureDesc.Height = canvasHeight;

		device->CreateTexture2D(&textureDesc, nullptr, &canvasTexture);

		if (canvasTexture)
		{
			device->CreateShaderResourceView(canvasTexture, nullptr, &canvasTextureView);

			D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
			renderTargetViewDesc.Format = textureDesc.Format;
			renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
			renderTargetViewDesc.Texture2D.MipSlice = 0;

			device->CreateRenderTargetView(canvasTexture, &renderTargetViewDesc, &canvasRenderTargetView);
		}
		else
		{
			std::cout << "CreateRenderTargetView() error" << std::endl;
		}

		// Full-screen quad geometry.
		{
			const std::vector<Vertex> vertices =
			{
				{ { -1.0f, -1.0f, 0.0f, 1.0f }, { 0.f, 1.f },},
				{ {  1.0f, -1.0f, 0.0f, 1.0f }, { 1.f, 1.f },},
				{ {  1.0f,  1.0f, 0.0f, 1.0f }, { 1.f, 0.f },},
				{ { -1.0f,  1.0f, 0.0f, 1.0f }, { 0.f, 0.f },},
			};

			D3D11_BUFFER_DESC bufferDesc;
			ZeroMemory(&bufferDesc, sizeof(bufferDesc));
			bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
			bufferDesc.ByteWidth = UINT(sizeof(Vertex) * vertices.size());
			bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			bufferDesc.StructureByteStride = sizeof(Vertex);

			D3D11_SUBRESOURCE_DATA vertexBufferData = { 0, };
			vertexBufferData.pSysMem = vertices.data();
			vertexBufferData.SysMemPitch = 0;
			vertexBufferData.SysMemSlicePitch = 0;

			const HRESULT hr = device->CreateBuffer(&bufferDesc, &vertexBufferData, &vertexBuffer);
			if (FAILED(hr)) {
				std::cout << "CreateBuffer() failed. " << std::hex << hr << std::endl;
			};
		}

		{
			const std::vector<uint16_t> indices =
			{
				3,1,0,
				2,1,3,
			};

			indexCount = UINT(indices.size());

			D3D11_BUFFER_DESC bufferDesc = {};
			bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
			bufferDesc.ByteWidth = UINT(sizeof(uint16_t) * indices.size());
			bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
			bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			bufferDesc.StructureByteStride = sizeof(uint16_t);

			D3D11_SUBRESOURCE_DATA indexBufferData = { 0 };
			indexBufferData.pSysMem = indices.data();
			indexBufferData.SysMemPitch = 0;
			indexBufferData.SysMemSlicePitch = 0;

			device->CreateBuffer(&bufferDesc, &indexBufferData, &indexBuffer);
		}
	}

	void Update()
	{
		Sleep(100);

		static int i = 0;

		// Rebuild the CPU-side canvas and upload it to the dynamic texture.
		std::vector<Vec4> pixels(canvasWidth * canvasHeight, Vec4{ backgroundColor[0], backgroundColor[1], backgroundColor[2], backgroundColor[3] });

		if (i >= pixels.size() - 1) 
		{
			i = 0;
		}
		else
		{
			i++;
		}

		int k = i % 3;

		if (k == 0)
		{
			pixels[i] = Vec4{ 1.0f, 0.0f, 0.0f, 1.0f };
		}
		else if (k == 1)
		{
			pixels[i] = Vec4{ 0.0f, 1.0f, 0.0f, 1.0f };
		}
		else
		{
			pixels[i] = Vec4{ 0.0f, 0.0f, 1.0f, 1.0f };

		}

		int l = i - 1;

		if (l >= 0)
		{
			pixels[l] = i % 3 == 0 ? Vec4{ 1.0f, 0.0f, 0.0f, 1.0f }
						: i % 3 == 1 ? Vec4{ 0.0f, 1.0f, 0.0f, 1.0f }
						: Vec4{ 0.0f, 0.0f, 1.0f, 1.0f };
		}

		D3D11_MAPPED_SUBRESOURCE ms;
		deviceContext->Map(canvasTexture, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
		memcpy(ms.pData, pixels.data(), pixels.size() * sizeof(Vec4));
		deviceContext->Unmap(canvasTexture, NULL);
	}

	void Render()
	{
		float clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
		deviceContext->RSSetViewports(1, &viewport);
		deviceContext->OMSetRenderTargets(1, &renderTargetView, nullptr);
		deviceContext->ClearRenderTargetView(renderTargetView, clearColor);

		// Draw the dynamic canvas texture on a screen-aligned quad.
		deviceContext->VSSetShader(vertexShader, 0, 0);
		deviceContext->PSSetShader(pixelShader, 0, 0);

		UINT stride = sizeof(Vertex);
		UINT offset = 0;
		deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
		deviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R16_UINT, 0);

		deviceContext->PSSetSamplers(0, 1, &colorSampler);
		deviceContext->PSSetShaderResources(0, 1, &canvasTextureView);
		deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		deviceContext->DrawIndexed(indexCount, 0, 0);
	}

	void Clean()
	{
		// Release D3D resources owned by this example.
		if (layout) { layout->Release(); layout = NULL; }
		if (vertexShader) { vertexShader->Release(); vertexShader = NULL; }
		if (pixelShader) { pixelShader->Release(); pixelShader = NULL; }
		if (vertexBuffer) { vertexBuffer->Release(); vertexBuffer = NULL; }
		if (indexBuffer) { indexBuffer->Release(); indexBuffer = NULL; }
		if (canvasTexture) { canvasTexture->Release(); canvasTexture = NULL; }
		if (canvasTextureView) { canvasTextureView->Release(); canvasTextureView = NULL; }
		if (canvasRenderTargetView) { canvasRenderTargetView->Release(); canvasRenderTargetView = NULL; }
		if (colorSampler) { colorSampler->Release(); colorSampler = NULL; }
		if (renderTargetView) { renderTargetView->Release(); renderTargetView = NULL; }
		if (swapChain) { swapChain->Release(); swapChain = NULL; }
		if (deviceContext) { deviceContext->Release(); deviceContext = NULL; }
		if (device) { device->Release(); device = NULL; }
	}

public:
	ID3D11Device* device;
	ID3D11DeviceContext* deviceContext;
	IDXGISwapChain* swapChain;
	D3D11_VIEWPORT viewport;
	ID3D11RenderTargetView* renderTargetView;
	ID3D11VertexShader* vertexShader;
	ID3D11PixelShader* pixelShader;
	ID3D11InputLayout* layout;

	ID3D11Buffer* vertexBuffer = nullptr;
	ID3D11Buffer* indexBuffer = nullptr;
	ID3D11Texture2D* canvasTexture = nullptr;
	ID3D11ShaderResourceView* canvasTextureView = nullptr;
	ID3D11RenderTargetView* canvasRenderTargetView = nullptr;
	ID3D11SamplerState* colorSampler;
	UINT indexCount;	

	int canvasWidth, canvasHeight;
	float backgroundColor[4] = { 0.8f, 0.8f, 0.8f, 1.0f };
};
