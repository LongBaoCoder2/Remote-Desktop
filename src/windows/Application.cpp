#include "Application.h"
#include "constant.hpp"


bool Application::OnInit()
{
    wxInitAllImageHandlers();
    SetAppDisplayName("Remote Desktop Control"); // Đặt tên cho ứng dụng của bạn
    SetVendorName("HCMUS-BCD"); // Tên công ty của bạn (tùy chọn)
    // Tạo và thiết lập biểu tượng cho toàn bộ ứng dụng
    icon = wxIcon("assets/app_icon1.png", wxBITMAP_TYPE_PNG);
    LoginWindow = new LoginFrame(wxT("Login"), wxDefaultPosition, CONFIG_UI::NORMAL_WINDOW);
    LoginWindow->SetIcon(icon);
    LoginWindow->Show(true);

    Connect(wxID_ANY, UserLoginEvent, wxCommandEventHandler(Application::OnUserLogin));
    Connect(wxID_ANY, AdminLoginEvent, wxCommandEventHandler(Application::OnAdminLogin));
    return true;
}

void Application::NavigateToMainWindow(std::unique_ptr<IModel> Model)
{
    if (LoginWindow) {
        LoginWindow->Destroy();
    }

    MainWindow = new MainFrame(wxT("Remote Desktop"), wxDefaultPosition, CONFIG_UI::NORMAL_WINDOW, std::move(Model));
    MainWindow->SetIcon(icon);
    MainWindow->Show(true);
}

void Application::OnUserLogin(wxCommandEvent& event) {
    std::string ID = LoginWindow->GetID();
    std::unique_ptr<IModel> User = factory.Create(Owned::USER, ID);

    NavigateToMainWindow(std::move(User));
}

void Application::OnAdminLogin(wxCommandEvent& event) {
    std::unique_ptr<IModel> Admin = factory.Create(Owned::ADMIN, "ADMIN");

    NavigateToMainWindow(std::move(Admin));
}
