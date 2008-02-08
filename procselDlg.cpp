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
// Name:        procselDlg.cpp
// Author:      ZioNz
// Created:     12/22/2007 11:58:40 PM
// Description: procselDlg class implementation
//
//---------------------------------------------------------------------------

#include <iostream>
#include <fstream>

#include "procselDlg.h"
#include "wx_util.h"
using namespace std;

//Do not add custom headers
//wxDev-C++ designer will remove them
////Header Include Start
////Header Include End

//----------------------------------------------------------------------------
// procselDlg
//----------------------------------------------------------------------------
//Add Custom Events only in the appropriate block.
//Code added in other places will be removed by wxDev-C++
////Event Table Start
BEGIN_EVENT_TABLE(procselDlg,wxDialog)
	////Manual Code Start
	////Manual Code End
	
	EVT_CLOSE(procselDlg::OnClose)
	EVT_ACTIVATE(procselDlg::procselDlgActivate)
	EVT_BUTTON(ID_WXBUTTON3,procselDlg::WxButton3Click)
	EVT_BUTTON(ID_WXBUTTON2,procselDlg::WxButton2Click)
	EVT_BUTTON(ID_WXBUTTON1,procselDlg::WxButton1Click)
END_EVENT_TABLE()
////Event Table End

procselDlg::procselDlg(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxDialog(parent, id, title, position, size, style)
{
	CreateGUIControls();
}

procselDlg::~procselDlg()
{
} 

void procselDlg::CreateGUIControls()
{
	//Do not add custom code between
	//GUI Items Creation Start and GUI Items Creation End.
	//wxDev-C++ designer will remove them.
	//Add the custom code before or after the blocks
	////GUI Items Creation Start

	WxPanel1 = new wxPanel(this, ID_WXPANEL1, wxPoint(0,0), wxSize(347,339));
	WxPanel1->SetFont(wxFont(8, wxSWISS, wxNORMAL,wxNORMAL, false, wxT("MS Shell Dlg")));

	WxListCtrl1 = new wxListCtrl(WxPanel1, ID_WXLISTCTRL1, wxPoint(5,10), wxSize(332,229), wxLC_REPORT | wxLC_ALIGN_LEFT | wxLC_SINGLE_SEL | wxLC_HRULES | wxLC_VRULES);
	WxListCtrl1->SetFont(wxFont(8, wxSWISS, wxNORMAL,wxNORMAL, false, wxT("MS Shell Dlg")));

	WxStaticText1 = new wxStaticText(WxPanel1, ID_WXSTATICTEXT1, wxT("Filter:"), wxPoint(8,251), wxDefaultSize, 0, wxT("WxStaticText1"));
	WxStaticText1->SetFont(wxFont(8, wxSWISS, wxNORMAL,wxNORMAL, false, wxT("MS Shell Dlg")));

	WxEdit1 = new wxTextCtrl(WxPanel1, ID_WXEDIT1, wxT(""), wxPoint(46,249), wxSize(100,20), 0, wxDefaultValidator, wxT("WxEdit1"));
	WxEdit1->SetFont(wxFont(8, wxSWISS, wxNORMAL,wxNORMAL, false, wxT("MS Shell Dlg")));

	WxButton1 = new wxButton(WxPanel1, ID_WXBUTTON1, wxT("Refresh"), wxPoint(247,249), wxSize(88,26), 0, wxDefaultValidator, wxT("WxButton1"));
	WxButton1->SetFont(wxFont(8, wxSWISS, wxNORMAL,wxNORMAL, false, wxT("MS Shell Dlg")));

	WxButton2 = new wxButton(WxPanel1, ID_WXBUTTON2, wxT("Ok"), wxPoint(20,298), wxSize(92,30), 0, wxDefaultValidator, wxT("WxButton2"));
	WxButton2->SetFont(wxFont(8, wxSWISS, wxNORMAL,wxNORMAL, false, wxT("MS Shell Dlg")));

	WxButton3 = new wxButton(WxPanel1, ID_WXBUTTON3, wxT("Cancel"), wxPoint(229,298), wxSize(92,30), 0, wxDefaultValidator, wxT("WxButton3"));
	WxButton3->SetFont(wxFont(8, wxSWISS, wxNORMAL,wxNORMAL, false, wxT("MS Shell Dlg")));

	SetTitle(wxT("Select a process:"));
	SetIcon(wxNullIcon);
	SetSize(8,8,355,366);
	Center();
	
	////GUI Items Creation End

	//Add columns to process list
	WxListCtrl1->InsertColumn(0, _T("PID"), wxLIST_FORMAT_LEFT,80);
    WxListCtrl1->InsertColumn(1, _T("Description"), wxLIST_FORMAT_LEFT,255);
}

void procselDlg::OnClose(wxCloseEvent& /*event*/)
{
	//Destroy();
	sel_pid = 0;
	sel_name = _T("");

	Hide();
}

/*
 * WxButton1Click
 */
void procselDlg::WxButton1Click(wxCommandEvent& event)
{
	//Refresh button
	ListProc();
}

//TMP!!!!!!!!!!!!!!!!!!!!! *************************************
string sget_pid(string linea){
    int i=0;
    string tpid="";

    while(linea[i]==' ' || isdigit(linea[i]) ){
        tpid+=linea[i];
        i++;
    }

    return tpid;
}

string sget_desc(string linea){
    int i=0;

    while(linea[i]!=':' ){ i++; }
    i++;
    while(linea[i]!=':' ){ i++; }


    if(i+3<linea.size()){
        return linea.substr(i+3,linea.size()-1);
    }else{
        return "";
    }
}

//----------------------------------------------------------------------------------------

void procselDlg::ListProc()
{
	ifstream entrada;
    string linea;
    string s_pid;
    string s_desc;
    string s_comando;

    int i=0;

    wxString tfiltro;
    tfiltro = WxEdit1->GetValue();

    if(tfiltro.size()>0){
        linea=wxstr_to_str(tfiltro);
        s_comando="ps -A | grep ";
        s_comando+=linea;
        s_comando+=" > t.tmp";
    }else{
        s_comando="ps -A > t.tmp";
    }

    system(s_comando.c_str());

    entrada.open("t.tmp",ifstream::in);

    if(!entrada.is_open()){
        return;
    }

    WxListCtrl1->DeleteAllItems();
	proc_names.clear();

    while(!entrada.eof()){
        getline(entrada,linea);

        if(linea.size()>0){
            s_pid=sget_pid(linea);
            s_desc=sget_desc(linea);

            if(s_desc.length()>0){
                WxListCtrl1->InsertItem(i,str_to_wxstr(s_pid,1));
                WxListCtrl1->SetItem(i,1,str_to_wxstr(s_desc,1));
				proc_names.push_back(s_desc);
                i++;
            }
        }

    }

    entrada.close();
	system("rm -rf t.tmp");
}

/*
 * WxButton2Click
 */
void procselDlg::WxButton2Click(wxCommandEvent& event)
{
	//Ok button
	string spid;
	long item = -1;
	long nitem = -1;
	int pid;

 	item = WxListCtrl1->GetNextItem(item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);

	if(item == -1){
		wxMessageBox(_T("Please select a process from the list."), _T("Error"), wxICON_ERROR);
		return;
	}

	//Set pid
	spid=wxstr_to_str(WxListCtrl1->GetItemText(item));
	sel_pid = atoi(spid.c_str());
	sel_name = str_to_wxstr(proc_names[item]);

	//Hide window
	Show(false);
}

int procselDlg::GetPID()
{
	return sel_pid;
}

wxString procselDlg::GetName()
{
	return sel_name;
}

/*
 * WxButton3Click
 */
void procselDlg::WxButton3Click(wxCommandEvent& event)
{
	//Cancel button
	sel_pid = 0;
	sel_name = _T("");
}

/*
 * procselDlgActivate
 */
void procselDlg::procselDlgActivate(wxActivateEvent& event)
{
	// insert your code here
	ListProc();
}
