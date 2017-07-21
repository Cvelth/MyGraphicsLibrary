#pragma once

typedef unsigned int GLenum;

namespace mgl {
	class IncorrectEnumException {};
	enum class OpenGLVersionMask {
		Core, Compatibility, ES
	};
	enum class BlendEnum {
		Zero, One, Color_SRC, Color_OneMinusSRC, Color_DST, Color_OneMinusDST,
		Alpha_SRC, Alpha_OneMinusSRC, Alpha_DST, Alpha_OneMinusDST,	Color_Const, 
		Color_OneMinusConst, Alpha_Const, Alpha_OneMinusConst, Alpha_SaturateSRC, 
		Color_SRC1, Color_OneMinusSRC1, Alpha_SRC1, Alpha_OneMinusSRC1
	};
	GLenum _enumSwitch(BlendEnum e);

	enum class SmoothMode {
		Nicest, Fastest, DontCare
	};
	GLenum _enumSwitch(SmoothMode e);
	
	enum class VertexConnectionType {
		Points, Lines, LineStrip, LineLoop, Triangles, TriangleStrip, TriangleFan, Quads, QuadStrip, Polygon
	};
	GLenum _enumSwitch(VertexConnectionType e);

	enum class BufferBindingPoint {
		ArrayBuffer, AtomicCounterBuffer, CopyReadBuffer, CopyWriteBuffer,
		DispatchIndirectBuffer, DrawIndirectBuffer, ElementArrayBuffer,
		PixelPackBuffer, PixelUnpackBuffer, QueryBuffer, ShaderStorageBuffer,
		TextureBuffer, TransformFeedbackBuffer, UniformBuffer
	};
	GLenum _enumSwitch(BufferBindingPoint e);

	enum class DataUsage {
		StreamDraw, StreamRead, StreamCopy,
		StaticDraw, StaticRead, StaticCopy,
		DynamicDraw, DynamicRead, DynamicCopy
	};
	GLenum _enumSwitch(DataUsage e);
}