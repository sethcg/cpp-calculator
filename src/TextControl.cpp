#include <wx/wx.h>
#include <TextControl.h>

TextControl::TextControl(wxWindow *parent, wxString defaultValue) : wxTextCtrl()
{
    this->SetBackgroundColour(wxColour(40, 40, 40, wxALPHA_OPAQUE));
    this->Create(parent, wxID_ANY, defaultValue, wxDefaultPosition, wxDefaultSize, wxTE_READONLY | wxSIMPLE_BORDER);
    this->SetWindowStyle(wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL | wxEXPAND);
    this->SetFont(wxFont(16, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_MAX, wxFONTWEIGHT_BOLD));
}