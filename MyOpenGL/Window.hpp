#pragma once
#include <string>
#include "Enums.hpp"

struct SDL_Window;
typedef void* SDL_GLContext;
union SDL_Event;

namespace mgl {
	class Window {
	private:
		SDL_Window* m_window;
		SDL_GLContext* m_context;
		SDL_Event* m_event;
		bool quit;
	protected:
		void initSDL();
		void initGLEW();
	protected:
		virtual void init() abstract;
		virtual void render() abstract;
		virtual void keyEvent(unsigned char key, int mouseX, int mouseY);
	public:
		explicit Window(std::string title, size_t x, size_t y, size_t width = 640, size_t height = 480);
		explicit Window(std::string title, DefaultWindowPos defaultPos = DefaultWindowPos::Centered, size_t width = 640, size_t height = 480);
		virtual ~Window();

		int loop();
	};
}