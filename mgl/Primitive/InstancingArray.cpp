#include "../MyGraphicsLibrary/MGL/OpenGL/OpenGL_Dependency/OpenGL.h"
#include "InstancingArray.hpp"
#include "../MyGraphicsLibrary/MGL/Math/Vector.hpp"

mgl::InstancingArray::InstancingArray() : AbstractSendableArray() {}
mgl::InstancingArray::InstancingArray(const float* array, size_t size, size_t NUMBERS_PER_ELEMENT) : InstancingArray() {
	if (size % NUMBERS_PER_ELEMENT != 0)
		throw Exceptions::InstancingArrayException("Wrong elements number.");

	NUMBERS_PER_ELEMENT--;
	for (size_t i = 0; i < size; i += NUMBERS_PER_ELEMENT)
		m_data.push_back(new mgl::math::vectorH(NUMBERS_PER_ELEMENT >= 0 ? array[i + 0] : 0,
											   NUMBERS_PER_ELEMENT >= 1 ? array[i + 1] : 0,
											   NUMBERS_PER_ELEMENT >= 2 ? array[i + 2] : 0,
											   NUMBERS_PER_ELEMENT >= 3 ? array[i + 3] : 0)
		);
}
mgl::InstancingArray::InstancingArray(math::vectorH* coords_array, size_t size) : InstancingArray() {
	for (size_t i = 0; i < size; i++)
		m_data.push_back(&coords_array[i]);
}
mgl::InstancingArray::InstancingArray(const std::initializer_list<math::vectorH*>& list) : InstancingArray() {
	for (auto it : list)
		m_data.push_back(it);
}
mgl::InstancingArray::InstancingArray(const std::list<math::vectorH*>& list) : InstancingArray() {
	for (auto it : list)
		m_data.push_back(it);
}
mgl::InstancingArray::~InstancingArray() {
	for (auto it : m_data)
		delete it;
}

size_t mgl::InstancingArray::getSize() const {
	return m_data.size() * 4;
}

size_t mgl::InstancingArray::getNumber() const {
	return m_data.size();
}

void mgl::InstancingArray::deleteObject(math::vectorH *obj) {
	delete obj;
}

void mgl::InstancingArray::send(DataUsage u) {
	float* temp = new float[getSize()];
	size_t i = 0;
	for (auto it : m_data) {
		temp[i++] = it->x();
		temp[i++] = it->y();
		temp[i++] = it->z();
		temp[i++] = it->w();
	}
	buffer_data(getSize(), temp, u);
	delete[] temp;
}