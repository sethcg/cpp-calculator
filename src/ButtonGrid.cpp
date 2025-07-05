#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <format>
#include <wx/wx.h>
#include <ctype.h>
#include <constants/Colors.hpp>
#include <constants/Buttons.hpp>
#include <CalculatorButton.hpp>
#include <ButtonGrid.hpp>

ButtonGrid::ButtonGrid(wxWindow *parent, wxTextCtrl *lastTextControl, wxTextCtrl *currentTextControl)
    : wxGridSizer(BUTTON_CONTAINER_ROWS, BUTTON_CONTAINER_COLS, 0, 0)
{
    const int BUTTON_CONTAINER_MARGIN = parent->FromDIP(8);
    this->SetHGap(BUTTON_CONTAINER_MARGIN);
    this->SetVGap(BUTTON_CONTAINER_MARGIN);

    std::vector<CalculatorButton *>
        buttons({
            // AC, CLEAR (ALL)
            new CalculatorButton([this, lastTextControl, currentTextControl]() -> void
                                 { ButtonGrid::HandleClear(lastTextControl, currentTextControl); }, parent, currentTextControl, BUTTON_STRING_ALL_CLEAR, COLOR_RED),
            // DEL, DELETE DIGIT
            new CalculatorButton([this, currentTextControl]() -> void
                                 { ButtonGrid::HandleDelete(currentTextControl); }, parent, currentTextControl, BUTTON_STRING_DELETE),
            // %, PERCENTAGE
            new CalculatorButton([this, lastTextControl, currentTextControl]() -> void
                                 { ButtonGrid::HandleAction(lastTextControl, currentTextControl, OperationType::PERCENT); }, parent, currentTextControl, BUTTON_STRING_PERCENT),
            // MULTIPLY
            new CalculatorButton([this, lastTextControl, currentTextControl]() -> void
                                 { ButtonGrid::HandleAction(lastTextControl, currentTextControl, OperationType::MULTIPLY); }, parent, currentTextControl, BUTTON_STRING_MULTIPLY),
            // 7
            new CalculatorButton([this, currentTextControl]() -> void
                                 { ButtonGrid::HandleDigit(currentTextControl, BUTTON_STRING_SEVEN_DIGIT); }, parent, currentTextControl, BUTTON_STRING_SEVEN_DIGIT),
            // 8
            new CalculatorButton([this, currentTextControl]() -> void
                                 { ButtonGrid::HandleDigit(currentTextControl, BUTTON_STRING_EIGHT_DIGIT); }, parent, currentTextControl, BUTTON_STRING_EIGHT_DIGIT),
            // 9
            new CalculatorButton([this, currentTextControl]() -> void
                                 { ButtonGrid::HandleDigit(currentTextControl, BUTTON_STRING_NINE_DIGIT); }, parent, currentTextControl, BUTTON_STRING_NINE_DIGIT),
            // DIVIDE
            new CalculatorButton([this, lastTextControl, currentTextControl]() -> void
                                 { ButtonGrid::HandleAction(lastTextControl, currentTextControl, OperationType::DIVIDE); }, parent, currentTextControl, BUTTON_STRING_DIVIDE),
            // 4
            new CalculatorButton([this, currentTextControl]() -> void
                                 { ButtonGrid::HandleDigit(currentTextControl, BUTTON_STRING_FOUR_DIGIT); }, parent, currentTextControl, BUTTON_STRING_FOUR_DIGIT),
            // 5
            new CalculatorButton([this, currentTextControl]() -> void
                                 { ButtonGrid::HandleDigit(currentTextControl, BUTTON_STRING_FIVE_DIGIT); }, parent, currentTextControl, BUTTON_STRING_FIVE_DIGIT),
            // 6
            new CalculatorButton([this, currentTextControl]() -> void
                                 { ButtonGrid::HandleDigit(currentTextControl, BUTTON_STRING_SIX_DIGIT); }, parent, currentTextControl, BUTTON_STRING_SIX_DIGIT),
            // SUBTRACT
            new CalculatorButton([this, lastTextControl, currentTextControl]() -> void
                                 { ButtonGrid::HandleAction(lastTextControl, currentTextControl, OperationType::SUBTRACT); }, parent, currentTextControl, BUTTON_STRING_SUBTRACT),
            // 1
            new CalculatorButton([this, currentTextControl]() -> void
                                 { ButtonGrid::HandleDigit(currentTextControl, BUTTON_STRING_ONE_DIGIT); }, parent, currentTextControl, BUTTON_STRING_ONE_DIGIT),
            // 2
            new CalculatorButton([this, currentTextControl]() -> void
                                 { ButtonGrid::HandleDigit(currentTextControl, BUTTON_STRING_TWO_DIGIT); }, parent, currentTextControl, BUTTON_STRING_TWO_DIGIT),
            // 3
            new CalculatorButton([this, currentTextControl]() -> void
                                 { ButtonGrid::HandleDigit(currentTextControl, BUTTON_STRING_THREE_DIGIT); }, parent, currentTextControl, BUTTON_STRING_THREE_DIGIT),
            // ADD
            new CalculatorButton([this, lastTextControl, currentTextControl]() -> void
                                 { ButtonGrid::HandleAction(lastTextControl, currentTextControl, OperationType::ADD); }, parent, currentTextControl, BUTTON_STRING_ADD),
            // NEGATE (POSITIVE/NEGATIVE)
            new CalculatorButton([this, currentTextControl]() -> void
                                 { ButtonGrid::HandleNegate(currentTextControl); }, parent, currentTextControl, BUTTON_STRING_NEGATE),
            // 0
            new CalculatorButton([this, currentTextControl]() -> void
                                 { ButtonGrid::HandleDigit(currentTextControl, BUTTON_STRING_ZERO_DIGIT); }, parent, currentTextControl, BUTTON_STRING_ZERO_DIGIT),
            // DECIMAL
            new CalculatorButton([this, currentTextControl]() -> void
                                 { ButtonGrid::HandleDecimal(currentTextControl); }, parent, currentTextControl, BUTTON_STRING_DECIMAL),
            // EQUAL
            new CalculatorButton([this, lastTextControl, currentTextControl]() -> void
                                 { ButtonGrid::HandleEvaluate(lastTextControl, currentTextControl); }, parent, currentTextControl, BUTTON_STRING_EQUAL, COLOR_ORANGE, *wxBLACK),
        });

    // ADD BUTTONS TO CONTAINER
    for (CalculatorButton *button : buttons)
        this->CreateButton(this, button);
}

