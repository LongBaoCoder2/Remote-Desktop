#include "ClientWindow.hpp"
#include "../../../constant.hpp"
#include "../../InforNetwork.hpp"
#include "../../../../utils/FileNameGenerator/FileNameGenerator.hpp"


wxDEFINE_EVENT(wxEVT_CLIENT_CONNECTED, wxCommandEvent);
wxDEFINE_EVENT(wxEVT_CLIENT_DISCONNECTED, wxCommandEvent);

ClientWindow* ClientWindow::instance = nullptr;
bool ClientWindow::allowHook = false;

ClientWindow::ClientWindow()
    : wxFrame(nullptr, wxID_ANY, "Client Window"), net::IClient<RemoteMessage>()
{
    instance = this;
}

void ClientWindow::ConnectToHost(std::string& host)
{
    this->host = host;

    if (!ConnectToServer(host))
    {
        // LOG
        wxMessageBox(wxT("Failed to connect to Server."), wxT("Error"),
            wxICON_ERROR | wxOK);
    }
    // wxMessageBox(wxT("Connection successful."), wxT("Connected"), wxICON_INFORMATION | wxOK);

    Bind(wxEVT_CLOSE_WINDOW, &ClientWindow::OnClose, this);

    CapturePanel = new wxPanel(this, wxID_ANY, wxDefaultPosition,
        CONFIG_UI::CLIENT_WINDOW_SIZE, wxTE_PROCESS_ENTER | wxTE_PROCESS_TAB);
    CapturePanel->SetBackgroundColour(wxColor(38, 37, 54));

    // toolbar
    toolbar = CreateToolBar(wxTB_HORIZONTAL | wxTB_TEXT);
    // Thêm nút vào thanh công cụ với thuộc tính wxTB_RIGHT
    toolbar->AddTool(CONFIG_APP::ID_TOOL_DISCONNECT, "Disconnect",
        wxBitmap("assets/disconnect.png", wxBITMAP_TYPE_PNG),
        "End current session", wxITEM_NORMAL);

    toolbar->AddTool(CONFIG_APP::ID_TOOL_CAPTURE, "Save capture",
        wxBitmap("assets/capture.png", wxBITMAP_TYPE_PNG),
        "Save current screen capture", wxITEM_NORMAL);

    toolbar->AddTool(CONFIG_APP::ID_TOOL_KEYLOG, "Key logger",
        wxBitmap("assets/keylog.png", wxBITMAP_TYPE_PNG),
        "End current session", wxITEM_NORMAL);

    toolbar->EnableTool(CONFIG_APP::ID_TOOL_KEYLOG, false);

    toolbar->AddTool(CONFIG_APP::ID_TOOL_HOOK, "Hook",
        wxBitmap("assets/hook.png", wxBITMAP_TYPE_PNG),
        "Receive special keys", wxITEM_NORMAL);

    toolbar->AddTool(CONFIG_APP::ID_TOOL_UNHOOK, "Unhook",
        wxBitmap("assets/unhook.png", wxBITMAP_TYPE_PNG),
        "Stop receiving special keys", wxITEM_NORMAL);

    // Kết nối sự kiện nhấn nút trên thanh công cụ với hàm xử lý tương ứng
    this->Bind(wxEVT_TOOL, &ClientWindow::OnDisconnectClick, this,
        CONFIG_APP::ID_TOOL_DISCONNECT);

    this->Bind(wxEVT_TOOL, &ClientWindow::OnCaptureClick, this,
        CONFIG_APP::ID_TOOL_CAPTURE);

    this->Bind(wxEVT_TOOL, &ClientWindow::OnKeylogClick, this,
        CONFIG_APP::ID_TOOL_KEYLOG);

    this->Bind(wxEVT_TOOL, &ClientWindow::OnHookClick, this,
        CONFIG_APP::ID_TOOL_HOOK);

    this->Bind(wxEVT_TOOL, &ClientWindow::OnUnhookClick, this,
        CONFIG_APP::ID_TOOL_UNHOOK);

    toolbar->Realize();

    clientTextWindow = new ClientTextWindow();
    clientTextWindow->Show();

    keylogWindow = new KeylogWindow(this);

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
    this->Bind(wxEVT_TIMER, &ClientWindow::OnUpdateWindow, this,
        timer->GetId());
    timer->Start(DELAY_MS);

    // Ở đâu đó trong constructor hoặc khởi tạo timer
    secondTimer = new wxTimer(this, 4);
    this->Bind(wxEVT_TIMER, &ClientWindow::OnSecondTimer, this,
        secondTimer->GetId());
    secondTimer->Start(1000);  // Đặt timer chạy mỗi giây (1000ms)

    this->SetSizerAndFit(MainSizer);
    this->Center();

    // Binding mouse down events
    CapturePanel->Bind(wxEVT_LEFT_DOWN, &ClientWindow::OnMouseClick, this);
    CapturePanel->Bind(wxEVT_MIDDLE_DOWN, &ClientWindow::OnMouseClick, this);
    CapturePanel->Bind(wxEVT_RIGHT_DOWN, &ClientWindow::OnMouseClick, this);
    CapturePanel->Bind(wxEVT_AUX1_DOWN, &ClientWindow::OnMouseClick, this);
    CapturePanel->Bind(wxEVT_AUX2_DOWN, &ClientWindow::OnMouseClick, this);

    // Binding mouse up events
    CapturePanel->Bind(wxEVT_LEFT_UP, &ClientWindow::OnMouseUnClick, this);
    CapturePanel->Bind(wxEVT_MIDDLE_UP, &ClientWindow::OnMouseUnClick, this);
    CapturePanel->Bind(wxEVT_RIGHT_UP, &ClientWindow::OnMouseUnClick, this);
    CapturePanel->Bind(wxEVT_AUX1_UP, &ClientWindow::OnMouseUnClick, this);
    CapturePanel->Bind(wxEVT_AUX2_UP, &ClientWindow::OnMouseUnClick, this);

    // Binding double-click events
    CapturePanel->Bind(wxEVT_LEFT_DCLICK, &ClientWindow::OnMouseDoubleClick, this);
    CapturePanel->Bind(wxEVT_MIDDLE_DCLICK, &ClientWindow::OnMouseDoubleClick, this);
    CapturePanel->Bind(wxEVT_RIGHT_DCLICK, &ClientWindow::OnMouseDoubleClick, this);
    CapturePanel->Bind(wxEVT_AUX1_DCLICK, &ClientWindow::OnMouseDoubleClick, this);
    CapturePanel->Bind(wxEVT_AUX2_DCLICK, &ClientWindow::OnMouseDoubleClick, this);

    // Binding other mouse events
    // CapturePanel->Bind(wxEVT_MOTION, &ClientWindow::OnMouseMove, this); 
    // CapturePanel->Bind(wxEVT_ENTER_WINDOW, &ClientWindow::OnMouseEnter, this);
    // CapturePanel->Bind(wxEVT_LEAVE_WINDOW, &ClientWindow::OnMouseLeave, this);
    CapturePanel->Bind(wxEVT_MOUSEWHEEL, &ClientWindow::OnMouseWheel, this);


    CapturePanel->Bind(wxEVT_KEY_DOWN, &ClientWindow::OnKeyDown, this);
    CapturePanel->Bind(wxEVT_KEY_UP, &ClientWindow::OnKeyUp, this);

    SendMetadata();
    SetKeyboardHook();
}

