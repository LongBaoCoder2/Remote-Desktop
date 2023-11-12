#include "MainFrame.hpp"


MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(nullptr, wxID_ANY, title, pos, size)
{
    // Setup the main frame
    this->SetupMainFrame();
}

// Create the navigation bar and add it to MainSizer
void MainFrame::CreateNavBar()
{
    Navbar = new NavigationBar(MainPanel, wxID_ANY, wxDefaultPosition, CONFIG_UI::NAVIGATION_SIZE, this);
    MainSizer->Add(Navbar, 0, wxEXPAND);
}

void MainFrame::SetupMainFrame()
{
    MainPanel = new wxPanel(this, wxID_ANY);
    MainSizer = new wxBoxSizer(wxHORIZONTAL);

    // Create and add the navigation bar to the main frame
    this->CreateNavBar();
    this->CreateMainWindow();

    // Set MainPanel as the sizer for the main frame
    MainPanel->SetSizer(MainSizer);

    // Configure the main frame background color
    this->SetBackgroundColour(CONFIG_UI::PRIMARY_LIGHT_COLOR);
    this->Center(); // Center the main frame on the screen
}

MainFrame::~MainFrame()
{
}

void MainFrame::CreateMainWindow()
{
    this->currentWindow = new HomeWindow(MainPanel);
    GetAllWindow()[Window_ID::HOME_WINDOW] = this->currentWindow;

    MainSizer->Add(this->currentWindow, 0, wxEXPAND);
}

std::map<Window_ID, wxWindow*>& MainFrame::GetAllWindow()
{
    return AllWindow;
}

void MainFrame::CreateMenuWindow()
{
    const bool hasMenuWindow = GetAllWindow().find(Window_ID::MENU_WINDOW) != GetAllWindow().end();
    if (!hasMenuWindow) {
        GetAllWindow()[Window_ID::MENU_WINDOW] = new MenuWindow(MainPanel);
    }
    this->currentWindow->Close();
    this->currentWindow = GetAllWindow()[Window_ID::MENU_WINDOW];
    this->currentWindow->Show(true);
    this->Refresh();
}

void MainFrame::CreateHomeWindow()
{
    // Not check as it was created
    this->currentWindow->Close();
    this->currentWindow = GetAllWindow()[Window_ID::HOME_WINDOW];
    this->currentWindow->Show(true);
    this->Refresh();
}

void MainFrame::CreateManageWindow()
{
    const bool hasManageWindow = GetAllWindow().find(Window_ID::MANAGE_WINDOW) != GetAllWindow().end();
    if (!hasManageWindow) {
        GetAllWindow()[Window_ID::MANAGE_WINDOW] = new ManageWindow(MainPanel);
    }
    this->currentWindow->Close();
    this->currentWindow = GetAllWindow()[Window_ID::MANAGE_WINDOW];
    this->currentWindow->Show(true);
    this->Refresh();
}

void MainFrame::CreateSettingWindow()
{
    const bool hasSettingWindow = GetAllWindow().find(Window_ID::SETTING_WINDOW) != GetAllWindow().end();
    if (!hasSettingWindow) {
        GetAllWindow()[Window_ID::SETTING_WINDOW] = new SettingWindow(MainPanel);
    }

    this->currentWindow->Close();
    this->currentWindow = GetAllWindow()[Window_ID::SETTING_WINDOW];
    this->currentWindow->Show(true);
    this->Refresh();
}