#pragma once

// std
#include <limits>
// project
#include <callisto/framework/configuration/object_enum.hpp>

namespace callisto::graphics
{

// clang-format off

CALLISTO_DEFINE_OBJECT_ENUM(
    key_type,
    ,
	(unknown,           0),
	(space,             32),
	(apostrophe,        39), /* ' */
	(comma,             44),  /* , < */
	(mimus,             45),  /* - */
	(period,            46),  /* . > */
	(slash,             47),  /* / */
	(key_0,             48),
	(key_1,             49),
	(key_2,             50),
	(key_3,             51),
	(key_4,             52),
	(key_5,             53),
	(key_6,             54),
	(key_7,             55),
	(key_8,             56),
	(key_9,             57),
	(semicolon,         59),  /* ; */
	(equal,             61),  /* = */
	(a,                 65),
	(b,                 66),
	(c,                 67),
	(d,                 68),
	(e,                 69),
	(f,                 70),
	(g,                 71),
	(h,                 72),
	(i,                 73),
	(j,                 74),
	(k,                 75),
	(l,                 76),
	(m,                 77),
	(n,                 78),
	(o,                 79),
	(p,                 80),
	(q,                 81),
	(r,                 82),
	(s,                 83),
	(t,                 84),
	(u,                 85),
	(v,                 86),
	(w,                 87),
	(x,                 88),
	(y,                 89),
	(z,                 90),
	(left_bracket,      91),  /* [ */
	(back_slash,        92),  /* \ */
	(right_bracket,     93),  /* ] */
	(grave_accent,      96),  /* ` */
	(world_1,           161), /* non-US #1 */
	(world_2,           162), /* non-US #2 */

	/* Function keys */
	(escape,            256),
	(enter,             257),
	(tab,               258),
	(backspace,         259),
	(insert,            260),
	(delete_,           261),
	(right,             262),
	(left,              263),
	(down,              264),
	(up,                265),
	(page_up,           266),
	(page_down,         267),
	(home,              268),

	(end,               269),
	(caps_lock,         280),
	(scroll_lock,       281),
	(num_lock,          282),
	(print_screen,      283),
	(pause,             284),
	(f1,                290),
	(f2,                291),
	(f3,                292),
	(f4,                293),
	(f5,                294),
	(f6,                295),
	(f7,                296),
	(f8,                297),
	(f9,                298),
	(f10,               299),
	(f11,               300),
	(f12,               301),
	(f13,               302),
	(f14,               303),
	(f15,               304),
	(f16,               305),
	(f17,               306),
	(f18,               307),
	(f19,               308),
	(f20,               309),
	(f21,               310),
	(f22,               311),
	(f23,               312),
	(f24,               313),
	(f25,               314),
	(kp_0,              320),
	(kp_1,              321),
	(kp_2,              322),
	(kp_3,              323),
	(kp_4,              324),
	(kp_5,              325),
	(kp_6,              326),
	(kp_7,              327),
	(kp_8,              328),
	(kp_9,              329),
	(kp_decimal,        330),
	(kp_divide,         331),
	(kp_multiply,       332),
	(kp_substract,      333),
	(kp_add,            334),
	(kp_enter,          335),
	(kp_equal,          336),
	(left_shift,        340),
	(left_control,      341),
	(left_alt,          342),
	(left_super,        343),
	(right_shift,       344),
	(right_control,     345),
	(right_alt,         346),
	(right_super,       347),
	(menu,              348)
);

// clang-format on

} // namespace callisto::graphics