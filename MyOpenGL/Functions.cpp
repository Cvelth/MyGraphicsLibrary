#include "OpenGL_header.h"
#include "Functions.hpp"
#include "Color.hpp"
#include "Buffer.hpp"

void mgl::setOpenGLVersion(int major, int minor, OpenGLVersionMask mask) {
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, major);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minor);
	switch (mask) {
		case OpenGLVersionMask::Core: SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE); break;
		case OpenGLVersionMask::Compatibility: SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY); break;
		case OpenGLVersionMask::ES: SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES); break;
	}
}

void mgl::setClearColor(const Color & c) {
	glClearColor(c.r(), c.g(), c.b(), c.a());
}

void mgl::setLineWidth(float w, SmoothMode mode) {
	glLineWidth(w);
	enableLineSmooth(mode);
}

void mgl::setPointSize(float s) {
	glPointSize(s);
}

void mgl::enableBlend(BlendEnum s, BlendEnum d) {
	glBlendFunc(_enumSwitch(s), _enumSwitch(d));
	glEnable(GL_BLEND);
}

void mgl::enableBlend(const Buffer & b, BlendEnum s, BlendEnum d) {
	glBlendFunci(b.id(), _enumSwitch(s), _enumSwitch(d));
}

void mgl::enableLineSmooth(SmoothMode mode) {
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, _enumSwitch(mode));
}

void mgl::enablePolygonSmooth(SmoothMode mode) {
	glEnable(GL_POLYGON_SMOOTH);
	glHint(GL_POLYGON_SMOOTH_HINT, _enumSwitch(mode));
}

void mgl::enablePointSmooth(SmoothMode mode) {
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, _enumSwitch(mode));
}

std::string mgl::getError() {
	return (const char*) glewGetErrorString(glGetError());
}

void mgl::clearColorBuffer() {
	glClear(GL_COLOR_BUFFER_BIT);
}

void mgl::viewport(size_t x, size_t y, size_t width, size_t height) {
	glViewport(x, y, width, height);
}
