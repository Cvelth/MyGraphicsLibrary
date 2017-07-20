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
		virtual void initializeRenderProcess() abstract;
		virtual void renderProcess() abstract;
		virtual void clearRenderProcess() abstract;
	protected:
		virtual void resize(int width, int height);
		void setOpenGLVersion(int major = 4, int minor = 3);
	public:
		explicit AbstractWindow();
		explicit AbstractWindow(std::string title, int width = 640, int height = 480, DefaultWindowMode mode = DefaultWindowMode::Windowed);
		virtual ~AbstractWindow();

		void initialize(std::string title, int width = 640, int height = 480, DefaultWindowMode mode = DefaultWindowMode::Windowed);
		void clean();

		Program* linkDefaultProgram(DefaulProgramType type = DefaulProgramType::Vertex1Matrix);
		void update();

		void initializeEventHandling();
		void changleEventHandler(AbstractEventHandler* h);

		inline GLFWwindow* window() { return m_window; }
		bool isWindowClosed();
	};

	class DefaultEventHandler : public EmptyEventHandler {
	protected:
		AbstractWindow* m_window;
	public:
		DefaultEventHandler(AbstractWindow* w) : m_window(w) {}

		virtual void resizeEvent(GLFWwindow* w, int x, int y) override;
	};
}