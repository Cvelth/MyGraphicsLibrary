#include "OpenGL_header.h"
#include "AbstractLoopWindow.hpp"

int mgl::AbstractLoopWindow::loop() {
	initializeEventHandling();
	initializeRender();

	int width, height;
	glfwGetFramebufferSize(window(), &width, &height);
	resize(width, height);

	while (!glfwWindowShouldClose(window())) {
		render();

		glfwSwapBuffers(window());
		glfwWaitEvents();
	}
	cleanRender();
	return 0;
}
