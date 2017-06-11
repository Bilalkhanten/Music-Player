/***************************************************************
 * Name:      music_playerMain.h
 * Purpose:   Defines Application Frame
 * Author:    Bilal Khan (Bilalkhanten@gmail.com)
 * Created:   2010-06-12
 **************************************************************/

#ifndef MUSIC_PLAYERMAIN_H
#define MUSIC_PLAYERMAIN_H

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "music_playerApp.h"

class music_playerFrame: public wxFrame
{
    public:
        music_playerFrame(wxFrame *frame, const wxString& title);
        ~music_playerFrame();
    private:
        enum
        {
            idMenuQuit = 1000,
            idMenuAbout
        };
        wxFileDialog *fileOpen;
        wxString fileOpen_str;
        wxSlider* musicSlider;
        wxToolBar* m_toolBar1;
        int trackPos;

        void OnClose(wxCloseEvent& event);
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnEject(wxCommandEvent& event);
        void OnPlay(wxCommandEvent& event);
        void OnOpen(wxCommandEvent& event);
        void OnPause(wxCommandEvent& event);
        void OnVolumeUp(wxCommandEvent& event);
        void OnVolumeDown(wxCommandEvent& event);
        void OnRewind(wxCommandEvent& event);
        void OnScroll(wxScrollEvent& event);
        DECLARE_EVENT_TABLE()
};


#endif // MUSIC_PLAYERMAIN_H
