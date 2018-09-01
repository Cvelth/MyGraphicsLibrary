#include "mgl/dependencies/OpenGL_Dependency/opengl_dependency.hpp"
#include "Buffer.hpp"
#include <algorithm>
mgl::MultiBuffer::MultiBuffer(size_t const number, uint32_t *ids) : m_number(number), m_mapped_id(-1), m_mapped_pointer(nullptr) {
	if (!GlobalStateController::is_initialized())
		throw Exceptions::InitializationNeeded();
	m_ids = new uint32_t[number];
	std::copy(ids, ids + number, m_ids);
	for (size_t i = 0; i < number; i++)
		if (!glIsBuffer(m_ids[i]))
			throw Exceptions::BufferCreationError();
}
mgl::MultiBuffer::MultiBuffer(size_t number) : m_number(number), m_mapped_id(-1), m_mapped_pointer(nullptr) {
	if (!GlobalStateController::is_initialized())
		throw Exceptions::InitializationNeeded();
	m_ids = new uint32_t[number];
	glGenBuffers(GLsizei(number), m_ids);
}
mgl::MultiBuffer::~MultiBuffer() {
	if (m_mapped_pointer) unmap();
	if (m_number) delete[] m_ids;
}

#include "mgl/EnumConverter/enum_converter.hpp"
#include "mgl/GlobalStateController/GlobalStateController.hpp"
void mgl::MultiBuffer::bind(size_t index, BufferBindingPoint binding_point) {
	if (index >= m_number) throw Exceptions::MultiBufferIndexOutOfBounds();
	GlobalStateController::bind_buffer(binding_point, this, index);
}
void mgl::MultiBuffer::data(size_t index, void *data, size_t size_of_data, BufferDataUsage usage, BufferBindingPoint binding_point) {
	bind(index, binding_point);
	glBufferData(mgl::enum_converter::convert(binding_point), size_of_data, 
				 data, mgl::enum_converter::convert(usage));
}
void mgl::MultiBuffer::data(size_t index, size_t size_of_data, BufferDataUsage usage, BufferBindingPoint binding_point) {
	bind(index, binding_point);
	glBufferData(mgl::enum_converter::convert(binding_point), size_of_data,
				 NULL, mgl::enum_converter::convert(usage));
}
void mgl::MultiBuffer::subdata(size_t index, void * data, size_t size_of_data, size_t offset, BufferBindingPoint binding_point) {
	bind(index, binding_point);
	glBufferSubData(mgl::enum_converter::convert(binding_point), offset,
					size_of_data, data);
}
void* mgl::MultiBuffer::map(size_t index, BufferMappedAccess access, BufferBindingPoint binding_point) {
	if (m_mapped_pointer)
		if (index == m_mapped_id)
			return m_mapped_pointer;
		else
			unmap();

	bind(index, binding_point);
	m_mapped_id = index;
	return m_mapped_pointer = glMapBuffer(mgl::enum_converter::convert(binding_point), 
										  mgl::enum_converter::convert(access));
}
void mgl::MultiBuffer::unmap(BufferBindingPoint binding_point) {
	if (!m_mapped_pointer) throw Exceptions::BufferMappingError("Buffer wasn't mapped.");

	bind(m_mapped_id, binding_point);
	glUnmapBuffer(mgl::enum_converter::convert(binding_point));
}
void mgl::MultiBuffer::copy(size_t destination_index, MultiBuffer &source, size_t source_index, size_t size_of_data, size_t read_offset, size_t write_offset) {
	bind(destination_index, BufferBindingPoint::CopyWriteBuffer);
	source.bind(destination_index, BufferBindingPoint::CopyReadBuffer);
	glCopyBufferSubData(mgl::enum_converter::convert(BufferBindingPoint::CopyReadBuffer),
						mgl::enum_converter::convert(BufferBindingPoint::CopyWriteBuffer),
						read_offset, write_offset, size_of_data);
}
void mgl::MultiBuffer::copy(size_t destination_index, size_t source_index, size_t size_of_data, size_t read_offset, size_t write_offset) {
	copy(destination_index, *this, source_index, size_of_data, read_offset, write_offset);
}
void mgl::MultiBuffer::invalidate(size_t index, size_t size_of_data, size_t offset) {
	if (index >= m_number) throw Exceptions::MultiBufferIndexOutOfBounds();
	glInvalidateBufferSubData(m_ids[index], offset, size_of_data);
}
void mgl::MultiBuffer::invalidate(size_t index) {
	if (index >= m_number) throw Exceptions::MultiBufferIndexOutOfBounds();
	glInvalidateBufferData(m_ids[index]);
}