void ButtonGrid::CreateButton(wxGridSizer *container, CalculatorButton *button)
{
    container->Add(new wxSizerItem(button, 1, wxEXPAND, 5));
}

void ButtonGrid::HandleDigit(wxTextCtrl *currentTextControl, std::string buttonValue)
{
    std::string currentValue = currentTextControl->GetValue().wxString::ToStdString();
    if (currentValue.length() < 9)
    {
        // REMOVE THE DEFAULT "0" VALUE OR "Error" MESSAGE
        if (currentValue == "0" || currentValue == "Error")
            currentValue = "";

        const std::string textValue = currentValue.append(buttonValue);
        currentTextControl->SetValue(textValue);
    }
}

void ButtonGrid::HandleDecimal(wxTextCtrl *currentTextControl)
{
    std::string currentValue = currentTextControl->GetValue().wxString::ToStdString();
    if (currentValue.length() < 9 && currentValue.length() >= 1 && !(currentValue == "0" || currentValue == "Error"))
    {
        if (currentValue.find('.') == std::string::npos)
        {
            const std::string textValue = currentValue.insert(currentValue.size(), 1, '.');
            currentTextControl->SetValue(textValue);
        }
    }
}

void ButtonGrid::HandleNegate(wxTextCtrl *currentTextControl)
{
    std::string currentValue = currentTextControl->GetValue().wxString::ToStdString();
    if (currentValue.length() < 9 && currentValue.length() >= 1 && !(currentValue == "0" || currentValue == "Error"))
    {
        if (ButtonGrid::isNegative && currentValue[0] == '-')
        {
            ButtonGrid::isNegative = false;
            const std::string textValue = currentValue.erase(0, 1);
            currentTextControl->SetValue(textValue);
        }
        else if (currentValue.find('-') == std::string::npos)
        {
            ButtonGrid::isNegative = true;
            const std::string textValue = currentValue.insert(0, 1, '-');
            currentTextControl->SetValue(textValue);
        }
    }
}

void ButtonGrid::HandleDelete(wxTextCtrl *currentTextControl)
{
    std::string currentValue = currentTextControl->GetValue().wxString::ToStdString();
    if (currentValue == "0")
        return;

    if (currentValue.length() == 1)
    {
        currentTextControl->SetValue("0");
        return;
    }
    else
    {
        currentValue.erase(currentValue.size() - 1);
        currentTextControl->SetValue(currentValue);
    }
}

void ButtonGrid::HandleClear(wxTextCtrl *lastTextControl, wxTextCtrl *currentTextControl)
{
    operationType = OperationType::NONE;
    lastTextControl->SetValue(wxEmptyString);
    currentTextControl->SetValue("0");
}

