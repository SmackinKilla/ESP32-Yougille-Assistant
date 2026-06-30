#include "PageManager.h"

void PageManager::addPage(Page* page) {
    _pages.push_back(page);
}

void PageManager::next() {
    if(_pages.empty()) return;
    _pages[_currentIndex]->OnExit();
    _currentIndex = (_currentIndex + 1) % _pages.size();
    _pages[_currentIndex]->OnEnter();
}

void PageManager::prev() {
    if(_pages.empty()) return;
    _pages[_currentIndex]->OnExit();
    _currentIndex = (_currentIndex == 0)
    ? _pages.size() - 1
    : _currentIndex - 1;
    _pages[_currentIndex]->OnEnter();
}

Page* PageManager::getCurrent() {
    return _pages[_currentIndex];
}

void PageManager::SwitchToIndex(int index) {
    if (_pages.empty()) return;
    if (index < 0 || index >= (int)_pages.size()) return;
    if (index == _currentIndex) return; 
    
    if (_currentIndex >= 0) {
        _pages[_currentIndex]->OnExit();
    }

    _currentIndex = index;
    _pages[_currentIndex]->OnEnter();
}
