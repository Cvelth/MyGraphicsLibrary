#include "OpenGL_Mirror\OpenGL_Dependency\OpenGL.h"
#include "EnumsMirror.hpp"

GLenum mgl::_enumSwitch(BlendEnum e) {
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
		default: throw IncorrectEnumException();
	}
}

GLenum mgl::_enumSwitch(SmoothMode e) {
	switch (e) {
		case SmoothMode::DontCare: return GL_DONT_CARE;
		case SmoothMode::Nicest: return GL_NICEST;
		case SmoothMode::Fastest: return GL_FASTEST;
		default: throw IncorrectEnumException();
	}
}

GLenum mgl::_enumSwitch(VertexConnectionType e) {
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
		default: throw IncorrectEnumException();
	}
}

GLenum mgl::_enumSwitch(BufferBindingPoint e) {
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
		default: throw IncorrectEnumException();
	}
}

GLenum mgl::_enumSwitch(DataUsage e) {
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
		default: throw IncorrectEnumException(	);
	}
}
