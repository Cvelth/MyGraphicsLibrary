#pragma once
#include "OpenGL\EnumsMirror\EnumsMirror.hpp"

namespace mgl {
	class Shader;

	Shader* compileDefaultFragmentShader();
	Shader* compileDefaultVertexShader(DefaultVertexShaderInput input);
}
