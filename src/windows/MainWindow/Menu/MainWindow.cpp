#include "MainWindow.hpp"
#include "../ServerWindow/ServerTextWindow.hpp"

MainWindow::MainWindow(wxWindow *parent, const wxPoint &pos, const wxSize &size)
    : wxWindow()
{
    wxWindow::Create(parent, wxID_ANY, pos, size);

    auto MainWindowPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(1124, 890));
    auto ButtonSizer = new wxBoxSizer(wxHORIZONTAL);

    auto ClientButton = new MyButton(MainWindowPanel, wxID_ANY, "CLIENT", wxDefaultPosition, wxSize(260, 45));
    ClientButton->Bind(wxEVT_LEFT_DOWN, [](wxMouseEvent &e)
    {
        wxMessageBox("Client");
        e.Skip(); 
        
    });
    auto ServerButton = new MyButton(MainWindowPanel, wxID_ANY, "SERVER", wxDefaultPosition, wxSize(260, 45));
    ServerButton->Bind(wxEVT_LEFT_DOWN, [](wxMouseEvent &e)
    {
        wxMessageBox("Server");
        ServerTextWindow* serverTextWindow = new ServerTextWindow(); 
        serverTextWindow->Show();
        // e.Skip(); 
    
    });

    ButtonSizer->Add(ClientButton, 1, wxALL, FromDIP(20));
    ButtonSizer->Add(ServerButton, 1, wxALL, FromDIP(20));

    this->SetSizerAndFit(ButtonSizer);
    this->Center();
    // MainWindowPanel->SetSizer(ButtonSizer);
}

void MainWindow::OnServerButtonClick(wxMouseEvent &event)
{

    event.Skip();
}

MainWindow::~MainWindow()
{
}