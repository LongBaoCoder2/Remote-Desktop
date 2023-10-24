#include "Application.h"

bool Application::OnInit()
{
    LoginFrame *LoginWindow = new LoginFrame(wxT("Remote Desktop"), wxDefaultPosition, wxDefaultSize);
    LoginWindow->Show(true);

    return true;
}
