#pragma once
#include <utility>
namespace mgl {
	class ShaderProgram;
	class MultiBuffer;
	class MultiVertexArray;
	enum class BufferBindingPoint;

	class GlobalStateController {
		static bool m_is_initialized;
		static ShaderProgram *m_shader_program_used;
		static std::pair<MultiBuffer*, size_t> m_buffers_bound[14];
		static std::pair<MultiVertexArray*, size_t> m_vertex_array_bound;
	protected:

	public:
		GlobalStateController() = delete;
		GlobalStateController(GlobalStateController const& other) = delete;
		GlobalStateController(GlobalStateController &&other) =delete;

		static void set_initialization(bool value) { m_is_initialized = value; }
		static bool is_initialized() { return m_is_initialized; }

		static void use_shader_program(ShaderProgram *program);
		static ShaderProgram const* used_shader_program();

		static void bind_buffer(BufferBindingPoint const& binding_point, MultiBuffer *buffer, size_t index = 0);
		static std::pair<MultiBuffer const*, size_t> const bound_buffer(BufferBindingPoint const& binding_point);

		static void bind_vertex_array(MultiVertexArray *vertex_array, size_t index = 0);
		static std::pair<MultiVertexArray const*, size_t> const bound_vertex_array();
	};
}

#include "mgl/exceptions.hpp"
DefineNewMGLException(InitializationNeeded)