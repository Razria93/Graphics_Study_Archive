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

	// 참고: OpenGL Sphere
	// http://www.songho.ca/opengl/gl_sphere.html
	// Texture 좌표계때문에 (numSlices + 1) 개의 버텍스 사용 (마지막에 닫아주는
	// 버텍스가 중복) Stack은 y 위쪽 방향으로 쌓아가는 방식

	const float dTheta = -XM_2PI / float(numSlices);
	const float dPhi = -XM_PI / float(numStacks);

	MeshData meshData;

	vector<Vertex> &vertices = meshData.vertices;

	for (int j = 0; j <= numStacks; j++)
	{

		// 스택에 쌓일 수록 시작점을 x-y 평면에서 회전 시켜서 위로 올리는 구조
		Vector3 stackStartPoint = Vector3::Transform(
		    Vector3(0.0f, -radius, 0.0f), Matrix::CreateRotationZ(dPhi * j));

		for (int i = 0; i <= numSlices; i++)
		{
			Vertex v;

			// 시작점을 x-z 평면에서 회전시키면서 원을 만드는 구조
			v.position = Vector3::Transform(
			    stackStartPoint, Matrix::CreateRotationY(dTheta * float(i)));

			v.normal = v.position; // 원점이 구의 중심
			v.normal.Normalize();
			v.texcoord =
			    Vector2(float(i) / numSlices, 1.0f - float(j) / numStacks);

			vertices.push_back(v);
		}
	}

	// cout << vertices.size() << endl;

	vector<uint16_t> &indices = meshData.indices;

	for (int j = 0; j < numStacks; j++)
	{

		const int offset = (numSlices + 1) * j;

		for (int i = 0; i < numSlices; i++)
		{

			indices.push_back(offset + i);
			indices.push_back(offset + i + numSlices + 1);
			indices.push_back(offset + i + 1 + numSlices + 1);

			indices.push_back(offset + i);
			indices.push_back(offset + i + 1 + numSlices + 1);
			indices.push_back(offset + i + 1);
		}
	}

	// cout << indices.size() << endl;
	// for (int i = 0; i < indices.size(); i++) {
	//     cout << indices[i] << " ";
	// }
	// cout << endl;

	return meshData;
}

