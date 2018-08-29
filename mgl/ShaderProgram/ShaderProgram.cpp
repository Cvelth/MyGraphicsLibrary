#include "mgl/dependencies/OpenGL_Dependency/opengl_dependency.hpp"
#include "ShaderProgram.hpp"
#include "Shader.hpp"
#include "ShaderVariable.hpp"
mgl::ShaderProgram::ShaderProgram(uint32_t id) : m_is_linked(false), m_id(id) {
	if (m_id == 0 || !glIsProgram(m_id)) throw Exceptions::ProgramCreationError();
}
mgl::ShaderProgram::ShaderProgram() : ShaderProgram(glCreateProgram()) {}
mgl::ShaderProgram::ShaderProgram(std::initializer_list<Shader> const& list) : ShaderProgram() {
	link(list);
}
mgl::ShaderProgram::~ShaderProgram() {
	glDeleteProgram(m_id);
}

void mgl::ShaderProgram::link(std::initializer_list<Shader> const& shaders) {
	if (shaders.size() == 0u)
		throw Exceptions::ProgramLinkageError("There are no shaders to attach.");

	for (auto &shader : shaders)
		glAttachShader(m_id, shader.m_id);

	glLinkProgram(m_id);

	GLint isLinked;
	glGetProgramiv(m_id, GL_LINK_STATUS, &isLinked);
	if (!isLinked) {
		GLsizei len;
		glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &len);

		GLchar* log = new GLchar[len + 1];
		glGetProgramInfoLog(m_id, len, &len, log);
		throw Exceptions::ProgramLinkageError(("Program linking error: " + std::string(log)).c_str());
		delete[] log;
	}
	m_is_linked = true;
}
bool mgl::ShaderProgram::is_linked() const {
	if (m_is_linked)
		return true;
	else if (glIsProgram(m_id)) {
		GLint isLinked;
		glGetProgramiv(m_id, GL_LINK_STATUS, &isLinked);
		return m_is_linked = bool(isLinked);
	} else
		return false;
}

#include "mgl/EnumConverter/enum_converter.hpp"
namespace mgl {
	template<typename Lambda>
	std::list<ShaderVariable> get(uint32_t id, GLenum a_type, GLenum type_length, Lambda lambda, ShaderVariableType v_type) {
		GLint number, max_length, name_length, size;
		GLenum type;
		GLchar *name;

		std::list<ShaderVariable> ret;

		glGetProgramiv(id, a_type, &number);
		glGetProgramiv(id, type_length, &max_length);
		for (int i = 0; i < number; i++) {
			name = new GLchar[max_length];
			lambda(id, i, max_length, &name_length, &size, &type, name);
			ret.push_back(ShaderVariable(name, v_type, i, enum_converter::convert_to_ShaderVariableDataType(type)));
		}
		return std::move(ret);
	}
}
std::list<mgl::ShaderVariable> mgl::ShaderProgram::getUniforms() {
	return mgl::get(m_id, GL_ACTIVE_UNIFORMS, GL_ACTIVE_UNIFORM_MAX_LENGTH, glGetActiveUniform, ShaderVariableType::Uniform);
}
std::list<mgl::ShaderVariable> mgl::ShaderProgram::getAttributes() {
	return mgl::get(m_id, GL_ACTIVE_ATTRIBUTES, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, glGetActiveAttrib, ShaderVariableType::Attribute);
}
#include <algorithm>
std::list<mgl::ShaderVariable> mgl::ShaderProgram::getVariables() {
	std::list<ShaderVariable> ret{getUniforms()};
	auto temp = getAttributes();
	std::move(temp.begin(), temp.end(), std::back_inserter(ret));
	return ret;
}

#include "mgl/GlobalStateController/GlobalStateController.hpp"
void mgl::ShaderProgram::use() {
	GlobalStateController::use_shader_program(this);
}