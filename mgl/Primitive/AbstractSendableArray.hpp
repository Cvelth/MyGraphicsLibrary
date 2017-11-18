#pragma once
#include <list>
#include "MGL\OpenGL\EnumsMirror\EnumsMirror.hpp"

namespace mgl {
	class Buffer;
	namespace SubFunctions {
		Buffer* generate_buffer();
		void buffer_bind(Buffer* buffer);
		void buffer_data(Buffer* buffer, size_t floats, float* data, DataUsage u);
		void delete_buffer(Buffer* buffer);
	}

	template <typename DataType>
	class AbstractSendableArray {
	private:
		Buffer* m_buffer;
		bool m_wasBufferGenerated;
	protected:
		std::list<DataType*> m_data;
	protected:
		void buffer_check() {
			if (!m_wasBufferGenerated) {
				m_buffer = SubFunctions::generate_buffer();
				m_wasBufferGenerated = true;
			}
		}
		void buffer_bind() {
			buffer_check();
			SubFunctions::buffer_bind(m_buffer);
		}
		void buffer_data(size_t floats, float* data, DataUsage u) {
			buffer_check();
			SubFunctions::buffer_data(m_buffer, floats, data, u);
		}

		bool wasBufferGenerated() {
			return m_wasBufferGenerated;
		}
	public:
		AbstractSendableArray() : m_wasBufferGenerated(false) {}
		virtual ~AbstractSendableArray() {
			if (m_wasBufferGenerated)
				SubFunctions::delete_buffer(m_buffer);
		}

		virtual void deleteObject(DataType* obj) abstract;

		virtual size_t getSize() const abstract;
		virtual size_t getNumber() const abstract;

		virtual void insert(DataType* v){
			m_data.push_back(v);
		}
		virtual void send(DataUsage u) abstract;
		virtual void clean() {
			buffer_data(getSize(), NULL, mgl::DataUsage::StaticRead);
		}

		virtual void deleteAll() {
			for (auto it = m_data.begin(); it != m_data.end(); it++)
				deleteObject(*it);
			m_data.clear();
		}
	};
}