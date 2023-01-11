#pragma once

#include <ldv/screen.h>
#include <ldv/color.h>
#include <ldv/box_representation.h>

namespace app {

class digit {

	public:

						digit(int, int, int, int, ldv::rgba_color, ldv::rgba_color);
	void                draw(ldv::screen&);
	void                update(int);

	private:

	ldv::rgba_color             color_on,
	                            color_off;
	ldv::box_representation     box32,
	                            box16,
	                            box8,
	                            box4,
	                            box2,
	                            box1;
};

}
