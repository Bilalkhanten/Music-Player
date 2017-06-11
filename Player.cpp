/***************************************************************
 * Name:      music_playerMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Bilal Khan (Bilalkhanten@gmail.com)
 * Created:   2017-06-12
 **************************************************************/
bool tray_open = false;
bool firstPlay = true;
int volume = 50;
char buf[100];
#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "music_playerMain.h"

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__WXMAC__)
        wxbuild << _T("-Mac");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

BEGIN_EVENT_TABLE(music_playerFrame, wxFrame)
    EVT_CLOSE(music_playerFrame::OnClose)
    EVT_MENU(idMenuQuit, music_playerFrame::OnQuit)
    EVT_MENU(idMenuAbout, music_playerFrame::OnAbout)
    EVT_MENU(1, music_playerFrame::OnEject)
    EVT_MENU(2, music_playerFrame::OnPlay)
    EVT_MENU(3, music_playerFrame::OnOpen)
    EVT_MENU(4, music_playerFrame::OnPause)
    EVT_MENU(5, music_playerFrame::OnRewind)
    EVT_MENU(6, music_playerFrame::OnVolumeUp)
    EVT_MENU(7, music_playerFrame::OnVolumeDown)
    EVT_MENU(8, music_playerFrame::OnPlay)
    EVT_MENU(9, music_playerFrame::OnPause)
    EVT_MENU(10, music_playerFrame::OnEject)
END_EVENT_TABLE()

music_playerFrame::music_playerFrame(wxFrame *frame, const wxString& title)
    : wxFrame(frame, -1, title)
{
    music_playerFrame::SetSize(640, 480);
#if wxUSE_MENUS
	// highest id: 11
    // create a menu bar
    this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer;
	bSizer = new wxBoxSizer( wxVERTICAL );
    
    wxMenuBar* mbar = new wxMenuBar();

	wxMenu* musicMenu = new wxMenu(_T(""));
	musicMenu->Append(3, _("&Open\tCtrl+o"));
	musicMenu->Append(idMenuQuit, _("&Quit\tAlt-F4"));
	mbar->Append(musicMenu, _("Music"));
	
	wxMenu* controlMenu = new wxMenu(_T(""));
	controlMenu->Append(6, _("Volume Increase\tCtrl+up"));
	controlMenu->Append(7, _("Volume Decrease\tCtrl+down"));
	controlMenu->Append(2, _("&Play\tCtrl+p"));
	controlMenu->Append(4, _("Pause\tCtrl+Shift+p"));
	controlMenu->Append(5, _("&Rewind\tCtrl+r"));
	controlMenu->Append(1, _("&Eject\tCtrl+e"));
    mbar->Append(controlMenu, _("&Control"));

    wxMenu* helpMenu = new wxMenu(_T(""));
    helpMenu->Append(idMenuAbout, _("&About\tF1"));
    mbar->Append(helpMenu, _("&Help"));
    SetMenuBar(mbar);
    
    musicSlider = new wxSlider(this, 11, volume, 0, 100, wxDefaultPosition, wxSize(630,-1), wxSL_HORIZONTAL );
	bSizer->Add( musicSlider, 0, wxALL, 5 );
	this->SetSizer( bSizer );
	this->Layout();
	Connect(11, wxEVT_COMMAND_SLIDER_UPDATED, wxScrollEventHandler(music_playerFrame::OnScroll));

	wxBitmap play(wxT("images/play.svg"));
	wxBitmap pause(wxT("images/pause.svg"));
	wxBitmap eject(wxT("images/eject.svg"));

	wxToolBar *toolbar = CreateToolBar();
	toolbar->AddTool(8, play, wxT("Play song"));
	toolbar->AddTool(9, pause, wxT("Pause song"));
	toolbar->AddTool(10, eject, wxT("Eject CD"));
	toolbar->Realize();
	
	#endif // wxUSE_MENUS
}


music_playerFrame::~music_playerFrame()
{
}

void music_playerFrame::OnClose(wxCloseEvent &event)
{
    Mix_CloseAudio();
	SDL_Quit();
    Destroy();
}

void music_playerFrame::OnQuit(wxCommandEvent &event)
{
    Mix_CloseAudio();
	SDL_Quit();
    Destroy();
}

void music_playerFrame::OnAbout(wxCommandEvent &event)
{
    wxString msg = _("Name: Music Player\nAuthor: Joel Moore\nLicence: GPLv3\nDescription: This is just a simple music player");
    wxMessageBox(msg, _("About"));
}

void music_playerFrame::OnEject(wxCommandEvent &event)
{
    if (tray_open == false)
    {
        system("eject"); // open CD tray
        tray_open = true;
    }

    else
    {
        system("eject -t"); // close CD tray
        tray_open = false;
    }
}

void music_playerFrame::OnOpen(wxCommandEvent &event)
{
	fileOpen = new wxFileDialog(this, _("Open a file"),_("."),_(""),
     _("All Files|**| mp3 (*.mp3)|*.mp3"),
     wxOPEN);
    fileOpen->ShowModal();
    fileOpen_str = fileOpen->GetPath();	
    Mix_HaltMusic();
    firstPlay = true;
}

void music_playerFrame::OnPlay(wxCommandEvent &event)
{
	if (firstPlay == true)
	{
		int audio_rate = 22050;
		Uint16 audio_format = AUDIO_S16;
		int audio_channels = 2;
		int audio_buffers = 4096;
		Mix_Music *music = NULL;
		Mix_QuerySpec(&audio_rate, &audio_format, &audio_channels);
		SDL_Init(SDL_INIT_AUDIO);
		strcpy( buf, (const char*)fileOpen_str.mb_str(wxConvUTF8) );
		Mix_HaltMusic();
		Mix_FreeMusic(music);
		if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers))
		{
			wxMessageBox(_("Unable to play audio"), _("Error"));
			exit(1);
		}
		
		if (strcmp(buf,"") == 0)
		{
			wxMessageBox(_("You have to open a music file!"), _("Alert"));
		}
		
		if (strcmp(buf,"") != 0)
		{
			firstPlay = false;
		}
		
		if(music == NULL)
		{
			music = Mix_LoadMUS(buf);
			Mix_PlayMusic(music, 0);
		}

		else
		{
			Mix_HaltMusic();
			Mix_FreeMusic(music);
			music = NULL;
		}
	}
	
	else
	{
		Mix_ResumeMusic();
	}
}
void music_playerFrame::OnPause(wxCommandEvent &event)
{
	Mix_PauseMusic();
}

void music_playerFrame::OnVolumeUp(wxCommandEvent &event)
{
	if (volume < 100)
	{
		Mix_VolumeMusic(volume+=10);
		musicSlider->SetValue(volume);
	}
	
	else
	{
		Mix_VolumeMusic(volume=100);
	}
}

void music_playerFrame::OnVolumeDown(wxCommandEvent &event)
{
		if (volume > 0)
	{
		Mix_VolumeMusic(volume-=10);
		musicSlider->SetValue(volume);
	}
	
	else
	{
		Mix_VolumeMusic(volume=0);
		Refresh();
	}
}

void music_playerFrame::OnScroll(wxScrollEvent& event)
{
	trackPos = musicSlider->GetValue();
	Mix_VolumeMusic(trackPos);
}

void music_playerFrame::OnRewind(wxCommandEvent& event)
{
	Mix_RewindMusic();
}
