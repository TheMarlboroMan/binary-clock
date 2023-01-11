#pragma once

#include <string>

namespace app {

class env {

	public:

	                    env(const std::string&, const std::string&);
	std::string         build_data_path(const std::string&) const;
	std::string         build_user_path(const std::string&) const;

	private:

	const std::string   exec_dir;
	const std::string   user_dir;
};
}
