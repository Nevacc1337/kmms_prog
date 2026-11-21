#pragma once

#include "rect.hpp"

namespace biv {
	class Carrier {
		public:
			virtual bool is_carrying(const Rect& obj) const noexcept = 0;

			virtual float get_last_shift() const noexcept = 0;
	};
}
