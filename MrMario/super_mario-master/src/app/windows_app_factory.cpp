#include "windows_app_factory.hpp"

#include "console_ui_factory.hpp"
#include "windows_control_settings.hpp"
#include "windows_keyboard.hpp"

using biv::WindowsAppFactory;

biv::OSControlSettings* WindowsAppFactory::create_control_settings(
	const int, const int
) {
	return new WindowsControlSettings();
}

biv::KeyBoard* WindowsAppFactory::create_keyboard() {
	return new WindowsKeyBoard();
}

biv::UIFactory* WindowsAppFactory::create_ui_factory(Game* game) {
	return new ConsoleUIFactory(game);
}

std::chrono::milliseconds WindowsAppFactory::get_frame_delay() const noexcept {
	return std::chrono::milliseconds(10);
}
