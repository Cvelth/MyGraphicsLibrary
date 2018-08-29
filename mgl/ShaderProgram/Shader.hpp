#pragma once
#include <cstdint>
namespace mgl {
	enum class ShaderType {
		Fragment, Vertex, Geometry, Compute, TesselationControl, TesselationEvaluation
	};
	class Shader {
		uint32_t m_id;
	protected:
		Shader(uint32_t id);
		Shader(char const* source, ShaderType type);
	public:
		Shader(ShaderType type);
		Shader(ShaderType type, char const* filename);
		~Shader();

		void compileFile(const char* filename);
		void compileSource(const char* sourceText);
		unsigned int id();

		static Shader compileShaderSource(ShaderType type, const char* source);
	};
}

#include "mgl/exceptions.hpp"
DefineNewMGLException(ShaderCompilationError)
DefineNewMGLException(ShaderCreationError)