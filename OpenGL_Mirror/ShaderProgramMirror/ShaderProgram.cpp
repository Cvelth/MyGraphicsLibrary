#include "OpenGL_Mirror\OpenGL_Dependency\OpenGL.h"
#include "ShaderProgram.hpp"
#include "Math\Vector.hpp"
#include "Math\Matrix.hpp"
#include "OpenGL_Mirror\FunctionsMirror\FunctionsMirror.hpp"

mgl::ShaderProgram::ShaderProgram() {
	m_id = glCreateProgram();
}

mgl::ShaderProgram::ShaderProgram(const std::initializer_list<Shader>& list) : ShaderProgram() {
	link(list);
}

mgl::ShaderProgram::~ShaderProgram() {
	glDeleteProgram(m_id);
}

void mgl::ShaderProgram::link(const std::initializer_list<Shader>& shaders) {
	if (shaders.size() == 0u)
		throw Exceptions::ProgramException("There is no shaders to attach");

	for (auto shader : shaders)
		glAttachShader(m_id, shader.id());

	glLinkProgram(m_id);

	GLint isLinked;
	glGetProgramiv(m_id, GL_LINK_STATUS, &isLinked);
	if (!isLinked) {
		GLsizei len;
		glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &len);

		GLchar* log = new GLchar[len + 1];
		glGetProgramInfoLog(m_id, len, &len, log);
		std::string t = std::string(log);
		delete[] log;

		throw Exceptions::ProgramException(std::string("Program linking error: ") + t);
	}
}

void mgl::ShaderProgram::use() {
	glUseProgram(m_id);
}

bool mgl::ShaderProgram::isLinked() {
	if (glIsProgram(m_id)) {
		GLint isLinked;
		glGetProgramiv(m_id, GL_LINK_STATUS, &isLinked);
		return isLinked;
	} else
		return false;
}

mgl::ShaderVariable* mgl::ShaderProgram::getUniform(const std::string fieldName) {
	GLint uniforms_number, max_uniform_length, name_length, size;
	GLenum type;
	GLchar* name;
	glGetProgramiv(m_id, GL_ACTIVE_UNIFORMS, &uniforms_number);
	glGetProgramiv(m_id, GL_ACTIVE_UNIFORM_MAX_LENGTH, &max_uniform_length);
	for (int i = 0; i < uniforms_number; i++) {
		name = new GLchar[max_uniform_length];
		glGetActiveUniform(m_id, i, max_uniform_length, &name_length, &size, &type, name);
		std::string name_str = std::string(name);
		delete[] name;

		if (name_str == fieldName)
			return new ShaderVariable(fieldName, ShaderVariableType::Uniform, i, switchShaderDataType(type));
	}
	throw Exceptions::ProgramException("No uniform with the 'fieldName' was found in the Shader.");
}

mgl::ShaderVariable* mgl::ShaderProgram::enableAttribWithNormalization(const std::string fieldName, size_t size,
												 bool normalized, size_t stride, size_t shift) {
	auto loc = glGetAttribLocation(m_id, fieldName.c_str());
	if (loc == -1)
		throw Exceptions::ProgramException("There are no atribute in the Shader with the 'fieldName'.");

	glVertexAttribPointer(loc, (GLint) size, GL_FLOAT, normalized ? GL_TRUE : GL_FALSE,
		sizeof(float) * (GLsizei) stride, (const void*) (sizeof(float) * shift));
	glEnableVertexAttribArray(loc);

	return new mgl::ShaderVariable(fieldName, ShaderVariableType::Attribute, loc, ShaderDataType::Float);
}

mgl::ShaderVariable* mgl::ShaderProgram::enableAttrib(const std::string fieldName, size_t size, size_t stride, size_t shift) {
	return enableAttribWithNormalization(fieldName, size, false, stride, shift);
}

void mgl::ShaderProgram::sendUniform(ShaderVariable* variable, const float & data) {
	if (variable->m_variable_type != ShaderVariableType::Uniform)
		throw Exceptions::ProgramException("You are trying to send uniform data to a non-uniform variable.");

	use();

	if (variable->m_data_type == ShaderDataType::Float)
		glUniform1f(variable->m_location, data);
	else
		throw Exceptions::ProgramException("Data type isn't supported by the uniform.");
}

void mgl::ShaderProgram::sendUniform(ShaderVariable* variable, const math::Vector & data) {
	if (variable->m_variable_type != ShaderVariableType::Uniform)
		throw Exceptions::ProgramException("You are trying to send uniform data to a non-uniform variable.");

	use();

	if (variable->m_data_type == ShaderDataType::Float_4)
		glUniform4f(variable->m_location, data.x(), data.y(), data.z(), data.w());
	else if (variable->m_data_type == ShaderDataType::Float_3)
	 	glUniform3f(variable->m_location, data.x(), data.y(), data.z());
	else if (variable->m_data_type == ShaderDataType::Float_2)
		glUniform2f(variable->m_location, data.x(), data.y());
	else
		throw Exceptions::ProgramException("Data type isn't supported by the uniform.");
}

void mgl::ShaderProgram::sendUniform(ShaderVariable* variable, const math::Matrix & data) {
	if (variable->m_variable_type != ShaderVariableType::Uniform)
		throw Exceptions::ProgramException("You are trying to send uniform data to a non-uniform variable.");

	use();

	if (variable->m_data_type == ShaderDataType::Float_4x4)
		glUniformMatrix4fv(variable->m_location, 1, GL_FALSE, data.data());
	else if (variable->m_data_type == ShaderDataType::Float_3x3)
		glUniformMatrix3fv(variable->m_location, 1, GL_FALSE, data.data3x3());
	else if (variable->m_data_type == ShaderDataType::Float_2x2)
		glUniformMatrix2fv(variable->m_location, 1, GL_FALSE, data.data2x2());
	else
		throw Exceptions::ProgramException("Data type isn't supported by the uniform.");
}

mgl::ShaderVariable::ShaderVariable(std::string name, ShaderVariableType v_type, int location, ShaderDataType d_type)
	: m_variable_name(name), m_variable_type(v_type), m_location(location), m_data_type(d_type) {}
