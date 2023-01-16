#pragma once

// std
#include <limits>

namespace callisto::graphics
{

enum class key_type
{
	unknown             = 0,
	space				= 32,
	apostrophe			= 39, /* ' */
	comma				= 44,  /* , < */
	mimus				= 45,  /* - */
	period				= 46,  /* . > */
	slash				= 47,  /* / */
	key_0				= 48,
	key_1				= 49,
	key_2				= 50,
	key_3				= 51,
	key_4				= 52,
	key_5				= 53,
	key_6				= 54,
	key_7				= 55,
	key_8				= 56,
	key_9				= 57,
	semicolon			= 59,  /* ; */
	equal				= 61,  /* = */
	a					= 65,
	b					= 66,
	c					= 67,
	d					= 68,
	e					= 69,
	f					= 70,
	g					= 71,
	h					= 72,
	i					= 73,
	j					= 74,
	k					= 75,
	l					= 76,
	m					= 77,
	n					= 78,
	o					= 79,
	p					= 80,
	q					= 81,
	r					= 82,
	s					= 83,
	t					= 84,
	u					= 85,
	v					= 86,
	w					= 87,
	x					= 88,
	y					= 89,
	z					= 90,
	left_bracket	    = 91,  /* [ */
	back_slash			= 92,  /* \ */
	right_bracket		= 93,  /* ] */
	grave_accent		= 96,  /* ` */
	world_1				= 161, /* non-US #1 */
	world_2				= 162, /* non-US #2 */

