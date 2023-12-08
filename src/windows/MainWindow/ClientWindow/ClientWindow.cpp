#include "ClientWindow.hpp"
#include "../../constant.hpp"

ClientWindow::ClientWindow(const std::string& host, uint16_t port)
    : wxFrame(nullptr, wxID_ANY, "Client Window"), net::IClient<RemoteMessage>()
{

    if (!ConnectToServer(host, port))
    {
        // LOG
        wxMessageBox(wxT("Failed to connect to Server."), wxT("Error"), wxICON_ERROR | wxOK);
    }
    // wxMessageBox(wxT("Connection successful."), wxT("Connected"), wxICON_INFORMATION | wxOK);
    // MouseKeyPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, CONFIG_UI::CLIENT_WINDOW_SIZE);
    // MouseKeyPanel->SetBackgroundStyle(wxBG_STYLE_TRANSPARENT);

    CapturePanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, CONFIG_UI::CLIENT_WINDOW_SIZE);
    CapturePanel->SetBackgroundColour(wxColor(38, 37, 54));

    clientTextWindow = new ClientTextWindow();
    clientTextWindow->Show();

    // Tạo một wxTextCtrl để hiển thị văn bản
   
    textCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize,
        wxTE_MULTILINE | wxTE_READONLY | wxHSCROLL);


    // Tạo một wxBoxSizer với hướng ngang
    wxBoxSizer* MainSizer = new wxBoxSizer(wxHORIZONTAL);

    // Thêm CapturePanel vào MainSizer với tỷ lệ 1
    MainSizer->Add(CapturePanel, 1, wxEXPAND, 0);

    // Thêm textCtrl vào MainSizer với tỷ lệ 1
    // MainSizer->Add(textCtrl, 1, wxEXPAND, 0);

    timer = new wxTimer(this, 1);
    this->Bind(wxEVT_TIMER, &ClientWindow::OnUpdateWindow, this, timer->GetId());
    timer->Start(DELAY_MS);

    // Ở đâu đó trong constructor hoặc khởi tạo timer
    secondTimer = new wxTimer(this, 4);
    this->Bind(wxEVT_TIMER, &ClientWindow::OnSecondTimer, this, secondTimer->GetId());
    secondTimer->Start(1000);  // Đặt timer chạy mỗi giây (1000ms)

    this->SetSizerAndFit(MainSizer);
    this->Center();
        
    // Inside ClientWindow constructor or appropriate setup function

    // Sử dụng overlay để vẽ lớp nhận tín hiệu chuột trên cùng
    // overlay = new wxOverlay();
    // overlay->Reset();

    // Binding mouse down events
    CapturePanel->Bind(wxEVT_LEFT_DOWN, &ClientWindow::OnMouseClick, this);
    CapturePanel->Bind(wxEVT_MIDDLE_DOWN, &ClientWindow::OnMouseClick, this);
    CapturePanel->Bind(wxEVT_RIGHT_DOWN, &ClientWindow::OnMouseClick, this);
    // CapturePanel->Bind(wxEVT_AUX1_DOWN, &ClientWindow::OnMouseClick, this);
    // CapturePanel->Bind(wxEVT_AUX2_DOWN, &ClientWindow::OnMouseClick, this);

    // Binding mouse up events
    CapturePanel->Bind(wxEVT_LEFT_UP, &ClientWindow::OnMouseUnClick, this);
    CapturePanel->Bind(wxEVT_MIDDLE_UP, &ClientWindow::OnMouseUnClick, this);
    CapturePanel->Bind(wxEVT_RIGHT_UP, &ClientWindow::OnMouseUnClick, this);
    // CapturePanel->Bind(wxEVT_AUX1_UP, &ClientWindow::OnMouseUnClick, this);
    // CapturePanel->Bind(wxEVT_AUX2_UP, &ClientWindow::OnMouseUnClick, this);

    // Binding double-click events
    CapturePanel->Bind(wxEVT_LEFT_DCLICK, &ClientWindow::OnMouseDoubleClick, this);
    CapturePanel->Bind(wxEVT_MIDDLE_DCLICK, &ClientWindow::OnMouseDoubleClick, this);
    CapturePanel->Bind(wxEVT_RIGHT_DCLICK, &ClientWindow::OnMouseDoubleClick, this);
    // CapturePanel->Bind(wxEVT_AUX1_DCLICK, &ClientWindow::OnMouseDoubleClick, this);
    // CapturePanel->Bind(wxEVT_AUX2_DCLICK, &ClientWindow::OnMouseDoubleClick, this);

    // Binding other mouse events
    // CapturePanel->Bind(wxEVT_MOTION, &ClientWindow::OnMouseMove, this);
    // CapturePanel->Bind(wxEVT_ENTER_WINDOW, &ClientWindow::OnMouseEnter, this);
    // CapturePanel->Bind(wxEVT_LEAVE_WINDOW, &ClientWindow::OnMouseLeave, this);
    CapturePanel->Bind(wxEVT_MOUSEWHEEL, &ClientWindow::OnMouseWheel, this);


    CapturePanel->Bind(wxEVT_KEY_DOWN, &ClientWindow::OnKeyDown, this);
    CapturePanel->Bind(wxEVT_KEY_UP, &ClientWindow::OnKeyUp, this);

}

