#include "DefaultPrimitives.hpp"
#include "Vector.hpp"
#include <cmath>

const float PI = 3.14159265359f;

mgl::Primitive mgl::generateN_Polygon(size_t n) {
	Primitive res(VertexConnectionType::LineLoop);
	float STEP = PI / n * 2;
	for (float f = 0.f; f < PI * 2; f += STEP)
		res.insert(new Vector(cosf(f), sinf(f)));
		return res;
	return Primitive();
}

mgl::Primitive mgl::generateRectangle(float aspectRatio) {
	mgl::Primitive res(mgl::VertexConnectionType::LineLoop);
	if (aspectRatio < 1.f && aspectRatio > 0.f) {
		res.insert(new Vector(-aspectRatio, -1.f));
		res.insert(new Vector(+aspectRatio, -1.f));
		res.insert(new Vector(+aspectRatio, +1.f));
		res.insert(new Vector(-aspectRatio, +1.f));
	} else if (aspectRatio >= 1.f) {
		res.insert(new Vector(-1.f, -1.f / aspectRatio));
		res.insert(new Vector(-1.f, +1.f / aspectRatio));
		res.insert(new Vector(+1.f, +1.f / aspectRatio));
		res.insert(new Vector(+1.f, -1.f / aspectRatio));
	} else
		throw mgl::PrimitiveException("Incorrect input data(aspectRatio).");
	return res;
}

mgl::Primitive mgl::generateCircle(size_t n) {
	return generateN_Polygon(n);
}
