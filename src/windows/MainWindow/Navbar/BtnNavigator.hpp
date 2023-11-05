// #pragma once
// #pragma once

// #include "../../components/SelectablePanel.hpp"

// class BtnNavigator : public SelectablePane
// {
// public:
//     BtnNavigator(wxWindow *parent, wxWindowID id, const wxColor &paneColor, const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxDefaultSize);

//     wxColour color;

// private:
//     virtual void DrawContent(wxGraphicsContext *gc, const wxRect &rect, int roundness) const override;
// };

// BtnNavigator::BtnNavigator(wxWindow *parent, wxWindowID id, const wxColor &paneColor, const wxPoint &pos, const wxSize &size)
//     : SelectablePane(parent, id, pos, size), color(paneColor)
// {
// }

// void BtnNavigator::DrawContent(wxGraphicsContext *gc, const wxRect &rect, int roundness) const
// {
//     gc->SetPen(wxPen(color));
//     gc->SetBrush(wxBrush(color));

//     gc->DrawRoundedRectangle(rect.GetX(), rect.GetY(), rect.GetWidth(), rect.GetHeight(), roundness);
// };