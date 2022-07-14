#include "math.h"

// prevent cross-border
float clamp(float f, float min, float max)
{
	return f < min ? min : (f > max ? max : f);
}

float saturate(float f)
{
	return f < 0 ? 0 : (f > 1 ? 1 : f);
}


// normalized
Vector3f viewport_transform(int width, int height, Vector3f ndc_coord)
{
	float x = (ndc_coord.x + 1) * 0.5f * (float)width;   /* [-1, 1] -> [0, w] */
	float y = (ndc_coord.y + 1) * 0.5f * (float)height;  /* [-1, 1] -> [0, h] */
	float z = (ndc_coord.z + 1) * 0.5f;                  /* [-1, 1] -> [0, 1] */
	return Vector3f(x, y, z);
}


// translate matrix
Matrix4f translate(float tx, float ty, float tz)
{
	Matrix4f m = Matrix4f::identity();
	m[0][3] = tx;
	m[1][3] = ty;
	m[2][3] = tz;
	return m;
}

// scale matrix
Matrix4f scale(float sx, float sy, float sz)
{
	Matrix4f m = Matrix4f::identity();
	assert(sx != 0 && sy != 0 && sz != 0);
	m[0][0] = sx;
	m[1][1] = sy;
	m[2][2] = sz;
	return m;
}

// rotate matrix
Matrix4f rotate(float angle, float vx, float vy, float vz)
{
	Vector3f n = Vector3f(vx, vy, vz).normalize();
	float c = (float)cos(angle);
	float s = (float)sin(angle);
	Matrix4f m = Matrix4f::identity();

	m[0][0] = n.x * n.x * (1 - c) + c;
	m[0][1] = n.y * n.x * (1 - c) - s * n.z;
	m[0][2] = n.z * n.x * (1 - c) + s * n.y;

	m[1][0] = n.x * n.y * (1 - c) + s * n.z;
	m[1][1] = n.y * n.y * (1 - c) + c;
	m[1][2] = n.z * n.y * (1 - c) - s * n.x;

	m[2][0] = n.x * n.z * (1 - c) - s * n.y;
	m[2][1] = n.y * n.z * (1 - c) + s * n.x;
	m[2][2] = n.z * n.z * (1 - c) + c;

	return m;
}

Matrix4f rotate_x(float angle)
{
	float c = (float)cos(angle);
	float s = (float)sin(angle);
	Matrix4f m = Matrix4f::identity();
	m[1][1] = c;
	m[1][2] = -s;
	m[2][1] = s;
	m[2][2] = c;
	return m;
}

Matrix4f rotate_y(float angle)
{
	float c = (float)cos(angle);
	float s = (float)sin(angle);
	Matrix4f m = Matrix4f::identity();
	m[0][0] = c;
	m[0][2] = s;
	m[2][0] = -s;
	m[2][2] = c;
	return m;
}

Matrix4f rotate_z(float angle)
{
	float c = (float)cos(angle);
	float s = (float)sin(angle);
	Matrix4f m = Matrix4f::identity();
	m[0][0] = c;
	m[0][1] = -s;
	m[1][0] = s;
	m[1][1] = c;
	return m;
}


Matrix4f lookat(Vector3f eye, Vector3f target, Vector3f up)
{
	Vector3f z_axis = (eye - target).normalize();
	Vector3f x_axis = cross(up, z_axis).normalize();
	Vector3f y_axis = cross(z_axis, x_axis);
	Matrix4f m = Matrix4f::identity();

	m[0] = embed<4>(x_axis, 0.f);
	m[1] = embed<4>(y_axis, 0.f);
	m[2] = embed<4>(z_axis, 0.f);

	m[0][3] = -(x_axis * eye);
	m[1][3] = -(y_axis * eye);
	m[2][3] = -(z_axis * eye);

	return m;
}

// orthographic projection
Matrix4f orthographic(float right, float top, float near, float far)
{
	float z_range = far - near;
	Matrix4f m = Matrix4f::identity();
	assert(right > 0 && top > 0 && z_range > 0);
	m[0][0] = 1 / right;
	m[1][1] = 1 / top;
	m[2][2] = -2 / z_range;
	m[2][3] = -(near + far) / z_range;
	return m;
}

// perspective projection
Matrix4f perspective(float fovy, float aspect, float near, float far)
{
	float z_range = far - near;
	Matrix4f m = Matrix4f::identity();
	assert(fovy > 0 && aspect > 0);
	assert(near > 0 && far > 0 && z_range > 0);
	m[1][1] = 1 / (float)tan(fovy / 2);
	m[0][0] = m[1][1] / aspect;
	m[2][2] = -(near + far) / z_range;
	m[2][3] = -2 * near * far / z_range;
	m[3][2] = -1;
	m[3][3] = 0;
	return m;
}