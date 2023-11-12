#include "Application.h"
#include "constant.hpp"

bool Application::OnInit()
{
    wxInitAllImageHandlers();
    // LoginFrame *LoginWindow = new LoginFrame(wxT("Remote Desktop"), wxDefaultPosition, wxDefaultSize);
    // LoginWindow->Show(true);

    MainWindow = new MainFrame("Main Menu", wxDefaultPosition, CONFIG_UI::NORMAL_WINDOW);
    MainWindow->Show(true);

    return true;
}
