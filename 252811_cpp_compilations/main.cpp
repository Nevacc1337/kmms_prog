#include <clocale>
#include <iostream>

#include "menu.hpp"
#include "menu_functions.hpp"

int main() {
    std::setlocale(LC_ALL, "65011");

    SDurnev::MenuItem study_summ = { "1 - Хочу учиться сложению!", SDurnev::study_summ };
    SDurnev::MenuItem study_substract = { "2 - Хочу учиться вычитанию!", SDurnev::study_substract };
    SDurnev::MenuItem study_multiply = { "3 - Хочу учиться умножению!", SDurnev::study_multiply };
    SDurnev::MenuItem study_divide = { "4 - Хочу учиться делению!", SDurnev::study_divide };
    SDurnev::MenuItem study_go_back = { "0 - Вернуться назад", SDurnev::study_go_back };

    SDurnev::MenuItem* study_children[] = {
        &study_go_back,
        &study_summ,
        &study_substract, 
        &study_multiply,
        &study_divide
    };
    const int study_size = sizeof(study_children) / sizeof(study_children[0]);

    SDurnev::MenuItem study = { "1 - Хочу учиться математике!", SDurnev::show_menu, study_children, study_size };
    SDurnev::MenuItem exit = { "0 - Я лучше пойду полежу...", SDurnev::exit };

    SDurnev::MenuItem* main_children[] = { &exit, &study };
    const int main_size = sizeof(main_children) / sizeof(main_children[0]);
	
	SDurnev::MenuItem main = { nullptr, SDurnev::show_menu, main_children, main_size };
	
	main.func(&main);
	int user_input;
	do {
		std::cin >> user_input;
		std::cout << std::endl;
		
		main.children[user_input]->func(main.children[user_input]);
	} while (true);
	
    return 0;
}