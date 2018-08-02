#include "../MyGraphicsLibrary/MGL/OpenGL/OpenGL_Dependency/OpenGL.h"
#include "InstancingArray.hpp"
#include "../MyGraphicsLibrary/MGL/Math/Vector.hpp"

size_t mgl::InstancingArray::recalculate_number() const { return m_data.size(); }
size_t mgl::InstancingArray::elements_per_item() const { return 4; }
void mgl::InstancingArray::delete_data() { m_data.clear(); }

mgl::InstancingArray::InstancingArray() : AbstractSendableArray() {}
mgl::InstancingArray::~InstancingArray() {
	delete_data();
}
void mgl::InstancingArray::send(DataUsage u) {
	float* temp = new float[getSize()];
	size_t i = 0;
	for (auto &it : m_data) {
		std::copy(it->begin(), it->end(), temp + i);
		i += it->size();
	}
	buffer_data(getSize(), temp, u);
	delete[] temp;
}

size_t mgl::InstancingMultiArray::recalculate_number() const {
	size_t ret = 0u;
	for (auto &it : m_data)
		ret += it.size();
	return ret;
}
size_t mgl::InstancingMultiArray::elements_per_item() const { return 4u; }
void mgl::InstancingMultiArray::delete_data() { m_data.clear(); }

mgl::InstancingMultiArray::InstancingMultiArray() : AbstractSendableArray() {}
mgl::InstancingMultiArray::~InstancingMultiArray() {
	delete_data();
}
void mgl::InstancingMultiArray::send(DataUsage u) {
	float* temp = new float[getSize()];
	size_t i = 0;
	for (auto &list : m_data)
		for (auto &it : list) {
			std::copy(it->begin(), it->end(), temp + i);
			i += it->size();
		}
	buffer_data(getSize(), temp, u);
	delete[] temp;
}