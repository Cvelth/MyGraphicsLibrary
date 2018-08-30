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
		void* map(size_t index, BufferMappedAccess access, BufferBindingPoint binding_point = BufferBindingPoint::ArrayBuffer);
		void unmap(BufferBindingPoint binding_point = BufferBindingPoint::ArrayBuffer);

		MultiBuffer(MultiBuffer const& other) = delete;
		MultiBuffer(MultiBuffer &&other) : MultiBuffer(other.m_number, other.m_ids) {}
	};

	class Buffer : private MultiBuffer {
	protected:
		Buffer(uint32_t id) : MultiBuffer(1, &id) {}
	public:
		Buffer() : MultiBuffer(1) {}
		virtual ~Buffer() {}

		void bind(BufferBindingPoint p = BufferBindingPoint::ArrayBuffer) {
			MultiBuffer::bind(0, p);
		}
		void data(void *data, size_t size_of_data, BufferDataUsage usage) {
			MultiBuffer::data(0, data, size_of_data, usage);
		}
		void* map(BufferMappedAccess access) {
			return MultiBuffer::map(0, access);
		}
		using MultiBuffer::unmap;

		Buffer(Buffer &&other) : MultiBuffer(std::move(other)) {}
	};
}

#include "mgl/exceptions.hpp"
DefineNewMGLException(BufferCreationError)
DefineNewMGLException(MultiBufferIndexOutOfBounds)
DefineNewMGLException(BufferMappingError)