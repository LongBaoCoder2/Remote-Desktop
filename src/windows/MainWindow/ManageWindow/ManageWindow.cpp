#include "ManageWindow.hpp"

ManageWindow::ManageWindow(wxWindow* parent, const wxPoint& pos, const wxSize& size)
    : wxPanel(parent, wxID_ANY, pos, size)
{

}

ManageWindow::~ManageWindow()
{

}

void ManageWindow::OnServerConnectButton(wxMouseEvent& event)
{
    // serverWindow = std::make_unique<ServerWindow>(CONFIG_APP::PORT);
    serverWindow = new ServerWindow();
    serverWindow->Show();
}

void ManageWindow::OnClientConnectButton(wxMouseEvent& event)
{
    std::string ipAddress = IPInput->GetValue().ToStdString();
    // clientWindow = std::make_unique<ClientWindow>(ipAddress, CONFIG_APP::PORT);
    clientWindow = new ClientWindow();
    clientWindow->ConnectToHost(ipAddress);
    clientWindow->Show();
}