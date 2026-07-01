#include "PageManager.h"
#include "Page.h"

TitleInfo getTitleInfo(PageIndex index) {
    switch (index) {
        case PageIndex::WEATHER:    return TitleInfo("Weather", false);
        case PageIndex::TASKS:      return TitleInfo("Tasks", true);
        case PageIndex::TIMEZONES:  return TitleInfo("Time Zones", false);
        case PageIndex::GAMES:      return TitleInfo("Gambling", false);
        case PageIndex::SETTINGS:   return TitleInfo("Settings", false);
        default:                    return TitleInfo("Unknown", false);
    }
}

PageManager::PageManager() {
    _pages.fill(nullptr);
}

void PageManager::addPage(PageIndex index, Page* page) {
    size_t idx = static_cast<size_t>(index);
    if (idx < _pages.size()) {
        _pages[idx] = page;
    }
}

void PageManager::SwitchToIndex(PageIndex index) {
    size_t nextIdx = static_cast<size_t>(index);
    size_t currIdx = static_cast<size_t>(_currentIndex);
    if (nextIdx >= _pages.size() || !_pages[nextIdx]) return;
    if (index == _currentIndex) return; 
    if (currIdx < _pages.size() && _pages[currIdx]) {
        _pages[currIdx]->OnExit();
    }
    _currentIndex = index;
    _pages[nextIdx]->OnEnter();
}

Page* PageManager::getCurrent() {
    return _pages[static_cast<size_t>(_currentIndex)];
}

void PageManager::next() {
    size_t startIdx = static_cast<size_t>(_currentIndex);
    size_t count = _pages.size();
    
    for (size_t i = 1; i <= count; ++i) {
        size_t nextIdx = (startIdx + i) % count;
        if (_pages[nextIdx]) {
            SwitchToIndex(static_cast<PageIndex>(nextIdx));
            return;
        }
    }
}

void PageManager::prev() {
    size_t startIdx = static_cast<size_t>(_currentIndex);
    size_t count = _pages.size();
    
    for (size_t i = 1; i <= count; ++i) {
        size_t prevIdx = (startIdx + count - i) % count;
        if (_pages[prevIdx]) {
            SwitchToIndex(static_cast<PageIndex>(prevIdx));
            return;
        }
    }
}