#include <wx/wx.h>
#include <calculatorbutton.h>

CalculatorButton::CalculatorButton(wxWindow *parent, const wxWindowID &id, const wxString &label, const wxPoint &pos, const wxSize &size, const wxColor &color, const wxColor &textColor)
    : wxButton(parent, id, label, pos, size, wxEXPAND)
{
    this->SetBackgroundColour(color);
    this->SetForegroundColour(textColor);
}