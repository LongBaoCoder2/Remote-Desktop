#pragma once

#include <wx/wx.h>
#include "LoginWindow/LoginFrame.h"

class Application : public wxApp
{
    // private:
    //     LoginFrame *LoginWindow;

public:
    virtual bool OnInit();
};
