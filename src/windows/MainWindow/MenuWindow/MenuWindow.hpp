#pragma once

#include <wx/wx.h>
#include "../../constant.hpp"
#include "../../components/Button.hpp"
#include "ListUserPanel.hpp"

class MenuWindow : public wxPanel
{
public:
    MenuWindow(wxWindow* parent, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize);
    ~MenuWindow();
};