#pragma once
#include <cstdint>
#define Convertion(enum_name) namespace mgl {\
	enum class enum_name;\
	namespace enum_converter {\
		uint32_t convert(enum_name);\
		enum_name convert(uint32_t);\
	}\
}

Convertion(ShaderType);

#include "mgl/exceptions.hpp"
DefineNewMGLException(EnumConvertionError);