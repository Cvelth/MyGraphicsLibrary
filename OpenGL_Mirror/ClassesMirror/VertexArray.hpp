#pragma once
#include "SharedHeaders\Exceptions.hpp"
DefineNewException(BufferException)

namespace mgl {
	class VertexArray {
	private:
		unsigned int m_id;
	public:
		VertexArray();
		VertexArray(unsigned int id);
		~VertexArray();

		unsigned int id() const;
		void bind();
		void enableAttrib(unsigned int index);
		void mgl::VertexArray::attribPointer(const char* fieldName, size_t size,
											 bool normalized, size_t stride, size_t shift);
	};
}