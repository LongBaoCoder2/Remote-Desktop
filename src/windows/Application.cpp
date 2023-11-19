#include "Application.h"
#include "constant.hpp"


bool Application::OnInit()
{
    wxInitAllImageHandlers();
    LoginWindow = new LoginFrame(wxT("Login"), wxDefaultPosition, wxDefaultSize);
    LoginWindow->Show(true);

    Connect(wxID_ANY, NavigateToMainWindow, wxCommandEventHandler(Application::OnNavigateToMainWindow));

    return true;
}

void Application::OnNavigateToMainWindow(wxCommandEvent& event)
{
    if (LoginWindow) {
        LoginWindow->Destroy();
    }

    MainWindow = new MainFrame(wxT("Remote Desktop"), wxDefaultPosition, wxDefaultSize, std::move(Model));
    MainWindow->Show(true);
}

