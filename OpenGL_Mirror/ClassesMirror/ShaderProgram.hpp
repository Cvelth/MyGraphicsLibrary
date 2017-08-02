#pragma once
#include "SharedHeaders\Exceptions.hpp"
DefineNewException(ProgramException)

namespace mgl {
	class Shader;
	class ShaderVariable;
	class VertexArray;
	namespace math {
		class Vector;
		class Matrix;
	}

	class ShaderProgram {
	protected:
		unsigned int m_id;
		VertexArray* m_vao;
	public:
		explicit ShaderProgram();
		explicit ShaderProgram(VertexArray& vao);
		explicit ShaderProgram(const std::initializer_list<Shader>& list);
		explicit ShaderProgram(const std::initializer_list<Shader>& list, VertexArray& vao);
		~ShaderProgram();

		void link(const std::initializer_list<Shader>& list);
		void use();

		bool isLinked();

		ShaderVariable* getUniform(const char* fieldName);
		ShaderVariable* enableAttribWithNormalization(const char* fieldName, size_t size = 4,
													  bool normalized = false, size_t stride = 4, size_t shift = 0);
		ShaderVariable* enableAttrib(const char* fieldName, size_t size = 4,
									 size_t stride = 4, size_t shift = 0);

		void sendUniform(ShaderVariable* variable, const float& data);
		void sendUniform(ShaderVariable* variable, const math::Vector& data);
		void sendUniform(ShaderVariable* variable, const math::Matrix& data);
	};
}