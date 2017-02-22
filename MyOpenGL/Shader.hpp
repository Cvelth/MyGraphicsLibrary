#pragma once
#include "OpenGL_header.h"

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
		Shader(ShaderType type, const std::string& filename);
		~Shader();

		void create(ShaderType type);
		void compile(const std::string& filename);
		GLuint id();
	};
}