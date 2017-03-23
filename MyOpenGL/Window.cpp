#include "OpenGL_header.h"
#include "Functions.hpp"
#include "Window.hpp"
#include "DefaultProgram.hpp"
#include "Matrix.hpp"

mgl::Window::Window() : projection(new Matrix()) { }

mgl::Window::Window(std::string title, int width, int height, DefaultWindowMode mode) : Window() {

	if (!glfwInit())
		throw InitializationException(std::string("GLFW inititalization error."));

	if (mode == DefaultWindowMode::Fullscreen)
		m_window = glfwCreateWindow(width, height, title.c_str(), glfwGetPrimaryMonitor(), NULL);
	else
		m_window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

	glfwMakeContextCurrent(m_window);
	glfwSwapInterval(1);

	glewExperimental = GL_TRUE;
	GLenum glewError = glewInit();
	if (glewError != GLEW_OK)
		throw InitializationException(std::string("GLEW inititalization error: ")
									  += (const char*) (glewGetErrorString(glewError)));

	setOpenGLVersion(3, 3);
}

mgl::Window::~Window() {
	for (auto it : m_events)
		delete it;
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

void mgl::Window::resize() {
	int width, height;
	glfwGetFramebufferSize(m_window, &width, &height);

	aspectRatio = float(width) / height;
	mgl::viewport(0, 0, width, height);

	delete projection;
	projection = new mgl::Matrix(mgl::Matrix::orthographicMatrix(
		aspectRatio > 1.f ? -aspectRatio : -1.f, 
		aspectRatio > 1.f ? aspectRatio : 1.f,
		-1.f / (aspectRatio > 1.f ? 1.f : aspectRatio),
		+1.f / (aspectRatio > 1.f ? 1.f : aspectRatio),
		+1.f, -1.f
	));
}

void mgl::Window::addEventsHandler(AbstractEventHandler * h) {
	m_events.insert(h);
}

void mgl::Window::removeEventsHandler(AbstractEventHandler * h) {
	m_events.erase(h);
}

void mgl::Window::removeAllEventsHandlers() {
	m_events.clear();
}

void mgl::Window::setOpenGLVersion(int major, int minor) {
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
}

mgl::Program* mgl::Window::linkDefaultProgram(DefaulProgramType type) {
	return new DefaultProgram(type);
}

int mgl::Window::loop() {
	resize();
	init();

	while (!glfwWindowShouldClose(m_window)) {
		render();

		glfwSwapBuffers(m_window);
		glfwWaitEvents();
	}
	return 0;
}

void mgl::Window::setErrorHandler(void(*handler)(int, const char *)) {
	glfwSetErrorCallback(handler);
}

void mgl::Window::setWindowCloseHandler(void(*handler)(GLFWwindow*)) {
	glfwSetWindowCloseCallback(m_window, handler);
}