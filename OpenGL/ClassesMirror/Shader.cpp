#include "MGL\OpenGL\OpenGL_Dependency\OpenGL.h"
#include "Shader.hpp"

mgl::Shader::Shader(ShaderType type) {
	switch (type) {
		case ShaderType::Compute: m_id = glCreateShader(GL_COMPUTE_SHADER); break;
		case ShaderType::Fragment: m_id = glCreateShader(GL_FRAGMENT_SHADER); break;
		case ShaderType::Geometry: m_id = glCreateShader(GL_GEOMETRY_SHADER); break;
		case ShaderType::Vertex: m_id = glCreateShader(GL_VERTEX_SHADER); break;
		case ShaderType::TessControl: m_id = glCreateShader(GL_TESS_CONTROL_SHADER); break;
		case ShaderType::TessEvaluation: m_id = glCreateShader(GL_TESS_EVALUATION_SHADER); break;
	}
}

mgl::Shader::Shader(ShaderType type, const char* filename) : Shader(type) {
	compileFile(filename);
}

mgl::Shader::~Shader() {
	glDeleteShader(m_id);
}

void mgl::Shader::compileFile(const char* filename) {
	compileSource(getShaderSourceFromFile(filename));
}

GLuint mgl::Shader::id() {
	return m_id;
}

mgl::Shader* mgl::Shader::compileShaderSource(ShaderType type, const char* source) {
	mgl::Shader* ret = new mgl::Shader(type);
	ret->compileSource(source);
	return ret;
}

#include <string>
void mgl::Shader::compileSource(const char* sourceText) {
	const GLchar* source = static_cast<const GLchar*>(sourceText);
	if (source == "") throw Exceptions::ShaderException("The source string or file is empty.");

	glShaderSource(m_id, 1, &source, NULL);
	glCompileShader(m_id);

	GLint isCompiled;
	glGetShaderiv(m_id, GL_COMPILE_STATUS, &isCompiled);

	if (!isCompiled) {
		GLsizei len;
		glGetShaderiv(m_id, GL_INFO_LOG_LENGTH, &len);

		GLchar* log = new GLchar[len + 1];
		glGetShaderInfoLog(m_id, len, &len, log);
		throw Exceptions::ShaderException(("Shader compilation error: " + std::string(log)).c_str());
		delete[] log;
	}
}

#include <fstream>
const char* mgl::Shader::getShaderSourceFromFile(const char* filename) {
	return std::string(std::istreambuf_iterator<char>(std::ifstream(filename)), std::istreambuf_iterator<char>()).c_str();
}