#include "MainFrame.hpp"


MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size, std::unique_ptr<IModel> model)
    : wxFrame(nullptr, wxID_ANY, title, pos, size), Model(std::move(model))
{
    // Setup the main frame
    this->SetupMainFrame();
}

// Create the navigation bar and add it to MainSizer
void MainFrame::CreateNavBar()
{
    Navbar = new NavigationBar(MainPanel, wxID_ANY, this, wxDefaultPosition, CONFIG_UI::NAVIGATION_SIZE);
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
    auto MainSize = this->GetSize() - CONFIG_UI::NAVIGATION_SIZE;
    WindowPanel = new wxPanel(MainPanel, wxID_ANY, wxDefaultPosition, MainSize);
    WindowSizer = new wxBoxSizer(wxVERTICAL);

    this->currentWindow = new HomeWindow(WindowPanel, Navbar, wxDefaultPosition, CONFIG_UI::NORMAL_WINDOW - CONFIG_UI::NAVIGATION_SIZE);
    GetAllWindow()[Window_ID::HOME_WINDOW] = this->currentWindow;
    WindowSizer->Add(this->currentWindow, 1, wxEXPAND);

    WindowPanel->SetSizerAndFit(WindowSizer);
    MainSizer->Add(WindowPanel, 0, wxEXPAND);
}

std::map<Window_ID, wxWindow*>& MainFrame::GetAllWindow()
{
    static std::map<Window_ID, wxWindow*> AllWindow;
    return AllWindow;
}

void MainFrame::CreateMenuWindow()
{
    // Hide the current window
    this->currentWindow->Hide();

    const bool hasMenuWindow = GetAllWindow().find(Window_ID::MENU_WINDOW) != GetAllWindow().end();
    if (!hasMenuWindow) {
        GetAllWindow()[Window_ID::MENU_WINDOW] = new MenuWindow(WindowPanel, wxDefaultPosition, CONFIG_UI::NORMAL_WINDOW - CONFIG_UI::NAVIGATION_SIZE);
        WindowSizer->Add(GetAllWindow()[Window_ID::MENU_WINDOW], 1, wxEXPAND);
    }
    this->currentWindow = GetAllWindow()[Window_ID::MENU_WINDOW];
    this->currentWindow->Show();
    Layout();
}

void MainFrame::CreateHomeWindow()
{
    // Hide the current window
    this->currentWindow->Hide();

    // Ensure that HomeWindow has been created
    if (GetAllWindow().find(Window_ID::HOME_WINDOW) != GetAllWindow().end()) {
        this->currentWindow = GetAllWindow()[Window_ID::HOME_WINDOW];
        this->currentWindow->Show();
        Layout();
    }
}

void MainFrame::CreateManageWindow()
{
    // Hide the current window
    this->currentWindow->Hide();

    const bool hasManageWindow = GetAllWindow().find(Window_ID::MANAGE_WINDOW) != GetAllWindow().end();
    if (!hasManageWindow) {
        GetAllWindow()[Window_ID::MANAGE_WINDOW] = new ManageWindow(WindowPanel, wxDefaultPosition, CONFIG_UI::NORMAL_WINDOW - CONFIG_UI::NAVIGATION_SIZE);
        WindowSizer->Add(GetAllWindow()[Window_ID::MANAGE_WINDOW], 1, wxEXPAND);
    }
    this->currentWindow = GetAllWindow()[Window_ID::MANAGE_WINDOW];
    this->currentWindow->Show();
    Layout();
}

// void MainFrame::CreateSettingWindow()
// {
//     // Hide the current window
//     this->currentWindow->Hide();

//     const bool hasSettingWindow = GetAllWindow().find(Window_ID::SETTING_WINDOW) != GetAllWindow().end();
//     if (!hasSettingWindow) {
//         GetAllWindow()[Window_ID::SETTING_WINDOW] = new SettingWindow(WindowPanel, wxDefaultPosition, WindowPanel->GetSize());
//         WindowSizer->Add(GetAllWindow()[Window_ID::SETTING_WINDOW], 1, wxEXPAND);
//     }

//     this->currentWindow = GetAllWindow()[Window_ID::SETTING_WINDOW];
//     this->currentWindow->Show();
//     Layout();
// }

void MainFrame::CreateSettingWindow()
{
    settingsFrame = new SettingsFrame(this);
    settingsFrame->Show();
}
