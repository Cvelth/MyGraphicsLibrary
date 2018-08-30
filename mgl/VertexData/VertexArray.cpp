#include "mgl/dependencies/OpenGL_Dependency/opengl_dependency.hpp"
#include "VertexArray.hpp"
mgl::MultiVertexArray::MultiVertexArray(size_t number, uint32_t *ids) : m_number(number) {
	m_ids = new uint32_t[number];
	std::copy(ids, ids + number, m_ids);
	for (size_t i = 0; i < number; i++)
		if (m_ids[i] == 0 || !glIsVertexArray(m_ids[i]))
			throw Exceptions::VertexArrayCreationError();
}
mgl::MultiVertexArray::MultiVertexArray(size_t number) : m_number(number) {
	m_ids = new uint32_t[number];
	glGenVertexArrays(GLsizei(number), m_ids);
}
mgl::MultiVertexArray::~MultiVertexArray() {
	if (m_number) delete[] m_ids;
}

#include "mgl/EnumConverter/enum_converter.hpp"
#include "mgl/GlobalStateController/GlobalStateController.hpp"
#include "mgl/ShaderProgram/ShaderVariable.hpp"
void mgl::MultiVertexArray::bind(size_t index) {
	if (index >= m_number) throw Exceptions::MultiVertexArrayIndexOutOfBounds();
	GlobalStateController::bind_vertex_array(this, index);
}
void mgl::MultiVertexArray::attrib_pointer(size_t index, ShaderVariable const& variable, size_t stride, size_t shift) {
	bind(index);
	auto type = enum_converter::convert_variable_type(variable.data_type);
	glVertexAttribPointer(variable.location, GLint(enum_converter::convert_to_number(type.second)), 
						  GLsizei(enum_converter::convert(type.first)), GL_FALSE, GLsizei(stride), (const void*) shift);
	glEnableVertexAttribArray(variable.location);
}
namespace mgl {
	size_t count_size(std::list<ShaderVariable> const& variables) {
		size_t ret = 0u;
		for (auto &it : variables)
			ret += enum_converter::get_size(enum_converter::convert_variable_type(it.data_type).first);
		return ret;
	}
}
void mgl::MultiVertexArray::attrib_pointer(size_t index, std::list<ShaderVariable> const& variables) {
	size_t stride = count_size(variables);
	size_t shift = 0u;
	for (auto &it : variables) {
		attrib_pointer(index, it, stride, shift);
		shift += enum_converter::get_size(enum_converter::convert_variable_type(it.data_type).first);
	}
}
