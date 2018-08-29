#include "mgl/dependencies/OpenGL_Dependency/opengl_dependency.hpp"
#include "Shader.hpp"
#include "mgl/EnumConverter/enum_converter.hpp"

mgl::Shader::Shader(uint32_t id) : m_id(id) {
	if (m_id == 0)
		throw Exceptions::ShaderCreationError();
}
mgl::Shader::Shader(char const* source, ShaderType type) : Shader(type) {
	compileSource(source);
}
mgl::Shader::Shader(ShaderType type) : m_id(0) {
	try {
		m_id = glCreateShader(enum_converter::convert(type));
	} catch (Exceptions::EnumConvertionError) {
		throw Exceptions::ShaderCreationError();
	}
	if (m_id == 0)
		throw Exceptions::ShaderCreationError();
}
mgl::Shader::Shader(ShaderType type, const char* filename) : Shader(type) {
	compileFile(filename);
}
mgl::Shader::~Shader() {
	glDeleteShader(m_id);
}

GLuint mgl::Shader::id() {
	return m_id;
}
mgl::Shader mgl::Shader::compileShaderSource(ShaderType type, const char* source) {
	return Shader(source, type);
}

#include <string>
void mgl::Shader::compileSource(const char* sourceText) {
	const GLchar* source = static_cast<const GLchar*>(sourceText);
	if (source == "") throw Exceptions::ShaderCompilationError("The source string or file is empty.");

	glShaderSource(m_id, 1, &source, NULL);
	glCompileShader(m_id);

	GLint isCompiled;
	glGetShaderiv(m_id, GL_COMPILE_STATUS, &isCompiled);

	if (!isCompiled) {
		GLsizei len;
		glGetShaderiv(m_id, GL_INFO_LOG_LENGTH, &len);

		GLchar* log = new GLchar[len + 1];
		glGetShaderInfoLog(m_id, len, &len, log);
		throw Exceptions::ShaderCompilationError(("Shader compilation error: " + std::string(log)).c_str());
		delete[] log;
	}
}

#include <fstream>
#include <string>
namespace mgl {
	const char* getShaderSourceFromFile(const char* filename) {
		using namespace std::literals;
		std::ifstream f;
		f.open(filename);
		if (!f)
			throw Exceptions::ShaderCompilationError(("File "s + filename + " cannot be oppened. Make sure it exists.").c_str());
		return std::string(std::istreambuf_iterator<char>(f), std::istreambuf_iterator<char>()).c_str();
	}
}
void mgl::Shader::compileFile(const char* filename) {
	compileSource(getShaderSourceFromFile(filename));
}