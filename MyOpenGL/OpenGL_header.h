#pragma once
#include <glew.h>
#include <SDL.h>
//#include <SDL_opengl.h>

#include "AbstractException.hpp"
namespace mgl {
	class InitializationException : public AbstractStringException { 
		using AbstractStringException::AbstractStringException;
	};
}