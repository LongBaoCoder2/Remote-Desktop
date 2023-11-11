#include "BasicTextFrame.hpp"

BasicTextFrame::BasicTextFrame(const wxString& title, const wxPoint &pos, const wxSize &size)
: wxFrame(NULL, wxID_ANY, title, pos, size)
{
    textCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);

    // Thêm các nút hoặc chức năng khác để thêm thông tin văn bản vào wxTextCtrl

    // Đặt wxTextCtrl thành chỉ đọc
    textCtrl->SetEditable(false);

    // Customize font
    // font = wxFont(16, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    // textCtrl->SetFont(font);
}


void BasicTextFrame::DisplayMessage(const wxString& host, const wxString& message) {
    textCtrl->AppendText("[" + host + "] ");
    textCtrl->AppendText(message + "\n");
}
