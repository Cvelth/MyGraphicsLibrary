#include "ShaderVariable.hpp"
namespace mgl {
	namespace enum_converter {
		std::pair<size_t, size_t> convert_to_numbers(ShaderVariableArrayType const& v);
		size_t get_size(ShaderVariableNonArrayDataType const& v);
	}
}
std::pair<size_t, size_t> mgl::ShaderVariable::dimention_sizes() const {
	return enum_converter::convert_to_numbers(enum_converter::convert_variable_type(data_type).second);
}
size_t mgl::ShaderVariable::type_size() const {
	return enum_converter::get_size(enum_converter::convert_variable_type(data_type).first);
}

#include "mgl/EnumConverter/enum_converter.hpp"
std::pair<mgl::ShaderVariableNonArrayDataType, mgl::ShaderVariableArrayType> mgl::enum_converter::convert_variable_type(ShaderVariableDataType const& v) {
	switch (v) {
		case ShaderVariableDataType::Float:   return std::make_pair(ShaderVariableNonArrayDataType::Float, ShaderVariableArrayType::_1);
		case ShaderVariableDataType::Float_2: return std::make_pair(ShaderVariableNonArrayDataType::Float, ShaderVariableArrayType::_2);
		case ShaderVariableDataType::Float_3: return std::make_pair(ShaderVariableNonArrayDataType::Float, ShaderVariableArrayType::_3);
		case ShaderVariableDataType::Float_4: return std::make_pair(ShaderVariableNonArrayDataType::Float, ShaderVariableArrayType::_4);

		case ShaderVariableDataType::Double:   return std::make_pair(ShaderVariableNonArrayDataType::Double, ShaderVariableArrayType::_1);
		case ShaderVariableDataType::Double_2: return std::make_pair(ShaderVariableNonArrayDataType::Double, ShaderVariableArrayType::_2);
		case ShaderVariableDataType::Double_3: return std::make_pair(ShaderVariableNonArrayDataType::Double, ShaderVariableArrayType::_3);
		case ShaderVariableDataType::Double_4: return std::make_pair(ShaderVariableNonArrayDataType::Double, ShaderVariableArrayType::_4);

		case ShaderVariableDataType::Int:   return std::make_pair(ShaderVariableNonArrayDataType::Int, ShaderVariableArrayType::_1);
		case ShaderVariableDataType::Int_2: return std::make_pair(ShaderVariableNonArrayDataType::Int, ShaderVariableArrayType::_2);
		case ShaderVariableDataType::Int_3: return std::make_pair(ShaderVariableNonArrayDataType::Int, ShaderVariableArrayType::_3);
		case ShaderVariableDataType::Int_4: return std::make_pair(ShaderVariableNonArrayDataType::Int, ShaderVariableArrayType::_4);

		case ShaderVariableDataType::UInt:   return std::make_pair(ShaderVariableNonArrayDataType::UInt, ShaderVariableArrayType::_1);
		case ShaderVariableDataType::UInt_2: return std::make_pair(ShaderVariableNonArrayDataType::UInt, ShaderVariableArrayType::_2);
		case ShaderVariableDataType::UInt_3: return std::make_pair(ShaderVariableNonArrayDataType::UInt, ShaderVariableArrayType::_3);
		case ShaderVariableDataType::UInt_4: return std::make_pair(ShaderVariableNonArrayDataType::UInt, ShaderVariableArrayType::_4);

		case ShaderVariableDataType::Bool:   return std::make_pair(ShaderVariableNonArrayDataType::Bool, ShaderVariableArrayType::_1);
		case ShaderVariableDataType::Bool_2: return std::make_pair(ShaderVariableNonArrayDataType::Bool, ShaderVariableArrayType::_2);
		case ShaderVariableDataType::Bool_3: return std::make_pair(ShaderVariableNonArrayDataType::Bool, ShaderVariableArrayType::_3);
		case ShaderVariableDataType::Bool_4: return std::make_pair(ShaderVariableNonArrayDataType::Bool, ShaderVariableArrayType::_4);

		case ShaderVariableDataType::Float_2x2: return std::make_pair(ShaderVariableNonArrayDataType::Float, ShaderVariableArrayType::_2x2);
		case ShaderVariableDataType::Float_3x3: return std::make_pair(ShaderVariableNonArrayDataType::Float, ShaderVariableArrayType::_3x3);
		case ShaderVariableDataType::Float_4x4: return std::make_pair(ShaderVariableNonArrayDataType::Float, ShaderVariableArrayType::_4x4);

		case ShaderVariableDataType::Float_2x3: return std::make_pair(ShaderVariableNonArrayDataType::Float, ShaderVariableArrayType::_2x3);
		case ShaderVariableDataType::Float_3x2: return std::make_pair(ShaderVariableNonArrayDataType::Float, ShaderVariableArrayType::_3x2);
		case ShaderVariableDataType::Float_4x2: return std::make_pair(ShaderVariableNonArrayDataType::Float, ShaderVariableArrayType::_4x2);

		case ShaderVariableDataType::Float_2x4: return std::make_pair(ShaderVariableNonArrayDataType::Float, ShaderVariableArrayType::_2x4);
		case ShaderVariableDataType::Float_3x4: return std::make_pair(ShaderVariableNonArrayDataType::Float, ShaderVariableArrayType::_3x4);
		case ShaderVariableDataType::Float_4x3: return std::make_pair(ShaderVariableNonArrayDataType::Float, ShaderVariableArrayType::_4x3);

		case ShaderVariableDataType::Double_2x2: return std::make_pair(ShaderVariableNonArrayDataType::Double, ShaderVariableArrayType::_2x2);
		case ShaderVariableDataType::Double_3x3: return std::make_pair(ShaderVariableNonArrayDataType::Double, ShaderVariableArrayType::_3x3);
		case ShaderVariableDataType::Double_4x4: return std::make_pair(ShaderVariableNonArrayDataType::Double, ShaderVariableArrayType::_4x4);
																									   
		case ShaderVariableDataType::Double_2x3: return std::make_pair(ShaderVariableNonArrayDataType::Double, ShaderVariableArrayType::_2x3);
		case ShaderVariableDataType::Double_3x2: return std::make_pair(ShaderVariableNonArrayDataType::Double, ShaderVariableArrayType::_3x2);
		case ShaderVariableDataType::Double_4x2: return std::make_pair(ShaderVariableNonArrayDataType::Double, ShaderVariableArrayType::_4x2);
																									   
		case ShaderVariableDataType::Double_2x4: return std::make_pair(ShaderVariableNonArrayDataType::Double, ShaderVariableArrayType::_2x4);
		case ShaderVariableDataType::Double_3x4: return std::make_pair(ShaderVariableNonArrayDataType::Double, ShaderVariableArrayType::_3x4);
		case ShaderVariableDataType::Double_4x3: return std::make_pair(ShaderVariableNonArrayDataType::Double, ShaderVariableArrayType::_4x3);
		default: throw Exceptions::EnumConvertionError();
	}
}
mgl::ShaderVariableDataType mgl::enum_converter::convert_variable_type(std::pair<ShaderVariableNonArrayDataType, ShaderVariableArrayType> const& v) {
	switch (v.first) {
		case ShaderVariableNonArrayDataType::Float:
			switch (v.second) {
				case ShaderVariableArrayType::_1: return ShaderVariableDataType::Float;
				case ShaderVariableArrayType::_2: return ShaderVariableDataType::Float_2;
				case ShaderVariableArrayType::_3: return ShaderVariableDataType::Float_3;
				case ShaderVariableArrayType::_4: return ShaderVariableDataType::Float_4;
				case ShaderVariableArrayType::_2x2:	return ShaderVariableDataType::Float_2x2;
				case ShaderVariableArrayType::_3x2:	return ShaderVariableDataType::Float_3x3;
				case ShaderVariableArrayType::_4x2:	return ShaderVariableDataType::Float_4x4;
				case ShaderVariableArrayType::_2x3:	return ShaderVariableDataType::Float_2x3;
				case ShaderVariableArrayType::_3x3:	return ShaderVariableDataType::Float_3x2;
				case ShaderVariableArrayType::_4x3:	return ShaderVariableDataType::Float_4x2;
				case ShaderVariableArrayType::_2x4:	return ShaderVariableDataType::Float_2x4;
				case ShaderVariableArrayType::_3x4:	return ShaderVariableDataType::Float_3x4;
				case ShaderVariableArrayType::_4x4:	return ShaderVariableDataType::Float_4x3;
				default: throw Exceptions::EnumConvertionError();
			}
		case ShaderVariableNonArrayDataType::Double:
			switch (v.second) {
				case ShaderVariableArrayType::_1: return ShaderVariableDataType::Double;
				case ShaderVariableArrayType::_2: return ShaderVariableDataType::Double_2;
				case ShaderVariableArrayType::_3: return ShaderVariableDataType::Double_3;
				case ShaderVariableArrayType::_4: return ShaderVariableDataType::Double_4;
				case ShaderVariableArrayType::_2x2:	return ShaderVariableDataType::Double_2x2;
				case ShaderVariableArrayType::_3x2:	return ShaderVariableDataType::Double_3x3;
				case ShaderVariableArrayType::_4x2:	return ShaderVariableDataType::Double_4x4;
				case ShaderVariableArrayType::_2x3:	return ShaderVariableDataType::Double_2x3;
				case ShaderVariableArrayType::_3x3:	return ShaderVariableDataType::Double_3x2;
				case ShaderVariableArrayType::_4x3:	return ShaderVariableDataType::Double_4x2;
				case ShaderVariableArrayType::_2x4:	return ShaderVariableDataType::Double_2x4;
				case ShaderVariableArrayType::_3x4:	return ShaderVariableDataType::Double_3x4;
				case ShaderVariableArrayType::_4x4:	return ShaderVariableDataType::Double_4x3;
				default: throw Exceptions::EnumConvertionError();
			}
		case ShaderVariableNonArrayDataType::Int:
			switch (v.second) {
				case ShaderVariableArrayType::_1: return ShaderVariableDataType::Int;
				case ShaderVariableArrayType::_2: return ShaderVariableDataType::Int_2;
				case ShaderVariableArrayType::_3: return ShaderVariableDataType::Int_3;
				case ShaderVariableArrayType::_4: return ShaderVariableDataType::Int_4;
				default: throw Exceptions::EnumConvertionError();
			}
		case ShaderVariableNonArrayDataType::UInt:
			switch (v.second) {
				case ShaderVariableArrayType::_1: return ShaderVariableDataType::UInt;
				case ShaderVariableArrayType::_2: return ShaderVariableDataType::UInt_2;
				case ShaderVariableArrayType::_3: return ShaderVariableDataType::UInt_3;
				case ShaderVariableArrayType::_4: return ShaderVariableDataType::UInt_4;
				default: throw Exceptions::EnumConvertionError();
			}
		case ShaderVariableNonArrayDataType::Bool:
			switch (v.second) {
				case ShaderVariableArrayType::_1: return ShaderVariableDataType::Bool;
				case ShaderVariableArrayType::_2: return ShaderVariableDataType::Bool_2;
				case ShaderVariableArrayType::_3: return ShaderVariableDataType::Bool_3;
				case ShaderVariableArrayType::_4: return ShaderVariableDataType::Bool_4;
				default: throw Exceptions::EnumConvertionError();
			}
		default: throw Exceptions::EnumConvertionError();
	}
}

