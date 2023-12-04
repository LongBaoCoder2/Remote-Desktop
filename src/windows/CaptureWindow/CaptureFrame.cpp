#include "CaptureFrame.h"
#include "../../utils/FileNameGenerator/FileNameGenerator.hpp"
#include "../constant.hpp"

CaptureFrame::CaptureFrame(wxWindow* parent, const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(parent, wxID_ANY, title, pos, size)
{
    // Tạo một wxPanel để hiển thị hình ảnh chụp màn hình
    CapturePanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(1366, 768));
    CapturePanel->SetBackgroundColour(wxColor(38, 37, 54));
    CapturePanel->Bind(wxEVT_PAINT, &CaptureFrame::OnPaint, CapturePanel);
    
    clientDC = new wxClientDC(CapturePanel);
    // paintDC = new wxPaintDC(CapturePanel);
    // bufferedDC = new wxBufferedDC(paintDC);

    CaptureFrameLogger = new BasicTextFrame("Capture Frame Logger", wxDefaultPosition, CONFIG_UI::SMALL_WINDOW);
    CaptureFrameLogger->Show();

    // Tạo một wxPanel để chứa các nút điều khiển
    ButtonPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    ButtonPanel->SetBackgroundColour(wxColor(52, 51, 62));

    // Tạo một wxBoxSizer chứa CapturePanel và ButtonPanel
    wxBoxSizer* MainSizer = new wxBoxSizer(wxVERTICAL);
    MainSizer->Add(CapturePanel, 1, wxEXPAND, 0);
    MainSizer->Add(ButtonPanel, 0, wxEXPAND, 0);

    // Tạo nút "Start Capture" và "Stop Capture"
    startCaptureBtn = new wxButton(ButtonPanel, wxID_ANY, "Start Capture");
    stopCaptureBtn = new wxButton(ButtonPanel, wxID_ANY, "Stop Capture");
    saveCaptureBtn = new wxButton(ButtonPanel, wxID_ANY, "Save Capture");

    // Liên kết sự kiện nhấn nút với các hàm xử lý tương ứng
    this->Bind(wxEVT_BUTTON, &CaptureFrame::OnStartPress, this, startCaptureBtn->GetId());
    this->Bind(wxEVT_BUTTON, &CaptureFrame::OnStopPress, this, stopCaptureBtn->GetId());
    this->Bind(wxEVT_BUTTON, &CaptureFrame::onSavePress, this, saveCaptureBtn->GetId());

    // Tạo một wxBoxSizer chứa nút "Start Capture" và "Stop Capture" va "Save Capture"
    wxBoxSizer* ButtonSizer = new wxBoxSizer(wxHORIZONTAL);
    ButtonSizer->Add(startCaptureBtn, 0, wxALIGN_CENTER | wxALL, FromDIP(10));
    ButtonSizer->Add(stopCaptureBtn, 0, wxALIGN_CENTER | wxALL, FromDIP(10));
    ButtonSizer->Add(saveCaptureBtn, 0, wxALIGN_CENTER | wxALL, FromDIP(10));
    ButtonPanel->SetSizer(ButtonSizer);

    // Tạo một wxTimer để chụp màn hình theo khoảng thời gian định sẵn
    timer = new wxTimer(this, 5);
    this->Bind(wxEVT_TIMER, &CaptureFrame::OnCaptureScreen, this);

    // Ở đâu đó trong constructor hoặc khởi tạo timer
    secondTimer = new wxTimer(this, 6);
    this->Bind(wxEVT_TIMER, &CaptureFrame::OnSecondTimer, this, secondTimer->GetId());
    secondTimer->Start(1000);  // Đặt timer chạy mỗi giây (1000ms)

    // Đặt layout sử dụng MainSizer và căn giữa cửa sổ
    this->SetSizerAndFit(MainSizer);
    this->Center();
}

void CaptureFrame::OnStartPress(wxCommandEvent& e)
{
    CAPTURING = true;
    timer->Start(DELAY_MS);
}

