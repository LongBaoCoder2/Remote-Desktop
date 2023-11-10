#include "Application.h"

bool Application::OnInit() {
  wxInitAllImageHandlers();
  // LoginFrame *LoginWindow = new LoginFrame(wxT("Remote Desktop"),
  // wxDefaultPosition, wxDefaultSize); LoginWindow->Show(true);

  MainFrame *MainWindow =
      new MainFrame("Main Menu", wxDefaultPosition, wxSize(1480, 890));
  MainWindow->Show(true);

  return true;
}
