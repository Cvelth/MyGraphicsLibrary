#pragma once
#include "OpenGL_header.h"

namespace mgl {
	void setOpenGLVersion(int major = 4, int minor = 3, OpenGLVersionMask mask = OpenGLVersionMask::Core);
}