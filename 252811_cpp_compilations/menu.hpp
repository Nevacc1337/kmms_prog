#pragma once

namespace SDurnev {
    struct MenuItem {
        const char* const title;
        void (*func)();
    };
}