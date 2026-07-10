#include "GeometryGenerator.h"

#include <iostream>

namespace hlab
{

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

MeshData GeometryGenerator::MakeSquare()
{
	vector<Vector3> positions;
	vector<Vector3> colors;
	vector<Vector3> normals;
	vector<Vector2> texcoords; // 텍스춰 좌표

	const float scale = 1.0f;

	// 앞면
	positions.push_back(Vector3(-1.0f, 1.0f, 0.0f) * scale);
	positions.push_back(Vector3(1.0f, 1.0f, 0.0f) * scale);
	positions.push_back(Vector3(1.0f, -1.0f, 0.0f) * scale);
	positions.push_back(Vector3(-1.0f, -1.0f, 0.0f) * scale);
	colors.push_back(Vector3(0.0f, 0.0f, 1.0f));
	colors.push_back(Vector3(0.0f, 0.0f, 1.0f));
	colors.push_back(Vector3(0.0f, 0.0f, 1.0f));
	colors.push_back(Vector3(0.0f, 0.0f, 1.0f));
	normals.push_back(Vector3(0.0f, 0.0f, -1.0f));
	normals.push_back(Vector3(0.0f, 0.0f, -1.0f));
	normals.push_back(Vector3(0.0f, 0.0f, -1.0f));
	normals.push_back(Vector3(0.0f, 0.0f, -1.0f));

	// Texture Coordinates (Direct3D 9)
	// https://learn.microsoft.com/en-us/windows/win32/direct3d9/texture-coordinates
	texcoords.push_back(Vector2(0.0f, 0.0f));
	texcoords.push_back(Vector2(1.0f, 0.0f));
	texcoords.push_back(Vector2(1.0f, 1.0f));
	texcoords.push_back(Vector2(0.0f, 1.0f));

	MeshData meshData;

	for (size_t i = 0; i < positions.size(); i++)
	{
		Vertex v;
		v.position = positions[i];
		v.normal = normals[i];
		v.texcoord = texcoords[i];

		// v.color = colors[i];

		meshData.vertices.push_back(v);
	}
	meshData.indices = {
	    0, 1, 2, 0, 2, 3, // 앞면
	};

	return meshData;
}

MeshData GeometryGenerator::MakeBox()
{

	vector<Vector3> positions;
	vector<Vector3> colors;
	vector<Vector3> normals;
	vector<Vector2> texcoords; // 텍스춰 좌표

	const float scale = 1.0f;

	// 윗면
	positions.push_back(Vector3(-1.0f, 1.0f, -1.0f) * scale);
	positions.push_back(Vector3(-1.0f, 1.0f, 1.0f) * scale);
	positions.push_back(Vector3(1.0f, 1.0f, 1.0f) * scale);
	positions.push_back(Vector3(1.0f, 1.0f, -1.0f) * scale);
	colors.push_back(Vector3(1.0f, 0.0f, 0.0f));
	colors.push_back(Vector3(1.0f, 0.0f, 0.0f));
	colors.push_back(Vector3(1.0f, 0.0f, 0.0f));
	colors.push_back(Vector3(1.0f, 0.0f, 0.0f));
	normals.push_back(Vector3(0.0f, 1.0f, 0.0f));
	normals.push_back(Vector3(0.0f, 1.0f, 0.0f));
	normals.push_back(Vector3(0.0f, 1.0f, 0.0f));
	normals.push_back(Vector3(0.0f, 1.0f, 0.0f));
	texcoords.push_back(Vector2(0.0f, 0.0f));
	texcoords.push_back(Vector2(1.0f, 0.0f));
	texcoords.push_back(Vector2(1.0f, 1.0f));
	texcoords.push_back(Vector2(0.0f, 1.0f));

	// 아랫면
	positions.push_back(Vector3(-1.0f, -1.0f, -1.0f) * scale);
	positions.push_back(Vector3(1.0f, -1.0f, -1.0f) * scale);
	positions.push_back(Vector3(1.0f, -1.0f, 1.0f) * scale);
	positions.push_back(Vector3(-1.0f, -1.0f, 1.0f) * scale);
	colors.push_back(Vector3(0.0f, 1.0f, 0.0f));
	colors.push_back(Vector3(0.0f, 1.0f, 0.0f));
	colors.push_back(Vector3(0.0f, 1.0f, 0.0f));
	colors.push_back(Vector3(0.0f, 1.0f, 0.0f));
	normals.push_back(Vector3(0.0f, -1.0f, 0.0f));
	normals.push_back(Vector3(0.0f, -1.0f, 0.0f));
	normals.push_back(Vector3(0.0f, -1.0f, 0.0f));
	normals.push_back(Vector3(0.0f, -1.0f, 0.0f));
	texcoords.push_back(Vector2(0.0f, 0.0f));
	texcoords.push_back(Vector2(1.0f, 0.0f));
	texcoords.push_back(Vector2(1.0f, 1.0f));
	texcoords.push_back(Vector2(0.0f, 1.0f));

	// 앞면
	positions.push_back(Vector3(-1.0f, -1.0f, -1.0f) * scale);
	positions.push_back(Vector3(-1.0f, 1.0f, -1.0f) * scale);
	positions.push_back(Vector3(1.0f, 1.0f, -1.0f) * scale);
	positions.push_back(Vector3(1.0f, -1.0f, -1.0f) * scale);
	colors.push_back(Vector3(0.0f, 0.0f, 1.0f));
	colors.push_back(Vector3(0.0f, 0.0f, 1.0f));
	colors.push_back(Vector3(0.0f, 0.0f, 1.0f));
	colors.push_back(Vector3(0.0f, 0.0f, 1.0f));
	normals.push_back(Vector3(0.0f, 0.0f, -1.0f));
	normals.push_back(Vector3(0.0f, 0.0f, -1.0f));
	normals.push_back(Vector3(0.0f, 0.0f, -1.0f));
	normals.push_back(Vector3(0.0f, 0.0f, -1.0f));
	texcoords.push_back(Vector2(0.0f, 0.0f));
	texcoords.push_back(Vector2(1.0f, 0.0f));
	texcoords.push_back(Vector2(1.0f, 1.0f));
	texcoords.push_back(Vector2(0.0f, 1.0f));

	// 뒷면
	positions.push_back(Vector3(-1.0f, -1.0f, 1.0f) * scale);
	positions.push_back(Vector3(1.0f, -1.0f, 1.0f) * scale);
	positions.push_back(Vector3(1.0f, 1.0f, 1.0f) * scale);
	positions.push_back(Vector3(-1.0f, 1.0f, 1.0f) * scale);
	colors.push_back(Vector3(0.0f, 1.0f, 1.0f));
	colors.push_back(Vector3(0.0f, 1.0f, 1.0f));
	colors.push_back(Vector3(0.0f, 1.0f, 1.0f));
	colors.push_back(Vector3(0.0f, 1.0f, 1.0f));
	normals.push_back(Vector3(0.0f, 0.0f, 1.0f));
	normals.push_back(Vector3(0.0f, 0.0f, 1.0f));
	normals.push_back(Vector3(0.0f, 0.0f, 1.0f));
	normals.push_back(Vector3(0.0f, 0.0f, 1.0f));
	texcoords.push_back(Vector2(0.0f, 0.0f));
	texcoords.push_back(Vector2(1.0f, 0.0f));
	texcoords.push_back(Vector2(1.0f, 1.0f));
	texcoords.push_back(Vector2(0.0f, 1.0f));

	// 왼쪽
	positions.push_back(Vector3(-1.0f, -1.0f, 1.0f) * scale);
	positions.push_back(Vector3(-1.0f, 1.0f, 1.0f) * scale);
	positions.push_back(Vector3(-1.0f, 1.0f, -1.0f) * scale);
	positions.push_back(Vector3(-1.0f, -1.0f, -1.0f) * scale);
	colors.push_back(Vector3(1.0f, 1.0f, 0.0f));
	colors.push_back(Vector3(1.0f, 1.0f, 0.0f));
	colors.push_back(Vector3(1.0f, 1.0f, 0.0f));
	colors.push_back(Vector3(1.0f, 1.0f, 0.0f));
	normals.push_back(Vector3(-1.0f, 0.0f, 0.0f));
	normals.push_back(Vector3(-1.0f, 0.0f, 0.0f));
	normals.push_back(Vector3(-1.0f, 0.0f, 0.0f));
	normals.push_back(Vector3(-1.0f, 0.0f, 0.0f));
	texcoords.push_back(Vector2(0.0f, 0.0f));
	texcoords.push_back(Vector2(1.0f, 0.0f));
	texcoords.push_back(Vector2(1.0f, 1.0f));
	texcoords.push_back(Vector2(0.0f, 1.0f));

	// 오른쪽
	positions.push_back(Vector3(1.0f, -1.0f, 1.0f) * scale);
	positions.push_back(Vector3(1.0f, -1.0f, -1.0f) * scale);
	positions.push_back(Vector3(1.0f, 1.0f, -1.0f) * scale);
	positions.push_back(Vector3(1.0f, 1.0f, 1.0f) * scale);
	colors.push_back(Vector3(1.0f, 0.0f, 1.0f));
	colors.push_back(Vector3(1.0f, 0.0f, 1.0f));
	colors.push_back(Vector3(1.0f, 0.0f, 1.0f));
	colors.push_back(Vector3(1.0f, 0.0f, 1.0f));
	normals.push_back(Vector3(1.0f, 0.0f, 0.0f));
	normals.push_back(Vector3(1.0f, 0.0f, 0.0f));
	normals.push_back(Vector3(1.0f, 0.0f, 0.0f));
	normals.push_back(Vector3(1.0f, 0.0f, 0.0f));
	texcoords.push_back(Vector2(0.0f, 0.0f));
	texcoords.push_back(Vector2(1.0f, 0.0f));
	texcoords.push_back(Vector2(1.0f, 1.0f));
	texcoords.push_back(Vector2(0.0f, 1.0f));

	MeshData meshData;
	for (size_t i = 0; i < positions.size(); i++)
	{
		Vertex v;
		v.position = positions[i];
		v.normal = normals[i];
		v.texcoord = texcoords[i];
		meshData.vertices.push_back(v);
	}

	meshData.indices = {
	    0, 1, 2, 0, 2, 3,       // 윗면
	    4, 5, 6, 4, 6, 7,       // 아랫면
	    8, 9, 10, 8, 10, 11,    // 앞면
	    12, 13, 14, 12, 14, 15, // 뒷면
	    16, 17, 18, 16, 18, 19, // 왼쪽
	    20, 21, 22, 20, 22, 23  // 오른쪽
	};

	return meshData;
}

MeshData GeometryGenerator::MakeCylinder(const float bottomRadius,
                                         const float topRadius, float height,
                                         int numSlices)
{

	// Texture 좌표계때문에 (numSlices + 1) x 2 개의 버텍스 사용

	const float dTheta = -XM_2PI / float(numSlices);

	MeshData meshData;

	vector<Vertex> &vertices = meshData.vertices;

	// 옆면의 바닥 버텍스들 (인덱스 0 이상 numSlices 미만)
	for (int i = 0; i <= numSlices; i++)
	{
		Vertex v;
		v.position =
		    Vector3::Transform(Vector3(bottomRadius, -0.5f * height, 0.0f),
		                       Matrix::CreateRotationY(dTheta * float(i)));

		// std::cout << v.position.x << " " << v.position.z << std::endl;

		v.normal = v.position - Vector3(0.0f, -0.5f * height, 0.0f);
		v.normal.Normalize();
		v.texcoord = Vector2(float(i) / numSlices, 1.0f);

		vertices.push_back(v);
	}

	// 옆면의 맨 위 버텍스들 (인덱스 numSlices 이상 2 * numSlices 미만)
	for (int i = 0; i <= numSlices; i++)
	{
		Vertex v;
		v.position =
		    Vector3::Transform(Vector3(topRadius, 0.5f * height, 0.0f),
		                       Matrix::CreateRotationY(dTheta * float(i)));
		v.normal = v.position - Vector3(0.0f, 0.5f * height, 0.0f);
		v.normal.Normalize();
		v.texcoord = Vector2(float(i) / numSlices, 0.0f);

		vertices.push_back(v);
	}

	vector<uint16_t> &indices = meshData.indices;

	for (int i = 0; i < numSlices; i++)
	{
		indices.push_back(i);
		indices.push_back(i + numSlices + 1);
		indices.push_back(i + 1 + numSlices + 1);

		indices.push_back(i);
		indices.push_back(i + 1 + numSlices + 1);
		indices.push_back(i + 1);
	}

	return meshData;
}

MeshData GeometryGenerator::MakeSphere(const float radius, const int numSlices,
                                       const int numStacks)
{
	using namespace DirectX;
	using DirectX::SimpleMath::Matrix;
	using DirectX::SimpleMath::Vector3;

	MeshData meshData;

	vector<Vertex> &vertices = meshData.vertices;
	vector<uint16_t> &indices = meshData.indices;

	int offset_half;

	float numSlices_float = float(numSlices);
	float numStacks_float = float(numStacks);

	// Top_HalfSphere
	bool isTop_HalfSphere = true;
	{
		float sign = isTop_HalfSphere ? +1.0f : -1.0f;

		const float dTheta = -XM_2PI / numSlices_float * sign; // DirectX Math는 회전을 CW방향이 +방향으로 전개되게 구성해놨음
		const float dPhi = XM_PI * 0.5f / numStacks_float * sign;

		// Vertex
		for (int j = 0; j <= numStacks; j++)
		{
			Vertex vertex;
			Vector3 v0 = Vector3(abs(radius) * sign, 0.0f, 0.0f);
			Vector3 normal = Vector3(1.0f * sign, 0.0f, 0.0f);

			float dPhi_j = dPhi * j * sign;
			Matrix rotate_Z = Matrix::CreateRotationZ(dPhi_j);
			// Vector3 v0_rotateZ= Vector3::Transform(v0, rotate_Z); // 하단에서 한번에 연산하기 위해 주석처리

			for (int i = 0; i <= numSlices; i++)
			{
				if (j == numStacks)
				{
					Vector3 extremePoint = Vector3(0.0f, radius, 0.0f);

					vertex.position = extremePoint * sign;
					vertex.normal = Vector3(0.0f, 1.0f * sign, 0.0f);
					vertex.texcoord.x = float(i) / numSlices_float;
					vertex.texcoord.y = 0.0f;
				}
				else
				{
					float dTheta_i = dTheta * i;
					Matrix rotate_Y = Matrix::CreateRotationY(dTheta_i);

					Matrix rotateZY = rotate_Z * rotate_Y;
					Vector3 v0_rotateZY = Vector3::Transform(v0, rotateZY);

					Matrix invpos_rotateZY = rotateZY.Invert().Transpose();
					Vector3 invposNormal_ZY = Vector3::Transform(normal, invpos_rotateZY);

					float ratio_x = float(i) / numSlices_float;
					float ratio_y = v0_rotateZY.y / radius;

					vertex.position = v0_rotateZY;
					vertex.normal = invposNormal_ZY;

					vertex.texcoord.x = ratio_x;
					vertex.texcoord.y = (1 - ratio_y) / 2;
				}

				// std::cout << "i : " << i << " / j : " << j << std::endl;
				// std::cout << "v0_rotateZY.x : " << v0_rotateZY.x << " / v0_rotateZY.y : " << v0_rotateZY.y << " / v0_rotateZY.z : " << v0_rotateZY.z << std::endl;
				// std::cout << "invposNormal_ZY.x : " << invposNormal_ZY.x << " / invposNormal_ZY.y : " << invposNormal_ZY.y << " / invposNormal_ZY.z : " << invposNormal_ZY.z << std::endl;
				// std::cout << "v.texcoord.x : " << v.texcoord.x << " / v.texcoord.y : " << v.texcoord.y << std::endl;

				vertices.push_back(vertex);
			}
		} // Vertex

		offset_half = vertices.size();

		// Index
		for (int j = 0; j < numStacks; j++)
		{
			int offset = (numSlices + 1);

			for (int i = 0; i < numSlices; i++)
			{
				if (j == (numStacks - 1))
				{
					int i0 = (offset * j) + i;
					int i1 = (offset * j) + (i + 1);
					int i3 = (offset * (j + 1)) + (i + 1);

					indices.push_back(i0);
					indices.push_back(i3);
					indices.push_back(i1);
				}
				else
				{
					int i0 = (offset * j) + i;
					int i1 = (offset * j) + (i + 1);
					int i2 = (offset * (j + 1)) + i;
					int i3 = (offset * (j + 1)) + (i + 1);

					indices.push_back(i0);
					indices.push_back(i2);
					indices.push_back(i3);

					indices.push_back(i0);
					indices.push_back(i3);
					indices.push_back(i1);
				}
			}
		} // Index
	} // Top_HalfSphere

	// Bottom_HalfSphere
	isTop_HalfSphere = false;
	{
		float sign = isTop_HalfSphere ? +1.0f : -1.0f;

		const float dTheta = -XM_2PI / numSlices_float * sign; // DirectX Math는 회전을 CW방향이 +방향으로 전개되게 구성해놨음
		const float dPhi = XM_PI * 0.5f / numStacks_float * sign;

		// Vertex
		for (int j = 0; j <= numStacks; j++)
		{
			Vertex vertex;
			Vector3 v0 = Vector3(abs(radius) * sign, 0.0f, 0.0f);
			Vector3 normal = Vector3(1.0f * sign, 0.0f, 0.0f);

			float dPhi_j = dPhi * j * sign;
			Matrix rotate_Z = Matrix::CreateRotationZ(dPhi_j);
			// Vector3 v0_rotateZ= Vector3::Transform(v0, rotate_Z); // 하단에서 한번에 연산하기 위해 주석처리

			for (int i = 0; i <= numSlices; i++)
			{
				if (j == numStacks)
				{
					Vector3 extremePoint = Vector3(0.0f, radius, 0.0f);

					vertex.position = extremePoint * sign;
					vertex.normal = Vector3(0.0f, 1.0f * sign, 0.0f);
					vertex.texcoord.x = float(i) / numSlices_float;
					vertex.texcoord.y = 1.0f;
				}

				else
				{
					float dTheta_i = dTheta * i;
					Matrix rotate_Y = Matrix::CreateRotationY(dTheta_i);

					Matrix rotateZY = rotate_Z * rotate_Y;
					Vector3 v0_rotateZY = Vector3::Transform(v0, rotateZY);

					Matrix invpos_rotateZY = rotateZY.Invert().Transpose();
					Vector3 invposNormal_ZY = Vector3::Transform(normal, invpos_rotateZY);

					float ratio_x = float(i) / numSlices_float;
					float ratio_y = v0_rotateZY.y / radius;

					vertex.position = v0_rotateZY;
					vertex.normal = invposNormal_ZY;

					vertex.texcoord.x = (1 - ratio_x) + 0.5f;
					vertex.texcoord.y = (1 - ratio_y) / 2;
				}

				// std::cout << "i : " << i << " / j : " << j << std::endl;
				// std::cout << "v0_rotateZY.x : " << v0_rotateZY.x << " / v0_rotateZY.y : " << v0_rotateZY.y << " / v0_rotateZY.z : " << v0_rotateZY.z << std::endl;
				// std::cout << "invposNormal_ZY.x : " << invposNormal_ZY.x << " / invposNormal_ZY.y : " << invposNormal_ZY.y << " / invposNormal_ZY.z : " << invposNormal_ZY.z << std::endl;
				// std::cout << "v.texcoord.x : " << v.texcoord.x << " / v.texcoord.y : " << v.texcoord.y << std::endl;

				vertices.push_back(vertex);
			}
		} // Vertex

		// Index
		for (int j = 0; j < numStacks; j++)
		{
			int offset = (numSlices + 1);

			for (int i = 0; i < numSlices; i++)
			{
				if (j == (numStacks - 1))
				{
					int i0 = offset_half + (offset * j) + i;
					int i1 = offset_half + (offset * j) + (i + 1);
					int i3 = offset_half + (offset * (j + 1)) + (i + 1);

					indices.push_back(i0);
					indices.push_back(i3);
					indices.push_back(i1);
				}
				else
				{
					int i0 = offset_half + (offset * j) + i;
					int i1 = offset_half + (offset * j) + (i + 1);
					int i2 = offset_half + (offset * (j + 1)) + i;
					int i3 = offset_half + (offset * (j + 1)) + (i + 1);

					indices.push_back(i0);
					indices.push_back(i2);
					indices.push_back(i3);

					indices.push_back(i0);
					indices.push_back(i3);
					indices.push_back(i1);
				}
			}
		} // Index
	} // Bottom_HalfSphere

	meshData.vertices = vertices;
	meshData.indices = indices;

	return meshData;
}

MeshData GeometryGenerator::MakeIcosahedron()
{

	const float X = 0.525731f;
	const float Z = 0.850651f;

	MeshData newMesh;

	vector<Vector3> pos = {
	    Vector3(-X, 0.0f, Z), Vector3(X, 0.0f, Z), Vector3(-X, 0.0f, -Z),
	    Vector3(X, 0.0f, -Z), Vector3(0.0f, Z, X), Vector3(0.0f, Z, -X),
	    Vector3(0.0f, -Z, X), Vector3(0.0f, -Z, -X), Vector3(Z, X, 0.0f),
	    Vector3(-Z, X, 0.0f), Vector3(Z, -X, 0.0f), Vector3(-Z, -X, 0.0f)};

	for (size_t i = 0; i < pos.size(); i++)
	{
		Vertex v;
		v.position = pos[i];
		v.normal = v.position;
		v.normal.Normalize();

		newMesh.vertices.push_back(v);
	}

	newMesh.indices = {1, 4, 0, 4, 9, 0, 4, 5, 9, 8, 5, 4, 1, 8, 4,
	                   1, 10, 8, 10, 3, 8, 8, 3, 5, 3, 2, 5, 3, 7, 2,
	                   3, 10, 7, 10, 6, 7, 6, 11, 7, 6, 0, 11, 6, 1, 0,
	                   10, 1, 6, 11, 0, 9, 2, 11, 9, 5, 2, 9, 11, 2, 7};

	return newMesh;
}

MeshData GeometryGenerator::MakeTetrahedron()
{

	// Regular Tetrahedron
	// https://mathworld.wolfram.com/RegularTetrahedron.html

	const float a = 1.0f;
	const float x = sqrt(3.0f) / 3.0f * a;
	const float d = sqrt(3.0f) / 6.0f * a; // = x / 2
	const float h = sqrt(6.0f) / 3.0f * a;

	vector<Vector3> points = {{0.0f, x, 0.0f},
	                          {-0.5f * a, -d, 0.0f},
	                          {+0.5f * a, -d, 0.0f},
	                          {0.0f, 0.0f, h}};

	Vector3 center = Vector3(0.0f);

	for (int i = 0; i < 4; i++)
	{
		center += points[i];
	}
	center /= 4.0f;

	for (int i = 0; i < 4; i++)
	{
		points[i] -= center;
	}

	MeshData meshData;

	for (int i = 0; i < points.size(); i++)
	{

		Vertex v;
		v.position = points[i];
		v.normal = v.position; // 중심이 원점
		v.normal.Normalize();

		meshData.vertices.push_back(v);
	}

	meshData.indices = {0, 1, 2, 3, 2, 1, 0, 3, 1, 0, 2, 3};

	return meshData;
}
MeshData GeometryGenerator::SubdivideToSphere(const float radius,
                                              MeshData meshData)
{

	using namespace DirectX;
	using DirectX::SimpleMath::Matrix;
	using DirectX::SimpleMath::Vector3;

	return MeshData();
}
} // namespace hlab