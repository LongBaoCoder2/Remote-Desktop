#pragma once

#include <wx/wx.h>
#include <wx/statbmp.h>
#include "../../components/Button.hpp"

class UserPanel : public wxPanel
{
public:
    UserPanel(wxWindow* parent, wxImage iconUser, std::string username);

    ~UserPanel();

    void OnPaint(wxPaintEvent& event);
private:
    wxImage iconUser;
    std::string username;
    std::string IpAddress;
};