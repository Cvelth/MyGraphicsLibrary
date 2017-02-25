#pragma once
#include "Enums.hpp"
#include "Color.hpp"

namespace mgl {
	void setOpenGLVersion(int major = 4, int minor = 3, OpenGLVersionMask mask = OpenGLVersionMask::Core);
	void setClearColor(Color c);
	void clearColorBuffer();
}