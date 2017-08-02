#include "AbstractDrawableObject.hpp"
#include "Primitive.hpp"

mgl::AbstractDrawableObject::AbstractDrawableObject() {}

mgl::AbstractDrawableObject::AbstractDrawableObject(const Primitive* array, size_t size) {
	for (size_t i = 0; i < size; i++) {
		auto t = array[i];
		m_data.push_back(&t);
	}
}

mgl::AbstractDrawableObject::AbstractDrawableObject(const std::initializer_list<Primitive*>& list) {
	for (auto it : list)
		m_data.push_back(it);
}

mgl::AbstractDrawableObject::AbstractDrawableObject(const std::list<Primitive*>& list) {
	for (auto it : list)
		m_data.push_back(it);
}

size_t mgl::AbstractDrawableObject::getSize() const {
	size_t res = 0;
	for (auto it : m_data)
		res += it->getSize();
	return res;
}

size_t mgl::AbstractDrawableObject::getNumber() const {
	size_t res = 0;
	for (auto it : m_data)
		res += it->getNumber();
	return res;
}

void mgl::AbstractDrawableObject::addPrimitive(Primitive* v) {
	m_data.push_back(v);
}

void mgl::AbstractDrawableObject::send(DataUsage u) {
	for (auto it : m_data)
		it->send(u);
}

void mgl::AbstractDrawableObject::draw() {
	for (auto it : m_data)
		it->draw();
}
void mgl::AbstractDrawableObject::draw(InstancingArray* instances) {
	for (auto it : m_data)
		it->draw(instances);
}

void mgl::AbstractDrawableObject::clean() {
	for (auto it : m_data)
		it->clean();
}

std::list<mgl::Primitive*>& mgl::AbstractDrawableObject::operator*() {
	return m_data;
}

const std::list<mgl::Primitive*>& mgl::AbstractDrawableObject::operator*() const {
	return m_data;
}