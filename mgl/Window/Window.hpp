#pragma once
#include <memory>

struct GLFWwindow;

namespace mgl {
	namespace math {
		class transformation;
	}
	class Color;

	class AbstractWindow {
	private:
		GLFWwindow *m_window;
	public:
		explicit AbstractWindow(char const* title, int width, int height, bool is_fullscreen = false);
		virtual ~AbstractWindow();

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