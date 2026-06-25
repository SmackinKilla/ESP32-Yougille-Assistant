#pragma once
#include "Page.h"
#include <vector>

class PageManager {
    public:
        void addPage(Page* page);
        void next();
        void prev();
        Page* getCurrent();
    private:
        std::vector<Page*> _pages;
        uint8_t _currentIndex = 0;
};