#pragma once
#include <cstdint>
namespace mgl {
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
		Double_3x4, Double_4x2, Double_4x3,
	};
	enum class ShaderVariableType {
		Attribute, Uniform
	};

	struct ShaderVariable {
		char const*const name;
		ShaderVariableType const& type;
		uint32_t const location;
		ShaderVariableDataType const& data_type;

		explicit ShaderVariable(char const*const name, ShaderVariableType const& type,
								int location, ShaderVariableDataType const& d_type)
			: name(name), type(type), location(location), data_type(d_type) {}
	};
}