#pragma once
#include <list>
#include "../MyGraphicsLibrary/MGL/OpenGL/EnumsMirror/EnumsMirror.hpp"

namespace mgl {
	class Primitive;
	class InstancingArray;
	class VertexArray;

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
		virtual void insertVertexArray(VertexArray *vao);
		virtual void send(DataUsage u);
		virtual void draw();
		virtual void draw(InstancingArray* instances);
		virtual void clean();

		std::list<Primitive*>& operator*();
		const std::list<Primitive*>& operator*() const;
	};
}