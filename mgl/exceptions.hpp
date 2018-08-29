#pragma once
#include <exception>
namespace mgl::Exceptions {
	class MGLException : std::exception {
	public: using std::exception::exception;
	};
}
#define DefineNewMGLException(name) namespace mgl::Exceptions {class name : public mgl::Exceptions::MGLException {public: using MGLException::MGLException;};}