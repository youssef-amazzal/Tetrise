#pragma once
#include "Screen.h"


class MainMenu : public Screen {
public:
    // declared public just so that I can use std::make_unique<MainMenu>()
    MainMenu() : Screen() {}



private:;

    void enter() override {
        std::cout << "Enter Main menu Screen" << "\n";
    }

    Screen* update() override;

    void exit() override {
        std::cout << "Exit Main menu Screen" << "\n";
    }

};