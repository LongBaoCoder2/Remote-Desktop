#pragma once

#include <wx/wx.h>

class ClientWindow;

class KeylogWindow : public wxFrame {
public:
    KeylogWindow(ClientWindow* clientWin);
    virtual ~KeylogWindow();

private:

    void OnHookButtonClick(wxCommandEvent& event);
    void OnUnhookButtonClick(wxCommandEvent& event);

    ClientWindow* clientWindow = nullptr;
    wxPanel* panel = nullptr;
    wxBoxSizer* vbox = nullptr;
    wxButton* hookButton = nullptr;
    wxButton* unhookButton = nullptr;
    wxTextCtrl* textControl = nullptr;
};