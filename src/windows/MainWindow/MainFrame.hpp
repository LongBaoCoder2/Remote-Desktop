#pragma once

#include <wx/wx.h>

#include "ClientWindow/ClientWindow.hpp"
#include "MenuWindow/MainWindow.hpp"
#include "NavigationBar/NavigationBar.hpp"
#include "ServerWindow/ServerWindow.hpp"

#include "../../utils/Logger/WindowLogger.hpp"

class MainFrame : public wxFrame
{
public:
  MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
  ~MainFrame();

private:
  wxPanel* MainPanel = nullptr;
  wxBoxSizer* MainSizer = nullptr;
  NavigationBar* Navbar = nullptr;


  void SetupMainFrame();
  void CreateNavBar();
  void CreateMainWindow();
};
