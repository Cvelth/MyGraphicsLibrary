#include "mgl/dependencies/OpenGL_Dependency/opengl_dependency.hpp"
#include "mgl/dependencies/WindowLibrary_Dependency/window_dependency.hpp"
#include "Window.hpp"

#include <map>
#include "mgl/Events/Events.hpp"
namespace mgl {
	class AbstractEventController;
	class EventSystem {
	private:
		static std::map<GLFWwindow*, std::shared_ptr<AbstractEventController>> controllers;
	public:
		static void set(AbstractWindow *window, std::shared_ptr<AbstractEventController> controller) {
			if (window != nullptr)
				controllers.insert(std::make_pair(window->m_window, controller));
		}
	public:
		static void mouse_button(GLFWwindow* w, int button, int action, int mods) {
			if (auto controller = controllers.find(w); controller != controllers.end() && controller->second)
				controller->second->mouse_button(enum_converter::convert_to_MouseButton(button),
												 enum_converter::convert_to_MouseAction(action),
												 enum_converter::convert_to_Modificators(mods));
		}
		static void mouse_move(GLFWwindow* w, double x, double y) {
			if (auto controller = controllers.find(w); controller != controllers.end() && controller->second)
				controller->second->mouse_move(x, y);
		}
		static void mouse_enter(GLFWwindow* w, int ent) {
			if (auto controller = controllers.find(w); controller != controllers.end() && controller->second)
				controller->second->mouse_enter(enum_converter::convert_to_MouseEnterAction(ent));
		}
		static void scroll(GLFWwindow* w, double x, double y) {
			if (auto controller = controllers.find(w); controller != controllers.end() && controller->second)
				controller->second->scroll(x, y);
		}
		static void key(GLFWwindow* w, int key, int scancode, int action, int mods) {
			if (auto controller = controllers.find(w); controller != controllers.end() && controller->second)
				controller->second->key(enum_converter::convert_to_Key(key), scancode,
												 enum_converter::convert_to_KeyAction(action),
												 enum_converter::convert_to_Modificators(mods));
		}
		static void character(GLFWwindow* w, unsigned int codepoint) {
			if (auto controller = controllers.find(w); controller != controllers.end() && controller->second)
				controller->second->character(codepoint);
		}
		static void character(GLFWwindow* w, unsigned int codepoint, int mods) {
			if (auto controller = controllers.find(w); controller != controllers.end() && controller->second)
				controller->second->character(codepoint, enum_converter::convert_to_Modificators(mods));
		}
		static void file_drop(GLFWwindow* w, int count, const char **paths) {
			if (auto controller = controllers.find(w); controller != controllers.end() && controller->second)
				controller->second->file_drop(count, paths);
		}
		static void resize(GLFWwindow* w, int x, int y) {
			if (auto controller = controllers.find(w); controller != controllers.end() && controller->second)
				controller->second->resize(x, y);
		}
	};
	std::map<GLFWwindow*, std::shared_ptr<AbstractEventController>> EventSystem::controllers;
}

#include <string>
mgl::AbstractWindow::AbstractWindow(char const* title, int width, int height, bool is_fullscreen, std::shared_ptr<AbstractEventController> controller) {
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

	setEventController(controller);
}
mgl::AbstractWindow::~AbstractWindow() {
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

void mgl::AbstractWindow::setEventController(std::shared_ptr<AbstractEventController> controller) {
	m_controller = controller;
	EventSystem::set(this, m_controller);
	glfwSetKeyCallback(m_window, EventSystem::key);
	glfwSetMouseButtonCallback(m_window, EventSystem::mouse_button);
	glfwSetCharCallback(m_window, EventSystem::character);
	glfwSetCharModsCallback(m_window, EventSystem::character);
	glfwSetCursorEnterCallback(m_window, EventSystem::mouse_enter);
	glfwSetCursorPosCallback(m_window, EventSystem::mouse_move);
	glfwSetDropCallback(m_window, EventSystem::file_drop);
	glfwSetScrollCallback(m_window, EventSystem::scroll);
	glfwSetFramebufferSizeCallback(m_window, EventSystem::resize);
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