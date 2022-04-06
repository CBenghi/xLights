#pragma once

#include "../SketchEffectDrawing.h"

#include <functional>
#include <string>

#include <wx/image.h>
#include <wx/panel.h>

class wxButton;
class wxFilePickerCtrl;
class wxKeyEvent;
class wxListBox;
class wxSlider;

class SketchCanvasPanel;

class SketchAssistPanel : public wxPanel
{
public:
    // Effect panels are static (a single panel for the lifetime of the app) but
    // assist panels are not... so it seems like it should be safe for an assist
    // panel to reference an effect panel via a lambda 'this' capture
    typedef std::function<void(const std::string&)> SketchUpdateCallback;

    SketchAssistPanel(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize);
    virtual ~SketchAssistPanel() = default;

    void SetSketchDef(const std::string& sketchDef);
    void SetSketchUpdateCallback(SketchUpdateCallback cb)
    {
        m_sketchUpdateCB = cb;
    }

    void ForwardKeyEvent(wxKeyEvent& event);

private:
    DECLARE_EVENT_TABLE()

    void OnFilePickerCtrl_FileChanged(wxCommandEvent& event);
    void OnSlider_BgAlphaChanged(wxCommandEvent& event);

    void OnButton_StartPath(wxCommandEvent& event);
    void OnButton_EndPath(wxCommandEvent& event);
    void OnButton_ClosePath(wxCommandEvent& event);
    void OnButton_ClearSketch(wxCommandEvent& event);

    void OnListBox_PathSelected(wxCommandEvent& event);
    void OnListBox_ContextMenu(wxContextMenuEvent& event);
    void OnPopupCommand(wxCommandEvent& event);

    void updateBgImage();
    void updateUIFromSketch();
    void populatePathListBoxFromSketch();
    void sketchUpdatedFromCanvasPanel();

    std::string m_sketchDef;
    SketchEffectSketch m_sketch;
    SketchUpdateCallback m_sketchUpdateCB;

    SketchCanvasPanel* m_sketchCanvasPanel = nullptr;
    wxFilePickerCtrl* m_filePicker = nullptr;
    wxSlider* m_bgAlphaSlider = nullptr;
    wxButton* m_startPathBtn = nullptr;
    wxButton* m_endPathBtn = nullptr;
    wxButton* m_closePathBtn = nullptr;
    wxListBox* m_pathsListBox = nullptr;
    static long ID_MENU_Delete;

    wxImage m_bgImage;
    unsigned char m_bitmapAlpha = 0x30;
    int m_pathIndexToDelete = -1;

    friend class SketchCanvasPanel;
};