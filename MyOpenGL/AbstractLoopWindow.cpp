#include "OpenGL_header.h"
#include "AbstractLoopWindow.hpp"

int mgl::AbstractLoopWindow::loop() {
	initializeEventHandling();
	initializeRenderProcess();

	int width, height;
	glfwGetFramebufferSize(window(), &width, &height);
	resize(width, height);

	while (!glfwWindowShouldClose(window())) {
		renderProcess();

		glfwSwapBuffers(window());
		glfwWaitEvents();
	}
	clearRenderProcess();
	return 0;
}
