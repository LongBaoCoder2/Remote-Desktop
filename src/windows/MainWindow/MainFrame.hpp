#pragma once

#include <wx/wx.h>
#include <map>

#include "ClientWindow/ClientWindow.hpp"
// #include "MenuWindow/MainWindow.hpp"
#include "NavigationBar/NavigationBar.hpp"
#include "ServerWindow/ServerWindow.hpp"
#include "../CaptureWindow/CaptureFrame.h"
#include "../constant.hpp"

#include "../../utils/Logger/WindowLogger.hpp"
#include "../AllWindow/HomeWindow/HomeWindow.hpp"
#include "../AllWindow/SettingWindow/SettingWindow.hpp"
#include "../AllWindow/MenuWindow/MenuWindow.hpp"
#include "../AllWindow/ManageWindow/ManageWindow.hpp"
#include "NavigationBar/WindowID.hpp"

class NavigationBar;

class MainFrame : public wxFrame
{
public:

  MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
  ~MainFrame();

  std::map<Window_ID, wxWindow*>& GetAllWindow();

  // Navigation Window
  void CreateMenuWindow();
  void CreateHomeWindow();
  void CreateManageWindow();
  void CreateSettingWindow();

private:
  wxPanel* MainPanel = nullptr;
  wxBoxSizer* MainSizer = nullptr;
  NavigationBar* Navbar = nullptr;

  std::map<Window_ID, wxWindow*> AllWindow;
  wxWindow* currentWindow = nullptr;

  void SetupMainFrame();
  void CreateNavBar();
  void CreateMainWindow();
};
