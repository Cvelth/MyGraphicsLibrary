#pragma once
#include "OpenGL_Mirror\EnumsMirror\EnumsMirror.hpp"
namespace mgl {
	class ShaderProgram;
	class ShaderVariable {
		friend ShaderProgram;
	private:
		const char* m_variable_name;
		ShaderVariableType m_variable_type;
		int m_location;
		ShaderDataType m_data_type;
	protected:
		explicit ShaderVariable(const char* name, ShaderVariableType v_type, int location, ShaderDataType d_type);
	};
}