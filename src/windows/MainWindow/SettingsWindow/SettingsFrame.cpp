#include "SettingsFrame.hpp"

SettingsFrame::SettingsFrame(wxWindow* parent, const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(parent, wxID_ANY, title, pos, size)
{
    // Tạo Sidebar Menu bên trái
    sidebar = new wxListBox(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);

    // Danh sách các tiêu đề của từng category
    std::vector<std::string> categoryTitles = {
        "General",
        "Account",
        "Security",
        "Remote Control",
        "Meeting",
        "Audio conferencing",
        "Video",
        "Custom invitation",
        "Advanced"
    };

    // Duyệt qua danh sách và thêm vào sidebar
    for (const std::string& title : categoryTitles) {
        sidebar->Append(title);
    }

    // Đặt mục "General" là mục được chọn mặc định
    sidebar->SetSelection(0);


    // Sự kiện khi người dùng chọn một mục trên sidebar
    sidebar->Bind(wxEVT_LISTBOX, &SettingsFrame::OnSidebarSelection, this);

    // Tạo "Detail View" bên phải
    detailView = new wxPanel(this, wxID_ANY);

    // // Tạo font mới với cỡ chữ lớn hơn
    // wxFont newFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);

    // // Đặt font mới cho cả sidebar và detailView
    // sidebar->SetFont(newFont);
    // detailView->SetFont(newFont);

    // Tạo nội dung ban đầu
    ShowDetailViewForGeneral();

    sizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->Add(sidebar, 1, wxEXPAND | wxALL, 5);
    sizer->Add(detailView, 2, wxEXPAND | wxALL, 5);

    SetSizer(sizer);

}

void SettingsFrame::OnSidebarSelection(wxCommandEvent& event) {
    // Xử lý khi người dùng chọn một mục trên sidebar
    int selectedItemIndex = dynamic_cast<wxListBox*>(event.GetEventObject())->GetSelection();
    SidebarItem selectedItem = static_cast<SidebarItem>(selectedItemIndex);

    switch (selectedItem) {
    case SidebarItem::GENERAL:
        ShowDetailViewForGeneral();
        break;
    case SidebarItem::ACCOUNT:
        ShowDetailViewForAccount();
        break;
    case SidebarItem::SECURITY:
        ShowDetailViewForSecurity();
        break;
    case SidebarItem::REMOTE_CONTROL:
        ShowDetailViewForRemoteControl();
        break;
    case SidebarItem::MEETING:
        ShowDetailViewForMeeting();
        break;
    case SidebarItem::AUDIO_CONFERENCING:
        ShowDetailViewForAudioConferencing();
        break;
    case SidebarItem::VIDEO:
        ShowDetailViewForVideo();
        break;
    case SidebarItem::CUSTOM_INVITATION:
        ShowDetailViewForCustomInvitation();
        break;
    case SidebarItem::ADVANCED:
        ShowDetailViewForAdvanced();
        break;
    default:
        // Xử lý khi một mục khác được chọn (nếu cần)
        break;
    }

    // wxString selectedItemText = dynamic_cast<wxListBox*>(event.GetEventObject())->GetString(selectedItemIndex);
    // ShowDetailViewForItem(selectedItemText);
}

void SettingsFrame::ClearPanelContents(wxWindow* panel) {
    wxWindowList children = panel->GetChildren();
    for (wxWindowList::const_iterator it = children.begin(); it != children.end(); ++it) {
        wxWindow* child = *it;
        panel->RemoveChild(child);
        child->Destroy();
    }
}

void SettingsFrame::ShowDetailViewForGeneral() {
    wxString category = "General";
    int index = static_cast<int>(SidebarItem::GENERAL);

    // Xóa nội dung cũ trong panel
    ClearPanelContents(detailView);

    // Tạo và hiển thị nội dung mới trong panel
    wxStaticText* text1 = new wxStaticText(detailView, wxID_ANY, wxString::Format("Detail View for %s", category));
    wxStaticText* text2 = new wxStaticText(detailView, wxID_ANY, wxString::Format("%s will be implemented soon, it has index %d", category, index));

    // Tạo sizer để sắp xếp các phần tử
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(text1, 0, wxALIGN_LEFT | wxALL, 5);
    sizer->Add(text2, 0, wxALIGN_LEFT | wxALL, 5);

    detailView->SetSizer(sizer);
}

void SettingsFrame::ShowDetailViewForAccount() {
    wxString category = "Account";
    int index = static_cast<int>(SidebarItem::ACCOUNT);

    ClearPanelContents(detailView);

    wxStaticText* text1 = new wxStaticText(detailView, wxID_ANY, wxString::Format("Detail View for %s", category));
    wxStaticText* text2 = new wxStaticText(detailView, wxID_ANY, wxString::Format("%s will be implemented soon, it has index %d", category, index));

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(text1, 0, wxALIGN_LEFT | wxALL, 5);
    sizer->Add(text2, 0, wxALIGN_LEFT | wxALL, 5);

    detailView->SetSizer(sizer);
}

void SettingsFrame::ShowDetailViewForSecurity() {
    wxString category = "Security";
    int index = static_cast<int>(SidebarItem::SECURITY);

    ClearPanelContents(detailView);

    wxStaticText* text1 = new wxStaticText(detailView, wxID_ANY, wxString::Format("Detail View for %s", category));
    wxStaticText* text2 = new wxStaticText(detailView, wxID_ANY, wxString::Format("%s will be implemented soon, it has index %d", category, index));

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(text1, 0, wxALIGN_LEFT | wxALL, 5);
    sizer->Add(text2, 0, wxALIGN_LEFT | wxALL, 5);

    detailView->SetSizer(sizer);
}

void SettingsFrame::ShowDetailViewForRemoteControl() {
    wxString category = "Remote Control";
    int index = static_cast<int>(SidebarItem::REMOTE_CONTROL);

    ClearPanelContents(detailView);

    wxStaticText* text1 = new wxStaticText(detailView, wxID_ANY, wxString::Format("Detail View for %s", category));
    wxStaticText* text2 = new wxStaticText(detailView, wxID_ANY, wxString::Format("%s will be implemented soon, it has index %d", category, index));

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(text1, 0, wxALIGN_LEFT | wxALL, 5);
    sizer->Add(text2, 0, wxALIGN_LEFT | wxALL, 5);

    detailView->SetSizer(sizer);
}

void SettingsFrame::ShowDetailViewForMeeting() {
    wxString category = "Meeting";
    int index = static_cast<int>(SidebarItem::MEETING);

    ClearPanelContents(detailView);

    wxStaticText* text1 = new wxStaticText(detailView, wxID_ANY, wxString::Format("Detail View for %s", category));
    wxStaticText* text2 = new wxStaticText(detailView, wxID_ANY, wxString::Format("%s will be implemented soon, it has index %d", category, index));

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(text1, 0, wxALIGN_LEFT | wxALL, 5);
    sizer->Add(text2, 0, wxALIGN_LEFT | wxALL, 5);

    detailView->SetSizer(sizer);
}

void SettingsFrame::ShowDetailViewForAudioConferencing() {
    wxString category = "Audio Conferencing";
    int index = static_cast<int>(SidebarItem::AUDIO_CONFERENCING);

    ClearPanelContents(detailView);

    wxStaticText* text1 = new wxStaticText(detailView, wxID_ANY, wxString::Format("Detail View for %s", category));
    wxStaticText* text2 = new wxStaticText(detailView, wxID_ANY, wxString::Format("%s will be implemented soon, it has index %d", category, index));

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(text1, 0, wxALIGN_LEFT | wxALL, 5);
    sizer->Add(text2, 0, wxALIGN_LEFT | wxALL, 5);

    detailView->SetSizer(sizer);
}

void SettingsFrame::ShowDetailViewForVideo() {
    wxString category = "Video";
    int index = static_cast<int>(SidebarItem::VIDEO);

    ClearPanelContents(detailView);

    wxStaticText* text1 = new wxStaticText(detailView, wxID_ANY, wxString::Format("Detail View for %s", category));
    wxStaticText* text2 = new wxStaticText(detailView, wxID_ANY, wxString::Format("%s will be implemented soon, it has index %d", category, index));

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(text1, 0, wxALIGN_LEFT | wxALL, 5);
    sizer->Add(text2, 0, wxALIGN_LEFT | wxALL, 5);

    detailView->SetSizer(sizer);
}

void SettingsFrame::ShowDetailViewForCustomInvitation() {
    wxString category = "Custom Invitation";
    int index = static_cast<int>(SidebarItem::CUSTOM_INVITATION);

    ClearPanelContents(detailView);

    wxStaticText* text1 = new wxStaticText(detailView, wxID_ANY, wxString::Format("Detail View for %s", category));
    wxStaticText* text2 = new wxStaticText(detailView, wxID_ANY, wxString::Format("%s will be implemented soon, it has index %d", category, index));

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(text1, 0, wxALIGN_LEFT | wxALL, 5);
    sizer->Add(text2, 0, wxALIGN_LEFT | wxALL, 5);

    detailView->SetSizer(sizer);
}

void SettingsFrame::ShowDetailViewForAdvanced() {
    wxString category = "Advanced";
    int index = static_cast<int>(SidebarItem::ADVANCED);

    ClearPanelContents(detailView);

    wxStaticText* text1 = new wxStaticText(detailView, wxID_ANY, wxString::Format("Detail View for %s", category));
    wxStaticText* text2 = new wxStaticText(detailView, wxID_ANY, wxString::Format("%s will be implemented soon, it has index %d", category, index));

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(text1, 0, wxALIGN_LEFT | wxALL, 5);
    sizer->Add(text2, 0, wxALIGN_LEFT | wxALL, 5);

    detailView->SetSizer(sizer);
}
