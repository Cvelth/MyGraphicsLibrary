#pragma once
#include <string>
#include "SharedEnums.hpp"
#include "AbstractException.hpp"
#include "EmptyEventHandler.hpp"

struct GLFWwindow;

namespace mgl {
	enum class DefaultWindowMode {
		Windowed = 0, Fullscreen = 1
	};
	namespace Exceptions {
		class WindowInitializationException : public AbstractStringException {
			using AbstractStringException::AbstractStringException;
		};
	}

	class Program;
	class Matrix;
	class DefaultEventHandler;

	class AbstractWindow {
		friend DefaultEventHandler;
	private:
		GLFWwindow* m_window;
	protected:
		float m_aspectRatio;
		Matrix* m_projection;
	protected:
		virtual void initializeRender() abstract;
		virtual void render() abstract;
		virtual void cleanRender() abstract;
	protected:
		virtual void resize(int width, int height);
		void setOpenGLVersion(int major = 4, int minor = 3);
	protected:
		AbstractWindow();
	public:
		explicit AbstractWindow(std::string title, int width = 640, int height = 480, DefaultWindowMode mode = DefaultWindowMode::Windowed);
		virtual ~AbstractWindow();

		Program* linkDefaultProgram(DefaulProgramType type = DefaulProgramType::Vertex1Matrix);
		void update();

		void initializeEventHandling();
		void changleEventHandler(AbstractEventHandler* h);

		inline GLFWwindow* window() { return m_window; }
	};

	class DefaultEventHandler : public EmptyEventHandler {
	protected:
		AbstractWindow* m_window;
	public:
		DefaultEventHandler(AbstractWindow* w) : m_window(w) {}

		virtual void resizeEvent(GLFWwindow* w, int x, int y) override;
	};
}