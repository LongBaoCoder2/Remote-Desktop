#include "SettingWindow.hpp"

SettingWindow::SettingWindow(wxWindow* parent, const wxPoint& pos, const wxSize& size)
    : wxWindow(parent, wxID_ANY, pos, size)
{
    auto TEXT = new wxStaticText(this, wxID_ANY, "Setting WINDOW");
}

SettingWindow::~SettingWindow()
{

}