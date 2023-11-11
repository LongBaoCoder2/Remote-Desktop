#pragma once

#include <wx/wx.h>
#include <vector>
#include "ButtonNavigation.hpp"

class NavigationBar : public wxPanel
{
public:
    NavigationBar(wxWindow* parent,
        wxWindowID id,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize);

    virtual ~NavigationBar();

private:
    std::string id = "Username";
    std::string iconPath = "assets/user_icon.png";

    wxBoxSizer* NavSizer, * UserSizer;
    wxStaticText* TitleText;
    wxPanel* UserInfoPanel;
    ButtonNavigation* BtnNav;

    void OnSettingSelected(wxMouseEvent&);
    void OnClick(wxMouseEvent&);
};
