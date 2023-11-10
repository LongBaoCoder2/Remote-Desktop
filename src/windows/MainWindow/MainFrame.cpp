#include "MainFrame.hpp"
#include "../CaptureWindow/CaptureFrame.h"

MainFrame::MainFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxFrame(nullptr, wxID_ANY, title, pos, size)
{
    // MainPanel = new wxPanel(this, wxID_ANY);
    // auto MainSizer = new wxBoxSizer(wxHORIZONTAL);

    // Navbar = new NavigationBar(this, wxID_ANY, wxDefaultPosition, wxSize(256, 890));
    // MainSizer->Add(Navbar, 0, wxEXPAND);

    // MainPanel->SetSizerAndFit(MainSizer);

    // this->SetBackgroundColour(wxColour(244, 243, 243));
    // this->Center();
    this->SetupMainMenu();
}

void MainFrame::SetupNavbar()
{

    // navPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(256, 720));
    NavSizer = new wxBoxSizer(wxVERTICAL);
    // navPanel = new wxPanel(this, wxID_ANY);
    // navPanel->SetSize(this->GetSize());

    // Set title
    auto titleText = new wxStaticText(navbarPanel, wxID_ANY, "Remote Desktop");
    titleText->SetFont(wxFont(15, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    titleText->SetForegroundColour(*wxWHITE);

    // Button Sizer
    buttonSizer = new wxBoxSizer(wxVERTICAL);
    btnPanel = new wxPanel(navbarPanel, wxID_ANY);

    // Button Navigation
    auto separateLine = new wxPanel(btnPanel, wxID_ANY, wxDefaultPosition, wxSize(240, 5));
    buttonSizer->Add(separateLine, 0, wxEXPAND | wxBOTTOM, FromDIP(8));

    auto HomeBtn = new MyButton(btnPanel, wxID_ANY, "HOME", wxDefaultPosition, wxSize(220, 45));
    auto MenuBtn = new MyButton(btnPanel, wxID_ANY, "MENU", wxDefaultPosition, wxSize(220, 45));
    auto ManagerBtn = new MyButton(btnPanel, wxID_ANY, "MANAGER", wxDefaultPosition, wxSize(220, 45));
    auto SettingBtn = new MyButton(btnPanel, wxID_ANY, "SETTING", wxDefaultPosition, wxSize(220, 45));
    std::vector<MyButton *> listButton{
        HomeBtn,
        MenuBtn,
        ManagerBtn,
        SettingBtn
    };
    for (auto button : listButton)
    {
        // button->SetFont(wxFont(10, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_MEDIUM));
        // button->SetBackgroundColour(wxColour(0, 0, 0));
        // button->SetForegroundColour(wxColour(255, 255, 255));
        button->Bind(wxEVT_LEFT_DOWN, &MainFrame::OnClickSelected, this);
        buttonSizer->Add(button, 0, wxTOP | wxALIGN_CENTER, FromDIP(5));
    }
    SettingBtn->Bind(wxEVT_LEFT_DOWN, &MainFrame::OnSettingSelected, this);
    btnPanel->SetSizerAndFit(buttonSizer);
    // ButtonSizer->Add(HomeBtn, 1, wxTOP | wxALIGN_CENTER, FromDIP(5));
    // HomeBtn->Bind(wxEVT_BUTTON, &NavigationBar::OnClick, this);

    // User Icon
    userInfoPanel = new wxPanel(navbarPanel, wxID_ANY);
    userSizer = new wxBoxSizer(wxVERTICAL);

    // auto userIcon = new wxPanel(userInfoPanel, 0, wxDefaultPosition, wxSize(50, 50));
    // userIcon->SetBackgroundColour(wxColour(100, 200, 100));
    // userSizer->Add(userIcon, 0, wxALIGN_CENTER);
    wxImage iconImage("./assets/user_icon.png", wxBITMAP_TYPE_PNG);

    if (iconImage.IsOk())
    {
        wxBitmap iconBitmap(iconImage.Rescale(64, 64));
        auto userBitmap = new wxStaticBitmap(userInfoPanel, wxID_ANY, iconBitmap);
        userSizer->Add(userBitmap, 0, wxALL, FromDIP(5));
    }

    auto userText = new wxStaticText(userInfoPanel, wxID_ANY, "Username");
    userSizer->Add(userText, 0, wxALIGN_CENTER | wxALL, FromDIP(5));
    userInfoPanel->SetSizerAndFit(userSizer);

    NavSizer->Add(titleText, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, FromDIP(25));
    NavSizer->Add(btnPanel, 0, wxEXPAND | wxTOP | wxBOTTOM, FromDIP(40));
    NavSizer->Add(userInfoPanel, 0, wxALIGN_CENTER | wxTOP, FromDIP(60));

    navbarPanel->SetBackgroundColour(wxColour(17, 25, 38));

    navbarPanel->SetSizer(NavSizer);
}

void MainFrame::OnClickSelected(wxMouseEvent &event)
{
    wxMessageBox("Button Clicked");

    event.Skip();
}

void MainFrame::OnSettingSelected(wxMouseEvent &) {
    wxMessageBox("Capture Frame activated");
    CaptureFrame* captureFrame = new CaptureFrame("Capture Window", wxDefaultPosition, wxDefaultSize);
    captureFrame->Show();
}

void MainFrame::SetupMainMenu()
{
    MainPanel = new wxPanel(this, wxID_ANY);
    auto MainSizer = new wxBoxSizer(wxHORIZONTAL);

    navbarPanel = new wxPanel(MainPanel, wxID_ANY, wxDefaultPosition, wxSize(256, 890));
    this->SetupNavbar();
    MainSizer->Add(navbarPanel, 0, wxEXPAND);

    auto mainWindow = new MainWindow(MainPanel, wxDefaultPosition, wxDefaultSize);
    mainWindow->Center();
    MainSizer->Add(mainWindow, 0, wxEXPAND);

    MainPanel->SetSizer(MainSizer);
    this->SetBackgroundColour(wxColour(244, 243, 243));
    this->Center();
}

MainFrame::~MainFrame()
{
}