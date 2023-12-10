#include "UserPanel.hpp"

UserPanel::UserPanel(wxWindow* parent,
    wxImage iconUser,
    std::string username)
    : wxPanel(parent), iconUser(iconUser), username(username)
{
    Bind(wxEVT_PAINT, &UserPanel::OnPaint, this, -1);

    auto* sizer = new wxBoxSizer(wxVERTICAL);
    if (iconUser.IsOk()) {
        auto UserPanelSize = CONFIG_UI::PRIMARY_USER_PANEL_SIZE;
        wxBitmap bitmap = iconUser.Rescale(UserPanelSize.x, UserPanelSize.y);

        auto iconPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, UserPanelSize);
        auto iconBitmap = new wxStaticBitmap(iconPanel, wxID_ANY, bitmap);
        auto text = new wxStaticText(this, wxID_ANY, username, wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
        auto button = new Button(this, wxID_ANY, "Connect", wxDefaultPosition, CONFIG_UI::PRIMARY_BUTTON_SIZE);

        sizer->Add(iconPanel, 0, wxALIGN_CENTER | wxALL, FromDIP(8));
        sizer->Add(text, 1, wxEXPAND | wxALL, FromDIP(8));
        sizer->Add(button, 0, wxALIGN_CENTER | wxALL, FromDIP(8));
    }


    SetSizerAndFit(sizer);
}

void UserPanel::OnPaint(wxPaintEvent& event) {
    wxPanel::OnPaint(event);
    wxPaintDC dc(this);
    wxGraphicsContext* gc = wxGraphicsContext::Create(dc);

    if (gc) {
        wxRect rect = GetClientRect();
        int radius = 5;

        gc->SetPen(*wxBLACK_PEN);
        gc->SetBrush(*wxTRANSPARENT_BRUSH);

        gc->DrawRoundedRectangle(rect.x, rect.y, rect.width - 5, rect.height - 5, radius);

        delete gc;
    }
}

UserPanel::~UserPanel() {
    // Add cleanup code here if necessary
}
