#include "include/app/time.h"
#include <time.h>

using namespace app;

app::time::time() {

	time_t rawtime;
	::time(&rawtime);
	struct tm * ptm=localtime(&rawtime);

	hour=ptm->tm_hour;
	minute=ptm->tm_min;
	second=ptm->tm_sec;
}
