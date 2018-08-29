#pragma once
#include <cstdint>
#include <list>
#include <initializer_list>
#include "mgl/ShaderProgram/ShaderVariable.hpp"
namespace mgl {
	class Shader;
	class GlobalStateController;
	class ShaderProgram {
		friend GlobalStateController;
	private:
		mutable bool m_is_linked;
		uint32_t m_id;
	protected:
		ShaderProgram(uint32_t id);
	public:
		ShaderProgram();
		ShaderProgram(std::initializer_list<Shader> const& shaders);
		~ShaderProgram();

		void link(std::initializer_list<Shader> const& shaders);
		bool is_linked() const;
		void use();

		std::list<ShaderVariable> getUniforms();
		std::list<ShaderVariable> getAttributes();
		std::list<ShaderVariable> getVariables();

		ShaderProgram(ShaderProgram const& other) = delete;
		ShaderProgram(ShaderProgram &&other) : ShaderProgram(other.m_id) {}
	};
}

#include "mgl/exceptions.hpp"
DefineNewMGLException(ProgramLinkageError)
DefineNewMGLException(ProgramCreationError)