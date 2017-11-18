#include "MGL\OpenGL\OpenGL_Dependency\OpenGL.h"
#include "EnumsMirror.hpp"

GLenum mgl::switchEnum(BlendEnum e) {
	switch (e) {
		case BlendEnum::Zero: return GL_ZERO;
		case BlendEnum::One: return GL_ONE;
		case BlendEnum::Color_SRC: return GL_SRC_COLOR;
		case BlendEnum::Color_OneMinusSRC: return GL_ONE_MINUS_SRC_COLOR;
		case BlendEnum::Color_DST: return GL_DST_COLOR;
		case BlendEnum::Color_OneMinusDST: return GL_ONE_MINUS_DST_COLOR;
		case BlendEnum::Alpha_SRC: return GL_SRC_ALPHA;
		case BlendEnum::Alpha_OneMinusSRC: return GL_ONE_MINUS_SRC_ALPHA;
		case BlendEnum::Alpha_DST: return GL_DST_ALPHA;
		case BlendEnum::Alpha_OneMinusDST: return GL_ONE_MINUS_DST_ALPHA;
		case BlendEnum::Color_Const: return GL_CONSTANT_COLOR;
		case BlendEnum::Color_OneMinusConst: return GL_ONE_MINUS_CONSTANT_COLOR;
		case BlendEnum::Alpha_Const: return GL_CONSTANT_ALPHA;
		case BlendEnum::Alpha_OneMinusConst: return GL_ONE_MINUS_CONSTANT_ALPHA;
		case BlendEnum::Alpha_SaturateSRC: return GL_SRC_ALPHA_SATURATE;
		case BlendEnum::Color_SRC1: return GL_SRC1_COLOR;
		case BlendEnum::Color_OneMinusSRC1: return GL_ONE_MINUS_SRC1_COLOR;
		case BlendEnum::Alpha_SRC1: return GL_SRC1_ALPHA;
		case BlendEnum::Alpha_OneMinusSRC1: return GL_ONE_MINUS_SRC1_ALPHA;
		default: throw Exceptions::IncorrectEnumException(" ");
	}
}

GLenum mgl::switchEnum(SmoothMode e) {
	switch (e) {
		case SmoothMode::DontCare: return GL_DONT_CARE;
		case SmoothMode::Nicest: return GL_NICEST;
		case SmoothMode::Fastest: return GL_FASTEST;
		default: throw Exceptions::IncorrectEnumException(" ");
	}
}

GLenum mgl::switchEnum(VertexConnectionType e) {
	switch (e) {
		case VertexConnectionType::Points: return GL_POINTS;
		case VertexConnectionType::Lines: return GL_LINES;
		case VertexConnectionType::LineStrip: return GL_LINE_STRIP;
		case VertexConnectionType::LineLoop: return GL_LINE_LOOP;
		case VertexConnectionType::Triangles: return GL_TRIANGLES;
		case VertexConnectionType::TriangleStrip: return GL_TRIANGLE_STRIP;
		case VertexConnectionType::TriangleFan: return GL_TRIANGLE_FAN;
		case VertexConnectionType::Quads: return GL_QUADS;
		case VertexConnectionType::QuadStrip: return GL_QUAD_STRIP;
		case VertexConnectionType::Polygon: return GL_POLYGON;
		default: throw Exceptions::IncorrectEnumException(" ");
	}
}

GLenum mgl::switchEnum(BufferBindingPoint e) {
	switch (e) {
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
		default: throw Exceptions::IncorrectEnumException(" ");
	}
}

GLenum mgl::switchEnum(BufferMappingAccess e) {
	switch (e) {
		case BufferMappingAccess::ReadOnly: return GL_READ_ONLY;
		case BufferMappingAccess::WriteOnly: return GL_WRITE_ONLY;
		case BufferMappingAccess::ReadWrite: return GL_READ_WRITE;
		default: throw Exceptions::IncorrectEnumException(" ");
	}
}

