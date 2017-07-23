#pragma once
#include <list>
#include "OpenGL_Mirror\EnumsMirror\EnumsMirror.hpp"

namespace mgl {
	class Primitive;

	class AbstractDrawableObject {
	protected:
		std::list<Primitive*> m_data;
	public:
		AbstractDrawableObject();
		AbstractDrawableObject(const Primitive* array, size_t size);
		AbstractDrawableObject(const std::initializer_list<Primitive*>& list);
		AbstractDrawableObject(const std::list<Primitive*>& list);

		virtual size_t getSize() const;
		virtual size_t getNumber() const;

		virtual void addPrimitive(Primitive* v);
		virtual void send(DataUsage u);
		virtual void draw();

		std::list<Primitive*>& operator*();
		const std::list<Primitive*>& operator*() const;
	};
}