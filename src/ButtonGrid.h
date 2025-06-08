#pragma once
#include <wx/wx.h>

inline const int BUTTON_CONTAINER_ROWS = 5;
inline const int BUTTON_CONTAINER_COLS = 4;

const enum OperationType {
    NONE,
    MULTIPLY,
    DIVIDE,
    SUBTRACT,
    ADD,
    PERCENT,
    EQUAL
};

class ButtonGrid : public wxGridSizer
{
public:
    ButtonGrid(wxWindow *parent, wxTextCtrl *lastTextControl, wxTextCtrl *currentTextControl);

private:
    OperationType operationType = OperationType::NONE;

    void CreateButton(wxGridSizer *container, CalculatorButton *button);

    void HandleDigit(wxTextCtrl *currentTextControl, std::string buttonValue);
    void HandleDecimal(wxTextCtrl *currentTextControl, std::string buttonValue);
    void HandleDelete(wxTextCtrl *currentTextControl);
    void HandleClear(wxTextCtrl *lastTextControl, wxTextCtrl *currentTextControl);
    void HandleAction(wxTextCtrl *lastTextControl, wxTextCtrl *currentTextControl, OperationType type);
    void HandleEvaluate(wxTextCtrl *lastTextControl, wxTextCtrl *currentTextControl);
};