#include <wx/wx.h>
#include <colors/Colors.h>
#include <TextControl.h>

TextControl::TextControl(wxWindow *parent, wxString defaultValue)
    : wxTextCtrl()
{
    this->SetBackgroundColour(COLOR_APPLICATION_BACKGROUND);
    this->Create(parent, wxID_ANY, defaultValue, wxDefaultPosition, wxDefaultSize, wxTE_READONLY | wxSIMPLE_BORDER);
    this->SetWindowStyle(wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL | wxEXPAND);
    this->SetFont(wxFont(16, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_MAX, wxFONTWEIGHT_BOLD));
}