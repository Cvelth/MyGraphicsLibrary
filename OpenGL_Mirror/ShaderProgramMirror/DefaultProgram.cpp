#include "DefaultProgram.hpp"

mgl::DefaultProgram::DefaultProgram(DefaulProgramType type) : Program() {
	fragmentShader = new Shader(ShaderType::Fragment);
	fragmentShader->compileSource(Fragment_Source);

	vertexShader = new Shader(ShaderType::Vertex);
	switch (type) {
		case DefaulProgramType::VertexNoMatrices:
			vertexShader->compileSource(Vertex_NoMatrix_Source);
			break;
		case DefaulProgramType::Vertex1Matrix:
			vertexShader->compileSource(Vertex_1Matrix_Source);
			break;
		case DefaulProgramType::Vertex2Matrices:
			vertexShader->compileSource(Vertex_2Matrices_Source);
			break;
		case DefaulProgramType::Vertex6Matrices:
			vertexShader->compileSource(Vertex_6Matrices_Source);
			break;
	}

	link({*vertexShader, *fragmentShader});
}

mgl::DefaultProgram::~DefaultProgram() {
	delete vertexShader;
	delete fragmentShader;
	Program::~Program();
}

const std::string mgl::DefaultProgram::Vertex_NoMatrix_Source =
"#version 330		   														  \n"
"																			  \n"
"attribute vec4 position;													  \n"
"attribute vec4 color;														  \n"
"varying vec4 theColor;														  \n"
"																			  \n"
"uniform vec4 translation;													  \n"
"uniform vec4 scaling;														  \n"
"																			  \n"
"void main() {																  \n"
"	gl_Position = (position * scaling) + translation;						  \n"
"	theColor = color;														  \n"
"}																			  \n";

const std::string mgl::DefaultProgram::Vertex_1Matrix_Source =
"#version 330		   														  \n"
"																			  \n"
"attribute vec4 positionVector;												  \n"
"varying vec4 theColor;														  \n"
"																			  \n"
"uniform vec4 drawingColor;													  \n"
"uniform mat4 transformationMatrix;											  \n"
"																			  \n"
"void main() {																  \n"
"	gl_Position = transformationMatrix * positionVector;					  \n"
"	theColor = drawingColor;												  \n"
"}																			  \n";
																			  
const std::string mgl::DefaultProgram::Vertex_2Matrices_Source =			  
"#version 330																  \n"
"																			  \n"
"attribute vec4 positionVector;												  \n"
"varying vec4 theColor;														  \n"
"																			  \n"
"uniform vec4 drawingColor;													  \n"
"uniform mat4 transformationMatrix;											  \n"
"uniform mat4 projectionMatrix;												  \n"
"																			  \n"
"void main() {																  \n"
"	gl_Position = projectionMatrix * transformationMatrix * positionVector;	  \n"
"	theColor = drawingColor;												  \n"
"}																			  \n";

const std::string mgl::DefaultProgram::Vertex_6Matrices_Source =
"#version 330																  \n"
"																			  \n"
"attribute vec4 positionVector;												  \n"
"varying vec4 theColor;														  \n"
"																			  \n"
"uniform vec4 drawingColor;													  \n"
"uniform mat4 translationMatrix;											  \n"
"uniform mat4 rotationElementMatrix;										  \n"
"uniform mat4 rotationSceneMatrix;											  \n"
"uniform mat4 scalingElementMatrix;											  \n"
"uniform mat4 scalingSceneMatrix;											  \n"
"uniform mat4 projectionMatrix;												  \n"
"																			  \n"
"void main() {																  \n"
"	gl_Position = projectionMatrix * rotationSceneMatrix * scalingSceneMatrix \n"
"		* translationMatrix * rotationElementMatrix * scalingElementMatrix	  \n"
"		* positionVector;												      \n"
"	theColor = drawingColor;												  \n"
"}																			  \n";

const std::string mgl::DefaultProgram::Fragment_Source =
"#version 140																  \n"
"																			  \n"
"varying vec4 theColor;													      \n"
"																			  \n"
"void main() {																  \n"
"	gl_FragColor = theColor;												  \n"
"}																			  \n";