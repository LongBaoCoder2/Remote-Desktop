#include "MenuWindow.hpp"
#include <wx/gbsizer.h>

MenuWindow::MenuWindow(wxWindow* parent, std::shared_ptr<IModel>& _model, const wxPoint& pos, const wxSize& size)
    : wxPanel(parent, wxID_ANY, pos, size)
{
    this->model = _model;

    if (this->model->GetTypeOwned() == Owned::ADMIN) {
        CreateAdminPanel();

        this->Bind(ConnectToUserEvent, &MenuWindow::OnConnectToServer, this);
    }
    else {
        CreateUserPanel();
    }
}

void MenuWindow::CreateUserPanel()
{
    this->SetBackgroundColour(CONFIG_UI::PRIMARY_LIGHT_COLOR);

    auto MainSizer = new wxBoxSizer(wxVERTICAL);

    auto TitlePanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    auto TitleSizer = new wxBoxSizer(wxVERTICAL);

    auto AppTitle = new wxStaticText(TitlePanel,
        wxID_ANY,
        "Let's connect to client",
        wxDefaultPosition,
        wxDefaultSize);
    AppTitle->SetFont(wxFontInfo(36).FaceName("Georgia").Bold());

    auto ButtonPanel = new wxPanel(TitlePanel, wxID_ANY);
    auto ButtonSizer = new wxBoxSizer(wxHORIZONTAL);
    auto ServerConnectButton = new Button(ButtonPanel,
        wxID_ANY,
        "Starting Listening",
        wxDefaultPosition,
        wxSize(274, 44));
    ServerConnectButton->Bind(wxEVT_LEFT_DOWN, &MenuWindow::OnStartListening, this);

    ButtonSizer->Add(ServerConnectButton, 0, wxALL, FromDIP(15));
    ButtonPanel->SetSizer(ButtonSizer);

    TitleSizer->Add(AppTitle, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, FromDIP(5));
    TitleSizer->Add(ButtonPanel, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, FromDIP(10));

    TitlePanel->SetSizerAndFit(TitleSizer);
    TitlePanel->Center();

    auto SizeOfWindow = CONFIG_UI::NORMAL_WINDOW;
    SizeOfWindow.x -= CONFIG_UI::NAVIGATION_SIZE.x;

    size_t CenterPanelX = (SizeOfWindow.y - TitlePanel->GetSize().y) / 3;
    MainSizer->Add(TitlePanel, 1, wxALIGN_CENTER | wxTOP, FromDIP(CenterPanelX));


    this->SetSizer(MainSizer);
    this->SetSize(SizeOfWindow);
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

    auto UserList = new ListUserPanel(this, static_cast<Admin*>(model.get()));

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

void MenuWindow::OnStartListening(wxMouseEvent& event)
{
    // serverWindow = std::make_unique<ServerWindow>(CONFIG_APP::PORT);
    auto button = dynamic_cast<Button*>(event.GetEventObject());
    if (button && !button->GetDisable()) {
        if (serverWindow) delete serverWindow;

        serverWindow = new ServerWindow();
        serverWindow->Show();
    }
}

void MenuWindow::ConnectToServer(std::string& host)
{
    auto button = dynamic_cast<Button*>(event.GetEventObject());
    if (button && !button->GetDisable()) {
        if (clientWindow) delete clientWindow;

        clientWindow = new ClientWindow();
        clientWindow->ConnectToHost(host);
        clientWindow->Show();
    }

}

void MenuWindow::OnConnectToServer(wxCommandEvent& event)
{
    std::string* IpAddress = (std::string*)event.GetClientData();
    if (IpAddress) {
        ConnectToServer(*IpAddress);
        delete IpAddress;
    }
}


void MenuWindow::OnDisableButton(wxCommandEvent& event)
{
    auto button = dynamic_cast<Button*>(event.GetEventObject());
    if (button) {
        button->SetDisable(true);
    }
}

void MenuWindow::OnEnableButton(wxCommandEvent& event)
{
    auto button = dynamic_cast<Button*>(event.GetEventObject());
    if (button) {
        button->SetDisable(false);
    }
}


MenuWindow::~MenuWindow()
{

}