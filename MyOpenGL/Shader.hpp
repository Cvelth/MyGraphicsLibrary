#pragma once
#include "AbstractException.hpp"
typedef unsigned int GLuint;

namespace mgl {
	enum class ShaderType {
		Fragment, Vertex, Geometry, Compute, TessControl, TessEvaluation
	};

	class ShaderException : public AbstractStringException {
		using AbstractStringException::AbstractStringException;
	};

	class Shader {
	private:
		GLuint m_id;
	public:
		Shader(ShaderType type);
		Shader(ShaderType type, const std::string& filename);
		~Shader();

		void compileFile(const std::string& filename);
		void compileSource(const std::string& sourceText);
		GLuint id();
	};
}