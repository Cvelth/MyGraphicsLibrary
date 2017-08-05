#pragma once
#include "OpenGL_Mirror\EnumsMirror\EnumsMirror.hpp"
#include "SharedHeaders\Exceptions.hpp"
DefineNewMglException(BufferException)

namespace mgl {
	class Buffer {
	private:
		unsigned int m_id;
		void* m_pointer;
	public:
		Buffer();
		Buffer(unsigned int id);
		~Buffer();

		unsigned int id() const;
		void bind(BufferBindingPoint p = BufferBindingPoint::ArrayBuffer);
		void data(size_t floats, float* data, DataUsage u);
		void* map(BufferMappingAccess a);
		void unmap();
	};
	class BufferArray {
	private:
		unsigned int m_size;
		unsigned int* m_id;
	public:
		BufferArray(unsigned int n = 1);
		~BufferArray();

		unsigned int id(unsigned int n) const;
		Buffer operator[](unsigned int n);
	};
}