#include "qt_app_factory.hpp"

#include "qt_control_settings.hpp"
#include "qt_keyboard.hpp"
#include "qt_ui_factory.hpp"

using biv::QtAppFactory;

biv::OSControlSettings* QtAppFactory::create_control_settings(
	const int, const int
) {
	return new QtControlSettings();
}

biv::KeyBoard* QtAppFactory::create_keyboard() {
	return new QtKeyboard();
}

biv::UIFactory* QtAppFactory::create_ui_factory(Game* game) {
	return new QtUIFactory(game);
}

std::chrono::milliseconds QtAppFactory::get_frame_delay() const noexcept {
	return std::chrono::milliseconds(16);
}
