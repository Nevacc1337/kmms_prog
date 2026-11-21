#pragma once

#include <chrono>

#include "keyboard.hpp"
#include "os_control_settings.hpp"
#include "ui_factory.hpp"

namespace biv {
	class Game;

	class AppFactory {
		public:
			virtual OSControlSettings* create_control_settings(
				const int map_height, const int map_width
			) = 0;
			virtual KeyBoard* create_keyboard() = 0;
			virtual UIFactory* create_ui_factory(Game*) = 0;
			virtual std::chrono::milliseconds get_frame_delay() const noexcept = 0;
	};
}
