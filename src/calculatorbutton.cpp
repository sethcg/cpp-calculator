#include <wx/wx.h>
#include <calculatorbutton.h>

CalculatorButton::CalculatorButton(wxWindow *parent, const wxWindowID &id, wxTextCtrl *currentTextControl, const wxString &label, const wxColor &backgroundColor, const wxColor &textColor)
    : wxButton(parent, id, label, wxDefaultPosition, wxDefaultSize, wxEXPAND)
{
    this->SetBackgroundColour(backgroundColor);
    this->SetForegroundColour(textColor);
    this->Bind(wxEVT_BUTTON, [this, currentTextControl](wxCommandEvent &event)
               { this->SetTextLabel(currentTextControl); });
}

void CalculatorButton::SetTextLabel(wxTextCtrl *currentTextControl)
{
    const auto buttonValue = this->GetLabelText();
    currentTextControl->SetValue(buttonValue);
}
