#pragma once
#include "Shader.hpp"

namespace mgl {
	class ProgramException : public AbstractStringException {
		using AbstractStringException::AbstractStringException;
	};

	class Program {
	protected:
		GLuint m_id;
	public:
		explicit Program();
		explicit Program(const std::initializer_list<Shader>& list);
		~Program();

		void link(const std::initializer_list<Shader>& list);
		void use();
	};

	using CustomProgram = Program;
}