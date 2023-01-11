#include "include/app/digit.h"

using namespace app;

digit::digit(
	int _offset_x,
	int _offset_y,
	int _w,
	int _h,
	ldv::rgba_color _color_on,
	ldv::rgba_color _color_off
): 
	color_on{_color_on},
	color_off{_color_off},
	box32{{ _offset_x, _offset_y, _w, _h}, _color_off},
	box16{{ _offset_x, _offset_y+(2*_h), _w, _h}, color_off},
	box8{{  _offset_x, _offset_y+(4*_h), _w, _h}, color_off},
	box4{{ _offset_x+(2*_w), _offset_y, _w, _h}, color_off},
	box2{{ _offset_x+(2*_w), _offset_y+(2*_h), _w, _h}, color_off},
	box1{{ _offset_x+(2*_w), _offset_y+(4*_h), _w, _h}, color_off}
{

}

void digit::draw(
	ldv::screen& _screen
) {

	box32.draw(_screen);
	box16.draw(_screen);
	box8.draw(_screen);
	box4.draw(_screen);
	box2.draw(_screen);
	box1.draw(_screen);
}

void digit::update(
	int _unit
) {

	box32.set_color(_unit & 32 ? color_on : color_off);
	box16.set_color(_unit & 16 ? color_on : color_off);
	box8.set_color(_unit & 8 ? color_on : color_off);
	box4.set_color(_unit & 4 ? color_on : color_off);
	box2.set_color(_unit & 2 ? color_on : color_off);
	box1.set_color(_unit & 1 ? color_on : color_off);
}
