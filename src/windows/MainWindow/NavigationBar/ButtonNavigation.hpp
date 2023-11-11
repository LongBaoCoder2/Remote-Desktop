#pragma once

#include <wx/wx.h>
#include "../../components/Button.hpp"
#include "../../CaptureWindow/CaptureFrame.h"

class ButtonNavigation : public wxPanel
{
public:
    enum Button_ID {
        HOME_WINDOW = wxID_ANY + 1,
        MENU_WINDOW,
        MANAGE_WINDOW,
        SETTING_WINDOW
    };

    ButtonNavigation(wxWindow* parent,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize);
private:
    wxBoxSizer* ButtonSizer;

    void OnClick(wxMouseEvent&);
    void OnSettingClick(wxMouseEvent&);
};
