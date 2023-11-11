#include "MenuWindow.hpp"

MenuWindow::MenuWindow(wxWindow* parent, const wxPoint& pos, const wxSize& size)
    : wxWindow(parent, wxID_ANY, pos, size)
{
    auto TEXT = new wxStaticText(this, wxID_ANY, "Menu Window");
}

MenuWindow::~MenuWindow()
{

}