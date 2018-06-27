#pragma once
#include "../MyGraphicsLibrary/MGL/OpenGL/EnumsMirror/EnumsMirror.hpp"
namespace mgl {
	class Color;
	class Buffer;

	const unsigned int getErrorCode();
	const char* getError();
	const char* getRendererName();

	void clearColorBuffer();
	void setViewport(size_t x, size_t y, size_t width, size_t height);

	void setClearColor(const Color& c);
	void setLineWidth(float w, SmoothMode mode = SmoothMode::DontCare);
	void setPointSize(float s);
	
	void enableBlend(BlendEnum s, BlendEnum d);
	void enableBlend(const Buffer& b, BlendEnum s, BlendEnum d);

	void enableLineSmooth(SmoothMode mode);
	void enablePolygonSmooth(SmoothMode mode);
	void enablePointSmooth(SmoothMode mode);
}