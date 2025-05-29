#pragma once
#include <wx/wx.h>

inline const int BUTTON_CONTAINER_ROWS = 6;
inline const int BUTTON_CONTAINER_COLS = 4;

class ButtonContainer : public wxGridSizer
{
public:
    ButtonContainer(wxWindow *parent, wxTextCtrl *textControl);

private:
    void CreateButton(wxGridSizer *container, CalculatorButton *button);
};