#pragma once
#include <wx/wx.h>

class CalculatorButton : public wxButton
{
public:
    CalculatorButton(wxWindow *parent, const wxWindowID &id, const wxString &label, const wxPoint &pos, const wxSize &size, const wxColor &color, const wxColor &textColor = *wxWHITE);

private:
    void OnClick(wxCommandEvent &event);
};
