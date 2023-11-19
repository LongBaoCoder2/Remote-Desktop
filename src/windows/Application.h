#pragma once

#include <wx/wx.h>
#include "LoginWindow/LoginFrame.h"
#include "MainWindow/MainFrame.hpp"
#include "../models/IModel.hpp"

class Application : public wxApp
{
private:
    MainFrame* MainWindow = nullptr;
    LoginFrame* LoginWindow = nullptr;

    std::unique_ptr<IModel> Model;

    void OnNavigateToMainWindow(wxCommandEvent& event);

public:
    virtual bool OnInit();
};