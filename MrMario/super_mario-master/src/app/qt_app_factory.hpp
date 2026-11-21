#pragma once

#include "app_factory.hpp"

namespace biv {
	class QtAppFactory : public AppFactory {
		public:
			OSControlSettings* create_control_settings(
				const int map_height, const int map_width
			) override;
			KeyBoard* create_keyboard() override;
			UIFactory* create_ui_factory(Game*) override;
			std::chrono::milliseconds get_frame_delay() const noexcept override;
	};
}
