#pragma once

#include <wx/wx.h>

class BasicTextFrame : public wxFrame {
public:
    BasicTextFrame(const wxString& title = "Basic Text Frame", const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxSize(1920 / 4, 1080 / 2));


protected:
    void DisplayMessage(const wxString& host = "Basic Text", const wxString& message = "Default message.");
    wxTextCtrl* textCtrl;
    wxFont font;

};