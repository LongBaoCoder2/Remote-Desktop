#pragma once

#include <wx/wx.h>
#include "LoginWindow/LoginFrame.h"
#include "MainWindow/MainFrame.hpp"

class Application : public wxApp
{
private:
    MainFrame* MainWindow;
public:
    virtual bool OnInit();
};
