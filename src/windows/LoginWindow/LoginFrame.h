#pragma once

#include <wx/wx.h>

class LoginFrame : public wxFrame {
 private:
  bool isAdminLogin = false;

  wxBoxSizer *MainSizer, *FormSizer, *IDSizer, *PwSizer;

  wxPanel *LeftPanel, *RightPanel;

  wxStaticText *TitleText;
  wxPanel *FormPanel;

  wxPanel *IDPanel, *PwPanel;
  wxStaticText *IDText, *PwText;
  wxTextCtrl *IDInput, *PwInput;

  wxCheckBox *AdminCheck;
  wxButton *SubmitBtn;
  wxStaticText *ErrorHint;

  wxStaticBitmap *staticBitmap;

  wxString id, password;

  void styleText(wxStaticText *text);

  void setupLoginForm();

  void setupImageForm();

  void OnCheckAdmin(wxCommandEvent &);
  void OnSubmit(wxCommandEvent &);

  // void OnLogin(wxCommandEvent& event);

 public:
  LoginFrame(const wxString &title, const wxPoint &pos, const wxSize &size);

  ~LoginFrame();
};