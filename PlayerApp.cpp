/***************************************************************
 * Name:      music_playerApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Bilal khan (Bilalkhanten@gmail.com)
 * Created:   2017-06-12
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "music_playerApp.h"
#include "music_playerMain.h"

IMPLEMENT_APP(music_playerApp);

bool music_playerApp::OnInit()
{
    music_playerFrame* frame = new music_playerFrame(0L, _("Music Player"));

    frame->Show();

    return true;
}
