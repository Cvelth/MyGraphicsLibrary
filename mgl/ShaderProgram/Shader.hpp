#pragma once
#include <cstdint>
#include <string>
namespace mgl {
	enum class ShaderType {
		Fragment, Vertex, Geometry, Compute, TesselationControl, TesselationEvaluation
	};
	class ShaderProgram;

	class Shader {
		friend ShaderProgram;
	private:
		uint32_t m_id;
	protected:
		Shader(uint32_t id);
		Shader(std::string const& source, ShaderType type);
	public:
		Shader(ShaderType type);
		Shader(ShaderType type, std::string const& filename);
		~Shader();

		void compileFile(std::string const& filename);
		void compileSource(std::string const& sourceText);

		static Shader compileShaderSource(ShaderType type, std::string const& source);

		Shader(Shader const& other) = delete;
		Shader(Shader &&other) : Shader(other.m_id) {}
	};
}

#include "mgl/exceptions.hpp"
DefineNewMGLException(ShaderCompilationError)
DefineNewMGLException(ShaderCreationError)