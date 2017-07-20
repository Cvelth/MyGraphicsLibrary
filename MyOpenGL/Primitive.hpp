#pragma once
#include <list>
#include "AbstractException.hpp"
#include "FunctionEnums.hpp"

namespace mgl {
	class Buffer;
	class BufferArray;
	class Vector;
	class Matrix;

	namespace Exceptions {
		class PrimitiveException : public AbstractStringException {
			using AbstractStringException::AbstractStringException;
		};
	}

	class Primitive {
	protected:
		std::list<Vector*> m_data;
		Buffer* m_buffer;
		VertexConnectionType m_connection;
	public:
		Primitive(VertexConnectionType type = VertexConnectionType::Points);
		Primitive(VertexConnectionType type, const float* array, size_t size, size_t POINT_NUMBER = 4);
		Primitive(VertexConnectionType type, Vector* array, size_t size);
		Primitive(VertexConnectionType type, const std::initializer_list<Vector*>& list);
		Primitive(VertexConnectionType type, const std::list<Vector*>& list);
		~Primitive();
		
		virtual size_t getSize() const;
		virtual size_t getNumber() const;
		
		virtual void insert(Vector* v);
		virtual void send(DataUsage u);
		virtual void bind();
		virtual void draw();
		
		std::list<Vector*>& operator*();
		const std::list<Vector*>& operator*() const;
	};

	class PrimitiveSet {
	protected:
		std::list<Primitive> m_data;
	public:
		PrimitiveSet();
		PrimitiveSet(const Primitive* array, size_t size);
		PrimitiveSet(const std::initializer_list<Primitive>& list);
		PrimitiveSet(const std::list<Primitive>& list);

		virtual size_t getSize() const;
		virtual size_t getNumber() const;

		virtual void insert(const Primitive& v);
		virtual void send(DataUsage u);

		std::list<Primitive>& operator*();
		const std::list<Primitive>& operator*() const;
	};
}