#include "OpenGL_Mirror\OpenGL_Dependency\OpenGL.h"
#include "AbstractWindow.hpp"
#include "OpenGL_Mirror\FunctionsMirror\FunctionsMirror.hpp"
#include "OpenGL_Mirror\BasicTypes\Color.hpp"
#include "OpenGL_Mirror\ShaderProgramMirror\DefaultProgram.hpp"
#include "Math\Matrix.hpp"
#include "Events\EventsSystem.hpp"

namespace mgl {
	class DefaultEventHandler : public EmptyEventHandler {
	protected:
		AbstractWindow* m_window;
	public:
		DefaultEventHandler(AbstractWindow* w) : m_window(w) {}

		virtual void resizeEvent(GLFWwindow* w, int x, int y) override;
	};
}

mgl::AbstractWindow::AbstractWindow() : m_projection(new mgl::math::Matrix()) {}

mgl::AbstractWindow::AbstractWindow(std::string title, int width, int height, DefaultWindowMode mode) : AbstractWindow() {
	initialize(title, width, height, mode);
}

mgl::AbstractWindow::~AbstractWindow() {
	clean();
}

void mgl::AbstractWindow::initialize(std::string title, int width, int height, DefaultWindowMode mode) {
	if (!glfwInit())
		throw Exceptions::WindowInitializationException(std::string("GLFW inititalization error."));

	if (mode == DefaultWindowMode::Fullscreen)
		m_window = glfwCreateWindow(width, height, title.c_str(), glfwGetPrimaryMonitor(), NULL);
	else
		m_window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

	if (!m_window)
		throw Exceptions::WindowInitializationException(std::string("Window inititalization error."));

	resize(width, height);

	glfwMakeContextCurrent(m_window);
	glfwSwapInterval(0);

	glewExperimental = GL_TRUE;
	GLenum glewError = glewInit();
	if (glewError != GLEW_OK)
		throw Exceptions::WindowInitializationException(std::string("GLEW inititalization error: ")
														+= (const char*) (glewGetErrorString(glewError)));

	//TEMPORARY!!!
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
}

void mgl::AbstractWindow::clean() {
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

void mgl::AbstractWindow::resize() {
	auto size = getSize();
	resize(size[0], size[1]);
}

void mgl::AbstractWindow::resize(int width, int height) {
	m_aspectRatio = float(width) / height;
	mgl::setViewport(0, 0, width, height);

	if (m_projection) delete m_projection;
	m_projection = new mgl::math::Matrix(mgl::math::Matrix::orthographicMatrix(
		m_aspectRatio > 1.f ? -m_aspectRatio : -1.f,
		m_aspectRatio > 1.f ? m_aspectRatio : 1.f,
		-1.f / (m_aspectRatio > 1.f ? 1.f : m_aspectRatio),
		+1.f / (m_aspectRatio > 1.f ? 1.f : m_aspectRatio),
		+1.f, -1.f
	));
}

void mgl::AbstractWindow::setOpenGLVersion(int major, int minor) {
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
}

mgl::Program* mgl::AbstractWindow::linkDefaultProgram(DefaulProgramType type) {
	return new DefaultProgram(type);
}

mgl::Program* mgl::AbstractWindow::linkProgramWithDefaultFragmentShader(Shader * vertex_shader) {
	return new DefaultProgram(vertex_shader);
}

void mgl::AbstractWindow::update() {
	glfwSwapBuffers(m_window);
}

void mgl::AbstractWindow::pollEvents() {
	glfwPollEvents();
}

void mgl::AbstractWindow::clearWindow() {
	mgl::clearColorBuffer();
}

void mgl::AbstractWindow::setClearColor(const mgl::Color & color) {
	mgl::setClearColor(color);
}

void mgl::AbstractWindow::setClearColor(const float r, const float g, const float b, const float a) {
	mgl::setClearColor(mgl::Color(r, g, b, a));
}

int mgl::AbstractWindow::getWidth() {
	int ret;
	glfwGetFramebufferSize(m_window, &ret, nullptr);
	return ret;
}

int mgl::AbstractWindow::getHeight() {
	int ret;
	glfwGetFramebufferSize(m_window, nullptr, &ret);
	return ret;
}

int* mgl::AbstractWindow::getSize() {
	int ret[2];
	glfwGetFramebufferSize(m_window, &ret[0], &ret[1]);
	return ret;
}

void mgl::AbstractWindow::changleEventHandler(AbstractEventHandler * h) {
	EventsSystem::setHandler(h);
}

bool mgl::AbstractWindow::isWindowClosed() {
	return glfwWindowShouldClose(m_window);
}

void mgl::AbstractWindow::initializeEventHandling() {
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