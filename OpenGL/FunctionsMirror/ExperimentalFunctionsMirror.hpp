#pragma once

namespace mgl {
	void enableSmooth(SmoothMode mode);
	void enableAlpha();

	void getWindowSize(GLFWwindow *window, int *width, int *height);
}