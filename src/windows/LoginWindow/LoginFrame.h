#pragma once

#include <wx/wx.h>
#include "../components/Button.hpp"
#include "../MainWindow/MainFrame.hpp"
#include "../Application.h"

wxDECLARE_EVENT(NavigateToMainWindow, wxCommandEvent);


class LoginFrame : public wxFrame {
private:
  std::unique_ptr<IModel> Model;

  bool isAdminLogin = false;

  wxBoxSizer* MainSizer, * FormSizer, * IDSizer, * PwSizer;

  wxPanel* LeftPanel, * RightPanel;

  wxStaticText* TitleText;
  wxPanel* FormPanel;

  wxPanel* IDPanel, * PwPanel;
  wxStaticText* IDText, * PwText;
  wxTextCtrl* IDInput, * PwInput;

  wxCheckBox* AdminCheck;
  Button* SubmitBtn;
  wxStaticText* ErrorHint;

  wxStaticBitmap* staticBitmap;

  wxString id, password;

  void styleText(wxStaticText* text);

  void setupLoginForm();

  void setupImageForm();

  void OnCheckAdmin(wxCommandEvent&);
  void OnSubmit(wxMouseEvent& e);
  void SendNavigationEvent();

  // void OnLogin(wxCommandEvent& event);

public:
  LoginFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

  ~LoginFrame();
};