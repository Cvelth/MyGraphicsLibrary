#pragma once
#include "SharedHeaders\Exceptions.hpp"
DefineNewException(ShaderException)

namespace mgl {
	enum class ShaderType {
		Fragment, Vertex, Geometry, Compute, TessControl, TessEvaluation
	};
	class Shader {
	private:
		unsigned int m_id;
	public:
		Shader(ShaderType type);
		Shader(ShaderType type, const char* filename);
		~Shader();

		void compileFile(const char* filename);
		void compileSource(const char* sourceText);
		unsigned int id();

		static const char* getShaderSourceFromFile(const char* filename);
		static Shader* compileShaderSource(ShaderType type, const char* source);
	};

}