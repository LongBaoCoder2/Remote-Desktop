#pragma once

#include <wx/wx.h>
#include <vector>
#include "ButtonNavigation.hpp"
#include "../../constant.hpp"

class NavigationBar : public wxPanel
{
public:
    NavigationBar(wxWindow* parent,
        wxWindowID id,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize);

    virtual ~NavigationBar();

private:
    std::string id = "ADMIN";
    std::string iconPath = CONFIG_APP::USER_ICON_PATH;

    wxBoxSizer* NavSizer, * UserSizer;
    wxStaticText* TitleText;
    wxPanel* UserInfoPanel;
    ButtonNavigation* BtnNav;

    void OnSettingSelected(wxMouseEvent&);
    void OnClick(wxMouseEvent&);
};
