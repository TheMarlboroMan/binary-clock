#include "include/app/env.h"

using namespace app;

env::env(
	const std::string& _exec,
	const std::string& _home
):
	exec_dir(_exec),
	user_dir{_home+"/.binary-clock/"}
{}

std::string env::build_data_path(const std::string& _file) const {

	return exec_dir+std::string{"data/"}+_file;
}

std::string env::build_user_path(const std::string& _file) const {

	return user_dir+"/"+_file;
}
