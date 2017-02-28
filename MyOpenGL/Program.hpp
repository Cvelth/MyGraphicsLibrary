#pragma once
#include "Shader.hpp"

namespace mgl {
	class ProgramException : public AbstractStringException {
		using AbstractStringException::AbstractStringException;
	};

	class Vector;
	class Matrix;

	class Program {
	protected:
		unsigned int m_id;
	public:
		explicit Program();
		explicit Program(const std::initializer_list<Shader>& list);
		~Program();

		void link(const std::initializer_list<Shader>& list);
		void use();
		void send(const std::string fieldName, const float& data);
		void send(const std::string fieldName, const Vector& data);
		void send(const std::string fieldName, const Matrix& data);
	};

	using CustomProgram = Program;
}