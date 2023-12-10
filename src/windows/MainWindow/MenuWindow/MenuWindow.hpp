#pragma once

#include <wx/wx.h>
#include "../../constant.hpp"
#include "../../components/Button.hpp"
#include "ListUserPanel.hpp"
#include "../../../models/IModel.hpp"

class MenuWindow : public wxPanel
{
public:
    MenuWindow(wxWindow* parent, std::shared_ptr<IModel>& _model, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize);
    ~MenuWindow();

private:
    std::shared_ptr<IModel> model;

    void CreateUserPanel();
    void CreateAdminPanel();

    void OnStartListening();

    wxTextCtrl* IPInput;
};