void ClientWindow::SendMetadata() {
    net::message<RemoteMessage> msg;
    msg.header.id = RemoteMessage::MetaData;
    std::string IP_Addr = GetIPAddress();
    std::string Mac_Addr = GetMACAddress();
    std::string OS_ver = GetCurrentWindowName();
    msg << IP_Addr << Mac_Addr << OS_ver;
    Send(msg);
}

void ClientWindow::OnUpdateWindow(wxTimerEvent& event)
{
    if (IsConnected())
    {
        // size_t sizeOfQueue = m_connectionEvent->getMessageQueueIn().count();
        // clientTextWindow->DisplayMessage(wxString::Format(wxT("Queue size: %zu"), sizeOfQueue));
        while (!Incoming().empty())
        {
            auto msg = Incoming().pop_front().msg;
            switch (msg.header.id) {
            case RemoteMessage::SERVER_ACCEPT: {
                // isWaitingForConnection = false;
                // wxMessageBox(wxT("Connection successful."), wxT("Connected"), wxICON_INFORMATION | wxOK);
                std::string IP_Addr = GetIPAddress();
                std::string Mac_Addr = GetMACAddress();
                std::string OS_ver = GetCurrentWindowName();
                msg >> OS_ver >> Mac_Addr >> IP_Addr;
                clientTextWindow->DisplayMessage(wxString::Format(wxT("Server IP : %s \n Server Mac : %s \n Server Window Name : %s"), wxString(IP_Addr), wxString(Mac_Addr), wxString(OS_ver)));
                break;
            }
            case RemoteMessage::SERVER_DENY:
                // Disconnect();
                wxMessageBox(wxT("Disconnected from the server."),
                    wxT("Disconnected"),
                    wxICON_INFORMATION | wxOK);
                break;
            case RemoteMessage::SERVER_DISCONNECT:
                wxMessageBox("You have been disconnected from server", "Notification", wxOK | wxICON_INFORMATION, this);
                Close();
                break;

            case RemoteMessage::SERVER_UPDATE: {
                // isWaitingForConnection = false;

                // OnReceiveImage(msg);

                // Tạo một memory stream từ dữ liệu nhận được
                wxMemoryInputStream memStream(msg.body.data(),
                    msg.body.size());

                // Tải hình ảnh từ memory stream
                wxImage image;
                image.LoadFile(memStream, wxBITMAP_TYPE_PNG);

                // Tăng biến đếm
                imagesSentThisSecond++;

                // clientTextWindow->DisplayMessage(wxString::Format(wxT("Data received: %llu bytes.\n"), msg.body.size()));
                // wxMessageBox(wxT("Image convert successful."), wxT("Connected"), wxICON_INFORMATION | wxOK);
                // wxMessageBox(wxString::Format(wxT("Data received: %llu bytes.\n"), msg.body.size()), wxT("Message"), wxICON_INFORMATION | wxOK);


                // Chuyển đổi wxImage thành wxBitmap để hiển thị
                if (image.IsOk()) {
                    screenshot = wxBitmap(image);
                    // wxMessageBox(wxT("Image sent successful."),
                    // wxT("Connected"), wxICON_INFORMATION | wxOK);
                }
                else {
                    wxMessageBox(wxT("Failed to load the image."),
                        wxT("Error"), wxICON_ERROR | wxOK);
                }

                break;
            }

            case RemoteMessage::CaptureSend: {
                // Tạo một memory stream từ dữ liệu nhận được
                wxMemoryInputStream memStream(msg.body.data(),
                    msg.body.size());

                // Tải hình ảnh từ memory stream
                wxImage image;
                image.LoadFile(memStream, wxBITMAP_TYPE_PNG);
                // Lưu wxImage thành một tệp hình ảnh
                if (!wxDirExists("Screenshots")) {
                    wxMkdir("Screenshots");
                }
                image.SaveFile(CreateScreenshotFileName(), wxBITMAP_TYPE_PNG);
            }

            }
        }
    }

    // textCtrl->AppendText("Chua thay connection!\n");

    UpdatePanel();
    event.Skip();
}




