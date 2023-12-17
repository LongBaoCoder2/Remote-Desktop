#include "KeylogWindow.hpp"
#include "../../../constant.hpp"


KeylogWindow::KeylogWindow(ClientWindow* clientWin)
    : wxFrame(NULL, wxID_ANY, "Keylog Window", wxDefaultPosition, CONFIG_UI::SMALL_WINDOW) 
{
    clientWindow = clientWin;

    // Tạo panel để chứa các phần tử
    panel = new wxPanel(this, wxID_ANY);

    // Tạo box sizer để sắp xếp các phần tử theo chiều dọc
    vbox = new wxBoxSizer(wxVERTICAL);

    // Tạo các nút Hook và Unhook và thêm vào box sizer
    hookButton = new wxButton(panel, wxID_ANY, "Hook");
    unhookButton = new wxButton(panel, wxID_ANY, "Unhook");

    vbox->Add(hookButton, 0, wxEXPAND | wxALL, 10);
    vbox->Add(unhookButton, 0, wxEXPAND | wxALL, 10);

    // Tạo text control để hiển thị text
    textControl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_READONLY | wxHSCROLL);
    vbox->Add(textControl, 1, wxEXPAND | wxALL, 10);

    panel->SetSizer(vbox);

    // Kết nối sự kiện click cho nút Hook và Unhook
    hookButton->Bind(wxEVT_BUTTON, &KeylogWindow::OnHookButtonClick, this);
    unhookButton->Bind(wxEVT_BUTTON, &KeylogWindow::OnUnhookButtonClick, this);
}

void KeylogWindow::OnHookButtonClick(wxCommandEvent& event) {
    // Xử lý khi nút Hook được nhấn
    textControl->AppendText("Hook button clicked!\n");
}

void KeylogWindow::OnUnhookButtonClick(wxCommandEvent& event) {
    // Xử lý khi nút Unhook được nhấn
    textControl->AppendText("Unhook button clicked!\n");
}

KeylogWindow::~KeylogWindow() {}