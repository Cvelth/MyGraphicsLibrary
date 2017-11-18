#pragma once

struct GLFWwindow;
namespace mgl {
	enum class SmoothMode;

	void enableSmooth(SmoothMode mode);
	void enableAlpha();

	void getWindowSize(GLFWwindow *window, int *width, int *height);
}