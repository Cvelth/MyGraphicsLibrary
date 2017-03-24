#include "OpenGL_header.h"
#include "Window.hpp"
#include "Functions.hpp"
#include "DefaultProgram.hpp"
#include "Matrix.hpp"
#include "EventsSystem.hpp"

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
}

mgl::Window::~Window() {
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

void mgl::Window::resize(int width, int height) {
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

void mgl::Window::setOpenGLVersion(int major, int minor) {
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
}

mgl::Program* mgl::Window::linkDefaultProgram(DefaulProgramType type) {
	return new DefaultProgram(type);
}

int mgl::Window::loop() {
	initializeEventHandling();
	init();

	int width, height;
	glfwGetFramebufferSize(m_window, &width, &height);
	resize(width, height);

	while (!glfwWindowShouldClose(m_window)) {
		render();

		glfwSwapBuffers(m_window);
		glfwWaitEvents();
	}
	return 0;
}

void mgl::Window::update() {
	render();
	glfwSwapBuffers(m_window);
}

void mgl::Window::changleEventHandler(AbstractEventHandler * h) {
	EventsSystem::setHandler(h);
}

void mgl::Window::initializeEventHandling() {
	EventsSystem::setHandler(new DefaultEventHandler(this));
	glfwSetKeyCallback(m_window, EventsSystem::keyEvent);
	glfwSetMouseButtonCallback(m_window, EventsSystem::mouseButtonEvent);
	glfwSetCharCallback(m_window, EventsSystem::characterEvent);
	glfwSetCharModsCallback(m_window, EventsSystem::characterEventWithModificators);
	glfwSetCursorEnterCallback(m_window, EventsSystem::mouseEnterEvent);
	glfwSetCursorPosCallback(m_window, EventsSystem::mouseMoveEvent);
	glfwSetDropCallback(m_window, EventsSystem::fileDropEvent);
	glfwSetScrollCallback(m_window, EventsSystem::scrollEvent);
	glfwSetFramebufferSizeCallback(m_window, EventsSystem::resizeEvent);
	glfwSetJoystickCallback(EventsSystem::joystickEvent);
	glfwSetErrorCallback(EventsSystem::errorEvent);
}

void mgl::DefaultEventHandler::resizeEvent(GLFWwindow * w, int x, int y) {
	m_window->resize(x, y);
	m_window->update();
}