#pragma once
#include "../MyGraphicsLibrary/MGL/OpenGL/EnumsMirror/EnumsMirror.hpp"

#include "../MyGraphicsLibrary/MGL/SharedHeaders/Exceptions.hpp"
DefineNewMglException(SendableArrayDataAccessProibitedException)

namespace mgl {
	class Buffer;
	namespace SubFunctions {
		Buffer* generate_buffer();
		void buffer_bind(Buffer* buffer);
		void buffer_data(Buffer* buffer, size_t floats, float* data, DataUsage u);
		void delete_buffer(Buffer* buffer);
	}

	template <typename ContainerType>
	class AbstractSendableArray {
	private:
		Buffer* m_buffer;
		bool m_wasBufferGenerated;

		size_t m_item_number;
		bool m_data_edit_mode;
	protected:
		ContainerType m_data;
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
		virtual size_t recalculate_number() const abstract;
		virtual size_t elements_per_item() const abstract;
		virtual void delete_data() abstract;
		bool is_in_data_edit_mode() const { return m_data_edit_mode; }
	public:
		AbstractSendableArray() : m_wasBufferGenerated(false), m_data_edit_mode(false) {}
		virtual ~AbstractSendableArray() {
			if (m_wasBufferGenerated)
				SubFunctions::delete_buffer(m_buffer);
		}

		inline size_t getSize() const { return getNumber() * elements_per_item(); }
		inline size_t getNumber() const { if (m_data_edit_mode) recalculate_number(); return m_item_number; }
		void deleteAll() { delete_data(); m_item_number = 0; }

		void initialize_data_edit() { m_data_edit_mode = true; }
		void stop_data_edit() { m_data_edit_mode = false; m_item_number = recalculate_number(); }

		ContainerType& operator*() { if (m_data_edit_mode) return m_data; else throw Exceptions::SendableArrayDataAccessProibitedException("Data was attempted to be changed while it was prohibited."); }
		ContainerType& operator->() { if (m_data_edit_mode) return m_data; else throw Exceptions::SendableArrayDataAccessProibitedException("Data was attempted to be changed while it was prohibited."); }
		ContainerType& get() { if (m_data_edit_mode) return m_data; else throw Exceptions::SendableArrayDataAccessProibitedException("Data was attempted to be changed while it was prohibited."); }
		ContainerType const& operator*() const { return m_data; }
		ContainerType const& operator->() const { return m_data; }
		ContainerType const& get() const { return m_data; }

		virtual void send(DataUsage u) abstract;
		virtual void clean() {
			buffer_data(getSize(), NULL, mgl::DataUsage::StaticRead);
		}
	};
}