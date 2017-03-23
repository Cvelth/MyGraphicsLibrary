#include "OpenGL_header.h"
#include "Functions.hpp"
#include "Window.hpp"
#include "DefaultProgram.hpp"
#include "Matrix.hpp"

mgl::Window::Window() : projection(new Matrix()) { }

mgl::Window::Window(std::string title, size_t x, size_t y, size_t width, size_t height) : Window() {
	initializeWindow(title, x, y, width, height);
}

mgl::Window::Window(std::string title, DefaultWindowPos defaultPos, size_t width, size_t height) : Window() {
	switch (defaultPos) {
		case DefaultWindowPos::Centered: 
			initializeWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, int(width), int(height)); break;
		case DefaultWindowPos::Undefined: 
			initializeWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, int(width), int(height)); break;
	}
}

mgl::Window::~Window() {
	for (auto it : m_events)
		delete it;
	SDL_GL_DeleteContext(*m_context);
	delete m_context;
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void mgl::Window::calculateProjection(int width, int height) {
	aspectRatio = float(width) / height;
	mgl::viewport(0, 0, width, height);
	delete projection;
	projection = new mgl::Matrix(mgl::Matrix::orthographicMatrix(
		aspectRatio > 1.f ? -aspectRatio : -1.f, 
		aspectRatio > 1.f ? aspectRatio : 1.f,
		-1.f / (aspectRatio > 1.f ? 1.f : aspectRatio),
		+1.f / (aspectRatio > 1.f ? 1.f : aspectRatio),
		+1.f, -1.f
	));
}

void mgl::Window::initializeWindowResize() {
	int w, h;
	SDL_GetWindowSize(m_window, &w, &h);
	calculateProjection(w, h);
}

void mgl::Window::addEventsHandler(AbstractEventHandler * h) {
	m_events.insert(h);
}

void mgl::Window::removeEventsHandler(AbstractEventHandler * h) {
	m_events.erase(h);
}

void mgl::Window::removeAllEventsHandlers() {
	m_events.clear();
}

mgl::Program* mgl::Window::linkDefaultProgram(DefaulProgramType type) {
	return new DefaultProgram(type);
}

int mgl::Window::loop() {
	initializeWindowResize();
	init();

	SDL_Event ev;

	quit = false;
	while (!quit) {
		while (SDL_PollEvent(&ev) != 0) {
			if (ev.type == SDL_QUIT)
				quit = true;
			else if (ev.type == SDL_WINDOWEVENT)
				switch (ev.window.event) {
					case SDL_WINDOWEVENT_RESIZED:
					case SDL_WINDOWEVENT_SIZE_CHANGED:
					case SDL_WINDOWEVENT_MAXIMIZED:
					case SDL_WINDOWEVENT_RESTORED:
						initializeWindowResize();
						render();
						break;
					case SDL_WINDOWEVENT_SHOWN:
					case SDL_WINDOWEVENT_EXPOSED:
					case SDL_WINDOWEVENT_MOVED:
					case SDL_WINDOWEVENT_FOCUS_GAINED:
					case SDL_WINDOWEVENT_TAKE_FOCUS:
					case SDL_WINDOWEVENT_ENTER:
						render();
						break;
					case SDL_WINDOWEVENT_CLOSE:
						quit = true;
						break;
				}

			for (auto it : m_events)
				it->handle(&ev);
		}
		SDL_GL_SwapWindow(m_window);
	}
	return 0;
}

void mgl::Window::getSize(int* w, int* h) const {
	SDL_GetWindowSize(m_window, w, h);
}

void mgl::Window::initSDL() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		throw InitializationException(std::string("SDL inititalization error: ") += SDL_GetError());
	setOpenGLVersion(3, 1);
}

void mgl::Window::initGLEW() {
	glewExperimental = GL_TRUE;
	GLenum glewError = glewInit();
	if (glewError != GLEW_OK)
		throw InitializationException(std::string("GLEW inititalization error: ") 
									  += (const char*)(glewGetErrorString(glewError)));
	if (SDL_GL_SetSwapInterval(1) < 0)
		throw InitializationException(std::string("VSync inititalization error: ") 
									  += SDL_GetError());
}

void mgl::Window::initializeWindow(std::string title, size_t x, size_t y, size_t width, size_t height) {
	initSDL();
	m_window = SDL_CreateWindow(title.c_str(), int(x), int(y), int(width), int(height), SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (m_window == NULL)
		throw InitializationException(std::string("Window couldn't be created. Error: ") += SDL_GetError());

	m_context = new SDL_GLContext();
	*m_context = SDL_GL_CreateContext(m_window);
	if (m_context == NULL)
		throw InitializationException(std::string("OpenGL context couldn't be created. Error: ") += SDL_GetError());

	initGLEW();
}