GLenum mgl::switchEnum(DataUsage e) {
	switch (e) {
		case DataUsage::StreamDraw: return GL_STREAM_DRAW;
		case DataUsage::StreamRead: return GL_STREAM_READ;
		case DataUsage::StreamCopy: return GL_STREAM_COPY;
		case DataUsage::StaticDraw: return GL_STATIC_DRAW;
		case DataUsage::StaticRead: return GL_STATIC_READ;
		case DataUsage::StaticCopy: return GL_STATIC_COPY;
		case DataUsage::DynamicDraw: return GL_DYNAMIC_DRAW;
		case DataUsage::DynamicRead: return GL_DYNAMIC_READ;
		case DataUsage::DynamicCopy: return GL_DYNAMIC_COPY;
		default: throw Exceptions::IncorrectEnumException(" ");
	}
}

mgl::ShaderDataType mgl::switchShaderDataType(GLenum e) {
	switch (e) {
		case GL_FLOAT: return mgl::ShaderDataType::Float;
		case GL_FLOAT_VEC2: return mgl::ShaderDataType::Float_2;
		case GL_FLOAT_VEC3: return mgl::ShaderDataType::Float_3;
		case GL_FLOAT_VEC4: return mgl::ShaderDataType::Float_4;

		case GL_DOUBLE: return mgl::ShaderDataType::Double;
		case GL_DOUBLE_VEC2: return mgl::ShaderDataType::Double_2;
		case GL_DOUBLE_VEC3: return mgl::ShaderDataType::Double_3;
		case GL_DOUBLE_VEC4: return mgl::ShaderDataType::Double_4;

		case GL_INT: return mgl::ShaderDataType::Int;
		case GL_INT_VEC2: return mgl::ShaderDataType::Int_2;
		case GL_INT_VEC3: return mgl::ShaderDataType::Int_3;
		case GL_INT_VEC4: return mgl::ShaderDataType::Int_4;

		case GL_UNSIGNED_INT: return mgl::ShaderDataType::UInt;
		case GL_UNSIGNED_INT_VEC2: return mgl::ShaderDataType::UInt_2;
		case GL_UNSIGNED_INT_VEC3: return mgl::ShaderDataType::UInt_3;
		case GL_UNSIGNED_INT_VEC4: return mgl::ShaderDataType::UInt_4;

		case GL_BOOL: return mgl::ShaderDataType::Bool;
		case GL_BOOL_VEC2: return mgl::ShaderDataType::Bool_2;
		case GL_BOOL_VEC3: return mgl::ShaderDataType::Bool_3;
		case GL_BOOL_VEC4: return mgl::ShaderDataType::Bool_4;

		case GL_FLOAT_MAT2: return mgl::ShaderDataType::Float_2x2;
		case GL_FLOAT_MAT3: return mgl::ShaderDataType::Float_3x3;
		case GL_FLOAT_MAT4: return mgl::ShaderDataType::Float_4x4;

		case GL_FLOAT_MAT2x3: return mgl::ShaderDataType::Float_2x3;
		case GL_FLOAT_MAT3x2: return mgl::ShaderDataType::Float_3x2;
		case GL_FLOAT_MAT4x2: return mgl::ShaderDataType::Float_4x2;

		case GL_FLOAT_MAT2x4: return mgl::ShaderDataType::Float_2x4;
		case GL_FLOAT_MAT3x4: return mgl::ShaderDataType::Float_3x4;
		case GL_FLOAT_MAT4x3: return mgl::ShaderDataType::Float_4x3;

		case GL_DOUBLE_MAT2: return mgl::ShaderDataType::Double_2x2;
		case GL_DOUBLE_MAT3: return mgl::ShaderDataType::Double_3x3;
		case GL_DOUBLE_MAT4: return mgl::ShaderDataType::Double_4x4;

		case GL_DOUBLE_MAT2x3: return mgl::ShaderDataType::Double_2x3;
		case GL_DOUBLE_MAT3x2: return mgl::ShaderDataType::Double_3x2;
		case GL_DOUBLE_MAT4x2: return mgl::ShaderDataType::Double_4x2;

		case GL_DOUBLE_MAT2x4: return mgl::ShaderDataType::Double_2x4;
		case GL_DOUBLE_MAT3x4: return mgl::ShaderDataType::Double_3x4;
		case GL_DOUBLE_MAT4x3: return mgl::ShaderDataType::Double_4x3;
		default: throw Exceptions::IncorrectEnumException("Uniform Type is Unsupported.");
	}
}

