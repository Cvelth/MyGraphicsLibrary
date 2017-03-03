#include "Program.hpp"
#include "OpenGL_header.h"
#include "Matrix.hpp"

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
		throw ProgramException("There is no shaders to attach");

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

		throw ProgramException(std::string("Program linking error: ") + t);
	}
}

void mgl::Program::use() {
	glUseProgram(m_id);
}

void mgl::Program::send(const std::string fieldName, const float & data) {
	auto loc = glGetUniformLocation(m_id, fieldName.c_str());
	if (loc == -1)
		throw ProgramException("The location is not valid.");
	glUniform1f(loc, data);
}

void mgl::Program::send(const std::string fieldName, const Vector & data) {
	auto loc = glGetUniformLocation(m_id, fieldName.c_str());
	if (loc == -1)
		throw ProgramException("The location is not valid.");
	glUniform4f(loc, data.x(),data.y(), data.z(), data.w());
}

void mgl::Program::send(const std::string fieldName, const Matrix & data) {
	auto loc = glGetUniformLocation(m_id, fieldName.c_str());
	if (loc == -1)
		throw ProgramException("The location is not valid.");
	glUniformMatrix4fv(loc, 1, GL_FALSE, data.data());
}