	/* Function keys */
	escape				= 256,
	enter				= 257,
	tab					= 258,
	backspace			= 259,
	insert				= 260,
	delete_				= 261,
	right				= 262,
	left				= 263,
	down				= 264,
	up					= 265,
	page_up				= 266,
	page_down			= 267,
	home				= 268,
	end					= 269,
	caps_lock			= 280,
	scroll_lock			= 281,
	num_lock			= 282,
	print_screen		= 283,
	pause				= 284,
	f1					= 290,
	f2					= 291,
	f3					= 292,
	f4					= 293,
	f5					= 294,
	f6					= 295,
	f7					= 296,
	f8					= 297,
	f9					= 298,
	f10					= 299,
	f11					= 300,
	f12					= 301,
	f13					= 302,
	f14					= 303,
	f15					= 304,
	f16					= 305,
	f17					= 306,
	f18					= 307,
	f19					= 308,
	f20					= 309,
	f21					= 310,
	f22					= 311,
	f23					= 312,
	f24					= 313,
	f25					= 314,
	kp_0				= 320,
	kp_1				= 321,
	kp_2				= 322,
	kp_3				= 323,
	kp_4				= 324,
	kp_5				= 325,
	kp_6				= 326,
	kp_7				= 327,
	kp_8				= 328,
	kp_9				= 329,
	kp_decimal			= 330,
	kp_divide			= 331,
	kp_multiply			= 332,
	kp_substract		= 333,
	kp_add				= 334,
	kp_enter			= 335,
	kp_equal			= 336,
	left_shift			= 340,
	left_control		= 341,
	left_alt			= 342,
	left_super			= 343,
	right_shift			= 344,
	right_control		= 345,
	right_alt			= 346,
	right_super			= 347,
	menu				= 348,
};


constexpr const char* key_type_str(key_type key)
{
    switch(key)
    {
        case key_type::space:       return "space";
        case key_type::apostrophe:  return "apostrophe"; 
        case key_type::comma:       return "comma"; 
        case key_type::mimus:       return "mimus"; 
        case key_type::period:      return "period"; 
        case key_type::slash:       return "slash"; 
        case key_type::key_0:       return "key_0";
        case key_type::key_1:       return "key_1";
        case key_type::key_2:       return "key_2";
        case key_type::key_3:       return "key_3";
        case key_type::key_4:       return "key_4";
        case key_type::key_5:       return "key_5";
        case key_type::key_6:       return "key_6";
        case key_type::key_7:       return "key_7";
        case key_type::key_8:       return "key_8";
        case key_type::key_9:       return "key_9";
        case key_type::semicolon:   return "semicolon"; 
        case key_type::equal:       return "equal"; 

        case key_type::a: return "a";
        case key_type::b: return "b";
        case key_type::c: return "c";
        case key_type::d: return "d";
        case key_type::e: return "e";
        case key_type::f: return "f";
        case key_type::g: return "g";
        case key_type::h: return "h";
        case key_type::i: return "i";
        case key_type::j: return "j";
        case key_type::k: return "k";
        case key_type::l: return "l";
        case key_type::m: return "m";
        case key_type::n: return "n";
        case key_type::o: return "o";
        case key_type::p: return "p";
        case key_type::q: return "q";
        case key_type::r: return "r";
        case key_type::s: return "s";
        case key_type::t: return "t";
        case key_type::u: return "u";
        case key_type::v: return "v";
        case key_type::w: return "w";
        case key_type::x: return "x";
        case key_type::y: return "y";
        case key_type::z: return "z";

        case key_type::left_bracket:    return "left_bracket";
        case key_type::back_slash:      return "back_slash"; 
        case key_type::right_bracket:   return "right_bracket";
        case key_type::grave_accent:    return "grave_accent"; 
        case key_type::world_1:         return "world_1"; 
        case key_type::world_2:         return "world_2"; 
        case key_type::escape:          return "escape";
        case key_type::enter:           return "enter";
        case key_type::tab:             return "tab";
        case key_type::backspace:       return "backspace";
        case key_type::insert:          return "insert";
        case key_type::delete_:         return "delete";
        case key_type::right:           return "right";
        case key_type::left:            return "left";
        case key_type::down:            return "down";
        case key_type::up:              return "up";
        case key_type::page_up:         return "page_up";
        case key_type::page_down:       return "page_down";
        case key_type::home:            return "home";
        case key_type::end:             return "end";
        case key_type::caps_lock:       return "caps_lock";
        case key_type::scroll_lock:     return "scroll_lock";
        case key_type::num_lock:        return "num_lock";
        case key_type::print_screen:    return "print_screen";
        case key_type::pause:           return "pause";

        case key_type::f1:  return "f1";
        case key_type::f2:  return "f2";
        case key_type::f3:  return "f3";
        case key_type::f4:  return "f4";
        case key_type::f5:  return "f5";
        case key_type::f6:  return "f6";
        case key_type::f7:  return "f7";
        case key_type::f8:  return "f8";
        case key_type::f9:  return "f9";
        case key_type::f10: return "f10";
        case key_type::f11: return "f11";
        case key_type::f12: return "f12";
        case key_type::f13: return "f13";
        case key_type::f14: return "f14";
        case key_type::f15: return "f15";
        case key_type::f16: return "f16";
        case key_type::f17: return "f17";
        case key_type::f18: return "f18";
        case key_type::f19: return "f19";
        case key_type::f20: return "f20";
        case key_type::f21: return "f21";
        case key_type::f22: return "f22";
        case key_type::f23: return "f23";
        case key_type::f24: return "f24";
        case key_type::f25: return "f25";

        case key_type::kp_0: return "kp_0";
        case key_type::kp_1: return "kp_1";
        case key_type::kp_2: return "kp_2";
        case key_type::kp_3: return "kp_3";
        case key_type::kp_4: return "kp_4";
        case key_type::kp_5: return "kp_5";
        case key_type::kp_6: return "kp_6";
        case key_type::kp_7: return "kp_7";
        case key_type::kp_8: return "kp_8";
        case key_type::kp_9: return "kp_9";

        case key_type::kp_decimal:      return "kp_decimal";
        case key_type::kp_divide:       return "kp_divide";
        case key_type::kp_multiply:     return "kp_multiply";
        case key_type::kp_substract:    return "kp_substract";
        case key_type::kp_add:          return "kp_add";
        case key_type::kp_enter:        return "kp_enter";
        case key_type::kp_equal:        return "kp_equal";
        case key_type::left_shift:      return "left_shift";
        case key_type::left_control:    return "left_control";
        case key_type::left_alt:        return "left_alt";
        case key_type::left_super:      return "left_super";
        case key_type::right_shift:     return "right_shift";
        case key_type::right_control:   return "right_control";
        case key_type::right_alt:       return "right_alt";
        case key_type::right_super:     return "right_super";
        case key_type::menu:            return "menu";

        default: return "";
    }
}

} // namespace callisto::graphics

namespace std
{

template<>
struct numeric_limits<callisto::graphics::key_type>
{
    using type = callisto::graphics::key_type;

    static constexpr bool is_specialized = true;

    static inline constexpr int min() { return static_cast<int>(type::unknown); }

    static inline constexpr int lowest() { return static_cast<int>(type::unknown); }

    static inline constexpr int max() { return static_cast<int>(type::menu); }
};

}