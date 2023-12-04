#include "HomeWindow.hpp"

HomeWindow::HomeWindow(wxWindow* parent, NavigationBar* navBar, const wxPoint& pos, const wxSize& size)
    : wxPanel(parent, wxID_ANY, pos, size)
{
    this->NavBar = navBar;

    auto HomeSizer = new wxBoxSizer(wxVERTICAL);

    auto TitlePanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    auto TitleSizer = new wxBoxSizer(wxVERTICAL);

    auto AppTitle = new wxStaticText(TitlePanel,
        wxID_ANY,
        "Remote Desktop App",
        wxDefaultPosition,
        wxDefaultSize);
    AppTitle->SetFont(wxFontInfo(36).FaceName("Georgia").Bold());

    auto TitleScript = new wxStaticText(TitlePanel,
        wxID_ANY,
        "Exploring your connection",
        wxDefaultPosition,
        wxDefaultSize);
    TitleScript->SetFont(wxFontInfo(16).FaceName("Georgia"));

    auto HomeButton = new Button(TitlePanel,
        wxID_ANY,
        "Continue",
        wxDefaultPosition,
        wxSize(274, 44));
    HomeButton->Bind(wxEVT_LEFT_DOWN, &HomeWindow::OnClick, this);


    TitleSizer->Add(AppTitle, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, FromDIP(5));
    TitleSizer->Add(TitleScript, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, FromDIP(5));
    TitleSizer->Add(HomeButton, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, FromDIP(100));

    TitlePanel->SetSizerAndFit(TitleSizer);
    TitlePanel->Center();

    size_t CenterPanelX = (TitlePanel->GetSize().y - this->GetSize().y) / 2;
    HomeSizer->Add(TitlePanel, 1, wxALIGN_CENTER | wxTOP, FromDIP(CenterPanelX));

    this->SetSizer(HomeSizer);
    this->SetSize(wxSize(1344, 900));
    this->SetBackgroundColour(CONFIG_UI::SECONDARY_LIGHT_COLOR);
}

void HomeWindow::OnClick(wxMouseEvent& event)
{
    this->NavBar->OnNavigation(Window_ID::MENU_WINDOW);

    event.Skip();
}



HomeWindow::~HomeWindow()
{

}