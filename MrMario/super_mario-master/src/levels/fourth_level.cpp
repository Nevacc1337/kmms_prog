#include "fourth_level.hpp"

using biv::FourthLevel;

FourthLevel::FourthLevel(UIFactory* ui_factory) : GameLevel(ui_factory) {
	init_data();
}

bool FourthLevel::is_final() const noexcept {
	return true;
}

biv::GameLevel* FourthLevel::get_next() {
	return next;
}

void FourthLevel::init_data() {
	ui_factory->create_mario({39, 10}, 3, 3);

	ui_factory->create_ship({20, 25}, 30, 2);

	ui_factory->create_ship({68, 25}, 4, 2);
	ui_factory->create_ship({92, 22}, 3, 5);
	ui_factory->create_ship({118, 25}, 3, 2);
	ui_factory->create_ship({140, 19}, 4, 8);
	ui_factory->create_ship({168, 24}, 3, 3);
	ui_factory->create_ship({196, 25}, 3, 2);
	ui_factory->create_ship({222, 21}, 3, 6);
	ui_factory->create_ship({250, 25}, 3, 2);

	ui_factory->create_moving_platform({278, 25}, 5, 2, 20);

	ui_factory->create_ship({303, 25}, 6, 2);

	ui_factory->create_flying_enemy({80, 14}, 3, 2, 8);
	ui_factory->create_flying_enemy({105, 14}, 3, 2, 8);
	ui_factory->create_flying_enemy({130, 12}, 3, 2, 8);
	ui_factory->create_jumping_enemy({141, 15}, 3, 2);
	ui_factory->create_flying_enemy({155, 12}, 3, 2, 8);
	ui_factory->create_flying_enemy({182, 14}, 3, 2, 8);
	ui_factory->create_flying_enemy({209, 14}, 3, 2, 8);
	ui_factory->create_flying_enemy({236, 14}, 3, 2, 8);
	ui_factory->create_flying_enemy({265, 14}, 3, 2, 10);
	ui_factory->create_flying_enemy({290, 14}, 3, 2, 10);
}
