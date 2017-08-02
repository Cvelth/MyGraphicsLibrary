#include "ShaderVariable.hpp"

mgl::ShaderVariable::ShaderVariable(const char* name, ShaderVariableType v_type, int location, ShaderDataType d_type)
	: m_variable_name(name), m_variable_type(v_type), m_location(location), m_data_type(d_type) {}
