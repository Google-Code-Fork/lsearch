/*
 *  Copyright (C) 2007-2008  ZioNz - zionztp@gmail.com
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

//---------------------------------------------------------------------------
//
// Name:        procselDlg.h
// Author:      ZioNz
// Created:     12/22/2007 11:58:40 PM
// Description: procselDlg class declaration
//
//---------------------------------------------------------------------------

#include <vector>

#ifndef __PROCSELDLG_h__
#define __PROCSELDLG_h__

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
	#include <wx/dialog.h>
#else
	#include <wx/wxprec.h>
#endif

//Do not add custom headers between 
//Header Include Start and Header Include End.
//wxDev-C++ designer will remove them. Add custom headers after the block.
////Header Include Start
#include <wx/button.h>
#include <wx/textctrl.h>
#include <wx/stattext.h>
#include <wx/listctrl.h>
#include <wx/panel.h>
////Header Include End

////Dialog Style Start
#undef procselDlg_STYLE
#define procselDlg_STYLE wxCAPTION | wxSYSTEM_MENU | wxDIALOG_NO_PARENT | wxMINIMIZE_BOX | wxCLOSE_BOX
////Dialog Style End

class procselDlg : public wxDialog
{
	private:
		DECLARE_EVENT_TABLE();
		
	public:
		procselDlg(wxWindow *parent, wxWindowID id = 1, const wxString &title = wxT("procsel"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = procselDlg_STYLE);
		virtual ~procselDlg();
		void WxButton1Click(wxCommandEvent& event);
		void WxButton2Click(wxCommandEvent& event);
	
		int GetPID();
		wxString GetName();
		void WxButton3Click(wxCommandEvent& event);

		void procselDlgActivate(wxActivateEvent& event);
	private:
		//Do not add custom control declarations between 
		//GUI Control Declaration Start and GUI Control Declaration End.
		//wxDev-C++ will remove them. Add custom code after the block.
		////GUI Control Declaration Start
		wxButton *WxButton3;
		wxButton *WxButton2;
		wxButton *WxButton1;
		wxTextCtrl *WxEdit1;
		wxStaticText *WxStaticText1;
		wxListCtrl *WxListCtrl1;
		wxPanel *WxPanel1;
		////GUI Control Declaration End
		
	private:
		//Note: if you receive any error with these enum IDs, then you need to
		//change your old form code that are based on the #define control IDs.
		//#defines may replace a numeric value for the enum names.
		//Try copy and pasting the below block in your old form header files.
		enum
		{
			////GUI Enum Control ID Start
			ID_WXBUTTON3 = 1007,
			ID_WXBUTTON2 = 1006,
			ID_WXBUTTON1 = 1005,
			ID_WXEDIT1 = 1004,
			ID_WXSTATICTEXT1 = 1003,
			ID_WXLISTCTRL1 = 1002,
			ID_WXPANEL1 = 1001,
			////GUI Enum Control ID End
			ID_DUMMY_VALUE_ //don't remove this value unless you have other enum values
		};
	
	private:
		void OnClose(wxCloseEvent& event);
		void CreateGUIControls();

		void ListProc();
		int sel_pid;
		wxString sel_name;
		std::vector<std::string> proc_names;
};

#endif
