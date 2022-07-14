#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "math.h"
#include "renderbuffer.h"
#include "model.h"
#include "shader.h"

struct DrawData {
	Model* model;
	IShader* shader;
	RenderBuffer* render_buffer;
};

void graphics_draw_triangle(DrawData* app_data);
#endif
