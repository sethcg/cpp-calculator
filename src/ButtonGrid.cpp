#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <wx/wx.h>
#include <colors/Colors.h>
#include <CalculatorButton.h>
#include <ButtonGrid.h>

ButtonGrid::ButtonGrid(wxWindow *parent, wxTextCtrl *textControl, OperationType *operationType) : wxGridSizer(BUTTON_CONTAINER_ROWS, BUTTON_CONTAINER_COLS, 0, 0)
{
    const int BUTTON_CONTAINER_MARGIN = parent->FromDIP(5);
    this->SetHGap(BUTTON_CONTAINER_MARGIN);
    this->SetVGap(BUTTON_CONTAINER_MARGIN);

    std::vector<CalculatorButton *>
        buttons({
            // AC, CLEAR (ALL)
            new CalculatorButton([operationType, textControl]() -> void
                                 {
                                    *operationType = OperationType::NONE;
                                    textControl->SetValue("0"); }, parent, textControl, BUTTON_STRING_ALL_CLEAR, COLOR_RED),
            // DEL, DELETE DIGIT
            new CalculatorButton([this, textControl]() -> void
                                 { ButtonGrid::DeleteDigit(textControl); }, parent, textControl, BUTTON_STRING_DELETE),
            // %, PERCENTAGE
            new CalculatorButton([]() -> void {}, parent, textControl, BUTTON_STRING_PERCENT),
            // MULTIPLY
            new CalculatorButton([operationType]() -> void
                                 { *operationType = OperationType::MULTIPLY; }, parent, textControl, BUTTON_STRING_MULTIPLY),
            // 7
            new CalculatorButton([this, textControl]() -> void
                                 { ButtonGrid::AppendDigit(textControl, BUTTON_STRING_SEVEN_DIGIT); }, parent, textControl, BUTTON_STRING_SEVEN_DIGIT),
            // 8
            new CalculatorButton([this, textControl]() -> void
                                 { ButtonGrid::AppendDigit(textControl, BUTTON_STRING_EIGHT_DIGIT); }, parent, textControl, BUTTON_STRING_EIGHT_DIGIT),
            // 9
            new CalculatorButton([this, textControl]() -> void
                                 { ButtonGrid::AppendDigit(textControl, BUTTON_STRING_NINE_DIGIT); }, parent, textControl, BUTTON_STRING_NINE_DIGIT),
            // DIVIDE
            new CalculatorButton([operationType]() -> void
                                 { *operationType = OperationType::DIVIDE; }, parent, textControl, BUTTON_STRING_DIVIDE),
            // 4
            new CalculatorButton([this, textControl]() -> void
                                 { ButtonGrid::AppendDigit(textControl, BUTTON_STRING_FOUR_DIGIT); }, parent, textControl, BUTTON_STRING_FOUR_DIGIT),
            // 5
            new CalculatorButton([this, textControl]() -> void
                                 { ButtonGrid::AppendDigit(textControl, BUTTON_STRING_FIVE_DIGIT); }, parent, textControl, BUTTON_STRING_FIVE_DIGIT),
            // 6
            new CalculatorButton([this, textControl]() -> void
                                 { ButtonGrid::AppendDigit(textControl, BUTTON_STRING_SIX_DIGIT); }, parent, textControl, BUTTON_STRING_SIX_DIGIT),
            // SUBTRACT
            new CalculatorButton([operationType]() -> void
                                 { *operationType = OperationType::SUBTRACT; }, parent, textControl, BUTTON_STRING_SUBTRACT),
            // 1
            new CalculatorButton([this, textControl]() -> void
                                 { ButtonGrid::AppendDigit(textControl, BUTTON_STRING_ONE_DIGIT); }, parent, textControl, BUTTON_STRING_ONE_DIGIT),
            // 2
            new CalculatorButton([this, textControl]() -> void
                                 { ButtonGrid::AppendDigit(textControl, BUTTON_STRING_TWO_DIGIT); }, parent, textControl, BUTTON_STRING_TWO_DIGIT),
            // 3
            new CalculatorButton([this, textControl]() -> void
                                 { ButtonGrid::AppendDigit(textControl, BUTTON_STRING_THREE_DIGIT); }, parent, textControl, BUTTON_STRING_THREE_DIGIT),
            // ADD
            new CalculatorButton([operationType, textControl]() -> void
                                 { *operationType = OperationType::ADD; }, parent, textControl, BUTTON_STRING_ADD),
            // NEGATE (POSITIVE/NEGATIVE)
            new CalculatorButton([this, textControl]() -> void {}, parent, textControl, BUTTON_STRING_NEGATE),
            // 0
            new CalculatorButton([this, textControl]() -> void
                                 { ButtonGrid::AppendDigit(textControl, BUTTON_STRING_ZERO_DIGIT); }, parent, textControl, BUTTON_STRING_ZERO_DIGIT),
            // DECIMAL
            new CalculatorButton([this, textControl]() -> void
                                 { ButtonGrid::AppendDigit(textControl, BUTTON_STRING_DECIMAL); }, parent, textControl, BUTTON_STRING_DECIMAL),
            // EQUAL
            new CalculatorButton([operationType, textControl]() -> void
                                 {
                                    *operationType = OperationType::NONE;
                                    const std::string stringValue = textControl->GetValue().wxString::ToStdString();
                                    const double currentValue = std::stod(stringValue); }, parent, textControl, BUTTON_STRING_EQUAL, COLOR_ORANGE, *wxBLACK),
        });

    // ADD BUTTONS TO CONTAINER
    for (CalculatorButton *button : buttons)
        this->CreateButton(this, button);
}

void ButtonGrid::CreateButton(wxGridSizer *container, CalculatorButton *button)
{
    container->Add(new wxSizerItem(button, 1, wxEXPAND, 5));
}

void ButtonGrid::AppendDigit(wxTextCtrl *textControl, std::string buttonValue)
{
    std::string currentValue = textControl->GetValue().wxString::ToStdString();
    if (currentValue.length() < 9)
    {
        // REMOVE THE DEFAULT "0" VALUE
        if (currentValue == "0")
            currentValue = "";

        const std::string textValue = currentValue.append(buttonValue);
        textControl->SetValue(textValue);
    }
}

void ButtonGrid::DeleteDigit(wxTextCtrl *textControl)
{
    std::string currentValue = textControl->GetValue().wxString::ToStdString();
    if (currentValue == "0")
        return;

    if (currentValue.length() == 1)
    {
        textControl->SetValue("0");
        return;
    }
    else
    {
        currentValue.erase(currentValue.size() - 1);
        textControl->SetValue(currentValue);
    }
}