#pragma once

#include <wx/wx.h>

#include "ClientWindow/ClientWindow.hpp"
#include "Menu/MainWindow.hpp"
#include "Navbar/Navbar.hpp"
#include "ServerWindow/ServerWindow.hpp"

class MainFrame : public wxFrame {
 public:
  enum class Windows : unsigned int { HOME = 0, MENU, MANAGER, SETTINGS };

  MainFrame(const wxString &title, const wxPoint &pos, const wxSize &size);

  ~MainFrame();

 private:
  //
  void OnClickSelected(wxMouseEvent &);
  void OnSettingSelected(wxMouseEvent &);
  //

  wxPanel *MainPanel = nullptr;

  // Navigation
  wxPanel *navbarPanel = nullptr;
  wxBoxSizer *NavSizer, *buttonSizer, *userSizer;
  wxPanel *btnPanel, *userInfoPanel;

  void SetupNavbar();
  void SetupMainMenu();

  // NavigationBar *Navbar = nullptr;

  Windows curWindows = Windows::HOME;
  wxWindow *currentWindows = nullptr;
};