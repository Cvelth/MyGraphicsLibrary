#include "mgl\dependencies\WindowLibrary_Dependency\window_dependency.hpp"
#include "Events.hpp"

int mgl::enum_converter::convert(MouseButton const& v) {
	switch (v) {
		case MouseButton::b_1: return GLFW_MOUSE_BUTTON_1;
		case MouseButton::b_2: return GLFW_MOUSE_BUTTON_2;
		case MouseButton::b_3: return GLFW_MOUSE_BUTTON_3;
		case MouseButton::b_4: return GLFW_MOUSE_BUTTON_4;
		case MouseButton::b_5: return GLFW_MOUSE_BUTTON_5;
		case MouseButton::b_6: return GLFW_MOUSE_BUTTON_6;
		case MouseButton::b_7: return GLFW_MOUSE_BUTTON_7;
		case MouseButton::b_8: return GLFW_MOUSE_BUTTON_8;
		default: throw Exceptions::EnumConvertionError();
	}
}
mgl::MouseButton mgl::enum_converter::convert_to_MouseButton(int v) {
	switch (v) {
		case GLFW_MOUSE_BUTTON_1: return MouseButton::b_1;
		case GLFW_MOUSE_BUTTON_2: return MouseButton::b_2;
		case GLFW_MOUSE_BUTTON_3: return MouseButton::b_3;
		case GLFW_MOUSE_BUTTON_4: return MouseButton::b_4;
		case GLFW_MOUSE_BUTTON_5: return MouseButton::b_5;
		case GLFW_MOUSE_BUTTON_6: return MouseButton::b_6;
		case GLFW_MOUSE_BUTTON_7: return MouseButton::b_7;
		case GLFW_MOUSE_BUTTON_8: return MouseButton::b_8;
		default: throw Exceptions::EnumConvertionError();
	}
}
int mgl::enum_converter::convert(MouseAction const& v) {
	switch (v) {
		case MouseAction::press: return GLFW_PRESS;
		case MouseAction::release: return GLFW_RELEASE;
		default: throw Exceptions::EnumConvertionError();
	}
}
mgl::MouseAction mgl::enum_converter::convert_to_MouseAction(int v) {
	switch (v) {
		case GLFW_PRESS: return MouseAction::press;
		case GLFW_RELEASE: return MouseAction::release;
		default: throw Exceptions::EnumConvertionError();
	}
}
int mgl::enum_converter::convert(Modificators const& v) {
	return int(v);
}
mgl::Modificators mgl::enum_converter::convert_to_Modificators(int v) {
	return mgl::Modificators(v);
}
using ModsType = std::underlying_type_t <mgl::Modificators>;
mgl::Modificators mgl::operator|(Modificators l, Modificators r) {
	return mgl::Modificators(static_cast<ModsType>(l) | static_cast<ModsType>(r));
}
mgl::Modificators mgl::operator|=(Modificators l, Modificators r) {
	return l = l | r;
}
mgl::Modificators mgl::operator&(Modificators l, Modificators r) {
	return mgl::Modificators(static_cast<ModsType>(l) & static_cast<ModsType>(r));
}
mgl::Modificators mgl::operator&=(Modificators l, Modificators r) {
	return l = l & r;
}
int mgl::enum_converter::convert(MouseEnterAction const& v) {
	switch (v) {
		case MouseEnterAction::enter: return GLFW_TRUE;
		case MouseEnterAction::leave: return GLFW_FALSE;
		default: throw Exceptions::EnumConvertionError();
	}
}
mgl::MouseEnterAction mgl::enum_converter::convert_to_MouseEnterAction(int v) {
	switch (v) {
		case GLFW_TRUE: return MouseEnterAction::enter;
		case GLFW_FALSE: return MouseEnterAction::leave;
		default: throw Exceptions::EnumConvertionError();
	}
}
int mgl::enum_converter::convert(Key const& v) {
	switch (v) {
		case Key::unknown: return GLFW_KEY_UNKNOWN;
		case Key::space: return GLFW_KEY_SPACE;
		case Key::apostrophe: return GLFW_KEY_APOSTROPHE;
		case Key::comma: return GLFW_KEY_COMMA;
		case Key::minus: return GLFW_KEY_MINUS;
		case Key::period: return GLFW_KEY_PERIOD;
		case Key::slash: return GLFW_KEY_SLASH;
		case Key::zero: return GLFW_KEY_0;
		case Key::one: return GLFW_KEY_1;
		case Key::two: return GLFW_KEY_2;
		case Key::three: return GLFW_KEY_3;
		case Key::four: return GLFW_KEY_4;
		case Key::five: return GLFW_KEY_5;
		case Key::six: return GLFW_KEY_6;
		case Key::seven: return GLFW_KEY_7;
		case Key::eight: return GLFW_KEY_8;
		case Key::nine: return GLFW_KEY_9;
		case Key::semicolon: return GLFW_KEY_SEMICOLON;
		case Key::equal: return GLFW_KEY_EQUAL;
		case Key::a: return GLFW_KEY_A;
		case Key::b: return GLFW_KEY_B;
		case Key::c: return GLFW_KEY_C;
		case Key::d: return GLFW_KEY_D;
		case Key::e: return GLFW_KEY_E;
		case Key::f: return GLFW_KEY_F;
		case Key::g: return GLFW_KEY_G;
		case Key::h: return GLFW_KEY_H;
		case Key::i: return GLFW_KEY_I;
		case Key::j: return GLFW_KEY_J;
		case Key::k: return GLFW_KEY_K;
		case Key::l: return GLFW_KEY_L;
		case Key::m: return GLFW_KEY_M;
		case Key::n: return GLFW_KEY_N;
		case Key::o: return GLFW_KEY_O;
		case Key::p: return GLFW_KEY_P;
		case Key::q: return GLFW_KEY_Q;
		case Key::r: return GLFW_KEY_R;
		case Key::s: return GLFW_KEY_S;
		case Key::t: return GLFW_KEY_T;
		case Key::u: return GLFW_KEY_U;
		case Key::v: return GLFW_KEY_V;
		case Key::w: return GLFW_KEY_W;
		case Key::x: return GLFW_KEY_X;
		case Key::y: return GLFW_KEY_Y;
		case Key::z: return GLFW_KEY_Z;
		case Key::bracket_left: return GLFW_KEY_LEFT_BRACKET;
		case Key::backslash: return GLFW_KEY_BACKSLASH;
		case Key::bracket_right: return GLFW_KEY_RIGHT_BRACKET;
		case Key::grave_accent: return GLFW_KEY_GRAVE_ACCENT;
		case Key::world_key_1: return GLFW_KEY_WORLD_1;
		case Key::world_key_2: return GLFW_KEY_WORLD_2;
		case Key::escape: return GLFW_KEY_ESCAPE;
		case Key::enter: return GLFW_KEY_ENTER;
		case Key::tab: return GLFW_KEY_TAB;
		case Key::backspace: return GLFW_KEY_BACKSPACE;
		case Key::insert: return GLFW_KEY_INSERT;
		case Key::delete_key: return GLFW_KEY_DELETE;
		case Key::right: return GLFW_KEY_RIGHT;
		case Key::left: return GLFW_KEY_LEFT;
		case Key::down: return GLFW_KEY_DOWN;
		case Key::up: return GLFW_KEY_UP;
		case Key::page_up: return GLFW_KEY_PAGE_UP;
		case Key::page_down: return GLFW_KEY_PAGE_DOWN;
		case Key::home: return GLFW_KEY_HOME;
		case Key::end: return GLFW_KEY_END;
		case Key::caps_lock: return GLFW_KEY_CAPS_LOCK;
		case Key::scroll_lock: return GLFW_KEY_SCROLL_LOCK;
		case Key::num_lock: return GLFW_KEY_NUM_LOCK;
		case Key::print_screen: return GLFW_KEY_PRINT_SCREEN;
		case Key::pause: return GLFW_KEY_PAUSE;
		case Key::f1: return GLFW_KEY_F1;
		case Key::f2: return GLFW_KEY_F2;
		case Key::f3: return GLFW_KEY_F3;
		case Key::f4: return GLFW_KEY_F4;
		case Key::f5: return GLFW_KEY_F5;
		case Key::f6: return GLFW_KEY_F6;
		case Key::f7: return GLFW_KEY_F7;
		case Key::f8: return GLFW_KEY_F8;
		case Key::f9: return GLFW_KEY_F9;
		case Key::f10: return GLFW_KEY_F10;
		case Key::f11: return GLFW_KEY_F11;
		case Key::f12: return GLFW_KEY_F12;
		case Key::f13: return GLFW_KEY_F13;
		case Key::f14: return GLFW_KEY_F14;
		case Key::f15: return GLFW_KEY_F15;
		case Key::f16: return GLFW_KEY_F16;
		case Key::f17: return GLFW_KEY_F17;
		case Key::f18: return GLFW_KEY_F18;
		case Key::f19: return GLFW_KEY_F19;
		case Key::f20: return GLFW_KEY_F20;
		case Key::f21: return GLFW_KEY_F21;
		case Key::f22: return GLFW_KEY_F22;
		case Key::f23: return GLFW_KEY_F23;
		case Key::f24: return GLFW_KEY_F24;
		case Key::f25: return GLFW_KEY_F25;
		case Key::zero_kp: return GLFW_KEY_KP_0;
		case Key::one_kp: return GLFW_KEY_KP_1;
		case Key::two_kp: return GLFW_KEY_KP_2;
		case Key::three_kp: return GLFW_KEY_KP_3;
		case Key::four_kp: return GLFW_KEY_KP_4;
		case Key::five_kp: return GLFW_KEY_KP_5;
		case Key::six_kp: return GLFW_KEY_KP_6;
		case Key::seven_kp: return GLFW_KEY_KP_7;
		case Key::eight_kp: return GLFW_KEY_KP_8;
		case Key::nine_kp: return GLFW_KEY_KP_9;
		case Key::decimal_kp: return GLFW_KEY_KP_DECIMAL;
		case Key::divide_kp: return GLFW_KEY_KP_DIVIDE;
		case Key::multiply_kp: return GLFW_KEY_KP_MULTIPLY;
		case Key::subtract_kp: return GLFW_KEY_KP_SUBTRACT;
		case Key::add_kp: return GLFW_KEY_KP_ADD;
		case Key::enter_kp: return GLFW_KEY_KP_ENTER;
		case Key::equal_kp: return GLFW_KEY_KP_EQUAL;
		case Key::shift_left: return GLFW_KEY_LEFT_SHIFT;
		case Key::control_left: return GLFW_KEY_LEFT_CONTROL;
		case Key::alt_left: return GLFW_KEY_LEFT_ALT;
		case Key::super_left: return GLFW_KEY_LEFT_SUPER;
		case Key::shift_right: return GLFW_KEY_RIGHT_SHIFT;
		case Key::control_right: return GLFW_KEY_RIGHT_CONTROL;
		case Key::alt_right: return GLFW_KEY_RIGHT_ALT;
		case Key::super_right: return GLFW_KEY_RIGHT_SUPER;
		case Key::menu: return GLFW_KEY_MENU;
		default: throw Exceptions::EnumConvertionError();
	}
}
mgl::Key mgl::enum_converter::convert_to_Key(int v) {
	switch (v) {
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
		default: throw Exceptions::EnumConvertionError();
	}
}
int mgl::enum_converter::convert(KeyAction const& v) {
	switch (v) {
		case KeyAction::press: return GLFW_PRESS;
		case KeyAction::release: return GLFW_RELEASE;
		case KeyAction::repeat: return GLFW_REPEAT;
		default: throw Exceptions::EnumConvertionError();
	}
}
mgl::KeyAction mgl::enum_converter::convert_to_KeyAction(int v) {
	switch (v) {
		case GLFW_PRESS: return KeyAction::press;
		case GLFW_RELEASE: return KeyAction::release;
		case GLFW_REPEAT: return KeyAction::repeat;
		default: throw Exceptions::EnumConvertionError();
	}
}