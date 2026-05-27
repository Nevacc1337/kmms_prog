#pragma once

namespace SDurnev {
    struct MenuItem {
        const char* const title;
        void (*func)(const MenuItem* current);

        const MenuItem* const *children;
        const int children_count;
    };
}