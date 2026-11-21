#include "qt_control_settings.hpp"

#include <QApplication>

using biv::QtControlSettings;

void QtControlSettings::init() {
	static int argc = 1;
	static char program_name[] = "super_mario";
	static char* argv[] = {program_name, nullptr};
	static QApplication* application = nullptr;

	if (application == nullptr && QApplication::instance() == nullptr) {
		application = new QApplication(argc, argv);
	}
}

void QtControlSettings::set_cursor_start_position() {}
