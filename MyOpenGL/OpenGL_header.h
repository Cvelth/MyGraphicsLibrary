#pragma once
#include <string>

#include <glew.h>
#include <SDL.h>
#include <SDL_opengl.h>

#include "Enums.hpp"
#include "AbstractException.hpp"

namespace mgl {
	class InitializationException : public AbstractStringException { 
		using AbstractStringException::AbstractStringException;
	};
}