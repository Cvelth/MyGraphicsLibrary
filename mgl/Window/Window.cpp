#include "mgl/dependencies/OpenGL_Dependency/opengl_dependency.hpp"
#include "mgl/dependencies/WindowLibrary_Dependency/window_dependency.hpp"
#include "Window.hpp"
#include <string>
mgl::AbstractWindow::AbstractWindow(char const* title, int width, int height, bool is_fullscreen) {
	if (!glfwInit())
		throw Exceptions::WindowCreationError();

	m_window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (!m_window) {
		glfwTerminate();
		throw Exceptions::WindowCreationError();
	}
	if (is_fullscreen) {
		auto monitor = glfwGetPrimaryMonitor();
		glfwSetWindowMonitor(m_window, monitor, 0, 0, width, height, glfwGetVideoMode(monitor)->refreshRate);
	}

	glfwMakeContextCurrent(m_window);
	glfwSwapInterval(0);

	auto error = glewInit();
	if (error != GLEW_OK) {
		glfwDestroyWindow(m_window);
		glfwTerminate();
		throw Exceptions::WindowCreationError((std::string("GLEW initialization error: ") +
											  (char const*) (glewGetErrorString(error))).c_str());
	}
}
mgl::AbstractWindow::~AbstractWindow() {
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

void mgl::AbstractWindow::update() {
	glfwSwapBuffers(m_window);
}
void mgl::AbstractWindow::pollEvents() const {
	glfwPollEvents();
}
void mgl::AbstractWindow::waitEvents() const {
	glfwWaitEvents();
}
void mgl::AbstractWindow::clearWindow() {
	glClear(GL_COLOR_BUFFER_BIT);
}
void mgl::AbstractWindow::setClearColor(mgl::Color const& color) {
	//to be implemented.
}
void mgl::AbstractWindow::setClearColor(const float r, const float g, const float b, const float a) {
	glClearColor(r, g, b, a);
}

int mgl::AbstractWindow::width() const {
	int ret;
	glfwGetFramebufferSize(m_window, &ret, nullptr);
	return ret;
}
int mgl::AbstractWindow::height() const {
	int ret;
	glfwGetFramebufferSize(m_window, nullptr, &ret);
	return ret;
}
std::pair<int, int> mgl::AbstractWindow::size() const {
	std::pair<int, int> ret;
	glfwGetFramebufferSize(m_window, &ret.first, &ret.second);
	return ret;
}
bool mgl::AbstractWindow::should_close() const {
	return glfwWindowShouldClose(m_window);
}