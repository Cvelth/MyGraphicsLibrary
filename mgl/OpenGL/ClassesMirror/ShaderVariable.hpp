#pragma once
#include "../MyGraphicsLibrary/MGL/OpenGL/EnumsMirror/EnumsMirror.hpp"
namespace mgl {
	class VertexArray;
	class ShaderProgram;
	class ShaderVariable {
		friend ShaderProgram;
		friend VertexArray;
	protected:
		const char* variable_name;
		ShaderVariableType variable_type;
		int location;
		ShaderDataType data_type;
	protected:
		explicit ShaderVariable(const char* name, const ShaderVariableType& v_type, int location, const ShaderDataType& d_type)
			: variable_name(name), variable_type(v_type), location(location), data_type(d_type) {}
	};
}