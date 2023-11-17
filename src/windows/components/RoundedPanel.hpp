#pragma once

#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/dcbuffer.h>
#include <wx/stattext.h>
#include <wx/graphics.h>
#include <wx/wx.h>


#include <wx/wx.h>

class RoundedPanel : public wxPanel {
public:
    RoundedPanel(wxWindow* parent, const wxString& label)
        : wxPanel(parent, wxID_ANY), labelText(label) {
        SetBackgroundStyle(wxBG_STYLE_CUSTOM);
#if defined(__WXMSW__)
        int extendedStyle = GetWindowLong(GetHWND(), GWL_EXSTYLE);
        SetWindowLong(GetHWND(), GWL_EXSTYLE, extendedStyle | WS_EX_TRANSPARENT);
#endif

        Bind(wxEVT_PAINT, &RoundedPanel::OnPaint, this);
    }

private:
    wxString labelText;

    void OnPaint(wxPaintEvent& event) {
        wxAutoBufferedPaintDC dc(this);
        Render(dc);
    }

    void Render(wxDC& dc) {
        int width = 500, height = 500;
        GetSize(&width, &height);

        // Vẽ hình chữ nhật bo tròn
        dc.SetBrush(*wxWHITE_BRUSH);
        dc.SetPen(wxPen(wxColour(0, 0, 0), 1));
        dc.DrawRoundedRectangle(0, 0, width, height, 10);

        // Hiển thị nội dung
        dc.SetTextForeground(*wxBLACK);
        dc.DrawText(labelText, 10, 10);
    }
};
