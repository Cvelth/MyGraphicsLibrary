#pragma once
#include <list>
#include "../MyGraphicsLibrary/MGL/Primitive/AbstractSendableArray.hpp"
#include "../MyGraphicsLibrary/MGL/SharedHeaders/Exceptions.hpp"
DefineNewMglException(PrimitiveException)

namespace mgl {
	class Buffer;
	class Color;
	namespace math {
		class vectorH;
	}
	class Vertex;
	class InstancingArray;
	class InstancingMultiArray;
	class VertexArray;

	class Primitive : public AbstractSendableArray<std::list<Vertex*>> {
	protected:
		VertexArray* m_vertex_array;
		VertexConnectionType m_connection;
		Color* m_default_color;
	protected:
		virtual size_t recalculate_number() const override;
		virtual size_t elements_per_item() const override;
		virtual void delete_data() override;
	public:
		Primitive(VertexConnectionType type = VertexConnectionType::Points, Color* defaultColor = nullptr);
		Primitive(VertexConnectionType type, Color* defaultColor, const float* array, size_t size, size_t COORDS_POINT_NUMBER = 3, size_t COLOR_POINT_NUMBER = 3);
		Primitive(VertexConnectionType type, Color* defaultColor, math::vectorH* coords_array, size_t size);
		Primitive(VertexConnectionType type, Color* defaultColor, math::vectorH* coords_array, Color* colors_array, size_t size);
		Primitive(VertexConnectionType type, Color* defaultColor, const std::initializer_list<math::vectorH*>& coords_list);
		Primitive(VertexConnectionType type, Color* defaultColor, const std::initializer_list<math::vectorH*>& coords_list, const std::initializer_list<Color*>& color_list);
		Primitive(VertexConnectionType type, Color* defaultColor, const std::list<math::vectorH*>& coords_list);
		Primitive(VertexConnectionType type, Color* defaultColor, const std::list<math::vectorH*>& coords_list, const std::list<Color*>& color_list);
		~Primitive();

		void insertVertexArray(VertexArray *vao);

		virtual Color* getDefaultColor() const;
		virtual void setDefaultColor(Color* color);
		virtual void setDefaultColor(float r = 0.f, float g = 0.f, float b = 0.f, float a = 1.f);
		
		virtual void insert(Vertex* v);
		virtual void insert(math::vectorH const& v);
		virtual void insert(math::vectorH&& v);
		virtual void insert(math::vectorH const& v, Color const& c);
		virtual void insert(math::vectorH&& v, Color&& c);
		virtual void send(DataUsage u) override;
		virtual void draw();
		virtual void draw(InstancingArray* instances);
		virtual void draw(InstancingMultiArray* instances);

		const Primitive& operator+=(const mgl::math::vectorH& v);
		const Primitive& operator+=(mgl::math::vectorH&& v);
		const Primitive& operator-=(const mgl::math::vectorH& v);
		const Primitive& operator-=(mgl::math::vectorH&& v);
		const Primitive& operator*=(const mgl::math::vectorH& v);
		const Primitive& operator*=(mgl::math::vectorH&& v);
		const Primitive& operator/=(const mgl::math::vectorH& v);
		const Primitive& operator/=(mgl::math::vectorH&& v);
		const Primitive& operator*=(const float f);
		const Primitive& operator/=(const float f);
	};
}