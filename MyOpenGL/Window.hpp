#pragma once
#include <string>
#include "SharedEnums.hpp"

struct SDL_Window;
typedef void* SDL_GLContext;

namespace mgl {
	enum class DefaultWindowPos {
		Undefined, Centered
	};

	class Program;
	class Matrix;

	class Window {
	private:
		SDL_Window* m_window;
		SDL_GLContext* m_context;
		bool quit;
	protected:
		float aspectRatio;
		Matrix* projection;
	protected:
		void initSDL();
		void initGLEW();
	protected:
		virtual void init() abstract;
		virtual void render() abstract;
		virtual void keyEvent(unsigned char key, int mouseX, int mouseY);
		virtual void resizeEvent(int width, int height);
	private:
		Window();
	public:
		explicit Window(std::string title, size_t x, size_t y, size_t width = 640, size_t height = 480);
		explicit Window(std::string title, DefaultWindowPos defaultPos = DefaultWindowPos::Centered, size_t width = 640, size_t height = 480);
		virtual ~Window();

		Program* linkDefaultProgram(DefaulProgramType type = DefaulProgramType::Vertex1Matrix);
		int loop();
	};
}