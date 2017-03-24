#pragma once
#include "AbstractEventHandler.hpp"

namespace mgl {
	class EmptyEventHandler : public AbstractEventHandler {

	public:
		virtual void mouseButtonEvent(GLFWwindow* w, MouseButton button,
									  MouseAction action, Mods mods) override { }
		virtual void mouseMoveEvent(GLFWwindow* w, double x, double y) override { }
		virtual void mouseScrollEvent(GLFWwindow* w, double x, double y) override { }
		virtual void mouseEnterEvent(GLFWwindow* w, MouseEnterAction action) override { }
		virtual void keyEvent(GLFWwindow* w, Key key, int scancode,
							  KeyAction action, Mods mods) override { }
		virtual void characterEvent(GLFWwindow* w, unsigned int codepoint) override { }
		virtual void characterEventWithModificators(GLFWwindow* w, unsigned int codepoint,
													Mods mods) override { }
		virtual void fileDropEvent(GLFWwindow* w, int count, const char **paths) override { }
		virtual void resizeEvent(GLFWwindow* w, int x, int y) override { }
		virtual void joystickEvent(int joy, int event) override { }
		virtual void errorEvent(int error, std::string description) override { }
	};
}