#pragma once
#include "Program.hpp"
#include "SharedHeaders\Enums.hpp"
#include <string>

namespace mgl {
	class DefaultProgram : public Program {
	private:
		Shader* vertexShader;
		Shader* fragmentShader;
	protected:
		const static std::string Vertex_NoMatrix_2Vectors_Source;
		const static std::string Vertex_1Matrix_2Vectors_Source;
		const static std::string Vertex_1Matrix_Source;
		const static std::string Vertex_2Matrices_Source;
		const static std::string Vertex_6Matrices_Source;
		const static std::string Fragment_Source;
	public:
		DefaultProgram(DefaulProgramType type = DefaulProgramType::Vertex_1Matrix);
		DefaultProgram(Shader* vertex_shader);
		~DefaultProgram();
	};
}