#pragma once

#include <wx/wx.h>
#include "LoginWindow/LoginFrame.h"
#include "MainWindow/MainFrame.hpp"

class Application : public wxApp
{

public:
    virtual bool OnInit();
};
