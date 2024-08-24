#pragma once
int screenWidth = 1366;
int screenHeight = 768;

struct view_matrix_t
{
	float* operator[ ](int index)
	{
		return matrix[index];
	}

	float matrix[4][4];
};

struct w2s_Vec3
{
	constexpr w2s_Vec3(
		const float x = 0.f, 
		const float y = 0.f, 
		const float z = 0.f
	) noexcept : x(x), y(y), z(z) {}

	constexpr const w2s_Vec3& operator-(const w2s_Vec3& other) const noexcept
	{
		return w2s_Vec3{ x - other.x, y - other.y, z - other.z };
	}

	constexpr const w2s_Vec3& operator+(const w2s_Vec3& other) const noexcept
	{
		return w2s_Vec3{ x + other.x, y + other.y, z + other.z };
	}

	constexpr const w2s_Vec3& operator/(const float factor) const noexcept
	{
		return w2s_Vec3{ x / factor, y / factor, z / factor };
	}

	constexpr const w2s_Vec3& operator*(const float factor) const noexcept
	{
		return w2s_Vec3{ x * factor, y * factor, z * factor };
	}

	w2s_Vec3 WorldToScreen(view_matrix_t matrix) const
	{
		float _x = matrix[0][0] * x + matrix[0][1] * y + matrix[0][2] * z + matrix[0][3];
		float _y = matrix[1][0] * x + matrix[1][1] * y + matrix[1][2] * z + matrix[1][3];
		float w = matrix[3][0] * x + matrix[3][1] * y + matrix[3][2] * z + matrix[3][3];

		if (w < 0.01f)
			return false;

		float inv_w = 1.f / w;
		_x *= inv_w;
		_y *= inv_w;

		float x = screenWidth * 0.5f;
		float y = screenHeight * 0.5f;

		x += 0.5f * _x * screenWidth + 0.5f;
		y -= 0.5f * _y * screenWidth + 0.5f;

		return { x, y, w };
	}

	float x, y, z;

};


struct w2s_Vec2
{
	float x, y;
};

//float _x = matrix[0][0] * x + matrix[0][1] * y + matrix[0][2] * z + matrix[0][3];
//float _y = matrix[1][0] * x + matrix[1][1] * y + matrix[1][2] * z + matrix[1][3];
//float w = matrix[3][0] * x + matrix[3][1] * y + matrix[3][2] * z + matrix[3][3];
//
//if (w < 0.01f)
//	return false;

//bool WorldToScreen(const Vector3& world, Vector2& screen, float m[16])
//{
//    Vector4 clipCoords;
//    clipCoords.x = world.x * m[0] + world.y * m[1] + world.z * m[2] + m[3];
//    clipCoords.y = world.x * m[4] + world.y * m[5] + world.z * m[6] + m[7];
//    clipCoords.z = world.x * m[8] + world.y * m[9] + world.z * m[10] + m[11];
//    clipCoords.w = world.x * m[12] + world.y * m[13] + world.z * m[14] + m[15];
//
//    if (clipCoords.w < 0.1f) return false;
//
//    Vector3 ndc;
//    ndc.x = clipCoords.x / clipCoords.w;
//    ndc.y = clipCoords.y / clipCoords.w;
//   // ndc.z = clipCoords.z / clipCoords.w;
//
//    screen.x = (screenWidth / 2 * ndc.x) + (ndc.x + screenWidth / 2);
//    screen.y = (screenHeight / 2 * ndc.y) + (ndc.y + screenHeight / 2);
//
//    return true;
//}