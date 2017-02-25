#include "OpenGL_header.h"
#include "FunctionEnums.hpp"

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
	}
}

GLenum mgl::_enumSwitch(SmoothMode e) {
	switch (e) {
		case SmoothMode::DontCare: return GL_DONT_CARE;
		case SmoothMode::Nicest: return GL_NICEST;
		case SmoothMode::Fastest: return GL_FASTEST;
	}
}