void ClientWindow::UpdatePanel() {
    // clientDC.Clear();
    if (screenshot.IsOk()) {
        wxClientDC clientDC(CapturePanel);
        clientDC.DrawBitmap(screenshot, 0, 0, false);
    }
}

void ClientWindow::ClearPanel() {
    wxClientDC clientDC(CapturePanel);
    clientDC.Clear();
}

void ClientWindow::OnReceiveImage(net::message<RemoteMessage>& msg) {
    unsigned char* bitmapData =
        reinterpret_cast<unsigned char*>(msg.body.data());

    wxImage image(1280, 960, bitmapData, true);
    screenshot = wxBitmap(image);
}

// Khi timer đếm giây chạy
void ClientWindow::OnSecondTimer(wxTimerEvent& event) {
    // In thông tin thống kê và đặt biến đếm về 0
    // clientTextWindow->DisplayMessage(wxString::Format(wxT("Images received this second: %d\n"), imagesSentThisSecond));
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

void ClientWindow::OnMouseMove(wxMouseEvent& event) {
    net::message<RemoteMessage> m;
    m.header.id = RemoteMessage::MouseMove;
    m << event.GetX() << event.GetY();
    Send(m);
    event.Skip();
}

// void ClientWindow::OnMouseLeave(wxMouseEvent& event) {
//     net::message<RemoteMessage> m;
//     m.header.id = RemoteMessage::MouseLeave;
//     Send(m);
//     event.Skip();
// }

// void ClientWindow::OnMouseEnter(wxMouseEvent& event) {
//     net::message<RemoteMessage> m;
//     m.header.id = RemoteMessage::MouseEnter;
//     Send(m);
//     event.Skip();
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
    event.Skip();  // Để sự kiện được xử lý tiếp
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
    event.Skip();  // Để sự kiện được xử lý tiếp
}

void ClientWindow::OnKeyDown(wxKeyEvent& event) {
    if (checkValidKey(static_cast<uint32_t>(event.GetRawKeyCode())) == false) {
        return;
    }
    // Tạo message bàn phím
    net::message<RemoteMessage> m;
    m.header.id = RemoteMessage::KeyPress;
    m << static_cast<uint32_t>(event.GetRawKeyCode());  // true for key down

    // Gửi message
    Send(m);
    // event.Skip();
}

