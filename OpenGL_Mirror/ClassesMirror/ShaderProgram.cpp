#include "OpenGL_Mirror\OpenGL_Dependency\OpenGL.h"
#include "ShaderProgram.hpp"
#include "Shader.hpp"
#include "ShaderVariable.hpp"
#include "VertexArray.hpp"
#include "Math\Vector.hpp"
#include "Math\Matrix.hpp"

mgl::ShaderProgram::ShaderProgram() {
	m_id = glCreateProgram();
	m_vao = new mgl::VertexArray();
}

mgl::ShaderProgram::ShaderProgram(VertexArray& vao) {
	m_id = glCreateProgram();
	if (vao.isValid())
		m_vao = new mgl::VertexArray(vao);
}

mgl::ShaderProgram::ShaderProgram(const std::initializer_list<Shader>& list) : ShaderProgram() {
	link(list);
}

mgl::ShaderProgram::ShaderProgram(const std::initializer_list<Shader>& list, VertexArray& vao) : ShaderProgram(vao) {
	link(list);
}

mgl::ShaderProgram::~ShaderProgram() {
	delete m_vao;
	glDeleteProgram(m_id);
}

void mgl::ShaderProgram::use() {
	glUseProgram(m_id);
	m_vao->bind();
}

bool mgl::ShaderProgram::isLinked() {
	if (glIsProgram(m_id)) {
		GLint isLinked;
		glGetProgramiv(m_id, GL_LINK_STATUS, &isLinked);
		return isLinked;
	} else
		return false;
}

mgl::ShaderVariable* mgl::ShaderProgram::enableAttribWithNormalization(const char* fieldName, size_t size,
												 bool normalized, size_t stride, size_t shift) {
	auto loc = glGetAttribLocation(m_id, fieldName);
	if (loc == -1)
		throw Exceptions::ProgramException("There are no atribute in the Shader with the 'fieldName'.");

	auto ret = new mgl::ShaderVariable(fieldName, ShaderVariableType::Attribute, loc, ShaderDataType::Float);
	m_vao->attribPointer(*ret, size, normalized, stride, shift);
	return ret;
}

mgl::ShaderVariable* mgl::ShaderProgram::enableAttrib(const char* fieldName, size_t size, size_t stride, size_t shift) {
	return enableAttribWithNormalization(fieldName, size, false, stride, shift);
}

void mgl::ShaderProgram::initializeInstancing(ShaderVariable *variable, size_t divisor) {
	if (variable->variable_type != ShaderVariableType::Attribute)
		throw Exceptions::ProgramException("Instancing can be initialized for Attribute variables only.");
	glVertexAttribDivisor(variable->location, divisor);
}

void mgl::ShaderProgram::sendUniform(ShaderVariable* variable, const float & data) {
	if (variable->variable_type != ShaderVariableType::Uniform)
		throw Exceptions::ProgramException("You are trying to send uniform data to a non-uniform variable.");

	use();
	if (variable->data_type == ShaderDataType::Float)
		glUniform1f(variable->location, data);
	else
		throw Exceptions::ProgramException("Data type isn't supported by the uniform.");
}

void mgl::ShaderProgram::sendUniform(ShaderVariable* variable, const math::Vector & data) {
	if (variable->variable_type != ShaderVariableType::Uniform)
		throw Exceptions::ProgramException("You are trying to send uniform data to a non-uniform variable.");

	use();
	if (variable->data_type == ShaderDataType::Float_4)
		glUniform4f(variable->location, data.x(), data.y(), data.z(), data.w());
	else if (variable->data_type == ShaderDataType::Float_3)
	 	glUniform3f(variable->location, data.x(), data.y(), data.z());
	else if (variable->data_type == ShaderDataType::Float_2)
		glUniform2f(variable->location, data.x(), data.y());
	else
		throw Exceptions::ProgramException("Data type isn't supported by the uniform.");
}

void mgl::ShaderProgram::sendUniform(ShaderVariable* variable, const math::Matrix & data) {
	if (variable->variable_type != ShaderVariableType::Uniform)
		throw Exceptions::ProgramException("You are trying to send uniform data to a non-uniform variable.");

	use();
	if (variable->data_type == ShaderDataType::Float_4x4)
		glUniformMatrix4fv(variable->location, 1, GL_FALSE, data.data());
	else if (variable->data_type == ShaderDataType::Float_3x3)
		glUniformMatrix3fv(variable->location, 1, GL_FALSE, data.data3x3());
	else if (variable->data_type == ShaderDataType::Float_2x2)
		glUniformMatrix2fv(variable->location, 1, GL_FALSE, data.data2x2());
	else
		throw Exceptions::ProgramException("Data type isn't supported by the uniform.");
}

#include <string>
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
		throw Exceptions::ProgramException(("Program linking error: " + std::string(log)).c_str());
		delete[] log;
	}
}

mgl::ShaderVariable* mgl::ShaderProgram::getUniform(const char* fieldName) {
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