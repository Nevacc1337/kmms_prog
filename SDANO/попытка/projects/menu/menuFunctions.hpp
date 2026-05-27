#pragma once

#include "menuStructures.hpp"

namespace tkr {
	const MenuItem* showMenu(const MenuItem* current);
	
	const MenuItem* exit(const MenuItem* current);
	const MenuItem* goBack(const MenuItem* current);

	// ALGEBRA
	const MenuItem* algebraSum(const MenuItem* current);
	const MenuItem* algebraSubt(const MenuItem* current);
	const MenuItem* algebraMult(const MenuItem* current);
	const MenuItem* algebraDiv(const MenuItem* current);
	
	// MATHANALYSIS
	const MenuItem* mathanDiff(const MenuItem* current);
	const MenuItem* mathanInter(const MenuItem* current);
}