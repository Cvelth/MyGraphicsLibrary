#pragma once
#include <cstdint>
#include <utility>
#include <string>
namespace mgl {
	enum class ShaderVariableType {
		Attribute, Uniform
	};
	enum class ShaderVariableDataType {
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
		Double_3x4, Double_4x2, Double_4x3
	};
	enum class ShaderVariableNonArrayDataType {
		Float, Double, Int, UInt, Bool
	};
	enum class ShaderVariableArrayType {
		_1, _2, _3, _4,
		_2x2, _3x2, _4x2,
		_2x3, _3x3, _4x3,
		_2x4, _3x4, _4x4
	};
	namespace enum_converter {
		std::pair<ShaderVariableNonArrayDataType, ShaderVariableArrayType> convert_variable_type(ShaderVariableDataType const& v);
		ShaderVariableDataType convert_variable_type(std::pair<ShaderVariableNonArrayDataType, ShaderVariableArrayType> const& v);
	}

	class ShaderVariable {
	public:
		std::string const name;
		ShaderVariableType const type;
		uint32_t const location;
		ShaderVariableDataType const data_type;

		explicit ShaderVariable(std::string const& name, ShaderVariableType const& type,
								int location, ShaderVariableDataType const& d_type)
			: name(name), type(type), location(location), data_type(d_type) {}

		std::pair<size_t, size_t> dimention_sizes() const;
		size_t type_size() const;
		inline size_t size() const {
			auto t = dimention_sizes();
			return type_size() * t.first * t.second;
		}
	};
}