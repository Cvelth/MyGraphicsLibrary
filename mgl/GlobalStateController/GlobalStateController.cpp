#include "mgl/dependencies/OpenGL_Dependency/opengl_dependency.hpp"
#include "GlobalStateController.hpp"

#include "mgl/ShaderProgram/ShaderProgram.hpp"
mgl::ShaderProgram *mgl::GlobalStateController::m_shader_program_used = nullptr;
void mgl::GlobalStateController::use_shader_program(ShaderProgram *program) {
	if (m_shader_program_used != program) {
		glUseProgram(program->m_id);
		m_shader_program_used = program;
	}
}
mgl::ShaderProgram const* mgl::GlobalStateController::used_shader_program() {
	return m_shader_program_used;
}