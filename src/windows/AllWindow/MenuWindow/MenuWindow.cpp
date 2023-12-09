#include "MenuWindow.hpp"
#include <wx/gbsizer.h>

MenuWindow::MenuWindow(wxWindow* parent, const wxPoint& pos, const wxSize& size)
    : wxPanel(parent, wxID_ANY, pos, size)
{
    auto MenuSizer = new wxBoxSizer(wxVERTICAL);

    auto TitlePanel = new wxPanel(this);
    TitlePanel->SetBackgroundColour(CONFIG_UI::PRIMARY_LIGHT_COLOR);

    auto TitleApp = new wxStaticText(TitlePanel, wxID_ANY, "Remote Desktop");
    TitleApp->SetFont(wxFontInfo(16).FaceName("Georgia").Bold());

    auto TitleSizer = new wxBoxSizer(wxHORIZONTAL);

    TitleSizer->Add(TitleApp, 0, wxALL, FromDIP(17));
    TitlePanel->SetSizer(TitleSizer);

    auto UserList = new ListUserPanel(this);

    // auto SplitPanel = new wxPanel(SubMenuPanel, wxID_ANY);
    // SplitPanel->SetBackgroundColour(CONFIG_UI::PRIMARY_DARK_COLOR);
    // SplitPanel->SetWindowStyle(wxALIGN_CENTER);

    // SubMenuSizer->Add(SplitPanel, 1, wxALL | wxEXPAND, FromDIP(10));

    MenuSizer->Add(TitlePanel, 0, wxEXPAND | wxBOTTOM, FromDIP(20));
    MenuSizer->Add(UserList, 1, wxALIGN_CENTER | wxALL, FromDIP(30));


    this->SetSizer(MenuSizer);
    this->SetSize(CONFIG_UI::NORMAL_WINDOW);
    this->SetBackgroundColour(CONFIG_UI::SECONDARY_LIGHT_COLOR);

    Layout();
    Refresh();
}

MenuWindow::~MenuWindow()
{

}