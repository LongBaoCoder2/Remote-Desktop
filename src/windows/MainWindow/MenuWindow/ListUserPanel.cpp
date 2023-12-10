#include "ListUserPanel.hpp"

ListUserPanel::ListUserPanel(wxWindow* parent,
    Admin* admin,
    const wxPoint& pos,
    const wxSize& size)
    : wxPanel(parent, wxID_ANY, pos, size)
{
    this->pAdmin = admin;

    // Dump data
    this->pAdmin->AppendUser(std::make_shared<User>("Nguyet Quynh", "127.0.0.1"));
    this->pAdmin->AppendUser(std::make_shared<User>("User 1", "197.168.0.2"));


    userIcon.LoadFile("assets/user_2.png", wxBITMAP_TYPE_PNG);
    if (!userIcon.IsOk()) {
        wxMessageBox("[Error Image]: Can't load user icon.", "Error Image");
    }

    auto MainSizer = new wxBoxSizer(wxVERTICAL);

    auto HeaderPanel = new wxPanel(this, wxID_ANY);
    auto HeaderSizer = new wxBoxSizer(wxHORIZONTAL);

    auto ListUserText = new wxStaticText(HeaderPanel, wxID_ANY, "List User");
    ListUserText->SetFont(wxFontInfo(14).FaceName("Georgia").Weight(500));

    auto AddUserButtonPanel = new wxPanel(HeaderPanel);
    auto AddUserButtonSizer = new wxBoxSizer(wxHORIZONTAL);
    auto AddUserButton = new Button(AddUserButtonPanel, wxID_ANY, "Add new user", wxDefaultPosition, wxSize(120, 40));
    auto ConnectionButton = new Button(AddUserButtonPanel, wxID_ANY, "Connection to user", wxDefaultPosition, wxSize(140, 40));

    AddUserButtonSizer->AddStretchSpacer(); // Add a spacer before the buttons
    AddUserButtonSizer->Add(AddUserButton, 0, wxRIGHT, FromDIP(20));
    AddUserButtonSizer->Add(ConnectionButton, 0);
    AddUserButtonPanel->SetSizerAndFit(AddUserButtonSizer);

    HeaderSizer->Add(ListUserText, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxLEFT, FromDIP(15)); // Align ListUserText to the left
    HeaderSizer->AddStretchSpacer(1); // Add a flexible spacer to push AddUserButtonPanel to the right
    HeaderSizer->Add(AddUserButtonPanel, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, FromDIP(15)); // Align AddUserButtonPanel to the right

    HeaderPanel->SetSizerAndFit(HeaderSizer);

    auto splitPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(1200, 2));
    splitPanel->SetBackgroundColour(*wxBLACK);

    auto _UserPanels = new wxPanel(this);
    const auto margin = FromDIP(15);
    auto Sizer = new wxGridBagSizer(margin, margin);
    // Simulated user data
    int row = 0;
    int col = 0;
    const int maxUsersPerRow = 4;
    if (pAdmin) {
        size_t noUser = pAdmin->GetUserCount();

        for (size_t i = 0; i < noUser; i++) {
            auto user = pAdmin->GetUserByIndex(i);

            auto userPanel = new UserPanel(_UserPanels, userIcon, user->GetID(), user->GetIPAddress());

            Sizer->Add(userPanel, wxGBPosition(row, col), { 1, 1 }, wxEXPAND);

            col++;
            if (col >= maxUsersPerRow) {
                col = 0;
                row++;
            }
        }
    }

    _UserPanels->SetSizerAndFit(Sizer);

    MainSizer->Add(HeaderPanel, 0, wxEXPAND | wxBOTTOM, FromDIP(10));
    MainSizer->Add(splitPanel, 0, wxEXPAND | wxBOTTOM, FromDIP(20));
    MainSizer->Add(_UserPanels, 1, wxALIGN_CENTER | wxALL, FromDIP(10));

    this->SetSizerAndFit(MainSizer);
}


ListUserPanel::~ListUserPanel()
{

}