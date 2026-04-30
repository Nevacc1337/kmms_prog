#include <cstddef>

#include "menuInit.hpp"
#include "menuFunctions.hpp"
#include "menuStructures.hpp"


// ALGEBRA
const tkr::MenuItem tkr::ALGEBRA_SUM = {
	"1 - Сложение", tkr::algebraSum, &tkr::STUDY_ALGEBRA
};
const tkr::MenuItem tkr::ALGEBRA_SUBT = {
	"2 - Вычитание", tkr::algebraSubt, &tkr::STUDY_ALGEBRA
};
const tkr::MenuItem tkr::ALGEBRA_MULT = {
	"3 - Умножение", tkr::algebraMult, &tkr::STUDY_ALGEBRA
};
const tkr::MenuItem tkr::ALGEBRA_DIV = {
	"4 - Деление", tkr::algebraDiv, &tkr::STUDY_ALGEBRA
};
const tkr::MenuItem tkr::ALGEBRA_GO_BACK = {
	"0 - Выйти в меню предметов", tkr::goBack, &tkr::STUDY_ALGEBRA
};

namespace {
	const tkr::MenuItem* const algebraChildren[] = {
		&tkr::ALGEBRA_GO_BACK,	
		&tkr::ALGEBRA_SUM,	
		&tkr::ALGEBRA_SUBT,	
		&tkr::ALGEBRA_MULT,	
		&tkr::ALGEBRA_DIV,	
	};
	const int algebraSize = sizeof(algebraChildren) / sizeof(algebraChildren[0]);
}

// MATHANALYSIS

const tkr::MenuItem tkr::MATHAN_DIFF = {
	"1 - Дифференциальное исчисление", tkr::mathanDiff, &tkr::STUDY_MATHAN
};
const tkr::MenuItem tkr::MATHAN_INTER = {
	"2 - Интегральное исчисление", tkr::mathanInter, &tkr::STUDY_MATHAN
};
const tkr::MenuItem tkr::MATHAN_GO_BACK = {
	"0 - Вернуться к выбору предметов", tkr::goBack, &tkr::STUDY_MATHAN
};

namespace {
	const tkr::MenuItem* const mathanChildren[] = {
		&tkr::MATHAN_GO_BACK,	
		&tkr::MATHAN_DIFF,	
		&tkr::MATHAN_INTER,	
	};
	const int mathanSize = sizeof(mathanChildren) / sizeof(mathanChildren[0]);
}

// STUDY

const tkr::MenuItem tkr::STUDY_ALGEBRA = {
	"1 - Алгебра", tkr::showMenu, &tkr::STUDY, algebraChildren, algebraSize
};

const tkr::MenuItem tkr::STUDY_MATHAN = {
	"2 - Математический анализ", tkr::showMenu, &tkr::STUDY, mathanChildren, mathanSize
};

const tkr::MenuItem tkr::STUDY_GO_BACK = {
	"0 - Вернуться к выбору предметов", tkr::goBack, &tkr::STUDY 
};

namespace {
	const tkr::MenuItem* studyChildren[] = {
		&tkr::STUDY_GO_BACK, 		
		&tkr::STUDY_ALGEBRA,
		&tkr::STUDY_MATHAN,
	};
	const int studySize = sizeof(studyChildren) / sizeof(studyChildren[0]);
}

// MAIN
const tkr::MenuItem tkr::STUDY = {
	"1 - Хочу учиться", tkr::showMenu, &tkr::MAIN, studyChildren, studySize
};
const tkr::MenuItem tkr::EXIT = {
	"0 - Не, не хочу чёта", tkr::exit, &tkr::MAIN 
};

namespace {
	const tkr::MenuItem* const mainChildren[] = {
		&tkr::EXIT,
		&tkr::STUDY,
	};
	const int mainSize = sizeof(mainChildren) / sizeof(mainChildren[0]);
}

const tkr::MenuItem tkr::MAIN = {
	nullptr, tkr::showMenu, nullptr, mainChildren, mainSize
};