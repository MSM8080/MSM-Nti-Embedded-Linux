#include "../include/navigator.h"
// -------------------------------------------------------------------
// #####################################################################################################################
// ##################################### class PageNavigator ###########################################################
// #####################################################################################################################
// -------------------------------------------------------------------
PageNavigator::PageNavigator(App* app)
{
    _app = app;
    // initilize first page = login page
    _current_page = std::make_unique<LoginPage>(_app);
    
}
// -------------------------------------------------------------------
PageNavigator::~PageNavigator()
{
    delete _app;
}
// -------------------------------------------------------------------
void PageNavigator::navigate()
{

    while(_current_page != nullptr)
    {
        // clear page
        _current_page->clear_page();
        // print logo
        _current_page->print_logo();
        // print page
        _current_page->print_page();
        // take & handle input
        _current_page->prompt();
        // change page according to prompt
        this->change_page();
    }
    return ;
}

// void PageNavigator::prompt()
// {
//     std::cout << std::endl; 

//     std::cout << "\033[1;32m $\033[0m" << "\033[1;34m> \033[0m"; // in GREEN & BLUE
//     std::cin >> _input;
    
//     std::cout << std::endl;
 
// }

void PageNavigator::change_page()
{
    _current_page = std::move(_current_page->get_next_page());

}


