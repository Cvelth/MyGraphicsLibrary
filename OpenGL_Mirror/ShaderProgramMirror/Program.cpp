#include "OpenGL_Mirror\OpenGL_Dependency\OpenGL.h"
#include "Program.hpp"
#include "Math\Vector.hpp"
#include "Math\Matrix.hpp"
#include "OpenGL_Mirror\FunctionsMirror\FunctionsMirror.hpp"

mgl::Program::Program() {
	m_id = glCreateProgram();
}

mgl::Program::Program(const std::initializer_list<Shader>& list) : Program() {
	link(list);
}

mgl::Program::~Program() {
	glDeleteProgram(m_id);
}

void mgl::Program::link(const std::initializer_list<Shader>& shaders) {
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

void mgl::Program::use() {
	glUseProgram(m_id);
}

mgl::UniformVariable* mgl::Program::getUniform(const std::string fieldName) {
	GLint uniforms_number;
	GLint max_uniform_length;
	glGetProgramiv(m_id, GL_ACTIVE_UNIFORMS, &uniforms_number);
	glGetProgramiv(m_id, GL_ACTIVE_UNIFORM_MAX_LENGTH, &max_uniform_length);
	for (int i = 0; i < uniforms_number; i++) {
		GLint name_length;
		glGetActiveUniform(m_id, i, max_uniform_length, &name_length, NULL, NULL, NULL);
		if (name_length > 0) {
			GLint size;
			GLenum type;
			GLchar* name = new GLchar[name_length + 1];
			glGetActiveUniform(m_id, i, max_uniform_length, &name_length, &size, &type, name);
			std::string name_str = std::string(name);
			//delete[] name;

			if (name_str == fieldName)
				return new UniformVariable(fieldName, i, switchUniformType(type));
		}
	}
	throw Exceptions::ProgramException("No uniform with the 'fieldName' was found in the Shader.");
}

void mgl::Program::sendUniform(UniformVariable* variable, const float & data) {
	if (variable->m_type != UniformType::Float)
		throw Exceptions::ProgramException("Data type isn't supported by the uniform.");
	glUniform1f(variable->m_location, data);
}

void mgl::Program::sendUniform(UniformVariable* variable, const math::Vector & data) {
	if (variable->m_type != UniformType::Float_4)
		glUniform4f(variable->m_location, data.x(), data.y(), data.z(), data.w());
	else if (variable->m_type != UniformType::Float_3)
	 	glUniform3f(variable->m_location, data.x(), data.y(), data.z());
	else if (variable->m_type != UniformType::Float_2)
		glUniform2f(variable->m_location, data.x(), data.y());
	else
		throw Exceptions::ProgramException("Data type isn't supported by the uniform.");
}

void mgl::Program::sendUniform(UniformVariable* variable, const math::Matrix & data) {
	if (variable->m_type != UniformType::Float_4x4)
		glUniformMatrix4fv(variable->m_location, 1, GL_FALSE, data.data());
	else if (variable->m_type != UniformType::Float_3x3)
		glUniformMatrix3fv(variable->m_location, 1, GL_FALSE, data.data3x3());
	else if (variable->m_type != UniformType::Float_2x2)
		glUniformMatrix2fv(variable->m_location, 1, GL_FALSE, data.data2x2());
	else
		throw Exceptions::ProgramException("Data type isn't supported by the uniform.");
}

void mgl::Program::enableAttrib(const std::string fieldName, size_t size,
							    bool normalized, size_t stride, size_t shift) {
	auto loc = glGetAttribLocation(m_id, fieldName.c_str());
	if (loc == -1)
		throw Exceptions::ProgramException("There are no atribute in the Shader with the 'fieldName'.");
	glVertexAttribPointer(loc, (GLint) size, GL_FLOAT, normalized, 
						  (GLsizei) sizeof(float) * (GLsizei) stride, (const void*)shift);
	glEnableVertexAttribArray(loc);
}

mgl::UniformVariable::UniformVariable(std::string name, int location, UniformType type)
	: m_variable_name(name), m_location(location), m_type(type) {}

mgl::UniformVariable::UniformVariable(std::string name, UniformType type)
	: m_variable_name(name), m_type(type) {}
