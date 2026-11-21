#include "linux_app_factory.hpp"

#include "console_ui_factory.hpp"
#include "linux_control_settings.hpp"
#include "linux_keyboard.hpp"

using biv::LinuxAppFactory;

biv::OSControlSettings* LinuxAppFactory::create_control_settings(
	const int map_height, const int map_width
) {
	return new LinuxControlSettings(map_height, map_width);
}

biv::KeyBoard* LinuxAppFactory::create_keyboard() {
	return new LinuxKeyboard();
}

biv::UIFactory* LinuxAppFactory::create_ui_factory(Game* game) {
	return new ConsoleUIFactory(game);
}

std::chrono::milliseconds LinuxAppFactory::get_frame_delay() const noexcept {
	return std::chrono::milliseconds(50);
}
