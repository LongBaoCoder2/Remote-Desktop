#include "HomeWindow.hpp"

HomeWindow::HomeWindow(wxWindow* parent, const wxPoint& pos, const wxSize& size)
    : wxPanel(parent, wxID_ANY, pos, size)
{
    auto HomeSizer = new wxBoxSizer(wxVERTICAL);

    auto TitlePanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    auto TitleSizer = new wxBoxSizer(wxVERTICAL);

    auto AppTitle = new wxStaticText(TitlePanel,
        wxID_ANY,
        "Remote Desktop App",
        wxDefaultPosition,
        wxDefaultSize,
        wxALIGN_CENTER);

    AppTitle->SetFont(wxFontInfo(24).FaceName("Georgia").Bold());
    AppTitle->SetBackgroundColour(wxColour(100, 100, 100));

    TitleSizer->Add(AppTitle, 1, wxALL | wxEXPAND, FromDIP(5));
    TitlePanel->SetSizerAndFit(TitleSizer);
    TitlePanel->Center();

    HomeSizer->Add(TitlePanel, 1, wxEXPAND | wxTOP, FromDIP(50));

    this->SetSizerAndFit(HomeSizer);
    // this->SetSize()
    this->SetBackgroundColour(CONFIG_UI::SECONDARY_LIGHT_COLOR);
}

HomeWindow::~HomeWindow()
{

}