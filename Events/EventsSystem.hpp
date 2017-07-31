#pragma once
#include "AbstractEventHandler.hpp"

struct GLFWwindow;

namespace mgl {
	class EventsSystem {
	protected:
		static AbstractEventHandler* e;

	public:
		static void setHandler(AbstractEventHandler* h) {
			e = h;
		}
	public:
		static void mouseButtonEvent(GLFWwindow* w, int button, int action, int mods) {
			e->mouseButtonEvent(w, _switchMouseButton(button),
								_switchMouseAction(action), _switchMods(mods));
		}
		static void mouseMoveEvent(GLFWwindow* w, double x, double y) {
			e->mouseMoveEvent(w, x, y);
		}
		static void mouseEnterEvent(GLFWwindow* w, int ent) {
			e->mouseEnterEvent(w, _switchMouseEnterAction(ent));
		}
		static void scrollEvent(GLFWwindow* w, double x, double y) {
			e->mouseScrollEvent(w, x, y);
		}
		static void keyEvent(GLFWwindow* w, int key, int scancode, int action, int mods) {
			e->keyEvent(w, _switchKey(key), scancode, _switchKeyAction(action), _switchMods(mods));
		}
		static void characterEvent(GLFWwindow* w, unsigned int codepoint) {
			e->characterEvent(w, codepoint);
		}
		static void characterEventWithModificators(GLFWwindow* w, unsigned int codepoint, int mods) {
			e->characterEventWithModificators(w, codepoint, _switchMods(mods));
		}
		static void fileDropEvent(GLFWwindow* w, int count, const char **paths) {
			e->fileDropEvent(w, count, paths);
		}		
		static void resizeEvent(GLFWwindow* w, int x, int y) {
			e->resizeEvent(w, x, y);
		}
		static void joystickEvent(int joy, int event) {
			e->joystickEvent(joy, event);
		}
		static void errorEvent(int error, const char* description) {
			e->errorEvent(error, description);
		}
	};
}