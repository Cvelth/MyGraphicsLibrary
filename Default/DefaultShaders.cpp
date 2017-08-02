#include "DefaultShaders.hpp"
#include "OpenGL_Mirror\ClassesMirror\Shader.hpp"

const char* Vertex_NoMatrix_2Vectors_Shader_Source =
"#version 330		   														\n"
"																			\n"
"attribute vec4 position;													\n"
"attribute vec4 color;														\n"
"varying vec4 outColor;														\n"
"																			\n"
"uniform vec4 translation;													\n"
"uniform vec4 scaling;														\n"
"																			\n"
"void main() {																\n"
"	gl_Position = position * scaling + translation;							\n"
"	outColor = color;														\n"
"}																			\n";

const char* Vertex_1Matrix_2Vectors_Shader_Source =
"#version 330		   														\n"
"																			\n"
"attribute vec4 position;													\n"
"attribute vec4 color;														\n"
"varying vec4 outColor;														\n"
"																			\n"
"uniform vec4 translation;													\n"
"uniform vec4 scaling;														\n"
"uniform mat4 projection;													\n"
"																			\n"
"void main() {																\n"
"	gl_Position = projection * (position * scaling + translation);			\n"
"	outColor = color;														\n"
"}																			\n";

const char* Vertex_1Matrix_Shader_Source =
"#version 330		   														\n"
"																			\n"
"attribute vec4 position;													\n"
"attribute vec4 color;														\n"
"varying vec4 outColor;														\n"
"																			\n"
"uniform mat4 transformation;												\n"
"																			\n"
"void main() {																\n"
"	gl_Position = transformation * position;								\n"
"	outColor = color;														\n"
"}																			\n";

const char* Vertex_2Matrices_Shader_Source =
"#version 330																\n"
"																			\n"
"attribute vec4 position;													\n"
"attribute vec4 color;														\n"
"varying vec4 outColor;														\n"
"																			\n"
"uniform mat4 transformation;												\n"
"uniform mat4 projection;													\n"
"																			\n"
"void main() {																\n"
"	gl_Position = projection * transformation * position;					\n"
"	outColor = color;														\n"
"}																			\n";

const char* Vertex_6Matrices_Shader_Source =
"#version 330																\n"
"																			\n"
"attribute vec4 position;													\n"
"attribute vec4 color;														\n"
"varying vec4 theColor;														\n"
"																			\n"
"uniform mat4 translation;													\n"
"uniform mat4 elementRotation;												\n"
"uniform mat4 sceneRotation;												\n"
"uniform mat4 elementScaling;												\n"
"uniform mat4 sceneScaling;													\n"
"uniform mat4 projection;													\n"
"																			\n"
"void main() {																\n"
"	gl_Position = projection * sceneRotation * sceneScaling * translation	\n"
"				* elementRotation * elementScaling * position;				\n"
"	outColor = color;														\n"
"}																			\n";

const char* Default_Fragment_Shader_Source =
"#version 140																\n"
"																			\n"
"varying vec4 outColor;													    \n"
"																			\n"
"void main() {																\n"
"	gl_FragColor = outColor;												\n"
"}																			\n";

mgl::Shader* mgl::compileDefaultFragmentShader() {
	return mgl::Shader::compileShaderSource(mgl::ShaderType::Fragment, Default_Fragment_Shader_Source);
}

mgl::Shader* mgl::compileDefaultVertexShader(DefaultVertexShaderInput input) {
	switch (input) {
		case DefaultVertexShaderInput::vec4x2:
			return mgl::Shader::compileShaderSource(mgl::ShaderType::Vertex, Vertex_NoMatrix_2Vectors_Shader_Source);
		case DefaultVertexShaderInput::vec4x2_mat4x1:
			return mgl::Shader::compileShaderSource(mgl::ShaderType::Vertex, Vertex_1Matrix_2Vectors_Shader_Source);
		case DefaultVertexShaderInput::mat4x1:
			return mgl::Shader::compileShaderSource(mgl::ShaderType::Vertex, Vertex_1Matrix_Shader_Source);
		case DefaultVertexShaderInput::mat4x2:
			return mgl::Shader::compileShaderSource(mgl::ShaderType::Vertex, Vertex_2Matrices_Shader_Source);
		case DefaultVertexShaderInput::mat4x6:
			return mgl::Shader::compileShaderSource(mgl::ShaderType::Vertex, Vertex_6Matrices_Shader_Source);
		default: throw Exceptions::IncorrectEnumException(" ");
	}
}