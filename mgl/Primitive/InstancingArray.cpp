#include "../MyGraphicsLibrary/MGL/OpenGL/OpenGL_Dependency/OpenGL.h"
#include "InstancingArray.hpp"
#include "../MyGraphicsLibrary/MGL/Math/Vector.hpp"

mgl::InstancingArray::InstancingArray() : AbstractSendableArray() {}
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

void mgl::InstancingArray::deleteAll() {
	for (auto it : m_data)
		delete it;
	m_data.clear();
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

mgl::InstancingMultiArray::InstancingMultiArray() : AbstractSendableArray() {}
mgl::InstancingMultiArray::~InstancingMultiArray() {
	for (auto it : m_data)
		for (auto t : it)
			delete t;
}

size_t mgl::InstancingMultiArray::getSize() const {
	return getNumber() * 4;
}

size_t mgl::InstancingMultiArray::getNumber() const {
	size_t ret = 0u;
	for (auto it : m_data)
		ret += it.size();
	return ret;
}

void mgl::InstancingMultiArray::deleteAll() {
	for (auto list : m_data)
		for (auto it : list)
			delete it;
	m_data.clear();
}

void mgl::InstancingMultiArray::send(DataUsage u) {
	float* temp = new float[getSize()];
	size_t i = 0;
	for (auto list : m_data) 
		for (auto it : list) {
			temp[i++] = it->x();
			temp[i++] = it->y();
			temp[i++] = it->z();
			temp[i++] = it->w();
		}
	buffer_data(getSize(), temp, u);
	delete[] temp;
}