#pragma once
#include "AbstractException.hpp"
#include "FunctionEnums.hpp"

namespace mgl {
	using BufferException = Exceptions::AbstractStringException;

	class Buffer {
	private:
		unsigned int m_id;
	public:
		Buffer();
		Buffer(unsigned int id);
		~Buffer();

		unsigned int id() const;
		void bind(BufferBindingPoint p = BufferBindingPoint::ArrayBuffer);
	};

	class BufferArray{
	private:
		unsigned int size;
		unsigned int* m_id;
	public:
		BufferArray(unsigned int n = 1);
		~BufferArray();

		unsigned int id(unsigned int n) const;
		Buffer operator[](unsigned int n);
	};
}