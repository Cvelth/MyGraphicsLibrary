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
mgl::ShaderType mgl::enum_converter::convert_to_ShaderType(uint32_t v) {
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

#include "mgl/ShaderProgram/ShaderVariable.hpp"
GLenum mgl::enum_converter::convert(ShaderVariableDataType e) {
	switch (e) {
		case mgl::ShaderVariableDataType::Float: return GL_FLOAT;
		case mgl::ShaderVariableDataType::Float_2: return GL_FLOAT_VEC2;
		case mgl::ShaderVariableDataType::Float_3: return GL_FLOAT_VEC3;
		case mgl::ShaderVariableDataType::Float_4: return GL_FLOAT_VEC4;

		case mgl::ShaderVariableDataType::Double: return GL_DOUBLE;
		case mgl::ShaderVariableDataType::Double_2: return GL_DOUBLE_VEC2;
		case mgl::ShaderVariableDataType::Double_3: return GL_DOUBLE_VEC3;
		case mgl::ShaderVariableDataType::Double_4: return GL_DOUBLE_VEC4;

		case mgl::ShaderVariableDataType::Int: return GL_INT;
		case mgl::ShaderVariableDataType::Int_2: return GL_INT_VEC2;
		case mgl::ShaderVariableDataType::Int_3: return GL_INT_VEC3;
		case mgl::ShaderVariableDataType::Int_4: return GL_INT_VEC4;

		case mgl::ShaderVariableDataType::UInt: return GL_UNSIGNED_INT;
		case mgl::ShaderVariableDataType::UInt_2: return GL_UNSIGNED_INT_VEC2;
		case mgl::ShaderVariableDataType::UInt_3: return GL_UNSIGNED_INT_VEC3;
		case mgl::ShaderVariableDataType::UInt_4: return GL_UNSIGNED_INT_VEC4;

		case mgl::ShaderVariableDataType::Bool: return GL_BOOL;
		case mgl::ShaderVariableDataType::Bool_2: return GL_BOOL_VEC2;
		case mgl::ShaderVariableDataType::Bool_3: return GL_BOOL_VEC3;
		case mgl::ShaderVariableDataType::Bool_4: return GL_BOOL_VEC4;

		case mgl::ShaderVariableDataType::Float_2x2: return GL_FLOAT_MAT2;
		case mgl::ShaderVariableDataType::Float_3x3: return GL_FLOAT_MAT3;
		case mgl::ShaderVariableDataType::Float_4x4: return GL_FLOAT_MAT4;

		case mgl::ShaderVariableDataType::Float_2x3: return GL_FLOAT_MAT2x3;
		case mgl::ShaderVariableDataType::Float_3x2: return GL_FLOAT_MAT3x2;
		case mgl::ShaderVariableDataType::Float_4x2: return GL_FLOAT_MAT4x2;

		case mgl::ShaderVariableDataType::Float_2x4: return GL_FLOAT_MAT2x4;
		case mgl::ShaderVariableDataType::Float_3x4: return GL_FLOAT_MAT3x4;
		case mgl::ShaderVariableDataType::Float_4x3: return GL_FLOAT_MAT4x3;

		case mgl::ShaderVariableDataType::Double_2x2: return GL_DOUBLE_MAT2;
		case mgl::ShaderVariableDataType::Double_3x3: return GL_DOUBLE_MAT3;
		case mgl::ShaderVariableDataType::Double_4x4: return GL_DOUBLE_MAT4;

		case mgl::ShaderVariableDataType::Double_2x3: return GL_DOUBLE_MAT2x3;
		case mgl::ShaderVariableDataType::Double_3x2: return GL_DOUBLE_MAT3x2;
		case mgl::ShaderVariableDataType::Double_4x2: return GL_DOUBLE_MAT4x2;

		case mgl::ShaderVariableDataType::Double_2x4: return GL_DOUBLE_MAT2x4;
		case mgl::ShaderVariableDataType::Double_3x4: return GL_DOUBLE_MAT3x4;
		case mgl::ShaderVariableDataType::Double_4x3: return GL_DOUBLE_MAT4x3;
		default: throw Exceptions::EnumConvertionError();
	}
}
mgl::ShaderVariableDataType mgl::enum_converter::convert_to_ShaderVariableDataType(GLenum e) {
	switch (e) {
		case GL_FLOAT: return mgl::ShaderVariableDataType::Float;
		case GL_FLOAT_VEC2: return mgl::ShaderVariableDataType::Float_2;
		case GL_FLOAT_VEC3: return mgl::ShaderVariableDataType::Float_3;
		case GL_FLOAT_VEC4: return mgl::ShaderVariableDataType::Float_4;

		case GL_DOUBLE: return mgl::ShaderVariableDataType::Double;
		case GL_DOUBLE_VEC2: return mgl::ShaderVariableDataType::Double_2;
		case GL_DOUBLE_VEC3: return mgl::ShaderVariableDataType::Double_3;
		case GL_DOUBLE_VEC4: return mgl::ShaderVariableDataType::Double_4;

		case GL_INT: return mgl::ShaderVariableDataType::Int;
		case GL_INT_VEC2: return mgl::ShaderVariableDataType::Int_2;
		case GL_INT_VEC3: return mgl::ShaderVariableDataType::Int_3;
		case GL_INT_VEC4: return mgl::ShaderVariableDataType::Int_4;

		case GL_UNSIGNED_INT: return mgl::ShaderVariableDataType::UInt;
		case GL_UNSIGNED_INT_VEC2: return mgl::ShaderVariableDataType::UInt_2;
		case GL_UNSIGNED_INT_VEC3: return mgl::ShaderVariableDataType::UInt_3;
		case GL_UNSIGNED_INT_VEC4: return mgl::ShaderVariableDataType::UInt_4;

		case GL_BOOL: return mgl::ShaderVariableDataType::Bool;
		case GL_BOOL_VEC2: return mgl::ShaderVariableDataType::Bool_2;
		case GL_BOOL_VEC3: return mgl::ShaderVariableDataType::Bool_3;
		case GL_BOOL_VEC4: return mgl::ShaderVariableDataType::Bool_4;

		case GL_FLOAT_MAT2: return mgl::ShaderVariableDataType::Float_2x2;
		case GL_FLOAT_MAT3: return mgl::ShaderVariableDataType::Float_3x3;
		case GL_FLOAT_MAT4: return mgl::ShaderVariableDataType::Float_4x4;

		case GL_FLOAT_MAT2x3: return mgl::ShaderVariableDataType::Float_2x3;
		case GL_FLOAT_MAT3x2: return mgl::ShaderVariableDataType::Float_3x2;
		case GL_FLOAT_MAT4x2: return mgl::ShaderVariableDataType::Float_4x2;

		case GL_FLOAT_MAT2x4: return mgl::ShaderVariableDataType::Float_2x4;
		case GL_FLOAT_MAT3x4: return mgl::ShaderVariableDataType::Float_3x4;
		case GL_FLOAT_MAT4x3: return mgl::ShaderVariableDataType::Float_4x3;

		case GL_DOUBLE_MAT2: return mgl::ShaderVariableDataType::Double_2x2;
		case GL_DOUBLE_MAT3: return mgl::ShaderVariableDataType::Double_3x3;
		case GL_DOUBLE_MAT4: return mgl::ShaderVariableDataType::Double_4x4;

		case GL_DOUBLE_MAT2x3: return mgl::ShaderVariableDataType::Double_2x3;
		case GL_DOUBLE_MAT3x2: return mgl::ShaderVariableDataType::Double_3x2;
		case GL_DOUBLE_MAT4x2: return mgl::ShaderVariableDataType::Double_4x2;

		case GL_DOUBLE_MAT2x4: return mgl::ShaderVariableDataType::Double_2x4;
		case GL_DOUBLE_MAT3x4: return mgl::ShaderVariableDataType::Double_3x4;
		case GL_DOUBLE_MAT4x3: return mgl::ShaderVariableDataType::Double_4x3;
		default: throw Exceptions::EnumConvertionError();
	}
}
