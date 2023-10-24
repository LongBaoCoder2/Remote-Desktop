#pragma once

#include <wx/wx.h>

class LoginFrame : public wxFrame
{
private:
    wxBoxSizer *MainSizer;
    wxBoxSizer *FormSizer;
    wxBoxSizer *IDSizer;
    wxBoxSizer *PwSizer;

    wxPanel *LeftPanel;
    wxPanel *RightPanel;

    wxStaticText *TitleText;
    wxPanel *FormPanel;

    wxPanel *IDPanel;
    wxStaticText *IDText;
    wxTextCtrl *IDInput;

    wxPanel *PwPanel;
    wxStaticText *PwText;
    wxTextCtrl *PwInput;

    wxCheckBox *AdminCheck;
    wxButton *SubmitBtn;

    wxStaticBitmap *staticBitmap;

    void styleText(wxStaticText *text);

    void setupLoginForm();

    void setupImageForm();

public:
    LoginFrame(const wxString &title, const wxPoint &pos, const wxSize &size);

    ~LoginFrame();
};