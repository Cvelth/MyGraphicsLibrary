#pragma once
#include "OpenGL_Mirror\EnumsMirror\EnumsMirror.hpp"
#include "Shader.hpp"

namespace mgl {
	namespace Exceptions {
		class ProgramException : public AbstractStringException {
			using AbstractStringException::AbstractStringException;
		};
	}
	namespace math {
		class Vector;
		class Matrix;
	}

	class Program;
	class UniformVariable {
		friend Program;
	private:
		std::string m_variable_name;
		int m_location;
		UniformType m_type;
	protected:
		explicit UniformVariable(std::string name, int location, UniformType type);
	public:
		explicit UniformVariable(std::string name, UniformType type);
	};

	class Program {
	protected:
		unsigned int m_id;
	public:
		explicit Program();
		explicit Program(const std::initializer_list<Shader>& list);
		~Program();

		void link(const std::initializer_list<Shader>& list);
		void use();
		UniformVariable getUniform(const std::string fieldName);
		void sendUniform(UniformVariable& variable, const float& data);
		void sendUniform(UniformVariable& variable, const math::Vector& data);
		void sendUniform(UniformVariable& variable, const math::Matrix& data);
		void enableAttrib(const std::string fieldName, size_t size = 4, 
						 bool normalized = false, size_t stride = 4, size_t shift = 0);
	};

	using CustomProgram = Program;
}