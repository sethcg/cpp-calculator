#pragma once
#include <wx/wx.h>

inline const int BUTTON_CONTAINER_ROWS = 5;
inline const int BUTTON_CONTAINER_COLS = 4;

const enum OperationType {
    NONE,
    MULTIPLY,
    DIVIDE,
    SUBTRACT,
    ADD
};

class ButtonGrid : public wxGridSizer
{
public:
    ButtonGrid(wxWindow *parent, wxTextCtrl *lastTextControl, wxTextCtrl *currentTextControl, OperationType *operationType);

private:
    void CreateButton(wxGridSizer *container, CalculatorButton *button);

    void HandleDigit(wxTextCtrl *currentTextControl, std::string buttonValue);
    void HandleDelete(wxTextCtrl *currentTextControl);
    void HandleClear(wxTextCtrl *lastTextControl, wxTextCtrl *currentTextControl, OperationType *operationType);
    void HandleAction(wxTextCtrl *lastTextControl, wxTextCtrl *currentTextControl, OperationType *operationType, OperationType type);
};