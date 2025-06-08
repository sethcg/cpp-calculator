#include <wx/wx.h>
#include <colors/Colors.h>
#include <CalculatorButton.h>

CalculatorButton::CalculatorButton(std::function<void()> onClick, wxWindow *parent, wxTextCtrl *textControl, const wxString &label, const wxColor &backgroundColor, const wxColor &textColor)
    : wxButton(parent, wxID_ANY, label, wxDefaultPosition, wxDefaultSize, wxEXPAND)
{
    this->SetBackgroundColour(backgroundColor);
    this->SetForegroundColour(textColor);
    this->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_SEMIBOLD));
    this->Bind(wxEVT_BUTTON, [onClick](wxCommandEvent &event) -> void
               { onClick(); }, wxID_ANY);
}
