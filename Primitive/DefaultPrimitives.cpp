#include "DefaultPrimitives.hpp"
#include "Primitive.hpp"
#include "Math\Vector.hpp"
#include <cmath>

const float PI = 3.14159265359f;

mgl::Primitive* mgl::generateN_Polygon(size_t n, mgl::Color * color, bool isFilled) {
	Primitive* res;
	if (isFilled)
		res = new Primitive(VertexConnectionType::TriangleStrip, color);
	else
		res = new Primitive(VertexConnectionType::LineLoop, color);
	float STEP = PI / n * 2;
	for (float f = 0.f; f < PI * 2; f += STEP)
		res->insert(new mgl::math::Vector(cosf(f), sinf(f)));
	return res;
}

mgl::Primitive* mgl::generateRectangle(float aspectRatio, mgl::Color * color, bool isFilled) {
	mgl::Primitive* res;
	if (isFilled)
		res = new Primitive(VertexConnectionType::TriangleStrip, color);
	else
		res = new Primitive(VertexConnectionType::LineLoop, color);
	if (aspectRatio < 1.f && aspectRatio > 0.f) {
		res->insert(new mgl::math::Vector(-aspectRatio, -1.f));
		res->insert(new mgl::math::Vector(+aspectRatio, -1.f));
		res->insert(new mgl::math::Vector(+aspectRatio, +1.f));
		res->insert(new mgl::math::Vector(-aspectRatio, +1.f));
	} else if (aspectRatio >= 1.f) {
		res->insert(new mgl::math::Vector(-1.f, -1.f / aspectRatio));
		res->insert(new mgl::math::Vector(-1.f, +1.f / aspectRatio));
		res->insert(new mgl::math::Vector(+1.f, +1.f / aspectRatio));
		res->insert(new mgl::math::Vector(+1.f, -1.f / aspectRatio));
	} else
		throw mgl::Exceptions::PrimitiveException("Incorrect input data(aspectRatio).");
	return res;
}

mgl::Primitive* mgl::generateCircle(size_t n, mgl::Color * color, bool isFilled) {
	return generateN_Polygon(n, color, isFilled);
}
