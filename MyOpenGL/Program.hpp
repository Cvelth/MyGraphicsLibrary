#pragma once
#include "Shader.hpp"

namespace mgl {
	class ProgramException : public AbstractStringException {
		using AbstractStringException::AbstractStringException;
	};

	class Program {
	private:
		GLuint m_id;
	public:
		explicit Program();
		~Program();

		void link(const std::initializer_list<Shader>& list);
		void use();
	};
}