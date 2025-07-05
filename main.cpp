#include <wx/wx.h>
#include <vector>
#include <constants/Colors.hpp>
#include <TextControl.hpp>
#include <CalculatorButton.hpp>
#include <ButtonGrid.hpp>

class MyApp : public wxApp
{
public:
    bool OnInit() override;
};

wxIMPLEMENT_APP(MyApp);

class CalculatorFrame : public wxFrame
{
public:
    CalculatorFrame(const wxString &title, const wxPoint &pos, const wxSize &size);
};

bool MyApp::OnInit()
{
    MyApp::SetAppearance(Appearance::Dark);

    CalculatorFrame *frame = new CalculatorFrame(wxEmptyString, wxDefaultPosition, wxSize(270, 360));
    frame->SetBackgroundColour(COLOR_FRAME_BACKGROUND);
    frame->SetIcon(wxIcon("assets\\icon.ico", wxBITMAP_TYPE_ICO));
    frame->Bind(wxEVT_CONTEXT_MENU, [](wxContextMenuEvent &event) {});
    frame->Show();

    return true;
}

CalculatorFrame::CalculatorFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxFrame(nullptr, wxID_ANY, title, pos, size, wxDEFAULT_FRAME_STYLE & ~(wxCAPTION | wxSYSTEM_MENU))
{
    // INITIALIZE TEXT DISPLAY
    auto *textPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);
    textPanel->SetBackgroundColour(COLOR_PANEL_BACKGROUND);

    auto textContainer = new wxBoxSizer(wxHORIZONTAL);
    auto textInnerContainer = new wxBoxSizer(wxVERTICAL);

    auto *lastTextControl = new TextControl(textPanel, wxEmptyString);
    lastTextControl->Bind(wxEVT_CONTEXT_MENU, [](wxContextMenuEvent &event) {});
    lastTextControl->Bind(wxEVT_SET_FOCUS, [](wxFocusEvent &event) {});

    auto *currentTextControl = new TextControl(textPanel, "0");
    currentTextControl->Bind(wxEVT_CONTEXT_MENU, [](wxContextMenuEvent &event) {});

    const int TEXT_CONTAINER_VERTICAL_MARGIN = FromDIP(5);
    textInnerContainer->AddSpacer(TEXT_CONTAINER_VERTICAL_MARGIN);
    textInnerContainer->Add(lastTextControl, 1, wxEXPAND, 0);
    textInnerContainer->AddSpacer(TEXT_CONTAINER_VERTICAL_MARGIN);
    textInnerContainer->Add(currentTextControl, 1, wxEXPAND, 0);
    textInnerContainer->AddSpacer(TEXT_CONTAINER_VERTICAL_MARGIN);

    const int TEXT_CONTAINER_HORIZONTAL_MARGIN = FromDIP(5);
    textContainer->AddSpacer(TEXT_CONTAINER_HORIZONTAL_MARGIN);
    textContainer->Add(textInnerContainer, 1, wxEXPAND, 0);
    textContainer->AddSpacer(TEXT_CONTAINER_HORIZONTAL_MARGIN);

    textPanel->SetSizer(textContainer);

    // INITIALIZE CALCULATOR BUTTONS
    auto buttonContainer = new wxBoxSizer(wxHORIZONTAL);
    auto buttonInnerContainer = new wxBoxSizer(wxVERTICAL);
    auto buttonGrid = new ButtonGrid(this, lastTextControl, currentTextControl);

    const int BUTTON_CONTAINER_TOP_VERTICAL_MARGIN = FromDIP(5);
    const int BUTTON_CONTAINER_BOTTOM_VERTICAL_MARGIN = FromDIP(10);
    buttonInnerContainer->AddSpacer(BUTTON_CONTAINER_TOP_VERTICAL_MARGIN);
    buttonInnerContainer->Add(buttonGrid, 1, wxEXPAND, 0);
    buttonInnerContainer->AddSpacer(BUTTON_CONTAINER_BOTTOM_VERTICAL_MARGIN);

    const int BUTTON_CONTAINER_HORIZONTAL_MARGIN = FromDIP(10);
    buttonContainer->AddSpacer(BUTTON_CONTAINER_HORIZONTAL_MARGIN);
    buttonContainer->Add(buttonInnerContainer, 1, wxEXPAND, 0);
    buttonContainer->AddSpacer(BUTTON_CONTAINER_HORIZONTAL_MARGIN);

    // ALWAYS FIT THE CONTENT ON THE FRAME/WINDOW WHEN ADJUSTING HEIGHT OR WIDTH
    const auto MARGIN = FromDIP(30);
    auto mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(textPanel, 0, wxEXPAND, MARGIN);
    mainSizer->Add(buttonContainer, 1, wxEXPAND, MARGIN);
    SetSizer(mainSizer);
    SetMinSize(size);

    Center();
}