void ClientWindow::OnUpdateWindow(wxTimerEvent& event)
{

    if (IsConnected())
    {
        while (!Incoming().empty())
        {
            auto msg = Incoming().pop_front().msg;
            switch (msg.header.id)
            {
            case RemoteMessage::SERVER_ACCEPT:
                isWaitingForConnection = false;
                wxMessageBox(wxT("Connection successful."), wxT("Connected"), wxICON_INFORMATION | wxOK);
                break;
            case RemoteMessage::SERVER_DENY:
                // Disconnect();
                wxMessageBox(wxT("Disconnected from the server."), wxT("Disconnected"), wxICON_INFORMATION | wxOK);
                break;

            case RemoteMessage::SERVER_UPDATE:
                isWaitingForConnection = false;

                // OnReceiveImage(msg);

                // Tạo một memory stream từ dữ liệu nhận được
                wxMemoryInputStream memStream(msg.body.data(), msg.body.size());

                // Tải hình ảnh từ memory stream
                wxImage image;
                image.LoadFile(memStream, wxBITMAP_TYPE_JPEG);

                // Tăng biến đếm
                imagesSentThisSecond++;

                clientTextWindow->DisplayMessage(wxString::Format(wxT("Data received: %llu bytes.\n"), msg.body.size()));
                // wxMessageBox(wxT("Image convert successful."), wxT("Connected"), wxICON_INFORMATION | wxOK);
                // wxMessageBox(wxString::Format(wxT("Data received: %llu bytes.\n"), msg.body.size()), wxT("Message"), wxICON_INFORMATION | wxOK);


                // Chuyển đổi wxImage thành wxBitmap để hiển thị
                if (image.IsOk())
                {
                    screenshot = wxBitmap(image);
                    // wxMessageBox(wxT("Image sent successful."), wxT("Connected"), wxICON_INFORMATION | wxOK);
                }
                else
                {
                    wxMessageBox(wxT("Failed to load the image."), wxT("Error"), wxICON_ERROR | wxOK);
                }

                break;
            }
        }
    }

    // textCtrl->AppendText("Chua thay connection!\n");

    if (isWaitingForConnection)
    {
        // ClearPanel();
        return;
    }

    UpdatePanel();
    event.Skip();
}

void ClientWindow::UpdatePanel()
{
    // clientDC.Clear();
    if (screenshot.IsOk()) {
        wxClientDC clientDC(CapturePanel);
        clientDC.DrawBitmap(screenshot, 0, 0, false);
    }
}

