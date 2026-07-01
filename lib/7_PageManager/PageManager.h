#pragma once
#include "Page.h"
#include <vector>
#include <array>
#include <cstdint>
#include <stddef.h>

enum class PageIndex : uint8_t {
    WEATHER = 0,
    TASKS,
    TIMEZONES,
    GAMES,
    SETTINGS,
    HOME,
    SCREENSAVER,
    COUNT 
};

class PageManager {
public:
    PageManager();
    void addPage(PageIndex index, Page* page);
    void SwitchToIndex(PageIndex index);
    void next();
    void prev();
    Page* getCurrent();
    PageIndex getCurrentIndex() const { return _currentIndex; }

private:
    std::array<Page*, static_cast<size_t>(PageIndex::COUNT)> _pages;
    PageIndex _currentIndex = PageIndex::COUNT;
};