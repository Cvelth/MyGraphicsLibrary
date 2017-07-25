#pragma once
#include "SharedHeaders\Exceptions.hpp"

namespace mgl {
	enum class ShaderType {
		Fragment, Vertex, Geometry, Compute, TessControl, TessEvaluation
	};

	namespace Exceptions {
		class ShaderException : public AbstractStringException {
			using AbstractStringException::AbstractStringException;
		};
	}

	class Shader {
	private:
		unsigned int m_id;
	public:
		Shader(ShaderType type);
		Shader(ShaderType type, const std::string& filename);
		~Shader();

		void compileFile(const std::string& filename);
		void compileSource(const std::string& sourceText);
		unsigned int id();

		static std::string getShaderSourceFromFile(const std::string& filename);
		static Shader* compileShaderSource(ShaderType type, const std::string& source);
	};

}