void ClientWindow::ClearPanel()
{
    wxClientDC clientDC(CapturePanel);
    clientDC.Clear();
}

void ClientWindow::OnReceiveImage(net::message<RemoteMessage>& msg)
{
    unsigned char* bitmapData = reinterpret_cast<unsigned char*>(msg.body.data());

    wxImage image(1280, 960, bitmapData, true);
    screenshot = wxBitmap(image);
}


// Khi timer đếm giây chạy
void ClientWindow::OnSecondTimer(wxTimerEvent& event)
{
    // In thông tin thống kê và đặt biến đếm về 0
    clientTextWindow->DisplayMessage(wxString::Format(wxT("Images received this second: %d\n"), imagesSentThisSecond));
    imagesSentThisSecond = 0;
    event.Skip();
}

void ClientWindow::OnMouseDoubleClick(wxMouseEvent& event) {
    net::message<RemoteMessage> m;
    m.header.id = RemoteMessage::DoubleClick;
    m << event.GetX() << event.GetY() << event.GetButton();
    Send(m);
    event.Skip();

}

// void ClientWindow::OnMouseMove(wxMouseEvent& event) {
//     net::message<RemoteMessage> m;
//     m.header.id = RemoteMessage::MouseMove;
//     m << event.GetX() << event.GetY();
//     Send(m);
//     // event.Skip();
// }

// void ClientWindow::OnMouseLeave(wxMouseEvent& event) {
//     net::message<RemoteMessage> m;
//     m.header.id = RemoteMessage::MouseLeave;
//     Send(m);
//     // event.Skip();
// }

// void ClientWindow::OnMouseEnter(wxMouseEvent& event) {
//     net::message<RemoteMessage> m;
//     m.header.id = RemoteMessage::MouseEnter;
//     Send(m);
//     // event.Skip();
// }

void ClientWindow::OnMouseWheel(wxMouseEvent& event) {
    net::message<RemoteMessage> m;
    m.header.id = RemoteMessage::MouseWheel;
    m << event.GetX() << event.GetY() << event.GetWheelRotation();
    Send(m);
    event.Skip();
}


void ClientWindow::OnMouseClick(wxMouseEvent& event) {
    // Tạo message chuột
    SetFocus();
    net::message<RemoteMessage> m;
    m.header.id = RemoteMessage::MouseClick;
    // int32_t button = MapMouseButton(event.GetButton());
    int button = event.GetButton();
    m << event.GetX() << event.GetY() << button;
    
    // Gửi message
    Send(m);
    event.Skip(); // Để sự kiện được xử lý tiếp
}

void ClientWindow::OnMouseUnClick(wxMouseEvent& event) {
    // Tạo message chuột
    net::message<RemoteMessage> m;
    m.header.id = RemoteMessage::MouseUnClick;
    // int32_t button = MapMouseButton(event.GetButton());
    int button = event.GetButton();
    m << event.GetX() << event.GetY() << button;
    
    // Gửi message
    Send(m);
    event.Skip(); // Để sự kiện được xử lý tiếp
}

void ClientWindow::OnKeyDown(wxKeyEvent& event) {
    // Tạo message bàn phím
    
    // clientTextWindow->DisplayMessage(wxString::Format(wxT("Got it\n")));
    net::message<RemoteMessage> m;
    m.header.id = RemoteMessage::KeyPress;
    m << static_cast<uint32_t>(event.GetRawKeyCode()); // true for key down
    
    // Gửi message
    Send(m);
    // event.Skip();
}

void ClientWindow::OnKeyUp(wxKeyEvent& event) {
    // Tạo message bàn phím
    net::message<RemoteMessage> m;
    m.header.id = RemoteMessage::KeyRelease;
    m << static_cast<uint32_t>(event.GetRawKeyCode()); // false for key up
    
    // Gửi message
    Send(m);
    // event.Skip();
}

ClientWindow::~ClientWindow()
{
    timer->Stop();
    ClearPanel();
}
