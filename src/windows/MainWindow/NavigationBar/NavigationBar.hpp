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
    ButtonNavigation::Button_ID currentID = ButtonNavigation::HOME_WINDOW;

    wxBoxSizer* NavSizer, * UserSizer;
    wxStaticText* TitleText;
    wxPanel* UserInfoPanel;
    ButtonNavigation* BtnNav;


    void OnNavigation(const ButtonNavigation::Button_ID& Window_id);
};
