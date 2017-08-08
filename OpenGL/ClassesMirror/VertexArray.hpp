#pragma once
#include "SharedHeaders\Exceptions.hpp"
DefineNewMglException(VertexArrayException)

#include <map>
namespace mgl {
	class ShaderVariable;
	struct VertexShaderAttributePointerData {
		size_t const size;
		bool const normalized;
		size_t const stride;
		size_t const shift;

		VertexShaderAttributePointerData(size_t const size, bool const normalized,
										 size_t const stride, size_t const shift)
			: size(size), normalized(normalized), stride(stride), shift(shift) {}
	};
	using AttributePointerDataType = std::pair<ShaderVariable const*, VertexShaderAttributePointerData const>;
	using AttributePointerDataStructure = std::map<ShaderVariable const*, VertexShaderAttributePointerData const>;
	class VertexArray {
	private:
		unsigned int m_id;
		AttributePointerDataStructure m_data;
	public:
		VertexArray();
		VertexArray(unsigned int id);
		VertexArray(const VertexArray& vao);
		~VertexArray();

		bool isValid();
		unsigned int id() const;

		void bind();
		void initializeAttribPointer(ShaderVariable const& attrib, size_t size,
									 bool normalized, size_t stride, size_t shift);
		void repeatAttribPointer(ShaderVariable const& attrib);
		void repeatAllAttribPointers();
	};
}