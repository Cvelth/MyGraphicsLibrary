#pragma once
#include "OpenGL_Mirror\EnumsMirror\EnumsMirror.hpp"

namespace mgl {
	class Shader;

	Shader* compileDefaultFragmentShader();
	Shader* compileDefaultVertexShader(DefaultVertexShaderInput input);
}
