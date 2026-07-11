#pragma once

#include <glm/glm.hpp>
#include <iostream>
#include <vector>

namespace hlab {

	using namespace glm;
	using namespace std;

	struct MyVertex
	{
		vec3 pos;
		vec3 color;
	};

	struct MyTriangle
	{
		MyVertex v0, v1, v2;
	};

	struct MyCircle
	{
		std::vector<MyTriangle> triangles;
	};

	class Rasterization
	{
	public:
		Rasterization(const int& width, const int& height);

		vec2 ProjectWorldToRaster(vec3 point);
		float EdgeFunction(const vec2& v0, const vec2& v1, const vec2& point);
		void SetTriangleCount(int newCount);
		void DrawTriangleCount(vector<vec4>& pixels);
		void Render(vector<vec4>& pixels);
		void Update();

	public:
		MyCircle circle;

		int width;
		int height;

		int triangleNums;
		int New_triangleNums;

		float radius;

	};
} // namespace hlab
