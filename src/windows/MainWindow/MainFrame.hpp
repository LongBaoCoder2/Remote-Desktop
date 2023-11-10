#pragma once

#include <wx/wx.h>

#include "ClientWindow/ClientWindow.hpp"
#include "MenuWindow/MainWindow.hpp"
#include "NavigationBar/NavigationBar.hpp"
#include "ServerWindow/ServerWindow.hpp"

#include "../../utils/Logger/WindowLogger.hpp"

// class MainFrame : public wxFrame
// {
// public:
//   enum class Windows : unsigned int
//   {
//     HOME = 0,
//     MENU,
//     MANAGER,
//     SETTINGS
//   };

//     ~MainFrame();

//   private:
//     //
//     void OnClickSelected(wxMouseEvent &);
//     void OnSettingSelected(wxMouseEvent &);
//     //

//     wxPanel *MainPanel = nullptr;

//     // // Navigation
//     wxPanel *navbarPanel = nullptr;
//     wxBoxSizer *NavSizer, *buttonSizer, *userSizer, *MainSizer;
//     wxPanel *btnPanel, *userInfoPanel;

//     void SetupNavbar();
//     void SetupMainMenu();

//     // // NavigationBar *Navbar = nullptr;

//     // Windows curWindows = Windows::HOME;
//     // wxWindow *currentWindows = nullptr;

//     NavigationBar *Navbar = nullptr;
//   };

class MainFrame : public wxFrame
{
public:
  MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
  ~MainFrame();

private:
  //
  void OnClickSelected(wxMouseEvent&);
  void OnSettingSelected(wxMouseEvent&);
  //

  wxPanel* MainPanel = nullptr;

  // Navigation
  wxPanel* NavbarPanel = nullptr;
  wxBoxSizer* NavSizer, * ButtonSizer, * UserSizer;
  wxPanel* BtnPanel, * UserInfoPanel;

  void SetupNavbar();
  void SetupMainMenu();

  // NavigationBar *Navbar = nullptr;
  std::unique_ptr<Logger> logger;
};
