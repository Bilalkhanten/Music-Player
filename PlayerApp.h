/***************************************************************
 * Name:      music_playerApp.h
 * Purpose:   Defines Application Class
 * Author:    Bilal khan (Bilalkhanten@gmail.com)
 * Created:   2017-06-12
 **************************************************************/

#ifndef MUSIC_PLAYERAPP_H
#define MUSIC_PLAYERAPP_H

#include <wx/app.h>
#include "SDL.h"
#include "SDL_mixer.h"

class music_playerApp : public wxApp
{
    public:
        virtual bool OnInit();
};

#endif // MUSIC_PLAYERAPP_H
