#pragma once

#include <wx/wx.h>
#include <vector>
#include "NavigationButtons.hpp"
#include "../../constant.hpp"
#include "../../MainWindow/MainFrame.hpp"
#include "WindowID.hpp"

class NavigationButtons; // Need to refactor

class NavigationBar : public wxPanel
{
public:
    NavigationBar(wxWindow* parent,
        wxWindowID id,
        MainFrame* parentFrame,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize);

    virtual ~NavigationBar();

    void OnNavigation(const Window_ID& Window_id);

private:
    MainFrame* MainParent = nullptr;

    std::string id = "ADMIN";
    std::string iconPath = CONFIG_APP::USER_ICON_PATH;
    Window_ID currentID = Window_ID::HOME_WINDOW;

    wxBoxSizer* NavSizer, * UserSizer;
    wxStaticText* TitleText;
    wxPanel* UserInfoPanel;

    NavigationButtons* BtnNav = nullptr;
};
