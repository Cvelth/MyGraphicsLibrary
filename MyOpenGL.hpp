#pragma once

#if defined MGL_INCLUDE_ALL
	#define MGL_INCLUDE_MATH
	#define MGL_INCLUDE_WINDOWS
	#define MGL_INCLUDE_DRAWABLE_OBJECT
	#define MGL_INCLUDE_PRIMITIVES
	#define MGL_INCLUDE_DEFAULT_PRIMITIVES
	#define MGL_INCLUDE_SHADER_PROGRAM_MIRROR
	#define MGL_INCLUDE_DEFAULT_SHADER_PROGRAM
	#define MGL_INCLUDE_OPENGL_FUNCTIONS_MIRROR
	#define MGL_INCLUDE_OPENGL_EXPERIMENTAL_FUNCTIONS_MIRROR
	#define MGL_INCLUDE_OPENGL_BASIC_TYPES_MIRROR
	#define MGL_INCLUDE_OPENGL_ACCESS
#endif

#if defined MGL_DEFAULT_INCLUDE
	#define MGL_INCLUDE_MATH
	#define MGL_INCLUDE_WINDOWS
	#define MGL_INCLUDE_DRAWABLE_OBJECT
	#define MGL_INCLUDE_PRIMITIVES
	#define MGL_INCLUDE_SHADER_PROGRAM_MIRROR
	#define MGL_INCLUDE_OPENGL_BASIC_TYPES_MIRROR
	#define MGL_INCLUDE_DEFAULT_HEADERS
#endif

#if defined MGL_INCLUDE_MATH
	#include "Math\Matrix.hpp"
	#include "Math\Vector.hpp"
#endif

#if defined MGL_INCLUDE_WINDOWS
	#if defined MGL_WINDOW_USE_LOOP
		#include "Windows\AbstractLoopWindow.hpp"
		namespace mgl {
			class Window : public AbstractLoopWindow {
			public:
				using AbstractLoopWindow::AbstractLoopWindow;
		};
	#else
		#include "Windows\AbstractWindow.hpp"
		namespace mgl {
			class Window : public AbstractWindow {
			public:
				using AbstractWindow::AbstractWindow;
			};
		}
	#endif
#endif

#if defined MGL_INCLUDE_DRAWABLE_OBJECT
	#include "Primitive\AbstractDrawableObject.hpp"
	namespace mgl {
		class DrawableObject : public AbstractDrawableObject {
		public:
			using AbstractDrawableObject::AbstractDrawableObject;
		};
	}
#endif
#if defined MGL_INCLUDE_PRIMITIVES
	#include "Primitive\Primitive.hpp"
#endif
#if defined MGL_INCLUDE_DEFAULT_PRIMITIVES
	#include "Primitive\DefaultPrimitives.hpp"
#endif

#if defined MGL_INCLUDE_SHADER_PROGRAM_MIRROR
	#include "OpenGL_Mirror\ShaderProgramMirror\Program.hpp"
#endif
#if defined MGL_INCLUDE_DEFAULT_SHADER_PROGRAM
	#include "OpenGL_Mirror\ShaderProgramMirror\DefaultProgram.hpp"
#endif

#if defined MGL_INCLUDE_OPENGL_FUNCTIONS_MIRROR
	#include "OpenGL_Mirror\FunctionsMirror\FunctionsMirror.hpp"
	#define MGL_INCLUDE_OPENGL_BASIC_TYPES_MIRROR
#endif
#if defined MGL_INCLUDE_OPENGL_EXPERIMENTAL_FUNCTIONS_MIRROR
	#include "OpenGL_Mirror\FunctionsMirror\ExperimentalFunctionsMirror.hpp"
#endif

#if defined MGL_INCLUDE_OPENGL_BASIC_TYPES_MIRROR
	#include "OpenGL_Mirror\BasicTypes\Buffer.hpp"
	#include "OpenGL_Mirror\BasicTypes\Color.hpp"
#endif

#if defined MGL_INCLUDE_DEFAULT_HEADERS
	#include "OpenGL_Mirror\BasicTypes\BasicColors.hpp"
#endif

#if defined MGL_INCLUDE_OPENGL_ACCESS
	#include "OpenGL_Mirror\OpenGL_Dependency\OpenGL.h"
#endif