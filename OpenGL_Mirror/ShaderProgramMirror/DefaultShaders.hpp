#pragma once

namespace mgl {
	class Shader;

	enum class DefaultVertexShaderInput {
		vec4x2, vec4x2_mat4x1, mat4x1, mat4x2, mat4x6
	};

	Shader* compileDefaultFragmentShader();
	Shader* compileDefaultVertexShader(DefaultVertexShaderInput input);
}