MeshData GeometryGenerator::MakeIcosahedron()
{

	// Luna DX12 교재 참고
	// 등20면체
	// https://mathworld.wolfram.com/Isohedron.html

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

MeshData GeometryGenerator::SubdivideToSphere(const float radius, MeshData meshData)
{

	using namespace DirectX;
	using DirectX::SimpleMath::Matrix;
	using DirectX::SimpleMath::Vector3;


	// 구의 중심이 원점이라고 가정
	// 구의 표면으로 옮기고 노멀과 texture 좌표 계산
	auto ProjectVertex = [&](Vertex &v)
	{
		v.normal = v.position;
		v.normal.Normalize();
		v.position = v.normal * radius;

		// 주의: 텍스춰가 이음매에서 깨집니다.
		// atan vs atan2
		// https://stackoverflow.com/questions/283406/what-is-the-difference-between-atan-and-atan2-in-c
		float theta = atan2f(v.position.z, v.position.x);
		if (theta < 0.0f)
			theta += XM_2PI; // [0, 2π]

		float phi = acosf(v.position.y / radius);
		if (phi < 0.0f)
			phi += XM_2PI; // [0, 2π]
		
		v.texcoord.x = theta / XM_2PI;
		v.texcoord.y = phi / XM_PI;
	};


	auto CalculateTextCoord = [](Vertex &v0, Vertex &v1, Vertex &others)
	{
		Vector2 returnTextCoord;

		// Calculate U
		float x0 = v1.texcoord.x - v0.texcoord.x;

		if (x0 > 0.5f)
		{
			if (others.texcoord.x > 0.5f)
			{
				returnTextCoord.x = (1.0f + v1.texcoord.x) / 2;
			}
			else
			{
				returnTextCoord.x = (v0.texcoord.x + 0.0f) / 2;
			}
		}

		if (x0 < -0.5f)
		{
			if (others.texcoord.x < 0.5f)
			{
				returnTextCoord.x = (0.0f + v1.texcoord.x) / 2;
			}
			else
			{
				returnTextCoord.x = (v0.texcoord.x + 1.0f) / 2;
			}
		}

		returnTextCoord.x = (v0.texcoord.x + v1.texcoord.x) / 2;

		// Calculate V

		float y0 = v1.texcoord.y - v0.texcoord.y;

		if (y0 > 0.5f)
		{
			if (others.texcoord.y > 0.5f)
			{
				returnTextCoord.y = (1.0f + v1.texcoord.y) / 2;
			}
			else
			{
				returnTextCoord.y = (v0.texcoord.y + 0.0f) / 2;
			}
		}

		if (y0 < -0.5f)
		{
			if (others.texcoord.y < 0.5f)
			{
				returnTextCoord.y = (0.0f + v1.texcoord.y) / 2;
			}
			else
			{
				returnTextCoord.y = (v0.texcoord.y + 1.0f) / 2;
			}
		}

		returnTextCoord.y = (v0.texcoord.y + v1.texcoord.y) / 2;

		return returnTextCoord;
	};


	auto UpdateFaceNormal = [](Vertex &v0, Vertex &v1, Vertex &v2)
	{
		auto faceNormal =
		    (v1.position - v0.position).Cross(v2.position - v0.position);
		faceNormal.Normalize();
		v0.normal = faceNormal;
		v1.normal = faceNormal;
		v2.normal = faceNormal;
	};


	auto CheckAndPushBack = [&](MeshData &meshData, Vertex &v0, Vertex &v1, Vertex &v2)
	{
		// Calculate U
		float x1 = abs(v1.texcoord.x - v0.texcoord.x);
		float x2 = abs(v2.texcoord.x - v0.texcoord.x);

		// 문제 없음
		if (x1 <= 0.5f && x2 <= 0.5f)
		{
			meshData.vertices.push_back(v0);
			meshData.vertices.push_back(v1);
			meshData.vertices.push_back(v2);
		}

		// 문제 있음 [x1, x2 둘중에 하나 이상이 0.5f 이상일 경우]
		else 
		{
			Vertex newVertex;

			// 비교결과값 둘 다 문제 있음 -> 비교값인 v0 스스로가 문제 있는 것
			if (x1 > 0.5f && x2 > 0.5f)
			{
				// v0가 문제인 경우, v1과 v2의 texcoord.x 값은 유사함. 따라서 한쪽을 기준으로 비교.
				float newTextCoord = v1.texcoord.x > 0.5f ? 1.0f : 0.0f;

				newVertex.position = v0.position;
				newVertex.normal = v0.normal;
				newVertex.texcoord = Vector2(newTextCoord, v0.texcoord.y);

				// std::cout << "v0.texcoord.x : " << v0.texcoord.x << std::endl;
				// std::cout << "v1.texcoord.x : " << v1.texcoord.x << std::endl;
				// std::cout << "v2.texcoord.x : " << v2.texcoord.x << std::endl;
				// std::cout << "newTextCoord.x : " << newTextCoord << std::endl
				//           << std::endl;

				meshData.vertices.push_back(newVertex);
				meshData.vertices.push_back(v1);
				meshData.vertices.push_back(v2);
			}

			// 비교결과값 중 하나만 문제 있음 -> 비교군인 v1이나 v2가 문제 있는 것
			else
			{
				// v1이 문제있는 경우
				if (x1 > 0.5f)
				{
					// v1가 문제인 경우, v0과 v2의 texcoord.x 값은 유사함. 따라서 v2를 기준으로 비교.
					float newTextCoord = v2.texcoord.x > 0.5f ? 1.0f : 0.0f;

					newVertex.position = v1.position;
					newVertex.normal = v1.normal;
					newVertex.texcoord = Vector2(newTextCoord, v1.texcoord.y);

					meshData.vertices.push_back(v0);
					meshData.vertices.push_back(newVertex);
					meshData.vertices.push_back(v2);
				}

				// v2가 문제있는 경우
				if (x2 > 0.5f)
				{
					// v2가 문제인 경우, v0과 v1의 texcoord.x 값은 유사함. 따라서 v1를 기준으로 비교.
					float newTextCoord = v1.texcoord.x > 0.5f ? 1.0f : 0.0f;

					newVertex.position = v2.position;
					newVertex.normal = v2.normal;
					newVertex.texcoord = Vector2(newTextCoord, v2.texcoord.y);

					meshData.vertices.push_back(v0);
					meshData.vertices.push_back(v1);
					meshData.vertices.push_back(newVertex);
				}
			}
		}

		int offset = meshData.indices.size();

		meshData.indices.push_back(offset + 0);
		meshData.indices.push_back(offset + 1);
		meshData.indices.push_back(offset + 2);

		return;
	};

	// Main
	// 버텍스가 중복되는 구조로 구현
	MeshData newMesh;
	uint16_t count = 0;
	for (size_t i = 0; i < meshData.indices.size(); i += 3)
	{
		size_t i0 = meshData.indices[i];
		size_t i1 = meshData.indices[i + 1];
		size_t i2 = meshData.indices[i + 2];

		Vertex v0 = meshData.vertices[i0];
		Vertex v1 = meshData.vertices[i1];
		Vertex v2 = meshData.vertices[i2];

		ProjectVertex(v0);
		ProjectVertex(v1);
		ProjectVertex(v2);

		Vertex v3;
		v3.position = (v0.position + v1.position) * 0.5f;
		v3.texcoord = (v0.texcoord + v1.texcoord) * 0.5f;
		ProjectVertex(v3);

		Vertex v4;
		v4.position = (v1.position + v2.position) * 0.5f;
		v4.texcoord = (v1.texcoord + v2.texcoord) * 0.5f;
		ProjectVertex(v4);

		Vertex v5;
		v5.position = (v2.position + v0.position) * 0.5f;
		v5.texcoord = (v2.texcoord + v0.texcoord) * 0.5f;
		ProjectVertex(v5);

		std::cout << "v0.texcoord.x : " << v0.texcoord.x << std::endl;
		std::cout << "v1.texcoord.x : " << v1.texcoord.x << std::endl;
		std::cout << "v2.texcoord.x : " << v2.texcoord.x << std::endl;
		std::cout << "v3.texcoord.x : " << v3.texcoord.x << std::endl;
		std::cout << "v4.texcoord.x : " << v4.texcoord.x << std::endl;
		std::cout << "v5.texcoord.x : " << v5.texcoord.x << std::endl << std::endl;

		// UpdateFaceNormal(v0, v3, v5);
		// UpdateFaceNormal(v3, v1, v4);
		// UpdateFaceNormal(v5, v4, v2);
		// UpdateFaceNormal(v3, v4, v5);

		CheckAndPushBack(newMesh, v0, v3, v5);
		CheckAndPushBack(newMesh, v3, v1, v4);
		CheckAndPushBack(newMesh, v5, v4, v2);
		CheckAndPushBack(newMesh, v3, v4, v5);
	}

	return newMesh;
}

MeshData GeometryGenerator::ProjectVertex(const float radius, MeshData meshData)
{

	using namespace DirectX;
	using DirectX::SimpleMath::Matrix;
	using DirectX::SimpleMath::Vector3;

	// 구의 중심이 원점이라고 가정

	// 구의 표면으로 옮기고 노멀과 texture 좌표 계산
	auto ProjectVertex = [&](Vertex &v)
	{
		v.normal = v.position;
		v.normal.Normalize();
		v.position = v.normal * radius;

		// 주의: 텍스춰가 이음매에서 깨집니다.
		// atan vs atan2
		// https://stackoverflow.com/questions/283406/what-is-the-difference-between-atan-and-atan2-in-c
		float theta = atan2f(v.position.z, v.position.x);
		if (theta < 0.0f)
			theta += XM_2PI; // [0, 2π]

		float phi = acosf(v.position.y / radius);
		if (phi < 0.0f)
			phi += XM_2PI; // [0, 2π]

		v.texcoord.x = theta / XM_2PI;
		v.texcoord.y = phi / XM_PI;

		std::cout << "v.position.x : " << v.position.x << " / v.position.y : " << v.position.y << std::endl;
		std::cout << "theta : " << theta << " / v.texcoord.x : " << v.texcoord.x << std::endl;
		std::cout << "phi : " << theta << " / v.texcoord.y : " << v.texcoord.y << std::endl
		          << std::endl;
	};

	// 버텍스가 중복되는 구조로 구현
	MeshData newMesh;
	uint16_t count = 0;
	for (size_t i = 0; i < meshData.indices.size(); i += 3)
	{
		size_t i0 = meshData.indices[i];
		size_t i1 = meshData.indices[i + 1];
		size_t i2 = meshData.indices[i + 2];

		Vertex v0 = meshData.vertices[i0];
		Vertex v1 = meshData.vertices[i1];
		Vertex v2 = meshData.vertices[i2];

		ProjectVertex(v0);
		ProjectVertex(v1);
		ProjectVertex(v2);

		newMesh.vertices.push_back(v0);
		newMesh.vertices.push_back(v1);
		newMesh.vertices.push_back(v2);

		for (uint16_t j = 0; j < 3; j++)
		{
			newMesh.indices.push_back(j + count);
		}
		count += 3;
	}

	return newMesh;
}
} // namespace hlab