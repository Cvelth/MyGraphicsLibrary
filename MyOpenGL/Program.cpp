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

void mgl::Program::link(const std::initializer_list<Shader>& list) {
	if (list.size() == 0u)
		throw ProgramException("There is no shaders to attach");

	for (auto shader : list)
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
	GLuint temp = glGetUniformLocation(m_id, fieldName.c_str());
	glUniform1f(temp, data);
}

void mgl::Program::send(const std::string fieldName, const Vector & data) {
	GLuint temp = glGetUniformLocation(m_id, fieldName.c_str());
	glUniform4f(temp, data.x(),data.y(), data.z(), data.w());
}

void mgl::Program::send(const std::string fieldName, const Matrix & data) {
	GLuint temp = glGetUniformLocation(m_id, fieldName.c_str());
	glUniformMatrix4fv(temp, 1, GL_FALSE, data.data()[0]);
}
