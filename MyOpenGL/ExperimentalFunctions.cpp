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