#pragma once
#include <string>
#include <set>
#include "SharedEnums.hpp"
#include "AbstractException.hpp"
#include "AbstractEventHandler.hpp"

struct SDL_Window;
typedef void* SDL_GLContext;

namespace mgl {
	enum class DefaultWindowPos {
		Undefined, Centered
	};
	class InitializationException : public AbstractStringException {
		using AbstractStringException::AbstractStringException;
	};

	class Program;
	class Matrix;

	class Window {
	private:
		SDL_Window* m_window;
		SDL_GLContext* m_context;
		std::set<AbstractEventHandler*> m_events;
		bool quit;
	protected:
		float aspectRatio;
		Matrix* projection;
	protected:
		void initSDL();
		void initGLEW();
		void initializeWindow(std::string title, size_t x, size_t y, size_t width, size_t height);
	protected:
		virtual void init() abstract;
		virtual void render() abstract;
		virtual void calculateProjection(int width, int height);
		virtual void initializeWindowResize();
		void initializeDefaultEventHandler();
		void addEventsHandler(AbstractEventHandler* h);
		void removeEventsHandler(AbstractEventHandler* h);
		void removeAllEventsHandlers();
	private:
		Window();
	public:
		explicit Window(std::string title, size_t x, size_t y, size_t width = 640, size_t height = 480);
		explicit Window(std::string title, DefaultWindowPos defaultPos = DefaultWindowPos::Centered, size_t width = 640, size_t height = 480);
		virtual ~Window();

		Program* linkDefaultProgram(DefaulProgramType type = DefaulProgramType::Vertex1Matrix);
		int loop();

		void getSize(int* w, int* h) const;
	};
}