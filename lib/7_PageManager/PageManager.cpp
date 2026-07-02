#include "PageManager.h"
#include "Page.h"

PageManager::PageManager() {
    _pages.fill(nullptr);
    
    // 🔒 зарезервируем место в векторе чтобы избежать переаллокаций
    _menuPages.reserve(MAX_MENU_PAGES);
    
    // Инициализируем метаданные по умолчанию
    for (size_t i = 0; i < _titles.size(); i++) {
        _titles[i] = TitleInfo("Unknown", false, false);
    }
}

void PageManager::registerPage(PageIndex index, Page* page, const TitleInfo& info) {
    if (page == nullptr) return;
    
    size_t idx = static_cast<size_t>(index);
    if (idx >= _pages.size()) return;
    
    _pages[idx] = page;
    _titles[idx] = info;
    
    // 🔒 если страница должна быть в меню, добавляем в кэш
    if (info.showInMenu) {
        // защита от переполнения вектора
        if (_menuPages.size() < MAX_MENU_PAGES) {
            _menuPages.push_back(index);
        }
    }
}

Page* PageManager::getCurrent() {
    size_t currIdx = static_cast<size_t>(_currentIndex);
    if (currIdx < _pages.size()) {
        return _pages[currIdx];
    }
    return nullptr;
}

Page* PageManager::getPageByIndex(PageIndex index) {
    size_t idx = static_cast<size_t>(index);
    if (idx < _pages.size()) {
        return _pages[idx];
    }
    return nullptr;
}

const TitleInfo& PageManager::getTitleByIndex(PageIndex index) const {
    size_t idx = static_cast<size_t>(index);
    if (idx < _titles.size()) {
        return _titles[idx];
    }
    // 🔒 возвращаем статический неизменяемый объект
    static const TitleInfo unknown("Unknown", false, false);
    return unknown;
}

const std::vector<PageIndex>& PageManager::getMenuPages() const {
    return _menuPages;
}

bool PageManager::SwitchToIndex(PageIndex index) {
    size_t nextIdx = static_cast<size_t>(index);
    size_t currIdx = static_cast<size_t>(_currentIndex);
    
    if (nextIdx >= _pages.size() || !_pages[nextIdx]) {
        return false;
    }
    if (index == _currentIndex) {
        return true;
    }
    
    if (currIdx < _pages.size() && _pages[currIdx]) {
        _pages[currIdx]->OnExit();
    }
    
    _currentIndex = index;
    _pages[nextIdx]->OnEnter();
    return true;
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
