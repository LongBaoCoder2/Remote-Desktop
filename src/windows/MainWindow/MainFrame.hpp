#pragma once

#include <wx/wx.h>
#include <map>
#include <memory>

#include "ClientWindow/ClientWindow.hpp"
#include "../components/NavigationBar/NavigationBar.hpp"
#include "ServerWindow/ServerWindow.hpp"
#include "../constant.hpp"

#include "SettingsWindow/SettingsFrame.hpp"
#include "HomeWindow/HomeWindow.hpp"
#include "MenuWindow/MenuWindow.hpp"
#include "ManageWindow/ManageWindow.hpp"
#include "../components/NavigationBar/WindowID.hpp"


#include "../../models/IModel.hpp"

class NavigationBar;

class MainFrame : public wxFrame
{
public:

  MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size, std::unique_ptr<IModel> model);
  ~MainFrame();

  std::map<Window_ID, wxWindow*>& GetAllWindow();

  // Navigation Window
  void CreateMenuWindow();
  void CreateHomeWindow();
  void CreateManageWindow();
  void CreateSettingWindow();

private:
  void SetupMainFrame();
  void CreateNavBar();
  void CreateMainWindow();

private:
  std::unique_ptr <IModel> Model;

  // Settings Frame
  SettingsFrame* settingsFrame = nullptr;

  wxPanel* MainPanel = nullptr;
  wxBoxSizer* MainSizer = nullptr;
  NavigationBar* Navbar = nullptr;

  wxWindow* currentWindow = nullptr;
  wxBoxSizer* WindowSizer = nullptr;
  wxPanel* WindowPanel = nullptr;
};
