#pragma once
#include <string>
#include <set>
#include "SharedEnums.hpp"
#include "AbstractException.hpp"
#include "AbstractEventHandler.hpp"

struct GLFWwindow;

namespace mgl {
	enum class DefaultWindowMode {
		Windowed = 0, Fullscreen
	};
	class InitializationException : public AbstractStringException {
		using AbstractStringException::AbstractStringException;
	};

	class Program;
	class Matrix;

	class Window {
	private:
		GLFWwindow* m_window;
		std::set<AbstractEventHandler*> m_events;
	protected:
		float aspectRatio;
		Matrix* projection;
	protected:
		virtual void init() abstract;
		virtual void resize();
		virtual void render() abstract;

		void addEventsHandler(AbstractEventHandler* h);
		void removeEventsHandler(AbstractEventHandler* h);
		void removeAllEventsHandlers();

		void setOpenGLVersion(int major = 4, int minor = 3);
	private:
		Window();
	public:
		explicit Window(std::string title, int width = 640, int height = 480, DefaultWindowMode mode = DefaultWindowMode::Windowed);
		virtual ~Window();

		Program* linkDefaultProgram(DefaulProgramType type = DefaulProgramType::Vertex1Matrix);
		int loop();

		void setErrorHandler(void(*handler)(int, const char*));
		void setWindowCloseHandler(void(*handler)(GLFWwindow*));
	};
}