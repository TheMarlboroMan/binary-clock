#pragma once

//local
#include "states.h"
#include "include/app/time.h"
#include "include/app/digit.h"

//framework
#include <dfw/controller_interface.h>

//logger
#include <lm/logger.h>

//std
#include <cmath>

namespace controller {

class main:
	public dfw::controller_interface {

	public:

								main(lm::logger&, int);
	virtual void 				loop(dfw::input&, const dfw::loop_iteration_data&);
	virtual void 				draw(ldv::screen&, int);
	virtual void 				awake(dfw::input& /*input*/) {}
	virtual void 				slumber(dfw::input& /*input*/) {}
	virtual bool				can_leave_state() const {return true;}

	private:

	//references...
	lm::logger&					log;

	//properties
	app::time                   time;
	app::digit                  digit_hours,
	                            digit_minutes,
	                            digit_seconds;
};

}
