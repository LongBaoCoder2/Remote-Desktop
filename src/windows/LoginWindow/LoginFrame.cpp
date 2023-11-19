#include "LoginFrame.h"
#include "../CaptureWindow/CaptureFrame.h"
#include "Validation/IDValidation.hpp"
#include "Validation/PasswordValidation.hpp"
#include <iostream>

wxDEFINE_EVENT(NavigateToMainWindow, wxCommandEvent);

LoginFrame::LoginFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(nullptr, wxID_ANY, title, pos, size)
{

    this->setupLoginForm();
    this->setupImageForm();

    this->SetSizerAndFit(MainSizer);
    this->Center();

    // Task: Optimization by optimizing wxBoxSizer and wxPanel
}

void LoginFrame::setupLoginForm()
{
    // MainSizer consist of LeftPanel and RightPanel
    MainSizer = new wxBoxSizer(wxHORIZONTAL);
    MainSizer->SetMinSize(wxSize(1240, 720));

    // LeftPanel is FormPanel
    LeftPanel = new wxPanel(this, wxID_ANY);
    LeftPanel->SetBackgroundColour(wxColour(255, 255, 255));
    LeftPanel->SetSize(wxSize(620, 720));

    // RightPanel for decoration and information
    RightPanel = new wxPanel(this, wxID_ANY);
    RightPanel->SetBackgroundColour(wxColour(250, 250, 250));
    RightPanel->SetSize(wxSize(620, 720));

    // Add Two Panel into MainSizer
    MainSizer->Add(LeftPanel, 1, wxEXPAND, 0);
    MainSizer->Add(RightPanel, 1, wxEXPAND, 0);

    // FormSizer consist of TextControl
    FormSizer = new wxBoxSizer(wxVERTICAL);
    FormPanel = new wxPanel(LeftPanel, wxID_ANY);

    // Title text
    TitleText = new wxStaticText(FormPanel, wxID_ANY, "LOGIN");
    TitleText->SetFont(wxFont(24, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

    // ID TextInput
    IDSizer = new wxBoxSizer(wxVERTICAL);
    IDPanel = new wxPanel(FormPanel, wxID_ANY);
    IDText = new wxStaticText(IDPanel, wxID_ANY, wxT("Enter your ID: "));
    IDInput = new wxTextCtrl(IDPanel, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(370, 40));

    IDSizer->Add(IDText, 0);
    IDSizer->Add(IDInput, 0, wxTOP | wxEXPAND, FromDIP(10));
    IDPanel->SetSizer(IDSizer);
    this->styleText(IDText);

    // ID TextInput
    PwSizer = new wxBoxSizer(wxVERTICAL);
    PwPanel = new wxPanel(FormPanel, wxID_ANY);
    PwText = new wxStaticText(PwPanel, wxID_ANY, wxT("Enter your password: "));
    PwInput = new wxTextCtrl(PwPanel, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(370, 40), wxTE_PASSWORD);

    PwSizer->Add(PwText, 0);
    PwSizer->Add(PwInput, 0, wxTOP | wxEXPAND, FromDIP(10));
    PwPanel->SetSizer(PwSizer);
    this->styleText(PwText);

    // CheckBox Admin
    AdminCheck = new wxCheckBox(FormPanel, wxID_ANY, "Login as ADMIN");
    AdminCheck->SetFont(IDText->GetFont());
    AdminCheck->Bind(wxEVT_CHECKBOX, &LoginFrame::OnCheckAdmin, this);

    // Error Hint
    ErrorHint = new wxStaticText(FormPanel, wxID_ANY, "");
    this->styleText(ErrorHint);

    SubmitBtn = new Button(FormPanel, wxID_ANY, "LOGIN", wxDefaultPosition, wxSize(220, 50));
    SubmitBtn->Bind(wxEVT_LEFT_DOWN, &LoginFrame::OnSubmit, this);

    FormSizer->Add(TitleText, 1, wxALIGN_CENTER | wxALL, FromDIP(10));
    FormSizer->Add(IDPanel, 1, wxTOP | wxEXPAND, FromDIP(15));
    FormSizer->Add(PwPanel, 1, wxTOP | wxBOTTOM | wxEXPAND, FromDIP(10));
    FormSizer->Add(AdminCheck, 0, wxEXPAND | wxTOP | wxBOTTOM, FromDIP(15));
    FormSizer->Add(SubmitBtn, 0, wxALIGN_CENTER | wxALL, FromDIP(20));
    FormPanel->SetSizerAndFit(FormSizer);
    FormPanel->Center();

    PwPanel->Show(false);
    FormPanel->Layout();
}

void LoginFrame::setupImageForm()
{

    wxPNGHandler* handler = new wxPNGHandler;
    wxImage::AddHandler(handler);
    // image = new wxStaticBitmap(this, wxID_ANY, , wxPoint(50, 100), wxSize(100, 500));
    wxImage logoImage("assets/RD.png", wxBITMAP_TYPE_PNG);

    if (logoImage.IsOk())
    {
        wxBitmap logoBitmap(logoImage.Rescale(700, 700));
        staticBitmap = new wxStaticBitmap(RightPanel, wxID_ANY, logoBitmap, wxDefaultPosition, wxDefaultSize);
    }
}

void LoginFrame::styleText(wxStaticText* text)
{
    text->SetFont(wxFont(12, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
}

// void LoginFrame::OnLogin(wxCommandEvent& event)
// {
//     wxString enteredID = IDInput->GetValue();
//     wxString enteredPassword = PwInput->GetValue();
//     wxString noti = "Notification";
//     wxString message;

//     // Thực hiện xác thực ID và mật khẩu tại đây (ví dụ: so sánh với giá trị mẫu)
//     if (enteredID == "admin" && enteredPassword == "password") {
//         // Xử lý khi đăng nhập thành công
//         message = wxT("Login success!");
//         wxMessageBox(message, noti, wxOK | wxICON_INFORMATION);
//         // Tạo và hiển thị CaptureFrame
//         CaptureFrame* captureFrame = new CaptureFrame("Capture Window", wxDefaultPosition, wxDefaultSize);
//         captureFrame->Show();

//         // Đóng cửa sổ LoginFrame
//         this->Close();
//     } else {
//         // Xử lý khi đăng nhập thất bại
//         message = wxT("Login failed!");
//         wxMessageBox(message, noti, wxOK | wxICON_ERROR);
//     }
// }

LoginFrame::~LoginFrame()
{
}

void LoginFrame::SendNavigationEvent()
{
    wxCommandEvent event(NavigateToMainWindow);
    wxGetApp().ProcessEvent(event);
}

void LoginFrame::OnSubmit(wxMouseEvent& e)
{
    SendNavigationEvent();
}

void LoginFrame::OnCheckAdmin(wxCommandEvent& e)
{
    wxCheckBox* checkBox = wxDynamicCast(e.GetEventObject(), wxCheckBox);
    if (checkBox)
    {
        wxWindow* pwPanel = AdminCheck->GetParent()->FindWindow(PwPanel->GetId());

        if (pwPanel)
        {
            IDInput->SetValue("");
            PwInput->SetValue("");
            isAdminLogin = !isAdminLogin;

            pwPanel->Show(AdminCheck->IsChecked());

            pwPanel->GetParent()->Layout();
        }
    }
}
