#pragma once

namespace app {

class time {

	public:
	                            time();
	int                         get_hour() const {return hour;}
	int                         get_minute() const {return minute;}
	int                         get_second() const {return second;}

	private:

	int                         hour{0},
	                            minute{0},
	                            second{0};
};
}
