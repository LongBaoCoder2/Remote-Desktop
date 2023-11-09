#pragma once

#include <wx/wx.h>

#include "ClientWindow/ClientWindow.hpp"
#include "Menu/MainWindow.hpp"
#include "NavigationBar/NavigationBar.hpp"
#include "ServerWindow/ServerWindow.hpp"

// class MainFrame : public wxFrame
// {
// public:
//   MainFrame(const wxString &title, const wxPoint &pos, const wxSize &size);

//   ~MainFrame();

// private:
//   //
//   void OnClickSelected(wxMouseEvent &);
//   void OnSettingSelected(wxMouseEvent &);
//   //

//   wxPanel *MainPanel = nullptr;

//   // // Navigation
//   wxPanel *navbarPanel = nullptr;
//   wxBoxSizer *NavSizer, *buttonSizer, *userSizer, *MainSizer;
//   wxPanel *btnPanel, *userInfoPanel;

//   void SetupNavbar();
//   void SetupMainMenu();

//   // // NavigationBar *Navbar = nullptr;

//   // Windows curWindows = Windows::HOME;
//   // wxWindow *currentWindows = nullptr;

//   NavigationBar *Navbar = nullptr;
// };

class MainFrame : public wxFrame
{
public:
  MainFrame(const wxString &title, const wxPoint &pos, const wxSize &size);
  ~MainFrame();

private:
  wxPanel *MainPanel;
  wxBoxSizer *MainSizer;
  NavigationBar *NavBar = nullptr;

  void SetupMainFrame();
  void CreateNavBar();
  void CreateMainWindow();
};