std::pair<size_t, size_t> mgl::enum_converter::convert_to_numbers(ShaderVariableArrayType const& v) {
	switch (v) {
		case ShaderVariableArrayType::_1: return std::make_pair(1, 1);
		case ShaderVariableArrayType::_2: return std::make_pair(1, 2);
		case ShaderVariableArrayType::_3: return std::make_pair(1, 3);
		case ShaderVariableArrayType::_4: return std::make_pair(1, 4);
		case ShaderVariableArrayType::_2x2:	return std::make_pair(2, 2);
		case ShaderVariableArrayType::_3x2:	return std::make_pair(3, 2);
		case ShaderVariableArrayType::_4x2:	return std::make_pair(4, 2);
		case ShaderVariableArrayType::_2x3:	return std::make_pair(2, 3);
		case ShaderVariableArrayType::_3x3:	return std::make_pair(3, 3);
		case ShaderVariableArrayType::_4x3:	return std::make_pair(4, 3);
		case ShaderVariableArrayType::_2x4:	return std::make_pair(2, 4);
		case ShaderVariableArrayType::_3x4:	return std::make_pair(3, 4);
		case ShaderVariableArrayType::_4x4:	return std::make_pair(4, 4);
		default: throw Exceptions::EnumConvertionError();
	}
}
size_t mgl::enum_converter::get_size(ShaderVariableNonArrayDataType const& v) {
	switch (v) {
		case ShaderVariableNonArrayDataType::Float: return sizeof(float);
		case ShaderVariableNonArrayDataType::Double: return sizeof(double);
		case ShaderVariableNonArrayDataType::Int: return sizeof(int);
		case ShaderVariableNonArrayDataType::UInt: return sizeof(unsigned int);
		case ShaderVariableNonArrayDataType::Bool: return sizeof(bool);
		default: throw Exceptions::EnumConvertionError();
	}
}