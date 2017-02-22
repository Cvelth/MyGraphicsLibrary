#pragma once
#include <string>

#include <glew.h>
#include <SDL.h>
#include <SDL_opengl.h>

#include "Enums.hpp"

namespace mgl {
	class AbstractStringException {
	protected:
		std::string m_error;
	public:
		AbstractStringException(const std::string& error) : m_error(error) {}
		AbstractStringException(const char* error) : m_error(error) {}
		const std::string& operator()() const { return m_error; }
	};

	class InitializationException : public AbstractStringException { 
		using AbstractStringException::AbstractStringException;
	};
}