void ClientWindow::OnKeyUp(wxKeyEvent& event) {
    if (checkValidKey(static_cast<uint32_t>(event.GetRawKeyCode())) == false) {
        return;
    }
    // Tạo message bàn phím
    net::message<RemoteMessage> m;
    m.header.id = RemoteMessage::KeyRelease;
    m << static_cast<uint32_t>(event.GetRawKeyCode());  // false for key up

    // Gửi message
    Send(m);
    // event.Skip();
}

bool ClientWindow::checkValidKey(uint32_t keyCode) {
    if(keyCode == 91)
        return false;
    if(keyCode == 92)
        return false;
    if(keyCode == 18)
        return false;
    if(keyCode == 28)
        return false;
    return true;
}

LRESULT CALLBACK ClientWindow::KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0 && allowHook) {
        KBDLLHOOKSTRUCT* kbdStruct = reinterpret_cast<KBDLLHOOKSTRUCT*>(lParam);
        DWORD vkCode = kbdStruct->vkCode;

        net::message<RemoteMessage> m;
        if (vkCode == VK_LWIN || vkCode == VK_RWIN) {
            if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
                m.header.id = RemoteMessage::KeyPress;
            }
            else if (wParam == WM_KEYUP || wParam == WM_SYSKEYUP) {
                m.header.id = RemoteMessage::KeyRelease;
            }
            m << 91;
            instance->Send(m);
            return 1;
        }
        else if (vkCode == VK_LMENU || vkCode == VK_RMENU) { // Alt trái
            if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
                m.header.id = RemoteMessage::KeyPress;
            } else if (wParam == WM_KEYUP || wParam == WM_SYSKEYUP) {
                m.header.id = RemoteMessage::KeyRelease;
            }
            m << 18;
            instance->Send(m);
            return 1;
        } else if (vkCode == VK_ESCAPE) {
            if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
                m.header.id = RemoteMessage::KeyPress;
            } else if (wParam == WM_KEYUP || wParam == WM_SYSKEYUP) {
                m.header.id = RemoteMessage::KeyRelease;
            }
            m << 28;
            instance->Send(m);
            return 1;
        }
    }

    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

void ClientWindow::SetKeyboardHook() {
    keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);
}

void ClientWindow::RemoveKeyboardHook() {
    if (keyboardHook != NULL) {
        UnhookWindowsHookEx(keyboardHook);
        keyboardHook = NULL;
    }
}

void ClientWindow::OnDisconnectClick(wxCommandEvent& event) {
    wxMessageDialog dialog(this,
        "Are you sure you want to close the connection?",
        "Confirm", wxYES_NO | wxICON_QUESTION);

    int result = dialog.ShowModal();

    if (result == wxID_YES) {
        // net::IClient<RemoteMessage>::Disconnect();
        net::message<RemoteMessage> m;
        m.header.id = RemoteMessage::CLIENT_DISCONNECT;
        Send(m);
        Close();
        // Người dùng chọn Đồng ý
        // Thực hiện hành động khi đồng ý đóng kết nối
        // wxMessageBox("YES", "Confirmation", wxYES_NO | wxICON_QUESTION,
        // this);
    }
    else if (result == wxID_NO) {
        // Người dùng chọn Huỷ
        // Thực hiện hành động khi huỷ đóng kết nối hoặc không làm gì cả
    }
}

void ClientWindow::OnCaptureClick(wxCommandEvent& event) {
    net::message<RemoteMessage> m;
    m.header.id = RemoteMessage::CaptureRequest;
    // Gửi message
    Send(m);
}

void ClientWindow::OnKeylogClick(wxCommandEvent& event) {
    keylogWindow->Show();
}

void ClientWindow::OnHookClick(wxCommandEvent& event) {
    allowHook = true;
}

void ClientWindow::OnUnhookClick(wxCommandEvent& event) {
    allowHook = false;
}

void ClientWindow::OnClose(wxCloseEvent& event) {
    net::IClient<RemoteMessage>::Disconnect();
    if (clientTextWindow->IsBeingDeleted() == false) {
        clientTextWindow->Destroy();
    }
    // this->Destroy();
    event.Skip();
}

ClientWindow::~ClientWindow() {
    timer->Stop();
    secondTimer->Stop();
    ClearPanel();
    // clientTextWindow->Destroy();
    net::IClient<RemoteMessage>::Disconnect();
    RemoveKeyboardHook();
    instance = nullptr;
    allowHook = false;
}
