#include "FileNameGenerator.hpp"

wxString CreateScreenshotFileName() {
    wxDateTime now = wxDateTime::Now();
    
    // Lấy ngày tháng năm và giờ phút giây hiện tại
    wxString date = now.Format("%d-%m-%Y");
    wxString time = now.Format("%H-%M-%S");
    
    // Tạo tên file sử dụng ngày và giờ hiện tại
    wxString fileName = wxString::Format("assets\\Screenshots\\%s %s screenshot.png", date, time);
    
    return fileName;
}
