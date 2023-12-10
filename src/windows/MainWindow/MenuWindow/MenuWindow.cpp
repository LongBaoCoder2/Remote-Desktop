#include "MenuWindow.hpp"
#include <wx/gbsizer.h>

MenuWindow::MenuWindow(wxWindow* parent, std::shared_ptr<IModel>& _model, const wxPoint& pos, const wxSize& size)
    : wxPanel(parent, wxID_ANY, pos, size)
{
    this->model = _model;

    if (this->model->GetTypeOwned() == Owned::ADMIN) {
        CreateAdminPanel();
    }
    else {
        CreateUserPanel();
    }
}

void MenuWindow::CreateUserPanel()
{
    auto MainSizer = new wxBoxSizer(wxVERTICAL);

    auto TitlePanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    auto TitleSizer = new wxBoxSizer(wxVERTICAL);

    auto AppTitle = new wxStaticText(TitlePanel,
        wxID_ANY,
        "Remote Desktop App",
        wxDefaultPosition,
        wxDefaultSize);
    AppTitle->SetFont(wxFontInfo(36).FaceName("Georgia").Bold());

    IPInput = new wxTextCtrl(TitlePanel, wxID_ANY, wxT("127.0.0.1"), wxDefaultPosition, wxSize(370, 40));

    auto ButtonPanel = new wxPanel(TitlePanel, wxID_ANY);
    auto ButtonSizer = new wxBoxSizer(wxHORIZONTAL);
    auto ServerConnectButton = new Button(ButtonPanel,
        wxID_ANY,
        "Server",
        wxDefaultPosition,
        wxSize(274, 44));
    // ServerConnectButton->Bind(wxEVT_LEFT_DOWN, &ManageWindow::OnServerConnectButton, this);

    auto ClientConnectButton = new Button(ButtonPanel,
        wxID_ANY,
        "Client",
        wxDefaultPosition,
        wxSize(274, 44));
    // ClientConnectButton->Bind(wxEVT_LEFT_DOWN, &ManageWindow::OnClientConnectButton, this);

    ButtonSizer->Add(ServerConnectButton, 0, wxALL, FromDIP(15));
    ButtonSizer->Add(ClientConnectButton, 0, wxALL, FromDIP(15));
    ButtonPanel->SetSizer(ButtonSizer);

    TitleSizer->Add(AppTitle, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, FromDIP(5));
    TitleSizer->Add(IPInput, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, FromDIP(5));
    TitleSizer->Add(ButtonPanel, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, FromDIP(10));

    TitlePanel->SetSizerAndFit(TitleSizer);
    TitlePanel->Center();

    // size_t CenterPanelX = (TitlePanel->GetSize().y - this->GetSize().y) / 2;
    MainSizer->Add(TitlePanel, 1, wxALIGN_CENTER | wxTOP, FromDIP(10));

    auto SizeOfWindow = CONFIG_UI::NORMAL_WINDOW;
    SizeOfWindow.x -= CONFIG_UI::NAVIGATION_SIZE.x;

    this->SetSizer(MainSizer);
    this->SetSize(SizeOfWindow);
    this->SetBackgroundColour(CONFIG_UI::PRIMARY_LIGHT_COLOR);
}

void MenuWindow::CreateAdminPanel()
{
    auto MenuSizer = new wxBoxSizer(wxVERTICAL);

    auto TitlePanel = new wxPanel(this);
    TitlePanel->SetBackgroundColour(CONFIG_UI::PRIMARY_LIGHT_COLOR);

    auto TitleApp = new wxStaticText(TitlePanel, wxID_ANY, "Remote Desktop");
    TitleApp->SetFont(wxFontInfo(16).FaceName("Georgia").Bold());

    auto TitleSizer = new wxBoxSizer(wxHORIZONTAL);

    TitleSizer->Add(TitleApp, 0, wxALL, FromDIP(17));
    TitlePanel->SetSizer(TitleSizer);

    auto UserList = new ListUserPanel(this);


    MenuSizer->Add(TitlePanel, 0, wxEXPAND | wxBOTTOM, FromDIP(20));
    MenuSizer->Add(UserList, 1, wxALIGN_CENTER | wxALL, FromDIP(30));

    auto SizeOfWindow = CONFIG_UI::NORMAL_WINDOW;
    SizeOfWindow.x -= CONFIG_UI::NAVIGATION_SIZE.x;

    this->SetSizer(MenuSizer);
    this->SetSize(SizeOfWindow);
    this->SetBackgroundColour(CONFIG_UI::SECONDARY_LIGHT_COLOR);

    Layout();
    Refresh();
}

MenuWindow::~MenuWindow()
{

}