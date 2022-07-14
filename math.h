#pragma once

#include "vector.h"
#include "matrix.h"

#define EPSILON 1e-5f
#define PI 3.1415927f

#define TO_RADIANS(degrees) ((PI / 180) * (degrees))
#define TO_DEGREES(radians) ((180 / PI) * (radians))

float clamp(float f, float min, float max);
float saturate(float f);

Vector3f viewport_transform(int width, int height, Vector3f ndc_coord);

// transformation matrices
Matrix4f translate(float tx, float ty, float tz);
Matrix4f scale(float sx, float sy, float sz);
Matrix4f rotate(float angle, float vx, float vy, float vz);
Matrix4f rotate_x(float angle);
Matrix4f rotate_y(float angle);
Matrix4f rotate_z(float angle);
Matrix4f lookat(Vector3f eye, Vector3f target, Vector3f up);
Matrix4f orthographic(float right, float top, float near, float far);
Matrix4f perspective(float fovy, float aspect, float near, float far);