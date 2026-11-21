#include "third_level.hpp"

#include "fourth_level.hpp"

using biv::ThirdLevel;

ThirdLevel::ThirdLevel(UIFactory* ui_factory) : GameLevel(ui_factory) {
	init_data();
}

biv::GameLevel* ThirdLevel::get_next() {
	if (!next) {
		clear_data();
		next = new biv::FourthLevel(ui_factory);
	}
	return next;
}

void ThirdLevel::init_data() {
	ui_factory->create_mario({39, 10}, 3, 3);

	ui_factory->create_ship({20, 25}, 40, 2);
	ui_factory->create_ship({80, 25}, 20, 2);
	ui_factory->create_jumping_enemy({90, 20}, 3, 2);

	ui_factory->create_ship({100, 18}, 15, 9);
	ui_factory->create_flying_enemy({100, 14}, 3, 2, 10);
	ui_factory->create_full_box({103, 8}, 5, 3);

	ui_factory->create_ship({115, 25}, 25, 2);
	ui_factory->create_enemy({120, 20}, 3, 2);
	ui_factory->create_enemy({130, 20}, 3, 2);

	ui_factory->create_moving_platform({160, 25}, 10, 2, 20);
	ui_factory->create_flying_enemy({150, 21}, 3, 2, 10);
	ui_factory->create_flying_enemy({170, 21}, 3, 2, 10);

	ui_factory->create_ship({190, 25}, 30, 2);
	ui_factory->create_jumping_enemy({200, 20}, 3, 2);
	ui_factory->create_jumping_enemy({208, 20}, 3, 2);

	ui_factory->create_ship({220, 22}, 8, 5);
	ui_factory->create_ship({228, 19}, 8, 8);
	ui_factory->create_ship({236, 16}, 10, 11);
}
