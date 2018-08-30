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
GLenum mgl::enum_converter::convert(ShaderVariableDataType v) {
	switch (v) {
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
mgl::ShaderVariableDataType mgl::enum_converter::convert_to_ShaderVariableDataType(GLenum v) {
	switch (v) {
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

uint32_t mgl::enum_converter::convert(ShaderVariableNonArrayDataType v) {
	switch (v) {
		case ShaderVariableNonArrayDataType::Float: return GL_FLOAT;
		case ShaderVariableNonArrayDataType::Double: return GL_DOUBLE;
		case ShaderVariableNonArrayDataType::Int: return GL_INT;
		case ShaderVariableNonArrayDataType::UInt: return GL_UNSIGNED_INT;
		case ShaderVariableNonArrayDataType::Bool: return GL_BOOL;
		default: throw Exceptions::EnumConvertionError();
	}
}
mgl::ShaderVariableNonArrayDataType mgl::enum_converter::convert_to_ShaderVariableNonArrayDataType(uint32_t v) {
	switch (v) {
		case GL_FLOAT: return ShaderVariableNonArrayDataType::Float;
		case GL_DOUBLE: return ShaderVariableNonArrayDataType::Double;
		case GL_INT: return ShaderVariableNonArrayDataType::Int;
		case GL_UNSIGNED_INT: return ShaderVariableNonArrayDataType::UInt;
		case GL_BOOL: return ShaderVariableNonArrayDataType::Bool;
		default: throw Exceptions::EnumConvertionError();
	}
}

#include "mgl/VertexData/Buffer.hpp"
GLenum mgl::enum_converter::convert(BufferBindingPoint v) {
	switch (v) {
		case BufferBindingPoint::ArrayBuffer: return GL_ARRAY_BUFFER;
		case BufferBindingPoint::AtomicCounterBuffer: return GL_ATOMIC_COUNTER_BUFFER;
		case BufferBindingPoint::CopyReadBuffer: return GL_COPY_READ_BUFFER;
		case BufferBindingPoint::CopyWriteBuffer: return GL_COPY_WRITE_BUFFER;
		case BufferBindingPoint::DispatchIndirectBuffer: return GL_DISPATCH_INDIRECT_BUFFER;
		case BufferBindingPoint::DrawIndirectBuffer: return GL_DRAW_INDIRECT_BUFFER;
		case BufferBindingPoint::ElementArrayBuffer: return GL_ELEMENT_ARRAY_BUFFER;
		case BufferBindingPoint::PixelPackBuffer: return GL_PIXEL_PACK_BUFFER;
		case BufferBindingPoint::PixelUnpackBuffer: return GL_PIXEL_UNPACK_BUFFER;
		case BufferBindingPoint::QueryBuffer: return GL_QUERY_BUFFER;
		case BufferBindingPoint::ShaderStorageBuffer: return GL_SHADER_STORAGE_BUFFER;
		case BufferBindingPoint::TextureBuffer: return GL_TEXTURE_BUFFER;
		case BufferBindingPoint::TransformFeedbackBuffer: return GL_TRANSFORM_FEEDBACK_BUFFER;
		case BufferBindingPoint::UniformBuffer: return GL_UNIFORM_BUFFER;
		default: throw Exceptions::EnumConvertionError();
	}
}
mgl::BufferBindingPoint mgl::enum_converter::convert_to_BufferBindingPoint(GLenum v) {
	switch (v) {
		case GL_ARRAY_BUFFER: return BufferBindingPoint::ArrayBuffer;
		case GL_ATOMIC_COUNTER_BUFFER: return BufferBindingPoint::AtomicCounterBuffer;
		case GL_COPY_READ_BUFFER: return BufferBindingPoint::CopyReadBuffer;
		case GL_COPY_WRITE_BUFFER: return BufferBindingPoint::CopyWriteBuffer;
		case GL_DISPATCH_INDIRECT_BUFFER: return BufferBindingPoint::DispatchIndirectBuffer;
		case GL_DRAW_INDIRECT_BUFFER: return BufferBindingPoint::DrawIndirectBuffer;
		case GL_ELEMENT_ARRAY_BUFFER: return BufferBindingPoint::ElementArrayBuffer;
		case GL_PIXEL_PACK_BUFFER: return BufferBindingPoint::PixelPackBuffer;
		case GL_PIXEL_UNPACK_BUFFER: return BufferBindingPoint::PixelUnpackBuffer;
		case GL_QUERY_BUFFER: return BufferBindingPoint::QueryBuffer;
		case GL_SHADER_STORAGE_BUFFER: return BufferBindingPoint::ShaderStorageBuffer;
		case GL_TEXTURE_BUFFER: return BufferBindingPoint::TextureBuffer;
		case GL_TRANSFORM_FEEDBACK_BUFFER: return BufferBindingPoint::TransformFeedbackBuffer;
		case GL_UNIFORM_BUFFER: return BufferBindingPoint::UniformBuffer;
		default: throw Exceptions::EnumConvertionError();
	}
}

GLenum mgl::enum_converter::convert(BufferMappedAccess v) {
	switch (v) {
		case BufferMappedAccess::ReadOnly: return GL_READ_ONLY;
		case BufferMappedAccess::WriteOnly: return GL_WRITE_ONLY;
		case BufferMappedAccess::ReadWrite: return GL_READ_WRITE;
		default: throw Exceptions::EnumConvertionError();
	}
}
mgl::BufferMappedAccess mgl::enum_converter::convert_to_BufferMappedAccess(GLenum v) {
	switch (v) {
		case GL_READ_ONLY: return BufferMappedAccess::ReadOnly;
		case GL_WRITE_ONLY: return BufferMappedAccess::WriteOnly;
		case GL_READ_WRITE: return BufferMappedAccess::ReadWrite;
		default: throw Exceptions::EnumConvertionError();
	}
}

GLenum mgl::enum_converter::convert(BufferDataUsage v) {
	switch (v) {
		case BufferDataUsage::StreamDraw: return GL_STREAM_DRAW;
		case BufferDataUsage::StreamRead: return GL_STREAM_READ;
		case BufferDataUsage::StreamCopy: return GL_STREAM_COPY;
		case BufferDataUsage::StaticDraw: return GL_STATIC_DRAW;
		case BufferDataUsage::StaticRead: return GL_STATIC_READ;
		case BufferDataUsage::StaticCopy: return GL_STATIC_COPY;
		case BufferDataUsage::DynamicDraw: return GL_DYNAMIC_DRAW;
		case BufferDataUsage::DynamicRead: return GL_DYNAMIC_READ;
		case BufferDataUsage::DynamicCopy: return GL_DYNAMIC_COPY;
		default: throw Exceptions::EnumConvertionError();
	}
}
mgl::BufferDataUsage mgl::enum_converter::convert_to_BufferDataUsage(GLenum v) {
	switch (v) {
		case GL_STREAM_DRAW: return BufferDataUsage::StreamDraw;
		case GL_STREAM_READ: return BufferDataUsage::StreamRead;
		case GL_STREAM_COPY: return BufferDataUsage::StreamCopy;
		case GL_STATIC_DRAW: return BufferDataUsage::StaticDraw;
		case GL_STATIC_READ: return BufferDataUsage::StaticRead;
		case GL_STATIC_COPY: return BufferDataUsage::StaticCopy;
		case GL_DYNAMIC_DRAW: return BufferDataUsage::DynamicDraw;
		case GL_DYNAMIC_READ: return BufferDataUsage::DynamicRead;
		case GL_DYNAMIC_COPY: return BufferDataUsage::DynamicCopy;
		default: throw Exceptions::EnumConvertionError();
	}
}

#include "mgl/VertexData/VertexArray.hpp"
GLenum mgl::enum_converter::convert(VertexConnectionType v) {
	switch (v) {
		case VertexConnectionType::Points:				return GL_POINTS;
		case VertexConnectionType::Lines:				return GL_LINES;
		case VertexConnectionType::LineStrip:			return GL_LINE_STRIP;
		case VertexConnectionType::LineLoop:			return GL_LINE_LOOP;
		case VertexConnectionType::Triangles:			return GL_TRIANGLES;
		case VertexConnectionType::TriangleStrip:		return GL_TRIANGLE_STRIP;
		case VertexConnectionType::TriangleFan:			return GL_TRIANGLE_FAN;
		case VertexConnectionType::Quads:				return GL_QUADS;
		case VertexConnectionType::QuadStrip:			return GL_QUAD_STRIP;
		case VertexConnectionType::Polygon:				return GL_POLYGON;
		default: throw Exceptions::EnumConvertionError();
	}
}
mgl::VertexConnectionType mgl::enum_converter::convert_to_VertexConnectionType(GLenum v) {
	switch (v) {
		case GL_POINTS: return VertexConnectionType::Points;
		case GL_LINES: return VertexConnectionType::Lines;
		case GL_LINE_STRIP: return VertexConnectionType::LineStrip;
		case GL_LINE_LOOP: return VertexConnectionType::LineLoop;
		case GL_TRIANGLES: return VertexConnectionType::Triangles;
		case GL_TRIANGLE_STRIP: return VertexConnectionType::TriangleStrip;
		case GL_TRIANGLE_FAN:  return VertexConnectionType::TriangleFan;
		case GL_QUADS:  return VertexConnectionType::Quads;
		case GL_QUAD_STRIP:  return VertexConnectionType::QuadStrip;
		case GL_POLYGON:  return VertexConnectionType::Polygon;
		default: throw Exceptions::EnumConvertionError();
	}
}