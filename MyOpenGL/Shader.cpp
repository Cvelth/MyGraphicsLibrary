#include "Shader.hpp"
#include "OpenGL_header.h"
#include <fstream>

mgl::Shader::Shader(ShaderType type, const std::string& filename) {
	create(type);
	compile(filename);
}

mgl::Shader::~Shader() {
	glDeleteShader(m_id);
}

void mgl::Shader::create(ShaderType type) {
	switch (type) {
		case ShaderType::Compute: m_id = glCreateShader(GL_COMPUTE_SHADER);
		case ShaderType::Fragment: m_id = glCreateShader(GL_FRAGMENT_SHADER);
		case ShaderType::Geometry: m_id = glCreateShader(GL_GEOMETRY_SHADER);
		case ShaderType::Vertex: m_id = glCreateShader(GL_VERTEX_SHADER);
		case ShaderType::TessControl: m_id = glCreateShader(GL_TESS_CONTROL_SHADER);
		case ShaderType::TessEvaluation: m_id = glCreateShader(GL_TESS_EVALUATION_SHADER);
	}
}

void mgl::Shader::compile(const std::string& filename) {
	std::string s = std::string(std::istreambuf_iterator<char>(std::ifstream(filename)), std::istreambuf_iterator<char>());
	const GLchar* source = static_cast<const GLchar*>(s.c_str());
	if (source == "") throw ShaderException("The source file is empty.");

	const size_t t = (s.size());
	glShaderSource(m_id, 1, &source, NULL);
	glCompileShader(m_id);

	GLint isCompiled;
	glGetShaderiv(m_id, GL_COMPILE_STATUS, &isCompiled);

	if (!isCompiled) {
		GLsizei len;
		glGetShaderiv(m_id, GL_INFO_LOG_LENGTH, &len);

		GLchar* log = new GLchar[len + 1];
		glGetShaderInfoLog(m_id, len, &len, log);
		std::string t = std::string(log);
		delete[] log;

		throw ShaderException(std::string("Shader compilation error: ") + t);
	}
}

GLuint mgl::Shader::id() {
	return m_id;
}
