#include "Application.h"

bool Application::OnInit()
{
    // LoginFrame *LoginWindow = new LoginFrame(wxT("Remote Desktop"), wxDefaultPosition, wxDefaultSize);
    // LoginWindow->Show(true);

    MainFrame *MainWindow = new MainFrame("Main Menu", wxDefaultPosition, wxDefaultSize);
    MainWindow->Show(true);

    return true;
}
