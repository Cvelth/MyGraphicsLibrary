#pragma once
#include "Color.hpp"

namespace mgl {
	enum class OpenGLVersionMask {
		Core, Compatibility, ES
	};

	void setOpenGLVersion(int major = 4, int minor = 3, OpenGLVersionMask mask = OpenGLVersionMask::Core);
	void setClearColor(Color c);
	void clearColorBuffer();
}