#include "enum_converter.hpp"
#include "mgl/dependencies/OpenGL_Dependency/opengl_dependency.hpp"

#include "mgl/ShaderProgram/Shader.hpp"
uint32_t mgl::enum_converter::convert(ShaderType v) {
	switch (v) {
		case ShaderType::Compute: return GL_COMPUTE_SHADER;
		case ShaderType::Fragment: return GL_FRAGMENT_SHADER;
		case ShaderType::Geometry: return GL_GEOMETRY_SHADER;
		case ShaderType::Vertex: return GL_VERTEX_SHADER;
		case ShaderType::TesselationControl: return GL_TESS_CONTROL_SHADER;
		case ShaderType::TesselationEvaluation: return GL_TESS_EVALUATION_SHADER;
		default: throw Exceptions::EnumConvertionError();
	}
}
mgl::ShaderType mgl::enum_converter::convert(uint32_t v) {
	switch (v) {
		case GL_COMPUTE_SHADER: return ShaderType::Compute;
		case GL_FRAGMENT_SHADER: return ShaderType::Fragment;
		case GL_GEOMETRY_SHADER: return ShaderType::Geometry;
		case GL_VERTEX_SHADER: return ShaderType::Vertex;
		case GL_TESS_CONTROL_SHADER: return ShaderType::TesselationControl;
		case GL_TESS_EVALUATION_SHADER: return ShaderType::TesselationEvaluation;
		default: throw Exceptions::EnumConvertionError();
	}
}