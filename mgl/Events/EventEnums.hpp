#pragma once
#include "../MyGraphicsLibrary/MGL/SharedHeaders/Exceptions.hpp"
DefineNewMglException(UnsupportedEnumEntryExceptions)

namespace mgl {
	enum class MouseButton {
		b_1, b_2, b_3, b_4,
		b_5, b_6, b_7, b_8,

		last = b_8,
		left = b_1,
		right = b_2,
		middle = b_3
	};
	MouseButton _switchMouseButton(int b);

	enum class MouseAction {
		press, release
	};
	MouseAction _switchMouseAction(int a);

	enum class Mods {
		none = 0x0, shift = 0x1,
		ctrl = 0x2, alt = 0x4,
		super = 0x8
	};
	Mods operator|(Mods l, Mods r);
	Mods operator|=(Mods l, Mods r);
	Mods operator&(Mods l, Mods r);
	Mods operator&=(Mods l, Mods r);
	Mods _switchMods(int m);

	enum class MouseEnterAction {
		enter, leave
	};
	MouseEnterAction _switchMouseEnterAction(int a);

	enum class Key {
		unknown, space, apostrophe, comma, minus, period, slash,
		one, two, three, four, five, six, seven, eight, nine, zero,
		semicolon, equal,
		a, b, c, d, e, f, g, h, i, j, k, l, m,
		n, o, p, q, r, s, t, u, v, w, x, y, z,
		bracket_left, backslash, bracket_right, grave_accent,
		world_key_1, world_key_2, escape, enter, tab, backspace,
		insert, delete_key, right, left, down, up, page_up, page_down,
		home, end, caps_lock, scroll_lock, num_lock, print_screen,
		pause, f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12,
		f13, f14, f15, f16, f17, f18, f19, f20, f21, f22, f23, f24, f25,
		one_kp, two_kp, three_kp, four_kp, five_kp, six_kp, seven_kp,
		eight_kp, nine_kp, zero_kp, decimal_kp, divide_kp, multiply_kp,
		subtract_kp, add_kp, enter_kp, equal_kp,
		shift_left, control_left, alt_left, super_left,
		shift_right, control_right, alt_right, super_right,
		menu, last = menu
	};
	Key _switchKey(int k);

	enum class KeyAction {
		press, release, repeat
	};
	KeyAction _switchKeyAction(int a);
}