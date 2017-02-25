#pragma once
#include <string>

namespace mgl {
	enum class OpenGLVersionMask {
		Core, Compatibility, ES
	};
	enum class DefaultWindowPos {
		Undefined, Centered
	};
}

namespace mgl {
	class AbstractStringException {
	protected:
		std::string m_error;
	public:
		AbstractStringException(const std::string& error) : m_error(error) {}
		AbstractStringException(const char* error) : m_error(error) {}
		const std::string& operator()() const { return m_error; }
	};
}