void CaptureFrame::OnStopPress(wxCommandEvent& e)
{
    CAPTURING = false;
    timer->Stop();
    wxClientDC clientDC(CapturePanel);
    clientDC.Clear();
}

void CaptureFrame::onSavePress(wxCommandEvent& e) {
    takeScreenshot();
    // Chuyển đổi wxBitmap thành wxImage
    wxImage image = screenshot.ConvertToImage();

    // Lưu wxImage thành một tệp hình ảnh
    image.SaveFile(CreateScreenshotFileName(), wxBITMAP_TYPE_PNG);
}

void CaptureFrame::OnCaptureScreen(wxTimerEvent& e)
{
    if (CAPTURING)
    {
        takeScreenshot(CapturePanel->GetSize().GetWidth(), CapturePanel->GetSize().GetHeight());

        // Thiết lập wxBufferedDC để vẽ lên CapturePanel
        // bufferedDC.SetTarget(CapturePanel);

        // CapturePanel->Refresh();

        // Update Screen
        // wxClientDC clientDC(CapturePanel);
        // clientDC.Clear();
        clientDC->DrawBitmap(screenshot, 0, 0, false);
        ++imagesDisplayedThisSecond;
    }
}

void CaptureFrame::takeScreenshot(int imgWidth, int imgHeight) {
    // Capture Screen
    // wxRect frameRect = CapturePanel->GetRect();
    // wxRect frameRect = wxRect(wxGetClientDisplayRect());

    // đây là cái thằng lưu giữ tấm chụp màn hình
    // wxGetDisplaySize() giúp lấy kích cỡ toàn màn hình
    screenshot.Create(wxGetDisplaySize());
    // wxBitmap screenshot(frameRect.GetSize());


    // Lấy kích thước toàn bộ màn hình
    int screenWidth = wxSystemSettings::GetMetric(wxSYS_SCREEN_X);
    int screenHeight = wxSystemSettings::GetMetric(wxSYS_SCREEN_Y);

    // Tính toán tỷ lệ scale
    double scaleX = static_cast<double>(imgWidth) / screenWidth;
    double scaleY = static_cast<double>(imgHeight) / screenHeight;

    // biến này đóng vai trò buffer trung gian để thao tác trên screenshot
    memDC.SelectObject(screenshot);

    // Thực hiện phép chuyển đổi để vẽ toàn bộ nội dung màn hình
    memDC.SetUserScale(scaleX, scaleY);
    // đẩy dữ liệu từ màn hình vô biến screenshot
    memDC.Blit(0, 0, screenWidth, screenHeight, &screenDC, 0, 0);
    // bỏ screenshot ra khỏi memDC để lát dùng để vẽ lên
    memDC.SelectObject(wxNullBitmap);
}

// Khi timer đếm giây chạy
void CaptureFrame::OnSecondTimer(wxTimerEvent& e)
{
    // In thông tin thống kê và đặt biến đếm về 0
    CaptureFrameLogger->DisplayMessage(wxT("Capture Frame"), wxString::Format(wxT("Images displayed this second: %d\n"), imagesDisplayedThisSecond));
    imagesDisplayedThisSecond = 0;
}

// void CaptureFrame::MyBufferedPanel::OnPaint(wxPaintEvent& event) {
//     // Vẽ hình ảnh lên bằng bufferedDC
//     wxBufferedPaintDC bufferedDC(this);
//     bufferedDC.Clear();
//     bufferedDC.DrawBitmap(screenshot, 0, 0, false);
// }

// CaptureFrame::MyBufferedPanel::MyBufferedPanel(
//     wxWindow* parent, 
//     wxWindowID id, 
//     const wxPoint& pos, 
//     const wxSize& size
// )
// : wxPanel(parent, id, pos, size)
// {
//     Bind(wxEVT_PAINT, &MyBufferedPanel::OnPaint, this);
// }