#include "OpenGL_Mirror\OpenGL_Dependency\OpenGL.h"
#include "EventEnums.hpp"
#include <type_traits>

mgl::MouseButton mgl::_switchMouseButton(int b) {
	switch (b) {
		case GLFW_MOUSE_BUTTON_1: return MouseButton::b_1;
		case GLFW_MOUSE_BUTTON_2: return MouseButton::b_2;
		case GLFW_MOUSE_BUTTON_3: return MouseButton::b_3;
		case GLFW_MOUSE_BUTTON_4: return MouseButton::b_4;
		case GLFW_MOUSE_BUTTON_5: return MouseButton::b_5;
		case GLFW_MOUSE_BUTTON_6: return MouseButton::b_6;
		case GLFW_MOUSE_BUTTON_7: return MouseButton::b_7;
		case GLFW_MOUSE_BUTTON_8: return MouseButton::b_8;
	}
}

mgl::MouseAction mgl::_switchMouseAction(int a) {
	switch (a) {
		case GLFW_PRESS: return MouseAction::press;
		case GLFW_RELEASE: return MouseAction::release;
	}
}

using ModsType = std::underlying_type_t <mgl::Mods>;
mgl::Mods mgl::operator|(mgl::Mods l, mgl::Mods r) {
	return mgl::Mods(static_cast<ModsType>(l) | static_cast<ModsType>(r));
}
mgl::Mods mgl::operator|=(mgl::Mods l, mgl::Mods r) {
	return l = l | r;
}
mgl::Mods mgl::operator&(mgl::Mods l, mgl::Mods r) {
	return mgl::Mods(static_cast<ModsType>(l) & static_cast<ModsType>(r));
}
mgl::Mods mgl::operator&=(mgl::Mods l, mgl::Mods r) {
	return l = l & r;
}

mgl::Mods mgl::_switchMods(int m) {
	return mgl::Mods(m);
}

mgl::MouseEnterAction mgl::_switchMouseEnterAction(int a) {
	switch (a) {
		case GLFW_TRUE: return MouseEnterAction::enter;
		case GLFW_FALSE: return MouseEnterAction::leave;
	}
}

