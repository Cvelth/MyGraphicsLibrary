#pragma once
#include <string>
#include "MGL\Events\EventEnums.hpp"

struct GLFWwindow;

namespace mgl {
	class AbstractEventHandler {

	public:
		virtual void mouseButtonEvent(GLFWwindow* w, MouseButton button, 
									  MouseAction action, Mods mods) abstract;
		virtual void mouseMoveEvent(GLFWwindow* w, double x, double y) abstract;
		virtual void mouseScrollEvent(GLFWwindow* w, double x, double y) abstract;
		virtual void mouseEnterEvent(GLFWwindow* w, MouseEnterAction action) abstract;
		virtual void keyEvent(GLFWwindow* w, Key key, int scancode,
							  KeyAction action, Mods mods) abstract;
		virtual void characterEvent(GLFWwindow* w, unsigned int codepoint) abstract;
		virtual void characterEventWithModificators(GLFWwindow* w, unsigned int codepoint, 
													Mods mods) abstract;
		virtual void fileDropEvent(GLFWwindow* w, int count, const char **paths) abstract;
		virtual void resizeEvent(GLFWwindow* w, int x, int y) abstract;
		virtual void joystickEvent(int joy, int event) abstract;
		virtual void errorEvent(int error, std::string description) abstract;
	};
}