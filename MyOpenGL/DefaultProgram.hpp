#pragma once
#include "Program.hpp"
#include "SharedEnums.hpp"

namespace mgl {
	class DefaultProgram : public Program {
	private:
		Shader* vertexShader;
		Shader* fragmentShader;
	protected:
		const static std::string Vertex_1Matrix_Source;
		const static std::string Vertex_6Matrices_Source;
		const static std::string Fragment_Source;
	public:
		DefaultProgram(DefaulProgramType type = DefaulProgramType::Vertex1Matrix);
		~DefaultProgram();
	};
}