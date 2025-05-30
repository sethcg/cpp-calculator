#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <wx/wx.h>
#include <colors/colors.h>
#include <calculatorbutton.h>
#include <buttoncontainer.h>

ButtonContainer::ButtonContainer(wxWindow *parent, wxTextCtrl *textControl) : wxGridSizer(BUTTON_CONTAINER_ROWS, BUTTON_CONTAINER_COLS, 0, 0)
{
    const int BUTTON_CONTAINER_MARGIN = parent->FromDIP(5);
    this->SetHGap(BUTTON_CONTAINER_MARGIN);
    this->SetVGap(BUTTON_CONTAINER_MARGIN);
    std::vector<CalculatorButton *>
        buttons({
            // %, PERCENTAGE
            new CalculatorButton([textControl]() -> void
                                 { textControl->SetValue(BUTTON_STRING_PERCENT); }, parent, textControl, BUTTON_STRING_PERCENT, DARK_GRAY),
            // CE, CLEAR ENTRY
            new CalculatorButton([textControl]() -> void
                                 { textControl->SetValue(BUTTON_STRING_CLEAR_ENTRY); }, parent, textControl, BUTTON_STRING_CLEAR_ENTRY, DARK_GRAY),
            // C, CLEAR (ALL)
            new CalculatorButton([textControl]() -> void
                                 { textControl->SetValue(BUTTON_STRING_CLEAR_ALL); }, parent, textControl, BUTTON_STRING_CLEAR_ALL, DARK_GRAY),
            // DEL, DELETE DIGIT
            new CalculatorButton([textControl]() -> void
                                 { textControl->SetValue(BUTTON_STRING_DELETE); }, parent, textControl, BUTTON_STRING_DELETE, DARK_GRAY),
            // FRACTION
            new CalculatorButton([textControl]() -> void
                                 { textControl->SetValue(BUTTON_STRING_FRACTION); }, parent, textControl, BUTTON_STRING_FRACTION, DARK_GRAY),
            // SQUARE
            new CalculatorButton([textControl]() -> void
                                 { textControl->SetValue(BUTTON_STRING_SQUARE); }, parent, textControl, BUTTON_STRING_SQUARE, DARK_GRAY),
            // SQUARE ROOT
            new CalculatorButton([textControl]() -> void
                                 { textControl->SetValue(BUTTON_STRING_SQUARE_ROOT); }, parent, textControl, BUTTON_STRING_SQUARE_ROOT, DARK_GRAY),
            // DIVIDE
            new CalculatorButton([textControl]() -> void
                                 { textControl->SetValue(BUTTON_STRING_DIVIDE); }, parent, textControl, BUTTON_STRING_DIVIDE, DARK_GRAY),
            // 7
            new CalculatorButton([textControl]() -> void
                                 { textControl->SetValue(BUTTON_STRING_SEVEN_DIGIT); }, parent, textControl, BUTTON_STRING_SEVEN_DIGIT, GRAY),
            // 8
            new CalculatorButton([textControl]() -> void
                                 { textControl->SetValue(BUTTON_STRING_EIGHT_DIGIT); }, parent, textControl, BUTTON_STRING_EIGHT_DIGIT, GRAY),
            // 9
            new CalculatorButton([textControl]() -> void
                                 { textControl->SetValue(BUTTON_STRING_NINE_DIGIT); }, parent, textControl, BUTTON_STRING_NINE_DIGIT, GRAY),
            // MULTIPLY
            new CalculatorButton([textControl]() -> void
                                 { textControl->SetValue(BUTTON_STRING_MULTIPLY); }, parent, textControl, BUTTON_STRING_MULTIPLY, DARK_GRAY),
            // 4
            new CalculatorButton([textControl]() -> void
                                 { textControl->SetValue(BUTTON_STRING_FOUR_DIGIT); }, parent, textControl, BUTTON_STRING_FOUR_DIGIT, GRAY),
            // 5
            new CalculatorButton([textControl]() -> void
                                 { textControl->SetValue(BUTTON_STRING_FIVE_DIGIT); }, parent, textControl, BUTTON_STRING_FIVE_DIGIT, GRAY),
            // 6
            new CalculatorButton([textControl]() -> void
                                 { textControl->SetValue(BUTTON_STRING_SIX_DIGIT); }, parent, textControl, BUTTON_STRING_SIX_DIGIT, GRAY),
            // SUBTRACT
            new CalculatorButton([textControl]() -> void
                                 { textControl->SetValue(BUTTON_STRING_SUBTRACT); }, parent, textControl, BUTTON_STRING_SUBTRACT, DARK_GRAY),
            // 1
            new CalculatorButton([textControl]() -> void
                                 { textControl->SetValue(BUTTON_STRING_ONE_DIGIT); }, parent, textControl, BUTTON_STRING_ONE_DIGIT, GRAY),
            // 2
            new CalculatorButton([textControl]() -> void
                                 { textControl->SetValue(BUTTON_STRING_TWO_DIGIT); }, parent, textControl, BUTTON_STRING_TWO_DIGIT, GRAY),
            // 3
            new CalculatorButton([textControl]() -> void
                                 { textControl->SetValue(BUTTON_STRING_THREE_DIGIT); }, parent, textControl, BUTTON_STRING_THREE_DIGIT, GRAY),
            // ADD
            new CalculatorButton([textControl]() -> void
                                 { textControl->SetValue(BUTTON_STRING_ADD); }, parent, textControl, BUTTON_STRING_ADD, DARK_GRAY),
            // NEGATE (POSITIVE/NEGATIVE)
            new CalculatorButton([textControl]() -> void
                                 { textControl->SetValue(BUTTON_STRING_NEGATE); }, parent, textControl, BUTTON_STRING_NEGATE, GRAY),
            // 0
            new CalculatorButton([textControl]() -> void
                                 { textControl->SetValue(BUTTON_STRING_ZERO_DIGIT); }, parent, textControl, BUTTON_STRING_ZERO_DIGIT, GRAY),
            // DECIMAL
            new CalculatorButton([textControl]() -> void
                                 { textControl->SetValue(BUTTON_STRING_DECIMAL); }, parent, textControl, BUTTON_STRING_DECIMAL, GRAY),
            // EQUAL
            new CalculatorButton([textControl]() -> void
                                 { textControl->SetValue(BUTTON_STRING_EQUAL); }, parent, textControl, BUTTON_STRING_EQUAL, LIGHT_BLUE, *wxBLACK),
        });

    // ADD BUTTONS TO CONTAINER
    for (CalculatorButton *button : buttons)
        this->CreateButton(this, button);
}

void ButtonContainer::CreateButton(wxGridSizer *container, CalculatorButton *button)
{
    container->Add(new wxSizerItem(button, 1, wxEXPAND, 5));
}