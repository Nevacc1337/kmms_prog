#pragma once

namespace tkr {
	struct MenuItem {
		const char* const text;
		const MenuItem* (*func) (const MenuItem* current); 

		const MenuItem* parent;

		const MenuItem* const *children;
		const int childrenSize;
	};
}