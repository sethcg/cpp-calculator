#pragma once
#include <wx/wx.h>

const inline wxString BUTTON_STRING_ZERO_DIGIT = "0";   // STRING VALUE: "0"
const inline wxString BUTTON_STRING_ONE_DIGIT = "1";    // STRING VALUE: "1"
const inline wxString BUTTON_STRING_TWO_DIGIT = "2";    // STRING VALUE: "2"
const inline wxString BUTTON_STRING_THREE_DIGIT = "3";  // STRING VALUE: "3"
const inline wxString BUTTON_STRING_FOUR_DIGIT = "4";   // STRING VALUE: "4"
const inline wxString BUTTON_STRING_FIVE_DIGIT = "5";   // STRING VALUE: "5"
const inline wxString BUTTON_STRING_SIX_DIGIT = "6";    // STRING VALUE: "6"
const inline wxString BUTTON_STRING_SEVEN_DIGIT = "7";  // STRING VALUE: "7"
const inline wxString BUTTON_STRING_EIGHT_DIGIT = "8";  // STRING VALUE: "8"
const inline wxString BUTTON_STRING_NINE_DIGIT = "9";   // STRING VALUE: "9"
const inline wxString BUTTON_STRING_CLEAR_ENTRY = "CE"; // STRING VALUE: "CE"
const inline wxString BUTTON_STRING_CLEAR_ALL = "C";    // STRING VALUE: "C"
const inline wxString BUTTON_STRING_DELETE = "DEL";     // STRING VALUE: "DEL"

const inline wxString BUTTON_STRING_PERCENT = "\u0025";  // STRING VALUE: "%"
const inline wxString BUTTON_STRING_DECIMAL = "\u002E";  // STRING VALUE: "."
const inline wxString BUTTON_STRING_MULTIPLY = "x";      // STRING VALUE: "x"
const inline wxString BUTTON_STRING_DIVIDE = "\u00F7";   // STRING VALUE: "÷"
const inline wxString BUTTON_STRING_ADD = "+";           // STRING VALUE: "+"
const inline wxString BUTTON_STRING_SUBTRACT = "\u002D"; // STRING VALUE: "-"
const inline wxString BUTTON_STRING_EQUAL = "\u003D";    // STRING VALUE: "="

const inline wxString BUTTON_STRING_FRACTION = wxString::FromUTF8("\xE2\x85\x9F\xF0\x9D\x93\x8D");    // STRING VALUE: "⅟𝓍"
const inline wxString BUTTON_STRING_SQUARE = wxString::FromUTF8("\xF0\x9D\x93\x8D\xC2\xB2");          // STRING VALUE: "𝓍²"
const inline wxString BUTTON_STRING_SQUARE_ROOT = wxString::FromUTF8("\xE2\x88\x9A\xF0\x9D\x93\x8D"); // STRING VALUE: "√𝓍"
const inline wxString BUTTON_STRING_NEGATE = wxString::FromUTF8("\xE2\x81\xBA\xCC\xB8\xE2\x82\x8B");  // STRING VALUE: "⁺̸₋"

class CalculatorButton : public wxButton
{
public:
    CalculatorButton(std::function<void()> onClick, wxWindow *parent, wxTextCtrl *textControl, const wxString &label, const wxColor &backgroundColor);
    CalculatorButton(std::function<void()> onClick, wxWindow *parent, wxTextCtrl *textControl, const wxString &label, const wxColor &backgroundColor, const wxColor &textColor);
};