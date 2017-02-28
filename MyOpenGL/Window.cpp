#include "OpenGL_header.h"
#include "Functions.hpp"
#include "Window.hpp"
#include "DefaultProgram.hpp"
#include "Matrix.hpp"

mgl::Window::Window() : projection(new Matrix()) { }

mgl::Window::Window(std::string title, size_t x, size_t y, size_t width, size_t height) : Window() {
	initSDL();
	m_window = SDL_CreateWindow(title.c_str(), int(x), int(y), int(width), int(height), SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if (m_window == NULL)
		throw InitializationException(std::string("Window couldn't be created. Error:") += SDL_GetError());

	*m_context = SDL_GL_CreateContext(m_window);
	if (m_context == NULL)
		throw InitializationException(std::string("OpenGL context couldn't be created. Error:") += SDL_GetError());

	initGLEW();
}

mgl::Window::Window(std::string title, DefaultWindowPos defaultPos, size_t width, size_t height) : Window() {
	initSDL();
	switch (defaultPos) {
		case DefaultWindowPos::Centered: m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
																	 int(width), int(height), SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN); break;
		case DefaultWindowPos::Undefined: m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
																	 int(width), int(height), SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN); break;
	}
	if (m_window == NULL)
		throw InitializationException(std::string("Window couldn't be created. Error:") += SDL_GetError());

	*m_context = SDL_GL_CreateContext(m_window);
	if (m_context == NULL)
		throw InitializationException(std::string("OpenGL context couldn't be created. Error:") += SDL_GetError());

	initGLEW();
}

mgl::Window::~Window() {
	SDL_GL_DeleteContext(*m_context);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void mgl::Window::keyEvent(unsigned char key, int mouseX, int mouseY) {
	//Does nothing when a key is pressed.
}

void mgl::Window::resizeEvent(int width, int height) {
	aspectRatio = float(width) / height;
	glViewport(0, 0, width, height);
	if (aspectRatio > 1.f) {
		*projection = Matrix::orthographicMatrix(-aspectRatio, +aspectRatio, -1.f, +1.f, -1.f, +1.f);
	} else {
		*projection = Matrix::orthographicMatrix(-1.f, +1.f, -1.f / aspectRatio, +1.f / aspectRatio, -1.f, +1.f);
	}
}

mgl::Program* mgl::Window::linkDefaultProgram(DefaulProgramType type) {
	return new DefaultProgram(type);
}

int mgl::Window::loop() {
	quit = false;
	init();

	SDL_Event event;
	SDL_StartTextInput();
	while (!quit) {
		while (SDL_PollEvent(&event) != 0)
			if (event.type == SDL_QUIT)
				quit = true;
			else if (event.type == SDL_TEXTINPUT) {
				int x, y;
				SDL_GetMouseState(&x, &y);
				keyEvent(event.text.text[0], x, y);
			}
			else if (event.type == SDL_WINDOWEVENT)
				resizeEvent(event.window.data1, event.window.data2);

			render();
			SDL_GL_SwapWindow(m_window);
	}
	SDL_StopTextInput();
	
	return 0;
}

void mgl::Window::initSDL() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		throw InitializationException(std::string("SDL inititalization error:") += SDL_GetError());
	setOpenGLVersion(4, 3);
	
	m_context = new SDL_GLContext;
}

void mgl::Window::initGLEW() {
	glewExperimental = GL_TRUE;
	GLenum glewError = glewInit();
	if (glewError != GLEW_OK)
		throw InitializationException(std::string("GLEW inititalization error:") += (const char*)(glewGetErrorString(glewError)));
	if (SDL_GL_SetSwapInterval(1) < 0)
		throw InitializationException(std::string("VSync inititalization error:") += SDL_GetError());
}
