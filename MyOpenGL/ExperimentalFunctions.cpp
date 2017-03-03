#include "OpenGL_header.h"
#include "Functions.hpp"
#include "ExperimentalFunctions.hpp"

void mgl::enableSmooth(SmoothMode mode) {
	enableLineSmooth(mode);
	enablePointSmooth(mode);
	enablePolygonSmooth(mode);
}

void mgl::enableAlpha() {
	enableBlend(BlendEnum::Alpha_SRC, BlendEnum::Alpha_OneMinusSRC);
}

void mgl::enableVertexAttribArray(size_t id) {
	glEnableVertexAttribArray(id);
}

void mgl::enableEveryVertexAttribArray(size_t id_b, size_t id_e) {
	for (size_t i = id_b; i < id_e; i++)
		enableVertexAttribArray(i);
}
