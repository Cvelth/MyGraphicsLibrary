#pragma once
#include <exception>
namespace mgl::Exceptions {
	class MGLException : std::exception {
	public: using std::exception::exception;
	};
}
#define DefineNewMGLException(name) namespace mgl { namespace Exceptions {class name : public mgl::Exceptions::MyOpenGLException {public: using MyOpenGLException::MyOpenGLException;};}}