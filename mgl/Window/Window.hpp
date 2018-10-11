#pragma once
#include <memory>

struct GLFWwindow;

namespace mml {
	class transformation;
}
namespace mgl {
	class Color;
	class EventSystem;
	class AbstractEventController;

	class AbstractWindow {
		friend EventSystem;
	private:
		GLFWwindow *m_window;
	protected:
		std::shared_ptr<AbstractEventController> m_controller;
	public:
		explicit AbstractWindow(char const* title, int width, int height, bool is_fullscreen = false,
								std::shared_ptr<AbstractEventController> controller = nullptr);
		virtual ~AbstractWindow();
		void setEventController(std::shared_ptr<AbstractEventController> controller);
		inline std::shared_ptr<AbstractEventController> event_controller() const {
			return m_controller;
		}

		void update();
		void pollEvents() const;
		void waitEvents() const;
		void clearWindow();
		void setClearColor(Color const& color);
		void setClearColor(const float r = 0.f, const float g = 0.f,
						   const float b = 0.f, const float a = 1.f);

		int width() const;
		int height() const;
		std::pair<int, int> size() const;

		bool should_close() const;
	};

	class Window : public AbstractWindow {
	protected:
		virtual void initializeRendering() {}
		virtual void render() {}
		virtual void clearRendering() {}
	public:
		using AbstractWindow::AbstractWindow;
		void loop() {
			initializeRendering();
			while (!should_close()) {
				render();
			}
			clearRendering();
		}
	};
}

#include "mgl/exceptions.hpp"
DefineNewMGLException(WindowCreationError);