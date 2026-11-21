#include "second_level.hpp"

#include "third_level.hpp"

using biv::SecondLevel;

SecondLevel::SecondLevel(UIFactory* ui_factory) : GameLevel(ui_factory) {
	init_data();
}

biv::GameLevel* SecondLevel::get_next() {
	if (!next) {
		clear_data();
		next = new biv::ThirdLevel(ui_factory);
	}
	return next;
}

// ----------------------------------------------------------------------------
// 									PROTECTED
// ----------------------------------------------------------------------------
void SecondLevel::init_data() {
	ui_factory->create_mario({39, 10}, 3, 3);

	ui_factory->create_ship({20, 25}, 80, 2);
	ui_factory->create_full_box({45, 15}, 5, 3);
	ui_factory->create_jumping_enemy({75, 20}, 3, 2);
	ui_factory->create_jumping_enemy({90, 20}, 3, 2);

	ui_factory->create_moving_platform({120, 25}, 10, 2, 20);
	ui_factory->create_flying_enemy({120, 21}, 3, 2, 15);

	ui_factory->create_ship({150, 25}, 30, 2);
	ui_factory->create_ship({180, 20}, 15, 7);
	ui_factory->create_enemy({185, 15}, 3, 2);
	ui_factory->create_ship({195, 25}, 20, 2);
	ui_factory->create_jumping_enemy({205, 20}, 3, 2);

	ui_factory->create_moving_platform({235, 25}, 10, 2, 20);
	ui_factory->create_flying_enemy({235, 21}, 3, 2, 15);

	ui_factory->create_ship({265, 25}, 40, 2);
}
