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
// Name:        lsearchFrm.h
// Author:      ZioNz
// Created:     12/22/2007 10:38:06 PM
// Description: lsearchFrm class declaration
//
//---------------------------------------------------------------------------

#ifndef __LSEARCHFRM_h__
#define __LSEARCHFRM_h__

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
	#include <wx/frame.h>
#else
	#include <wx/wxprec.h>
#endif

#include <vector>
using namespace std;

#include "procselDlg.h"
//Do not add custom headers between 
//Header Include Start and Header Include End.
//wxDev-C++ designer will remove them. Add custom headers after the block.
////Header Include Start
#include <wx/timer.h>
#include <wx/menu.h>
#include <wx/combobox.h>
#include <wx/checkbox.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/listctrl.h>
#include <wx/stattext.h>
#include <wx/gauge.h>
#include <wx/bmpbuttn.h>
#include <wx/panel.h>
////Header Include End

////Dialog Style Start
#undef lsearchFrm_STYLE
#define lsearchFrm_STYLE wxCAPTION | wxSYSTEM_MENU | wxMINIMIZE_BOX | wxCLOSE_BOX | wxMINIMIZE
////Dialog Style End

struct Tfounditem
{
	int type;
	unsigned long addr;
	long data_4;
	short int data_2;
	char data_1;
	string data_s;
};

struct Twatchitem
{
	int type;
	unsigned long addr;
	long data_4;
	short int data_2;
	char data_1;
	string data_s;
	string desc;
};

class lsearchFrm : public wxFrame
{
	private:
		DECLARE_EVENT_TABLE();
		
	public:
		lsearchFrm(wxWindow *parent, wxWindowID id = 1, const wxString &title = wxT("lsearch"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = lsearchFrm_STYLE);
		virtual ~lsearchFrm();
		void WxBitmapButton1Click(wxCommandEvent& event);
		void WxListCtrl1RightClick(wxListEvent& event);
		void WxButton1Click(wxCommandEvent& event);
		wxGauge *Wxgauge1;		
	void Mnutest1020Click(wxCommandEvent& event);
		void WxButton3Click(wxCommandEvent& event);
		void WxButton2Click(wxCommandEvent& event);
	void Mnuaddtowatchlist1022Click(wxCommandEvent& event);
	void Mnucopyaddress1023Click(wxCommandEvent& event);

		void WxTimer1Timer(wxTimerEvent& event);
		void WxCheckBox2Click(wxCommandEvent& event);
		void WxListCtrl2RightClick(wxListEvent& event);
	void Mnuremove1026Click(wxCommandEvent& event);
	private:
		//Do not add custom control declarations between
		//GUI Control Declaration Start and GUI Control Declaration End.
		//wxDev-C++ will remove them. Add custom code after the block.
		////GUI Control Declaration Start
		wxMenu *WxPopupMenu2;
		wxTimer *WxTimer1;
		wxMenu *WxPopupMenu1;
		wxCheckBox *WxCheckBox2;
		wxButton *WxButton3;
		wxListCtrl *WxListCtrl2;
		wxComboBox *WxComboBox2;
		wxComboBox *WxComboBox1;
		wxStaticText *WxStaticText5;
		wxStaticText *WxStaticText4;
		wxCheckBox *WxCheckBox1;
		wxTextCtrl *WxEdit1;
		wxStaticText *WxStaticText3;
		wxButton *WxButton2;
		wxButton *WxButton1;
		wxStaticText *WxStaticText2;
		wxListCtrl *WxListCtrl1;
		wxStaticText *WxStaticText1;
		wxGauge *WxGauge1;
		wxBitmapButton *WxBitmapButton3;
		wxBitmapButton *WxBitmapButton2;
		wxBitmapButton *WxBitmapButton1;
		wxPanel *WxPanel1;
		////GUI Control Declaration End

		//Process selector dialog
		procselDlg* dlg_proc_selector;
	private:
		//Note: if you receive any error with these enum IDs, then you need to
		//change your old form code that are based on the #define control IDs.
		//#defines may replace a numeric value for the enum names.
		//Try copy and pasting the below block in your old form header files.
		enum
		{
			////GUI Enum Control ID Start
			ID_MNU_REMOVE_1026 = 1026,
			ID_MNU_CHANGEADDRESS_1027 = 1027,
			ID_MNU_CHAGEDESCRIPTION_1028 = 1028,
			ID_MNU_COPYADDRESS_1029 = 1029,
			
			ID_WXTIMER1 = 1024,
			ID_MNU_TEST_1020 = 1020,
			ID_MNU_ADDTOWATCHLIST_1022 = 1022,
			ID_MNU_COPYADDRESS_1023 = 1023,
			
			ID_WXCHECKBOX2 = 1025,
			ID_WXBUTTON3 = 1021,
			ID_WXLISTCTRL2 = 1019,
			ID_WXCOMBOBOX2 = 1018,
			ID_WXCOMBOBOX1 = 1017,
			ID_WXSTATICTEXT5 = 1016,
			ID_WXSTATICTEXT4 = 1015,
			ID_WXCHECKBOX1 = 1014,
			ID_WXEDIT1 = 1013,
			ID_WXSTATICTEXT3 = 1012,
			ID_WXBUTTON2 = 1011,
			ID_WXBUTTON1 = 1010,
			ID_WXSTATICTEXT2 = 1009,
			ID_WXLISTCTRL1 = 1008,
			ID_WXSTATICTEXT1 = 1007,
			ID_WXGAUGE1 = 1006,
			ID_WXBITMAPBUTTON3 = 1005,
			ID_WXBITMAPBUTTON2 = 1004,
			ID_WXBITMAPBUTTON1 = 1003,
			ID_WXPANEL1 = 1001,
			////GUI Enum Control ID End
			ID_DUMMY_VALUE_ //don't remove this value unless you have other enum values
		};
		
	private:
		void OnClose(wxCloseEvent& event);
		void CreateGUIControls();

		bool ScanExact();
		bool ReScanExact();

		void UpdateFoundList();
		void ClearFoundList();

		void UpdateWatchList();
		void ClearWatchList();

		vector<Tfounditem> found;
		vector<Twatchitem> watch;
		wxString proc_name;
		int proc_id;
		int scan_type;
		int data_type;
};

#endif
