#pragma once
#include <wx/wx.h>

class TextControl : public wxTextCtrl
{
public:
    TextControl(wxWindow *parent, wxString defaultValue);
};