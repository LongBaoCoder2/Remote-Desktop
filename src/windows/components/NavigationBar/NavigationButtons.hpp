#pragma once

#include <wx/wx.h>
#include "../../components/Button.hpp"
#include "NavigationBar.hpp"
#include "../../constant.hpp"
#include "WindowID.hpp"

class MainFrame;
class NavigationBar;

class NavigationButtons : public wxPanel
{
public:
    NavigationButtons(NavigationBar* parentBar,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize);
private:
    NavigationBar* parentBar = nullptr;
    wxBoxSizer* ButtonSizer;

    Button* HomeBtn = new Button(this, Window_ID::HOME_WINDOW, "HOME", wxDefaultPosition, CONFIG_UI::PRIMARY_BUTTON_SIZE);
    Button* MenuBtn = new Button(this, Window_ID::MENU_WINDOW, "MENU", wxDefaultPosition, CONFIG_UI::PRIMARY_BUTTON_SIZE);
    Button* ManagerBtn = new Button(this, Window_ID::MANAGE_WINDOW, "MANAGER", wxDefaultPosition, CONFIG_UI::PRIMARY_BUTTON_SIZE);
    Button* SettingBtn = new Button(this, Window_ID::SETTING_WINDOW, "SETTING", wxDefaultPosition, CONFIG_UI::PRIMARY_BUTTON_SIZE);
    std::vector<Button*> listButton{
        HomeBtn,
        MenuBtn,
        ManagerBtn,
        SettingBtn
    };

    void OnClick(wxMouseEvent&);
    // void OnSettingClick(wxMouseEvent&);
};
