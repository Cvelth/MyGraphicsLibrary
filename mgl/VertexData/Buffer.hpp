#pragma once
#include <cstdint>
#include <utility>
namespace mgl {
	enum class BufferBindingPoint {
		ArrayBuffer, AtomicCounterBuffer, CopyReadBuffer, CopyWriteBuffer,
		DispatchIndirectBuffer, DrawIndirectBuffer, ElementArrayBuffer,
		PixelPackBuffer, PixelUnpackBuffer, QueryBuffer, ShaderStorageBuffer,
		TextureBuffer, TransformFeedbackBuffer, UniformBuffer
	};
	enum class BufferMappedAccess {
		ReadOnly, WriteOnly, ReadWrite
	};
	enum class BufferDataUsage {
		StreamDraw, StreamRead, StreamCopy,
		StaticDraw, StaticRead, StaticCopy,
		DynamicDraw, DynamicRead, DynamicCopy
	};
	class GlobalStateController;

	class MultiBuffer {
		friend GlobalStateController;
	private:
		size_t const m_number;
		uint32_t *m_ids;

		//Buffer Mapping.
		size_t m_mapped_id;
		void *m_mapped_pointer;

	protected:
		MultiBuffer(size_t const number, uint32_t *ids);
	public:
		MultiBuffer(size_t number);
		virtual ~MultiBuffer();

		void bind(size_t index, BufferBindingPoint binding_point = BufferBindingPoint::ArrayBuffer);
		void data(size_t index, void *data, size_t size_of_data, BufferDataUsage usage, BufferBindingPoint binding_point = BufferBindingPoint::ArrayBuffer);
		void data(size_t index, size_t size_of_data, BufferDataUsage usage, BufferBindingPoint binding_point = BufferBindingPoint::ArrayBuffer);
		void subdata(size_t index, void *data, size_t size_of_data, size_t offset = 0, BufferBindingPoint binding_point = BufferBindingPoint::ArrayBuffer);
		void* map(size_t index, BufferMappedAccess access, BufferBindingPoint binding_point = BufferBindingPoint::ArrayBuffer);
		void unmap(BufferBindingPoint binding_point = BufferBindingPoint::ArrayBuffer);
		void copy(size_t destination_index, MultiBuffer &source, size_t source_index, size_t size_of_data, size_t read_offset = 0, size_t write_offset = 0);
		void copy(size_t destination_index, size_t source_index, size_t size_of_data, size_t read_offset = 0, size_t write_offset = 0);
		void invalidate(size_t index, size_t size_of_data, size_t offset = 0); 
		void invalidate(size_t index);

		MultiBuffer(MultiBuffer const& other) = delete;
		MultiBuffer(MultiBuffer &&other) : MultiBuffer(other.m_number, other.m_ids) {}
	};

	class Buffer : private MultiBuffer {
	protected:
		Buffer(uint32_t id) : MultiBuffer(1, &id) {}
	public:
		Buffer() : MultiBuffer(1) {}
		virtual ~Buffer() {}

		void bind(BufferBindingPoint binding_point = BufferBindingPoint::ArrayBuffer) {
			MultiBuffer::bind(0, binding_point);
		}
		void data(void *data, size_t size_of_data, BufferDataUsage usage, BufferBindingPoint binding_point = BufferBindingPoint::ArrayBuffer) {
			MultiBuffer::data(0, data, size_of_data, usage, binding_point);
		}
		void data(size_t size_of_data, BufferDataUsage usage, BufferBindingPoint binding_point = BufferBindingPoint::ArrayBuffer) {
			MultiBuffer::data(0, size_of_data, usage, binding_point);
		}
		void subdata(void *data, size_t size_of_data, size_t offset = 0, BufferBindingPoint binding_point = BufferBindingPoint::ArrayBuffer) {
			MultiBuffer::subdata(0, data, size_of_data, offset, binding_point);
		}
		void* map(BufferMappedAccess access, BufferBindingPoint binding_point = BufferBindingPoint::ArrayBuffer) {
			return MultiBuffer::map(0, access, binding_point);
		}
		using MultiBuffer::unmap;
		void copy(MultiBuffer &source, size_t source_index, size_t size_of_data, size_t read_offset = 0, size_t write_offset = 0) {
			MultiBuffer::copy(0, source, source_index, size_of_data, read_offset, write_offset);
		}
		void copy(Buffer &source, size_t size_of_data, size_t read_offset = 0, size_t write_offset = 0) {
			MultiBuffer::copy(0, source, 0, size_of_data, read_offset, write_offset);
		}
		void invalidate(size_t size_of_data, size_t offset = 0) {
			MultiBuffer::invalidate(0, size_of_data, offset);
		}
		void invalidate() {
			MultiBuffer::invalidate(0);
		}

		Buffer(Buffer &&other) : MultiBuffer(std::move(other)) {}
	};
}

#include "mgl/exceptions.hpp"
DefineNewMGLException(BufferCreationError)
DefineNewMGLException(MultiBufferIndexOutOfBounds)
DefineNewMGLException(BufferMappingError)