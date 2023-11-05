#pragma once

#include <wx/wx.h>
#include "Navbar/Navbar.hpp"

class MainFrame : public wxFrame
{
public:
    MainFrame(const wxString &title, const wxPoint &pos, const wxSize &size);

    ~MainFrame();

private:
    wxPanel *MainPanel = nullptr;

    // Navigation
    wxPanel *navbarPanel = nullptr;
    wxBoxSizer *NavSizer, *buttonSizer, *userSizer;
    wxPanel *btnPanel, *userInfoPanel;

    void SetupNavbar();
    void SetupMainMenu();

    // NavigationBar *Navbar = nullptr;
};