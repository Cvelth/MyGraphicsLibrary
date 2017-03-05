#include "DefaultProgram.hpp"

mgl::DefaultProgram::DefaultProgram(DefaulProgramType type) : Program() {
	vertexShader = new Shader(ShaderType::Vertex);
	fragmentShader = new Shader(ShaderType::Fragment);
	switch (type) {
		case DefaulProgramType::Vertex1Matrix:
			vertexShader->compileSource(Vertex_1Matrix_Source);
			fragmentShader->compileSource(Fragment_Source);
			break;
		case DefaulProgramType::Vertex6Matrices:
			vertexShader->compileSource(Vertex_6Matrices_Source);
			fragmentShader->compileSource(Fragment_Source);
			break;
	}
	link({*vertexShader, *fragmentShader});
}

mgl::DefaultProgram::~DefaultProgram() {
	delete vertexShader;
	delete fragmentShader;
	Program::~Program();
}

const std::string mgl::DefaultProgram::Vertex_1Matrix_Source =
"#version 140		   											   \n"
"																   \n"
"in vec4 positionVector;										   \n"
"out vec4 theColor;												   \n"
"																   \n"
"uniform vec4 drawingColor;										   \n"
"uniform mat4 transformationMatrix;								   \n"
"																   \n"
"void main() {													   \n"
"	gl_Position = transformationMatrix * positionVector;		   \n"
"	theColor = drawingColor;									   \n"
"}																   \n";

const std::string mgl::DefaultProgram::Vertex_6Matrices_Source =
"#version 140																  \n"
"																			  \n"
"in vec4 positionVector;													  \n"
"out vec4 theColor;															  \n"
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
"#version 140				  \n"
"							  \n"
"in vec4 theColor;			  \n"
"							  \n"
"void main() {				  \n"
"	gl_FragColor = theColor;  \n"
"}							  \n";