#include "MainFrame.hpp"
#include "../CaptureWindow/CaptureFrame.h"

MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(nullptr, wxID_ANY, title, pos, size)
{
    this->SetupMainFrame();
}

void MainFrame::CreateNavBar()
{
    Navbar = new NavigationBar(this, wxID_ANY);
    MainSizer->Add(Navbar, 0, wxEXPAND);
}

void MainFrame::SetupMainFrame()
{
    MainPanel = new wxPanel(this, wxID_ANY);
    MainSizer = new wxBoxSizer(wxHORIZONTAL);

    this->CreateNavBar();

    // auto mainWindow = new MainWindow(MainPanel, wxDefaultPosition, wxDefaultSize);
    // mainWindow->Center();
    // MainSizer->Add(mainWindow, 0, wxEXPAND);

    MainPanel->SetSizer(MainSizer);
    // this->SetBackgroundColour(wxColour(244, 243, 243));
    this->Center();
}

MainFrame::~MainFrame()
{
}



void MainFrame::CreateMainWindow()
{
    // auto mainWindow = new MainWindow(MainPanel, wxDefaultPosition, wxDefaultSize);
    // mainWindow->Center();
    // MainSizer->Add(mainWindow, 0, wxEXPAND);
}

