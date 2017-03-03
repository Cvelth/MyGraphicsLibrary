#pragma once
#include "FunctionEnums.hpp"

namespace mgl {
	class Color;
	class Buffer;

	void clearColorBuffer();
	void viewport(size_t x, size_t y, size_t width, size_t height);

	void setOpenGLVersion(int major = 4, int minor = 3, OpenGLVersionMask mask = OpenGLVersionMask::Core);
	void setClearColor(const Color& c);
	void setLineWidth(float w, SmoothMode mode = SmoothMode::DontCare);
	void setPointSize(float s);
	
	void enableBlend(BlendEnum s, BlendEnum d);
	void enableBlend(const Buffer& b, BlendEnum s, BlendEnum d); //To make after Buffer class creating.

	void enableLineSmooth(SmoothMode mode);
	void enablePolygonSmooth(SmoothMode mode);
	void enablePointSmooth(SmoothMode mode);
}