#pragma once

#include <wx/wx.h>
#include <wx/graphics.h>
#include <wx/bitmap.h>

class Button : public wxWindow
{
public:
    Button(wxWindow* parent, wxWindowID id, std::string m_text, const wxPoint& pos, const wxSize& size, long style = 0, const wxString& name = wxPanelNameStr)
        : wxWindow(), text(m_text)
    {
        SetBackgroundStyle(wxBG_STYLE_TRANSPARENT);
        wxWindow::Create(parent, id, pos, size, style, name);

#if defined(__WXMSW__)
        int extendedStyle = GetWindowLong(GetHWND(), GWL_EXSTYLE);
        SetWindowLong(GetHWND(), GWL_EXSTYLE, extendedStyle | WS_EX_TRANSPARENT);
#endif

        this->Bind(wxEVT_PAINT, &Button::OnPaint, this);

        this->Bind(wxEVT_ENTER_WINDOW, &Button::OnMouseEnter, this);
        this->Bind(wxEVT_LEAVE_WINDOW, &Button::OnMouseLeave, this);
    }

    void OnPaint(wxPaintEvent& event)
    {
        wxPaintDC dc(this);
        wxColor color{ "#202124" };
        std::unique_ptr<wxGraphicsContext> gc{ wxGraphicsContext::Create(dc) };

        if (gc)
        {
            if (this->isHovered || this->isSelected)
            {
                this->DrawOnContext(*gc, this->hoveredColor);
            }
            else
            {
                this->DrawOnContext(*gc, this->backgroundColor);
            }
        }

        event.Skip();
    }

    void OnMouseEnter(wxMouseEvent& event)
    {
        isHovered = true;
        Refresh();
        event.Skip();
    }

    void OnMouseLeave(wxMouseEvent& event)
    {
        isHovered = false;
        Refresh();
        event.Skip();
    }

    void DrawOnContext(wxGraphicsContext& gc, const wxColour& color)
    {

        gc.SetBrush(wxBrush(color));

        auto buttonRect = this->GetClientRect();

        gc.DrawRoundedRectangle(buttonRect.GetLeft(),
            buttonRect.GetTop(),
            buttonRect.GetWidth(),
            buttonRect.GetHeight(),
            buttonRect.GetHeight() / 8);

        wxFont font(wxFontInfo({ 0, int(1.0 * buttonRect.GetHeight() / 2.8) }).FaceName("Georgia").Bold());

        gc.SetFont(font, *wxWHITE);

        double textWidth, textHeight;
        gc.GetTextExtent(this->text, &textWidth, &textHeight);

        gc.Clip(buttonRect.GetLeft(),
            buttonRect.GetTop(),
            buttonRect.GetWidth(),
            buttonRect.GetHeight());

        gc.DrawText(this->text,
            (buttonRect.GetWidth() - textWidth) / 2.0,
            (buttonRect.GetHeight() - textHeight) / 2.0);
    }

    void SetSelected(bool isSelected)
    {
        this->isSelected = isSelected;
    }

    std::string text;

private:
    bool isHovered = false;
    bool isSelected = false;
    wxColour backgroundColor = wxColour(17, 25, 38);
    wxColour hoveredColor = wxColour(52, 58, 70);
};