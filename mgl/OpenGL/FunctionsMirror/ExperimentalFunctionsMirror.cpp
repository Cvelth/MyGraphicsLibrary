#include "../MyGraphicsLibrary/MGL/OpenGL/OpenGL_Dependency/OpenGL.h"
#include "FunctionsMirror.hpp"
#include "ExperimentalFunctionsMirror.hpp"

void mgl::enableSmooth(SmoothMode mode) {
	enableLineSmooth(mode);
	enablePointSmooth(mode);
	enablePolygonSmooth(mode);
}

void mgl::enableAlpha() {
	enableBlend(BlendEnum::Alpha_SRC, BlendEnum::Alpha_OneMinusSRC);
}

void mgl::getWindowSize(GLFWwindow *window, int *width, int *height) {
	glfwGetFramebufferSize(window, width, height);
}
