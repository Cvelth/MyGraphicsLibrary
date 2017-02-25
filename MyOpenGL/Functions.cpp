#include "OpenGL_header.h"
#include "Functions.hpp"

void mgl::setOpenGLVersion(int major, int minor, OpenGLVersionMask mask) {
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, major);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minor);
	switch (mask) {
		case OpenGLVersionMask::Core: SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE); break;
		case OpenGLVersionMask::Compatibility: SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY); break;
		case OpenGLVersionMask::ES: SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES); break;
	}
}

void mgl::setClearColor(Color c) {
	glClearColor(c.r(), c.g(), c.b(), c.a());
}

void mgl::clearColorBuffer() {
	glClear(GL_COLOR_BUFFER_BIT);
}
