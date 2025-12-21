#pragma once

namespace dsv {
    struct MenuItem {
        const char* title;
        const MenuItem* (*func)(const MenuItem* current);
        const MenuItem* parent;
        const MenuItem* const *children;
        const int childrenCount;
    };
}