GLenum mgl::switchEnum(ShaderDataType e) {
	switch (e) {
		case mgl::ShaderDataType::Float: return GL_FLOAT;
		case mgl::ShaderDataType::Float_2: return GL_FLOAT_VEC2;
		case mgl::ShaderDataType::Float_3: return GL_FLOAT_VEC3;
		case mgl::ShaderDataType::Float_4: return GL_FLOAT_VEC4;

		case mgl::ShaderDataType::Double: return GL_DOUBLE;
		case mgl::ShaderDataType::Double_2: return GL_DOUBLE_VEC2;
		case mgl::ShaderDataType::Double_3: return GL_DOUBLE_VEC3;
		case mgl::ShaderDataType::Double_4: return GL_DOUBLE_VEC4;

		case mgl::ShaderDataType::Int: return GL_INT;
		case mgl::ShaderDataType::Int_2: return GL_INT_VEC2;
		case mgl::ShaderDataType::Int_3: return GL_INT_VEC3;
		case mgl::ShaderDataType::Int_4: return GL_INT_VEC4;

		case mgl::ShaderDataType::UInt: return GL_UNSIGNED_INT;
		case mgl::ShaderDataType::UInt_2: return GL_UNSIGNED_INT_VEC2;
		case mgl::ShaderDataType::UInt_3: return GL_UNSIGNED_INT_VEC3;
		case mgl::ShaderDataType::UInt_4: return GL_UNSIGNED_INT_VEC4;

		case mgl::ShaderDataType::Bool: return GL_BOOL;
		case mgl::ShaderDataType::Bool_2: return GL_BOOL_VEC2;
		case mgl::ShaderDataType::Bool_3: return GL_BOOL_VEC3;
		case mgl::ShaderDataType::Bool_4: return GL_BOOL_VEC4;

		case mgl::ShaderDataType::Float_2x2: return GL_FLOAT_MAT2;
		case mgl::ShaderDataType::Float_3x3: return GL_FLOAT_MAT3;
		case mgl::ShaderDataType::Float_4x4: return GL_FLOAT_MAT4;

		case mgl::ShaderDataType::Float_2x3: return GL_FLOAT_MAT2x3;
		case mgl::ShaderDataType::Float_3x2: return GL_FLOAT_MAT3x2;
		case mgl::ShaderDataType::Float_4x2: return GL_FLOAT_MAT4x2;

		case mgl::ShaderDataType::Float_2x4: return GL_FLOAT_MAT2x4;
		case mgl::ShaderDataType::Float_3x4: return GL_FLOAT_MAT3x4;
		case mgl::ShaderDataType::Float_4x3: return GL_FLOAT_MAT4x3;

		case mgl::ShaderDataType::Double_2x2: return GL_DOUBLE_MAT2;
		case mgl::ShaderDataType::Double_3x3: return GL_DOUBLE_MAT3;
		case mgl::ShaderDataType::Double_4x4: return GL_DOUBLE_MAT4;
												  
		case mgl::ShaderDataType::Double_2x3: return GL_DOUBLE_MAT2x3;
		case mgl::ShaderDataType::Double_3x2: return GL_DOUBLE_MAT3x2;
		case mgl::ShaderDataType::Double_4x2: return GL_DOUBLE_MAT4x2;
												  
		case mgl::ShaderDataType::Double_2x4: return GL_DOUBLE_MAT2x4;
		case mgl::ShaderDataType::Double_3x4: return GL_DOUBLE_MAT3x4;
		case mgl::ShaderDataType::Double_4x3: return GL_DOUBLE_MAT4x3;
		default: throw Exceptions::IncorrectEnumException("Uniform Type is Unsupported.");
	}
}
