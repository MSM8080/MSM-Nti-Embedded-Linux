#pragma once
#include <string>
#include <memory>
#include "pages.h"

class App;
class Page;

// --------------------------------------------------------------------------------------

class PageNavigator
{
    public:
        PageNavigator(App* app);
        ~PageNavigator();
        void navigate();
        void change_page();

    protected:
        std::unique_ptr<Page> _current_page;
        App* _app;
        
};
