#pragma once
#include <utility>
namespace mgl {
	class ShaderProgram;
	class MultiBuffer;
	enum class BufferBindingPoint;

	class GlobalStateController {
		static ShaderProgram *m_shader_program_used;
		static std::pair<MultiBuffer*, size_t> m_buffers_bound[14];
	protected:

	public:
		GlobalStateController() = delete;
		GlobalStateController(GlobalStateController const& other) = delete;
		GlobalStateController(GlobalStateController &&other) =delete;

		static void use_shader_program(ShaderProgram *program);
		static ShaderProgram const* used_shader_program();

		static void bind_buffer(BufferBindingPoint const& binding_point, MultiBuffer *buffer, size_t index = 0);
		static std::pair<MultiBuffer const*, size_t> const bound_buffer(BufferBindingPoint const& binding_point);
	};
}