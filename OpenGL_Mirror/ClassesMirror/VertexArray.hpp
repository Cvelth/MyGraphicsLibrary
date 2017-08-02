#pragma once
#include "SharedHeaders\Exceptions.hpp"
DefineNewException(VertexArrayException)
namespace mgl {
	class ShaderVariable;
	class VertexArray {
	private:
		unsigned int m_id;
	public:
		VertexArray();
		VertexArray(unsigned int id);
		~VertexArray();

		bool isValid();
		unsigned int id() const;

		void bind();
		void mgl::VertexArray::attribPointer(const ShaderVariable& attrib, size_t size,
											 bool normalized, size_t stride, size_t shift);
	};
}