mgl::Key mgl::_switchKey(int k) {
	switch (k) {
		case GLFW_KEY_UNKNOWN: return Key::unknown;
		case GLFW_KEY_SPACE: return Key::space;
		case GLFW_KEY_APOSTROPHE: return Key::apostrophe;
		case GLFW_KEY_COMMA: return Key::comma;
		case GLFW_KEY_MINUS: return Key::minus;
		case GLFW_KEY_PERIOD: return Key::period;
		case GLFW_KEY_SLASH: return Key::slash;
		case GLFW_KEY_0: return Key::zero;
		case GLFW_KEY_1: return Key::one;
		case GLFW_KEY_2: return Key::two;
		case GLFW_KEY_3: return Key::three;
		case GLFW_KEY_4: return Key::four;
		case GLFW_KEY_5: return Key::five;
		case GLFW_KEY_6: return Key::six;
		case GLFW_KEY_7: return Key::seven;
		case GLFW_KEY_8: return Key::eight;
		case GLFW_KEY_9: return Key::nine;
		case GLFW_KEY_SEMICOLON: return Key::semicolon;
		case GLFW_KEY_EQUAL: return Key::equal;
		case GLFW_KEY_A: return Key::a;
		case GLFW_KEY_B: return Key::b;
		case GLFW_KEY_C: return Key::c;
		case GLFW_KEY_D: return Key::d;
		case GLFW_KEY_E: return Key::e;
		case GLFW_KEY_F: return Key::f;
		case GLFW_KEY_G: return Key::g;
		case GLFW_KEY_H: return Key::h;
		case GLFW_KEY_I: return Key::i;
		case GLFW_KEY_J: return Key::j;
		case GLFW_KEY_K: return Key::k;
		case GLFW_KEY_L: return Key::l;
		case GLFW_KEY_M: return Key::m;
		case GLFW_KEY_N: return Key::n;
		case GLFW_KEY_O: return Key::o;
		case GLFW_KEY_P: return Key::p;
		case GLFW_KEY_Q: return Key::q;
		case GLFW_KEY_R: return Key::r;
		case GLFW_KEY_S: return Key::s;
		case GLFW_KEY_T: return Key::t;
		case GLFW_KEY_U: return Key::u;
		case GLFW_KEY_V: return Key::v;
		case GLFW_KEY_W: return Key::w;
		case GLFW_KEY_X: return Key::x;
		case GLFW_KEY_Y: return Key::y;
		case GLFW_KEY_Z: return Key::z;
		case GLFW_KEY_LEFT_BRACKET: return Key::bracket_left;
		case GLFW_KEY_BACKSLASH: return Key::backslash;
		case GLFW_KEY_RIGHT_BRACKET: return Key::bracket_right;
		case GLFW_KEY_GRAVE_ACCENT: return Key::grave_accent;
		case GLFW_KEY_WORLD_1: return Key::world_key_1;
		case GLFW_KEY_WORLD_2: return Key::world_key_2;
		case GLFW_KEY_ESCAPE: return Key::escape;
		case GLFW_KEY_ENTER: return Key::enter;
		case GLFW_KEY_TAB: return Key::tab;
		case GLFW_KEY_BACKSPACE: return Key::backspace;
		case GLFW_KEY_INSERT: return Key::insert;
		case GLFW_KEY_DELETE: return Key::delete_key;
		case GLFW_KEY_RIGHT: return Key::right;
		case GLFW_KEY_LEFT: return Key::left;
		case GLFW_KEY_DOWN: return Key::down;
		case GLFW_KEY_UP: return Key::up;
		case GLFW_KEY_PAGE_UP: return Key::page_up;
		case GLFW_KEY_PAGE_DOWN: return Key::page_down;
		case GLFW_KEY_HOME: return Key::home;
		case GLFW_KEY_END: return Key::end;
		case GLFW_KEY_CAPS_LOCK: return Key::caps_lock;
		case GLFW_KEY_SCROLL_LOCK: return Key::scroll_lock;
		case GLFW_KEY_NUM_LOCK: return Key::num_lock;
		case GLFW_KEY_PRINT_SCREEN: return Key::print_screen;
		case GLFW_KEY_PAUSE: return Key::pause;
		case GLFW_KEY_F1: return Key::f1;
		case GLFW_KEY_F2: return Key::f2;
		case GLFW_KEY_F3: return Key::f3;
		case GLFW_KEY_F4: return Key::f4;
		case GLFW_KEY_F5: return Key::f5;
		case GLFW_KEY_F6: return Key::f6;
		case GLFW_KEY_F7: return Key::f7;
		case GLFW_KEY_F8: return Key::f8;
		case GLFW_KEY_F9: return Key::f9;
		case GLFW_KEY_F10: return Key::f10;
		case GLFW_KEY_F11: return Key::f11;
		case GLFW_KEY_F12: return Key::f12;
		case GLFW_KEY_F13: return Key::f13;
		case GLFW_KEY_F14: return Key::f14;
		case GLFW_KEY_F15: return Key::f15;
		case GLFW_KEY_F16: return Key::f16;
		case GLFW_KEY_F17: return Key::f17;
		case GLFW_KEY_F18: return Key::f18;
		case GLFW_KEY_F19: return Key::f19;
		case GLFW_KEY_F20: return Key::f20;
		case GLFW_KEY_F21: return Key::f21;
		case GLFW_KEY_F22: return Key::f22;
		case GLFW_KEY_F23: return Key::f23;
		case GLFW_KEY_F24: return Key::f24;
		case GLFW_KEY_F25: return Key::f25;
		case GLFW_KEY_KP_0: return Key::zero_kp;
		case GLFW_KEY_KP_1: return Key::one_kp;
		case GLFW_KEY_KP_2: return Key::two_kp;
		case GLFW_KEY_KP_3: return Key::three_kp;
		case GLFW_KEY_KP_4: return Key::four_kp;
		case GLFW_KEY_KP_5: return Key::five_kp;
		case GLFW_KEY_KP_6: return Key::six_kp;
		case GLFW_KEY_KP_7: return Key::seven_kp;
		case GLFW_KEY_KP_8: return Key::eight_kp;
		case GLFW_KEY_KP_9: return Key::nine_kp;
		case GLFW_KEY_KP_DECIMAL: return Key::decimal_kp;
		case GLFW_KEY_KP_DIVIDE: return Key::divide_kp;
		case GLFW_KEY_KP_MULTIPLY: return Key::multiply_kp;
		case GLFW_KEY_KP_SUBTRACT: return Key::subtract_kp;
		case GLFW_KEY_KP_ADD: return Key::add_kp;
		case GLFW_KEY_KP_ENTER: return Key::enter_kp;
		case GLFW_KEY_KP_EQUAL: return Key::equal_kp;
		case GLFW_KEY_LEFT_SHIFT: return Key::shift_left;
		case GLFW_KEY_LEFT_CONTROL: return Key::control_left;
		case GLFW_KEY_LEFT_ALT: return Key::alt_left;
		case GLFW_KEY_LEFT_SUPER: return Key::super_left;
		case GLFW_KEY_RIGHT_SHIFT: return Key::shift_right;
		case GLFW_KEY_RIGHT_CONTROL: return Key::control_right;
		case GLFW_KEY_RIGHT_ALT: return Key::alt_right;
		case GLFW_KEY_RIGHT_SUPER: return Key::super_right;
		case GLFW_KEY_MENU: return Key::menu;
	}
}

mgl::KeyAction mgl::_switchKeyAction(int a) {
	switch (a) {
		case GLFW_PRESS: return KeyAction::press;
		case GLFW_RELEASE: return KeyAction::release;
		case GLFW_REPEAT: return KeyAction::repeat;
	}
}
