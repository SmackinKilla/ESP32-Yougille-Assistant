#pragma once
#include "Page.h"
#include <array>
#include <vector>
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

struct TitleInfo {
    const char* title;
    bool hasCounter;
    bool showInMenu;
    
    TitleInfo(const char* t = "Unknown", bool counter = false, bool show = true) 
        : title(t), hasCounter(counter), showInMenu(show) {}
};

class PageManager {
public:
    PageManager();
    
    // 🔒 Регистрация страницы с метаданными
    void registerPage(PageIndex index, Page* page, const TitleInfo& info);
    
    // Геттеры
    Page* getCurrent();
    Page* getPageByIndex(PageIndex index);
    const TitleInfo& getTitleByIndex(PageIndex index) const;
    const std::vector<PageIndex>& getMenuPages() const;  // список видимых в меню
    
    // Навигация
    bool SwitchToIndex(PageIndex index);
    void next();
    void prev();
    PageIndex getCurrentIndex() const { return _currentIndex; }

private:
    static constexpr size_t MAX_PAGES = static_cast<size_t>(PageIndex::COUNT);
    static constexpr size_t MAX_MENU_PAGES = 10;  // 🔒 максимум видимых страниц
    
    std::array<Page*, MAX_PAGES> _pages;
    std::array<TitleInfo, MAX_PAGES> _titles;
    std::vector<PageIndex> _menuPages;  // кэш видимых в меню страниц
    PageIndex _currentIndex = PageIndex::HOME;
};
