#include "UserPanel.hpp"

UserPanel::UserPanel(wxWindow* parent,
    wxImage iconUser,
    std::string username)
    : wxPanel(parent), iconUser(iconUser), username(username)
{
    Bind(wxEVT_PAINT, &UserPanel::OnPaint, this, -1);

    auto* sizer = new wxBoxSizer(wxVERTICAL);
    if (iconUser.IsOk()) {
        wxBitmap bitmap = iconUser.Rescale(60, 60);


        auto iconPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(60, 60));
        auto iconBitmap = new wxStaticBitmap(iconPanel, wxID_ANY, bitmap);
        auto text = new wxStaticText(this, wxID_ANY, username, wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
        auto button = new Button(this, wxID_ANY, "Connect", wxDefaultPosition, wxSize(210, 40));

        sizer->Add(iconPanel, 0, wxALIGN_CENTER | wxALL, FromDIP(15));
        sizer->Add(text, 1, wxEXPAND | wxALL, FromDIP(8));
        sizer->Add(button, 0, wxALIGN_CENTER | wxALL, FromDIP(15));
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
