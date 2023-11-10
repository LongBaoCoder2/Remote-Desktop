#pragma once

#include <wx/wx.h>
#include <wx/aui/auibook.h>
#include <vector>
#include "../../components/Button.hpp"

class NavigationBar : public wxPanel
{
public:
    NavigationBar(wxWindow *parent,
                  wxWindowID id,
                  const wxPoint &pos = wxDefaultPosition,
                  const wxSize &size = wxDefaultSize);

    virtual ~NavigationBar();

    void OnClick(wxMouseEvent &e)
    {
        wxMessageBox("Button Click");
        e.Skip();
    }

private:
    std::string id = "Username";
    std::string iconPath = "assets/user_icon.png";

    wxBoxSizer *NavSizer, *ButtonSizer, *UserSizer;
    wxStaticText *TitleText;
    wxPanel *BtnPanel, *UserInfoPanel;
};
