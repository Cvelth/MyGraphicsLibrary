#pragma once
typedef unsigned int GLenum;

#include "MGL\SharedHeaders\Exceptions.hpp"
DefineNewMglException(IncorrectEnumException)

namespace mgl {
	enum class OpenGLVersionMask {
		Core, Compatibility, ES
	};
	enum class BlendEnum {
		Zero, One, Color_SRC, Color_OneMinusSRC, Color_DST, Color_OneMinusDST,
		Alpha_SRC, Alpha_OneMinusSRC, Alpha_DST, Alpha_OneMinusDST,	Color_Const, 
		Color_OneMinusConst, Alpha_Const, Alpha_OneMinusConst, Alpha_SaturateSRC, 
		Color_SRC1, Color_OneMinusSRC1, Alpha_SRC1, Alpha_OneMinusSRC1
	};
	GLenum switchEnum(BlendEnum e);

	enum class SmoothMode {
		Nicest, Fastest, DontCare
	};
	GLenum switchEnum(SmoothMode e);
	
	enum class VertexConnectionType {
		Points, Lines, LineStrip, LineLoop, Triangles, TriangleStrip, TriangleFan, Quads, QuadStrip, Polygon
	};
	GLenum switchEnum(VertexConnectionType e);

	enum class BufferBindingPoint {
		ArrayBuffer, AtomicCounterBuffer, CopyReadBuffer, CopyWriteBuffer,
		DispatchIndirectBuffer, DrawIndirectBuffer, ElementArrayBuffer,
		PixelPackBuffer, PixelUnpackBuffer, QueryBuffer, ShaderStorageBuffer,
		TextureBuffer, TransformFeedbackBuffer, UniformBuffer
	};
	GLenum switchEnum(BufferBindingPoint e);

	enum class BufferMappingAccess {
		ReadOnly, WriteOnly, ReadWrite
	};
	GLenum switchEnum(BufferMappingAccess e);

	enum class DataUsage {
		StreamDraw, StreamRead, StreamCopy,
		StaticDraw, StaticRead, StaticCopy,
		DynamicDraw, DynamicRead, DynamicCopy
	};
	GLenum switchEnum(DataUsage e);

	enum class ShaderDataType {
		Float, Float_2, Float_3, Float_4,
		Double, Double_2, Double_3, Double_4,
		Int, Int_2, Int_3, Int_4,
		UInt, UInt_2, UInt_3, UInt_4,
		Bool, Bool_2, Bool_3, Bool_4,
		Float_2x2, Float_3x3, Float_4x4,
		Float_2x3, Float_2x4, Float_3x2,
		Float_3x4, Float_4x2, Float_4x3,
		Double_2x2, Double_3x3, Double_4x4,
		Double_2x3, Double_2x4, Double_3x2,
		Double_3x4, Double_4x2, Double_4x3,
	};
	GLenum switchEnum(ShaderDataType e);
	mgl::ShaderDataType switchShaderDataType(GLenum e);

	enum class ShaderVariableType {
		Attribute, Uniform
	};
	enum class DefaultVertexShaderInput {
		vec4x2, vec4x2_mat4x1, mat4x1, mat4x2, mat4x6
	};
}