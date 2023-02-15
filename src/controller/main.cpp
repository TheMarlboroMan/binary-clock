#include "../../include/controller/main.h"

//local
#include "../../include/input/input.h"
#include "include/app/time.h"

#include <thread>
#include <chrono>
#include <iostream>

using namespace controller;

main::main(
	lm::logger& plog,
	int _dim,
	ldv::rgba_color _color_on,
	ldv::rgba_color _color_off
)
	:log(plog),
	digit_hours{_dim,_dim, _dim, _dim, _color_on, _color_off},
	digit_minutes{6*_dim, _dim, _dim, _dim, _color_on, _color_off},
	digit_seconds{11*_dim, _dim, _dim, _dim, _color_on, _color_off}
{

}

void main::loop(dfw::input& _input, const dfw::loop_iteration_data& /*lid*/) {

	if(_input().is_exit_signal() || _input.is_input_down(input::escape)) {
		set_leave(true);
		return;
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	time=app::time();
	digit_seconds.update(time.get_second());
	digit_minutes.update(time.get_minute());
	digit_hours.update(time.get_hour());
}

void main::draw(ldv::screen& screen, int /*fps*/) {

	screen.clear(ldv::rgba8(0, 0, 0, 255));
	digit_seconds.draw(screen);
	digit_minutes.draw(screen);
	digit_hours.draw(screen);
}
