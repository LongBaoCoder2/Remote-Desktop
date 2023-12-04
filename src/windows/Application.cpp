#include "Application.h"

#include "constant.hpp"

bool Application::OnInit() {
  wxInitAllImageHandlers();
  // LoginFrame *LoginWindow = new LoginFrame(wxT("Remote Desktop"),
  // wxDefaultPosition, wxDefaultSize); LoginWindow->Show(true);

  MainFrame *MainWindow =
      new MainFrame("Main Menu", wxDefaultPosition, CONFIG_UI::SMALL_WINDOW);
  MainWindow->Show(true);

  return true;
}
