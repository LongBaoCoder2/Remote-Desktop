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
    Navbar = new NavigationBar(MainPanel, wxID_ANY, wxDefaultPosition, CONFIG_UI::NAVIGATION_SIZE);
    MainSizer->Add(Navbar, 0, wxEXPAND);
}

void MainFrame::SetupMainFrame()
{
    MainPanel = new wxPanel(this, wxID_ANY);
    MainSizer = new wxBoxSizer(wxHORIZONTAL);

    // Create and add the navigation bar to the main frame
    this->CreateNavBar();

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
    // Create the main window and add it to the MainSizer
    auto mainWindow = new MainWindow(MainPanel, wxDefaultPosition, wxDefaultSize);
    mainWindow->Center(); // Center the main window
    MainSizer->Add(mainWindow, 0, wxEXPAND);
}


void CreateMenuWindow()
{

}

void CreateHomeWindow()
{

}

void CreateManageWindow()
{

}

void CreateSettingWindow()
{

}