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
		glGetShaderiv(m_id, GL_INFO_LOG_LENGTH, &len);

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

void mgl::Program::sendUniform(const std::string fieldName, const float & data) {
	auto loc = glGetUniformLocation(m_id, fieldName.c_str());
	if (loc == -1)
		throw Exceptions::ProgramException("The location is not valid.");
	glUniform1f(loc, data);
}

void mgl::Program::sendUniform(const std::string fieldName, const math::Vector & data) {
	auto loc = glGetUniformLocation(m_id, fieldName.c_str());
	if (loc == -1)
		throw Exceptions::ProgramException("The location is not valid.");
	glUniform4f(loc, data.x(),data.y(), data.z(), data.w());
}

void mgl::Program::sendUniform(const std::string fieldName, const math::Matrix & data) {
	auto loc = glGetUniformLocation(m_id, fieldName.c_str());
	if (loc == -1)
		throw Exceptions::ProgramException("The location is not valid.");
	glUniformMatrix4fv(loc, 1, GL_FALSE, data.data());
}

void mgl::Program::enableAttrib(const std::string fieldName, size_t size,
							    bool normalized, size_t stride, size_t shift) {
	auto loc = glGetAttribLocation(m_id, fieldName.c_str());
	if (loc == -1)
		throw Exceptions::ProgramException("The location is not valid.");
	glVertexAttribPointer(loc, (GLint) size, GL_FLOAT, normalized, 
						  (GLsizei) sizeof(float) * (GLsizei) stride, (const void*)shift);
	glEnableVertexAttribArray(loc);
}