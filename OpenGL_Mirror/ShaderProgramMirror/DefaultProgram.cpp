#include "DefaultProgram.hpp"

mgl::DefaultProgram::DefaultProgram(DefaulProgramType type) : Program() {
	fragmentShader = new Shader(ShaderType::Fragment);
	fragmentShader->compileSource(Fragment_Source);

	vertexShader = new Shader(ShaderType::Vertex);
	switch (type) {
		case DefaulProgramType::Vertex_2Vectors:
			vertexShader->compileSource(Vertex_NoMatrix_2Vectors_Source);
			break;
		case DefaulProgramType::Vertex_1Matrix_2Vectors:
			vertexShader->compileSource(Vertex_1Matrix_2Vectors_Source);
			break;
		case DefaulProgramType::Vertex_1Matrix:
			vertexShader->compileSource(Vertex_1Matrix_Source);
			break;
		case DefaulProgramType::Vertex_2Matrices:
			vertexShader->compileSource(Vertex_2Matrices_Source);
			break;
		case DefaulProgramType::Vertex_6Matrices:
			vertexShader->compileSource(Vertex_6Matrices_Source);
			break;
	}

	link({*vertexShader, *fragmentShader});
	delete fragmentShader;
	delete vertexShader;
}

mgl::DefaultProgram::DefaultProgram(Shader* vertex_shader) : Program() {
	fragmentShader = new Shader(ShaderType::Fragment);
	fragmentShader->compileSource(Fragment_Source);
	vertexShader = vertex_shader;

	link({*vertexShader, *fragmentShader});
}

mgl::DefaultProgram::~DefaultProgram() {
	delete vertexShader;
	delete fragmentShader;
	Program::~Program();
}

const std::string mgl::DefaultProgram::Vertex_NoMatrix_2Vectors_Source =
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

const std::string mgl::DefaultProgram::Vertex_1Matrix_2Vectors_Source =
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

const std::string mgl::DefaultProgram::Vertex_1Matrix_Source =
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
																			
const std::string mgl::DefaultProgram::Vertex_2Matrices_Source =			
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
																			
const std::string mgl::DefaultProgram::Vertex_6Matrices_Source =			
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
																			
const std::string mgl::DefaultProgram::Fragment_Source =					
"#version 140																\n"
"																			\n"
"varying vec4 outColor;													    \n"
"																			\n"
"void main() {																\n"
"	gl_FragColor = outColor;												\n"
"}																			\n";