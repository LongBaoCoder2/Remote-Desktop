#pragma once

#include <wx/wx.h>
#include <wx/app.h> 
#include "LoginWindow/LoginFrame.h"
#include "MainWindow/MainFrame.hpp"
#include "../models/IModel.hpp"
#include "../models/ModelFactory.hpp"

class Application : public wxApp
{
private:
    void NavigateToMainWindow(std::unique_ptr<IModel> Model);
    void OnUserLogin(wxCommandEvent& event);
    void OnAdminLogin(wxCommandEvent& event);

private:
    MainFrame* MainWindow = nullptr;
    LoginFrame* LoginWindow = nullptr;

    ModelFactory factory;

public:
    virtual bool OnInit();
};