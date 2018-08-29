#pragma once
namespace mgl {
	class ShaderProgram;

	class GlobalStateController {
		static ShaderProgram *m_shader_program_used;
	public:
		GlobalStateController() = delete;
		GlobalStateController(GlobalStateController const& other) = delete;
		GlobalStateController(GlobalStateController &&other) =delete;

		static void use_shader_program(ShaderProgram *program);
		static ShaderProgram const* used_shader_program();
	};
}