void ButtonGrid::HandleAction(wxTextCtrl *lastTextControl, wxTextCtrl *currentTextControl, OperationType type)
{
    if (operationType == OperationType::EQUAL)
        lastTextControl->SetValue(wxEmptyString);

    if (lastTextControl->GetValue().length() > 0)
        return;

    std::string currentValue = currentTextControl->GetValue().wxString::ToStdString();

    // REMOVE UNNECESSARY DECIMAL
    if (currentValue.back() == '.')
        currentValue = currentValue.substr(0, currentValue.size() - 1);

    double doubleResult;
    double currentValueDouble = std::stod(currentValue);
    std::string stringResult = std::format("{:g}", currentValueDouble);
    switch (type)
    {
    case OperationType::ADD:
        operationType = OperationType::ADD;
        stringResult.push_back(' ');
        stringResult.push_back(BUTTON_STRING_ADD[0]);
        lastTextControl->SetValue(stringResult);
        currentTextControl->SetValue("0");
        break;
    case OperationType::SUBTRACT:
        operationType = OperationType::SUBTRACT;
        stringResult.push_back(' ');
        stringResult.push_back(BUTTON_STRING_SUBTRACT[0]);
        lastTextControl->SetValue(stringResult);
        currentTextControl->SetValue("0");
        break;
    case OperationType::MULTIPLY:
        operationType = OperationType::MULTIPLY;
        stringResult.push_back(' ');
        stringResult.push_back(BUTTON_STRING_MULTIPLY[0]);
        lastTextControl->SetValue(stringResult);
        currentTextControl->SetValue("0");
        break;
    case OperationType::DIVIDE:
        operationType = OperationType::DIVIDE;
        stringResult.push_back(' ');
        stringResult.push_back(BUTTON_STRING_DIVIDE[0]);
        lastTextControl->SetValue(stringResult);
        currentTextControl->SetValue("0");
        break;
    case OperationType::PERCENT:
        operationType = OperationType::EQUAL;
        currentValueDouble = std::stod(currentValue);
        doubleResult = currentValueDouble / 100;
        stringResult = std::format("{:g}", doubleResult);
        lastTextControl->SetValue(stringResult);
        currentTextControl->SetValue(stringResult);
        break;
    default:
        return;
    }
}

void ButtonGrid::HandleEvaluate(wxTextCtrl *lastTextControl, wxTextCtrl *currentTextControl)
{
    if (lastTextControl->GetValue().length() <= 0)
        return;

    try
    {
        std::string currentValue = currentTextControl->GetValue().wxString::ToStdString();
        std::string lastValue = lastTextControl->GetValue().wxString::ToStdString();

        // REMOVE UNNECESSARY DECIMAL
        if (currentValue.back() == '.')
            currentValue = currentValue.substr(0, currentValue.size() - 1);

        // SET OPERATION HISTORY
        std::string stringOperation = lastValue;
        stringOperation.push_back(' ');
        stringOperation.append(currentValue);
        stringOperation.push_back(' ');
        stringOperation.push_back(BUTTON_STRING_EQUAL[0]);
        lastTextControl->SetValue(stringOperation);

        // REMOVE NON-NUMERIC CHARACTERS FROM STRING
        std::string temp = currentValue;
        currentValue = "";
        for (char &character : temp)
        {
            std::string allowed = "0123456789.-";
            if (allowed.find(character) != std::string::npos)
                currentValue.push_back(character);
        }

        double result = 0;
        const double currentValueDouble = std::stod(currentValue);
        const double lastValueDouble = std::stod(lastValue);

        std::string equalResult;
        switch (ButtonGrid::operationType)
        {
        case OperationType::ADD:
            result = lastValueDouble + currentValueDouble;
            break;
        case OperationType::SUBTRACT:
            result = lastValueDouble - currentValueDouble;
            break;
        case OperationType::MULTIPLY:
            result = lastValueDouble * currentValueDouble;
            break;
        case OperationType::DIVIDE:
            result = lastValueDouble / currentValueDouble;
            break;
        case OperationType::EQUAL:
            equalResult = std::format("{:g}", currentValueDouble);
            lastTextControl->SetValue(equalResult);
            currentTextControl->SetValue(equalResult);
            return;
        default:
            return;
        }

        // RESET THE CONTROLS
        ButtonGrid::operationType = OperationType::EQUAL;

        // ROUND RESULT BY DEFAULT (REMOVE TRAILING ZEROS)
        std::string stringResult = std::format("{:g}", result);
        currentTextControl->SetValue(stringResult);
    }
    catch (int exception)
    {
        (void)exception;
        currentTextControl->SetValue("Error");
    }
}