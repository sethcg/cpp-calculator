#include <wx/wx.h>
#include <calculatorbutton.h>

CalculatorButton::CalculatorButton(std::function<void()> onClick, wxWindow *parent, wxTextCtrl *textControl, const wxWindowID &id, const wxString &label, const wxColor &backgroundColor, const wxColor &textColor)
    : wxButton(parent, id, label, wxDefaultPosition, wxDefaultSize, wxEXPAND)
{
    this->SetBackgroundColour(backgroundColor);
    this->SetForegroundColour(textColor);
    this->Bind(wxEVT_BUTTON, [onClick](wxCommandEvent &event) -> void
               { onClick(); }, wxID_ANY);
}
