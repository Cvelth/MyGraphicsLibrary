#pragma once
#include <cstdint>
#define Convertion(enum_name) namespace mgl {\
	enum class enum_name;\
	namespace enum_converter {\
		uint32_t convert(enum_name);\
		enum_name convert_to_##enum_name(uint32_t);\
	}\
}

Convertion(ShaderType);
Convertion(ShaderVariableDataType);

#include "mgl/exceptions.hpp"
DefineNewMGLException(EnumConvertionError);