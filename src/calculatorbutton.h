#pragma once
#include <wx/wx.h>

class CalculatorButton : public wxButton
{
public:
    CalculatorButton(wxWindow *parent, const wxWindowID &id, wxTextCtrl *currentTextControl, const wxString &label, const wxColor &backgroundColor, const wxColor &textColor = *wxWHITE);

private:
    void SetTextLabel(wxTextCtrl *currentTextControl);
};
