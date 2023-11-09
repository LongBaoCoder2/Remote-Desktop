#pragma once

#include <wx/wx.h>
#include "../constant.hpp"

class BasicTextFrame : public wxFrame {
public:
    BasicTextFrame(const wxString& title = "Basic Text Frame", const wxPoint &pos = wxDefaultPosition, const wxSize &size = CONFIG_UI::VERY_SMALL_WINDOW);


protected:
    void DisplayMessage(const wxString& host = "Basic Text", const wxString& message = "Default message.");
    wxTextCtrl* textCtrl;
    wxFont font;

};