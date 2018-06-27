#include "../MyGraphicsLibrary/MGL/OpenGL/OpenGL_Dependency/OpenGL.h"
#include "AbstractWindow.hpp"
#include "../MyGraphicsLibrary/MGL/OpenGL/FunctionsMirror/FunctionsMirror.hpp"
#include "../MyGraphicsLibrary/MGL/SharedHeaders/Color.hpp"
#include "../MyGraphicsLibrary/MGL/OpenGL/ClassesMirror/ShaderProgram.hpp"
#include "../MyGraphicsLibrary/MGL/Math/Matrix.hpp"
#include "../MyGraphicsLibrary/MGL/Events/EventsSystem.hpp"

namespace mgl {
	class DefaultEventHandler : public EmptyEventHandler {
	protected:
		AbstractWindow* m_window;
	public:
		DefaultEventHandler(AbstractWindow* w) : m_window(w) {}

		virtual void resizeEvent(GLFWwindow* w, int x, int y) override;
	};
}

mgl::AbstractWindow::AbstractWindow() : m_projection(new mgl::math::Matrix()), isWindowInitialized(false) {}

mgl::AbstractWindow::AbstractWindow(std::string title, int width, int height, DefaultWindowMode mode) : AbstractWindow() {
	initialize(title, width, height, mode);
}

mgl::AbstractWindow::~AbstractWindow() {
	clean();
	if (m_default_event_handler)
		delete m_default_event_handler;
}

void mgl::AbstractWindow::initialize(std::string title, int width, int height, DefaultWindowMode mode) {
	if (!glfwInit())
		throw Exceptions::WindowInitializationException("GLFW inititalization error.");

	m_window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if (mode == DefaultWindowMode::Fullscreen) {
		auto monitor = glfwGetPrimaryMonitor();
		auto window_mode = glfwGetVideoMode(monitor);
		glfwSetWindowMonitor(m_window, monitor, 0, 0, width, height, window_mode->refreshRate);
	}

	if (!m_window)
		throw Exceptions::WindowInitializationException("Window inititalization error.");

	resize(width, height);

	glfwMakeContextCurrent(m_window);
	glfwSwapInterval(0);

	glewExperimental = GL_TRUE;
	GLenum glewError = glewInit();
	if (glewError != GLEW_OK)
		throw Exceptions::WindowInitializationException((std::string("GLEW inititalization error: ")
														+ (const char*) (glewGetErrorString(glewError))).c_str());

	isWindowInitialized = true;

	//TEMPORARY!!!
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
}

void mgl::AbstractWindow::clean() {
	if (isWindowInitialized) {
		glfwDestroyWindow(m_window);
		glfwTerminate();
	}
	isWindowInitialized = false;
}

void mgl::AbstractWindow::resize() {
	auto size = getSize();
	resize(size.w, size.h);
}

void mgl::AbstractWindow::resize(int width, int height) {
	m_aspectRatio = float(width) / height;
	mgl::setViewport(0, 0, width, height);

	if (m_projection) delete m_projection;
	m_projection = new mgl::math::Matrix(mgl::math::Matrix::orthographicMatrix(
		m_aspectRatio > 1.f ? -m_aspectRatio : -1.f,
		m_aspectRatio > 1.f ? m_aspectRatio : 1.f,
		+1.f / (m_aspectRatio > 1.f ? 1.f : m_aspectRatio),
		-1.f / (m_aspectRatio > 1.f ? 1.f : m_aspectRatio),
		-1.f, +1.f
	));
}

void mgl::AbstractWindow::setOpenGLVersion(int major, int minor) {
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
}

void mgl::AbstractWindow::update() {
	glfwSwapBuffers(m_window);
}

void mgl::AbstractWindow::pollEvents() {
	glfwPollEvents();
}

void mgl::AbstractWindow::waitEvents() {
	glfwWaitEvents();
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

mgl::Size mgl::AbstractWindow::getSize() {
	Size ret;
	glfwGetFramebufferSize(m_window, &ret.w, &ret.h);
	return ret;
}

void mgl::AbstractWindow::changleEventHandler(AbstractEventHandler * h) {
	EventsSystem::setHandler(h);
}

bool mgl::AbstractWindow::isWindowClosed() {
	return glfwWindowShouldClose(m_window);
}

void mgl::AbstractWindow::initializeEventHandling(AbstractEventHandler * h) {
	EventsSystem::setHandler(h);
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

void mgl::AbstractWindow::initializeEventHandling() {
	m_default_event_handler = new DefaultEventHandler(this);
	initializeEventHandling(m_default_event_handler);
}

void mgl::DefaultEventHandler::resizeEvent(GLFWwindow * w, int x, int y) {
	m_window->resize(x, y);
	m_window->update();
}

#include "../MyGraphicsLibrary/MGL/OpenGL/ClassesMirror/Shader.hpp"
#include "../MyGraphicsLibrary/MGL/Default/DefaultShaders.hpp"
mgl::ShaderProgram* mgl::AbstractWindow::linkDefaultProgram(DefaultVertexShaderInput input) {
	auto ret = new mgl::ShaderProgram();
	auto vertex_shader = mgl::compileDefaultVertexShader(input);
	auto fragment_shader = mgl::compileDefaultFragmentShader();
	ret->link({*vertex_shader, *fragment_shader});
	delete vertex_shader;
	delete fragment_shader;
	return ret;
}

mgl::ShaderProgram* mgl::AbstractWindow::linkProgramWithDefaultFragmentShader(Shader* vertex_shader) {
	auto ret = new mgl::ShaderProgram();
	auto fragment_shader = mgl::compileDefaultFragmentShader();
	ret->link({*vertex_shader, *fragment_shader});
	delete vertex_shader;
	delete fragment_shader;
	return ret;
}