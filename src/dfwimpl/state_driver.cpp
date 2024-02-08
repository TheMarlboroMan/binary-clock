#include "../../include/dfwimpl/state_driver.h"
#include "../../include/input/input.h"
#include "../../include/controller/states.h"

#include <lm/log.h>
#include <tools/string_utils.h>

#include <algorithm>

using namespace dfwimpl;

state_driver::state_driver(dfw::kernel& kernel, dfwimpl::config& c)
	:state_driver_interface(controller::t_states::state_main),
	config(c), log(kernel.get_log()) {

	lm::log(log).info()<<"setting state check function..."<<std::endl;

	states.set_function([](int v){
		return v > controller::state_min && v < controller::state_max;
	});

	lm::log(log).info()<<"init state driver building: preparing video..."<<std::endl;
	prepare_video(kernel);

	lm::log(log).info()<<"preparing audio..."<<std::endl;
	prepare_audio(kernel);

	lm::log(log).info()<<"preparing input..."<<std::endl;
	prepare_input(kernel);

	lm::log(log).info()<<"preparing resources..."<<std::endl;
	prepare_resources(kernel);

	lm::log(log).info()<<"registering controllers..."<<std::endl;
	register_controllers(kernel);

	lm::log(log).info()<<"virtualizing input..."<<std::endl;
	virtualize_input(kernel.get_input());

	lm::log(log).info()<<"state driver fully constructed"<<std::endl;
}

void state_driver::init(dfw::kernel&) {

}

void state_driver::prepare_video(dfw::kernel& kernel) {

	int dimension=config.int_from_path("app:dimension");

	kernel.init_video_system({
		15*dimension,
		7*dimension,
		15*dimension,
		7*dimension,
		config.string_from_path("video:window_title"),
		config.bool_from_path("video:window_show_cursor"),
		config.get_screen_vsync()
	});

	auto& screen=kernel.get_screen();
	screen.set_fullscreen(config.bool_from_path("video:fullscreen"));
	screen.set_borders(config.bool_from_path("video:borders"));
}

void state_driver::prepare_audio(dfw::kernel& kernel) {

	kernel.init_audio_system({
		config.get_audio_ratio(),
		config.get_audio_out(),
		config.get_audio_buffers(),
		config.get_audio_channels(),
		config.get_audio_volume(),
		config.get_music_volume()
	});
}

void state_driver::prepare_input(dfw::kernel& kernel) {

	using namespace dfw;

	std::vector<input_pair> pairs{
		{{input_description::types::keyboard, SDL_SCANCODE_ESCAPE, 0}, input::escape}
	};

	kernel.init_input_system(pairs);
}

void state_driver::prepare_resources(dfw::kernel& /*kernel*/) {

/*
	dfw::resource_loader r_loader(kernel.get_video_resource_manager(), kernel.get_audio_resource_manager());

	r_loader.generate_textures(tools::explode_lines_from_file(std::string("data/resources/textures.txt")));
	r_loader.generate_sounds(tools::explode_lines_from_file(std::string("data/resources/audio.txt")));
	r_loader.generate_music(tools::explode_lines_from_file(std::string("data/resources/music.txt")));
*/
}

void state_driver::register_controllers(dfw::kernel& /*kernel*/) {

	auto reg=[this](ptr_controller& _ptr, int _i, dfw::controller_interface * _ci) {
		_ptr.reset(_ci);
		register_controller(_i, *_ptr);
	};

	int dimension=config.int_from_path("app:dimension");
	ldv::rgba_color color_on=ldv::rgba8(
		config.int_from_path("app:on_color_r"),
		config.int_from_path("app:on_color_g"),
		config.int_from_path("app:on_color_b"),
		255
	);

	ldv::rgba_color color_off=ldv::rgba8(
		config.int_from_path("app:off_color_r"),
		config.int_from_path("app:off_color_g"),
		config.int_from_path("app:off_color_b"),
		255
	);


	reg(c_main, controller::t_states::state_main, new controller::main(log, dimension, color_on, color_off));
	//[new-controller-mark]
}

void state_driver::prepare_state(int /*next*/, int /*current*/) {

/*
	switch(next) {
		case t_states::state_placeholder:
		break;
		default:
		break;
	}
*/
}

void state_driver::common_pre_loop_input(dfw::input& input, float /*delta*/) {

	if(input().is_event_joystick_connected()) {
		lm::log(log).info()<<"New joystick detected..."<<std::endl;
		virtualize_input(input);
	}
}

void state_driver::common_loop_input(dfw::input& /*input*/, float /*delta*/) {

}

void state_driver::common_pre_loop_step(float /*delta*/) {

}

void state_driver::common_loop_step(float /*delta*/) {

}

void state_driver::virtualize_input(dfw::input& input) {

	lm::log(log).info()<<"trying to virtualize "<<input().get_joysticks_size()<<" controllers..."<<std::endl;

	for(size_t i=0; i < input().get_joysticks_size(); ++i) {
		input().virtualize_joystick_hats(i);
		input().virtualize_joystick_axis(i, 15000);
		lm::log(log).info()<<"Joystick virtualized "<<i<<std::endl;
	}
}
