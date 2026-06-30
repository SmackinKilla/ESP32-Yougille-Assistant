#pragma once
#include "Page.h"
#include <vector>

class PageManager {
    public:
        void addPage(Page* page);
        void next();
        void prev();
        void SwitchToIndex(int index);
        Page* getCurrent();
    private:
        std::vector<Page*> _pages;
        int _currentIndex = 0;
};
