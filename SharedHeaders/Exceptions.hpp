#pragma once
#include <exception>
namespace mgl {
	namespace Exceptions {
		class MyOpenGLException : std::exception {
		protected:
			const char* m_error;
		public:
			MyOpenGLException(char* error) : m_error(error) {}
			MyOpenGLException(const char* error) : m_error(error) {}
			virtual const char* what() const override {	return m_error; }
			const char* operator*() const { return what(); }
		};
	}
}
#define DefineNewException(name) namespace mgl { namespace Exceptions {class name : public mgl::Exceptions::MyOpenGLException {using MyOpenGLException::MyOpenGLException;};}}