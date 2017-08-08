#pragma once
#include <list>
#include "AbstractSendableArray.hpp"
#include "SharedHeaders\Exceptions.hpp"
DefineNewMglException(PrimitiveException)

namespace mgl {
	class Buffer;
	class Color;
	namespace math {
		class Vector;
	}
	class Vertex;
	class InstancingArray;
	class VertexArray;

	class Primitive : public AbstractSendableArray<Vertex> {
	protected:
		VertexArray* m_vertex_array;
		VertexConnectionType m_connection;
		Color* m_default_color;
	public:
		Primitive(VertexConnectionType type = VertexConnectionType::Points, Color* defaultColor = nullptr);
		Primitive(VertexConnectionType type, Color* defaultColor, const float* array, size_t size, size_t COORDS_POINT_NUMBER = 3, size_t COLOR_POINT_NUMBER = 3);
		Primitive(VertexConnectionType type, Color* defaultColor, math::Vector* coords_array, size_t size);
		Primitive(VertexConnectionType type, Color* defaultColor, math::Vector* coords_array, Color* colors_array, size_t size);
		Primitive(VertexConnectionType type, Color* defaultColor, const std::initializer_list<math::Vector*>& coords_list);
		Primitive(VertexConnectionType type, Color* defaultColor, const std::initializer_list<math::Vector*>& coords_list, const std::initializer_list<Color*>& color_list);
		Primitive(VertexConnectionType type, Color* defaultColor, const std::list<math::Vector*>& coords_list);
		Primitive(VertexConnectionType type, Color* defaultColor, const std::list<math::Vector*>& coords_list, const std::list<Color*>& color_list);
		~Primitive();

		void insertVertexArray(VertexArray *vao);
		
		virtual size_t getSize() const override;
		virtual size_t getNumber() const override;

		virtual void deleteObject(Vertex* obj) override;

		virtual Color* getDefaultColor() const;
		virtual void setDefaultColor(Color* color);
		virtual void setDefaultColor(float r = 0.f, float g = 0.f, float b = 0.f, float a = 1.f);
		
		using AbstractSendableArray<Vertex>::insert;
		virtual void insert(math::Vector const& v);
		virtual void insert(math::Vector&& v);
		virtual void insert(math::Vector const& v, Color const& c);
		virtual void insert(math::Vector&& v, Color&& c);
		virtual void send(DataUsage u) override;
		virtual void draw();
		virtual void draw(InstancingArray* instances);
		
		std::list<Vertex*>& operator*();
		const std::list<Vertex*>& operator*() const;

		const Primitive& operator+=(const mgl::math::Vector& v);
		const Primitive& operator+=(mgl::math::Vector&& v);
		const Primitive& operator+=(mgl::math::Vector* v);
		const Primitive& operator-=(const mgl::math::Vector& v);
		const Primitive& operator-=(mgl::math::Vector&& v);
		const Primitive& operator-=(mgl::math::Vector* v);
		const Primitive& operator*=(const mgl::math::Vector& v);
		const Primitive& operator*=(mgl::math::Vector&& v);
		const Primitive& operator*=(mgl::math::Vector* v);
		const Primitive& operator/=(const mgl::math::Vector& v);
		const Primitive& operator/=(mgl::math::Vector&& v);
		const Primitive& operator/=(mgl::math::Vector* v);
		const Primitive& operator*=(const float f);
		const Primitive& operator/=(const float f);
	};
}