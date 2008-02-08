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
// Name:        lsearchFrm.cpp
// Author:      ZioNz
// Created:     12/22/2007 10:38:06 PM
// Description: lsearchFrm class implementation
//
//---------------------------------------------------------------------------

#include "lsearchFrm.h"

#include "wx_util.h"
#include "mem_util.h"
Cmemutil *mem;

#include <sys/ptrace.h>
#include <sys/types.h>
#include <signal.h>
#include <errno.h>
#include <sys/wait.h>

#include <wx/clipbrd.h>
#include <wx/dataobj.h>

//Do not add custom headers between
//Header Include Start and Header Include End
//wxDev-C++ designer will remove them
////Header Include Start
#include "Images/lsearchFrm_WxBitmapButton3_XPM.xpm"
#include "Images/lsearchFrm_WxBitmapButton2_XPM.xpm"
#include "Images/lsearchFrm_WxBitmapButton1_XPM.xpm"
////Header Include End

//----------------------------------------------------------------------------
// lsearchFrm
//----------------------------------------------------------------------------
//Add Custom Events only in the appropriate block.
//Code added in other places will be removed by wxDev-C++
////Event Table Start
BEGIN_EVENT_TABLE(lsearchFrm,wxFrame)
	////Manual Code Start
	////Manual Code End
	
	EVT_CLOSE(lsearchFrm::OnClose)
	EVT_MENU(ID_MNU_REMOVE_1026 , lsearchFrm::Mnuremove1026Click)
	EVT_TIMER(ID_WXTIMER1,lsearchFrm::WxTimer1Timer)
	EVT_MENU(ID_MNU_TEST_1020 , lsearchFrm::Mnutest1020Click)
	EVT_MENU(ID_MNU_ADDTOWATCHLIST_1022 , lsearchFrm::Mnuaddtowatchlist1022Click)
	EVT_MENU(ID_MNU_COPYADDRESS_1023 , lsearchFrm::Mnucopyaddress1023Click)
	EVT_CHECKBOX(ID_WXCHECKBOX2,lsearchFrm::WxCheckBox2Click)
	EVT_BUTTON(ID_WXBUTTON3,lsearchFrm::WxButton3Click)
	
	EVT_LIST_ITEM_RIGHT_CLICK(ID_WXLISTCTRL2,lsearchFrm::WxListCtrl2RightClick)
	EVT_BUTTON(ID_WXBUTTON2,lsearchFrm::WxButton2Click)
	EVT_BUTTON(ID_WXBUTTON1,lsearchFrm::WxButton1Click)
	
	EVT_LIST_ITEM_RIGHT_CLICK(ID_WXLISTCTRL1,lsearchFrm::WxListCtrl1RightClick)
	EVT_BUTTON(ID_WXBITMAPBUTTON1,lsearchFrm::WxBitmapButton1Click)
END_EVENT_TABLE()
////Event Table End

void getdata(pid_t child, long addr,
             char *str, int len)
{   char *laddr;
    int i, j;
    union u {
            long val;
            char chars[4];
    }data;
    i = 0;
    j = len / 4;
    laddr = str;
    while(i < j) {
        data.val = ptrace(PTRACE_PEEKDATA, child,
                          addr + i * 4, NULL);
        memcpy(laddr, data.chars, 4);
        ++i;
        laddr += 4;
    }
    j = len % 4;
    if(j != 0) {
        data.val = ptrace(PTRACE_PEEKDATA, child,
                          addr + i * 4, NULL);
        memcpy(laddr, data.chars, j);
    }
    str[len] = '\0';
}

lsearchFrm::lsearchFrm(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxFrame(parent, id, title, position, size, style)
{
	CreateGUIControls();
}

lsearchFrm::~lsearchFrm()
{
}

void lsearchFrm::CreateGUIControls()
{
	//Do not add custom code between
	//GUI Items Creation Start and GUI Items Creation End
	//wxDev-C++ designer will remove them.
	//Add the custom code before or after the blocks
	////GUI Items Creation Start

	WxPanel1 = new wxPanel(this, ID_WXPANEL1, wxPoint(0,0), wxSize(515,469));
	WxPanel1->SetFont(wxFont(8, wxSWISS, wxNORMAL,wxNORMAL, false, wxT("MS Shell Dlg")));

	wxBitmap WxBitmapButton1_BITMAP (lsearchFrm_WxBitmapButton1_XPM);
	WxBitmapButton1 = new wxBitmapButton(WxPanel1, ID_WXBITMAPBUTTON1, WxBitmapButton1_BITMAP, wxPoint(5,5), wxSize(35,35), wxBU_AUTODRAW, wxDefaultValidator, wxT("WxBitmapButton1"));
	WxBitmapButton1->SetFont(wxFont(8, wxSWISS, wxNORMAL,wxNORMAL, false, wxT("MS Shell Dlg")));

	wxBitmap WxBitmapButton2_BITMAP (lsearchFrm_WxBitmapButton2_XPM);
	WxBitmapButton2 = new wxBitmapButton(WxPanel1, ID_WXBITMAPBUTTON2, WxBitmapButton2_BITMAP, wxPoint(45,5), wxSize(35,35), wxBU_AUTODRAW, wxDefaultValidator, wxT("WxBitmapButton2"));
	WxBitmapButton2->SetFont(wxFont(8, wxSWISS, wxNORMAL,wxNORMAL, false, wxT("MS Shell Dlg")));

	wxBitmap WxBitmapButton3_BITMAP (lsearchFrm_WxBitmapButton3_XPM);
	WxBitmapButton3 = new wxBitmapButton(WxPanel1, ID_WXBITMAPBUTTON3, WxBitmapButton3_BITMAP, wxPoint(85,5), wxSize(35,35), wxBU_AUTODRAW, wxDefaultValidator, wxT("WxBitmapButton3"));
	WxBitmapButton3->SetFont(wxFont(8, wxSWISS, wxNORMAL,wxNORMAL, false, wxT("MS Shell Dlg")));

	WxGauge1 = new wxGauge(WxPanel1, ID_WXGAUGE1, 100, wxPoint(139,20), wxSize(354,20), wxGA_HORIZONTAL, wxDefaultValidator, wxT("WxGauge1"));
	WxGauge1->SetRange(100);
	WxGauge1->SetValue(0);
	WxGauge1->SetFont(wxFont(8, wxSWISS, wxNORMAL,wxNORMAL, false, wxT("MS Shell Dlg")));

	WxStaticText1 = new wxStaticText(WxPanel1, ID_WXSTATICTEXT1, wxT("-"), wxPoint(138,3), wxDefaultSize, 0, wxT("WxStaticText1"));
	WxStaticText1->SetFont(wxFont(8, wxSWISS, wxNORMAL,wxNORMAL, false, wxT("MS Shell Dlg")));

	WxListCtrl1 = new wxListCtrl(WxPanel1, ID_WXLISTCTRL1, wxPoint(5,70), wxSize(188,230), wxLC_REPORT | wxLC_HRULES | wxLC_VRULES);
	WxListCtrl1->SetFont(wxFont(8, wxSWISS, wxNORMAL,wxNORMAL, false, wxT("MS Shell Dlg")));

	WxStaticText2 = new wxStaticText(WxPanel1, ID_WXSTATICTEXT2, wxT("Found: 0"), wxPoint(7,49), wxDefaultSize, 0, wxT("WxStaticText2"));
	WxStaticText2->SetFont(wxFont(8, wxSWISS, wxNORMAL,wxNORMAL, false, wxT("MS Shell Dlg")));

	WxButton1 = new wxButton(WxPanel1, ID_WXBUTTON1, wxT("First scan"), wxPoint(209,70), wxSize(90,30), 0, wxDefaultValidator, wxT("WxButton1"));
	WxButton1->Enable(false);
	WxButton1->SetFont(wxFont(8, wxSWISS, wxNORMAL,wxNORMAL, false, wxT("MS Shell Dlg")));

	WxButton2 = new wxButton(WxPanel1, ID_WXBUTTON2, wxT("Next scan"), wxPoint(314,70), wxSize(90,30), 0, wxDefaultValidator, wxT("WxButton2"));
	WxButton2->Enable(false);
	WxButton2->SetFont(wxFont(8, wxSWISS, wxNORMAL,wxNORMAL, false, wxT("MS Shell Dlg")));

	WxStaticText3 = new wxStaticText(WxPanel1, ID_WXSTATICTEXT3, wxT("Value:"), wxPoint(203,113), wxDefaultSize, 0, wxT("WxStaticText3"));
	WxStaticText3->SetFont(wxFont(8, wxSWISS, wxNORMAL,wxNORMAL, false, wxT("MS Shell Dlg")));

	WxEdit1 = new wxTextCtrl(WxPanel1, ID_WXEDIT1, wxT(""), wxPoint(257,133), wxSize(243,21), 0, wxDefaultValidator, wxT("WxEdit1"));
	WxEdit1->SetFont(wxFont(8, wxSWISS, wxNORMAL,wxNORMAL, false, wxT("MS Shell Dlg")));

	WxCheckBox1 = new wxCheckBox(WxPanel1, ID_WXCHECKBOX1, wxT("Hex"), wxPoint(200,134), wxSize(54,17), 0, wxDefaultValidator, wxT("WxCheckBox1"));
	WxCheckBox1->SetFont(wxFont(8, wxSWISS, wxNORMAL,wxNORMAL, false, wxT("MS Shell Dlg")));

	WxStaticText4 = new wxStaticText(WxPanel1, ID_WXSTATICTEXT4, wxT("Scan type:"), wxPoint(200,169), wxDefaultSize, 0, wxT("WxStaticText4"));
	WxStaticText4->SetFont(wxFont(8, wxSWISS, wxNORMAL,wxNORMAL, false, wxT("MS Shell Dlg")));

	WxStaticText5 = new wxStaticText(WxPanel1, ID_WXSTATICTEXT5, wxT("Data type:"), wxPoint(200,201), wxDefaultSize, 0, wxT("WxStaticText5"));
	WxStaticText5->SetFont(wxFont(8, wxSWISS, wxNORMAL,wxNORMAL, false, wxT("MS Shell Dlg")));

	wxArrayString arrayStringFor_WxComboBox1;
	arrayStringFor_WxComboBox1.Add(wxT("Exact value"));
	arrayStringFor_WxComboBox1.Add(wxT("Bigger than..."));
	arrayStringFor_WxComboBox1.Add(wxT("Smaller than..."));
	arrayStringFor_WxComboBox1.Add(wxT("Unknown value"));
	WxComboBox1 = new wxComboBox(WxPanel1, ID_WXCOMBOBOX1, wxT(""), wxPoint(257,164), wxSize(187,21), arrayStringFor_WxComboBox1, 0, wxDefaultValidator, wxT("WxComboBox1"));
	WxComboBox1->SetFont(wxFont(8, wxSWISS, wxNORMAL,wxNORMAL, false, wxT("MS Shell Dlg")));

	wxArrayString arrayStringFor_WxComboBox2;
	arrayStringFor_WxComboBox2.Add(wxT("1 Byte"));
	arrayStringFor_WxComboBox2.Add(wxT("2 Bytes"));
	arrayStringFor_WxComboBox2.Add(wxT("4 Bytes"));
	arrayStringFor_WxComboBox2.Add(wxT("String"));
	WxComboBox2 = new wxComboBox(WxPanel1, ID_WXCOMBOBOX2, wxT(""), wxPoint(257,196), wxSize(187,21), arrayStringFor_WxComboBox2, 0, wxDefaultValidator, wxT("WxComboBox2"));
	WxComboBox2->SetFont(wxFont(8, wxSWISS, wxNORMAL,wxNORMAL, false, wxT("MS Shell Dlg")));

	WxListCtrl2 = new wxListCtrl(WxPanel1, ID_WXLISTCTRL2, wxPoint(5,334), wxSize(504,130), wxLC_REPORT);
	WxListCtrl2->SetFont(wxFont(8, wxSWISS, wxNORMAL,wxNORMAL, false, wxT("MS Shell Dlg")));

	WxButton3 = new wxButton(WxPanel1, ID_WXBUTTON3, wxT("Reset"), wxPoint(419,70), wxSize(90,30), 0, wxDefaultValidator, wxT("WxButton3"));
	WxButton3->SetFont(wxFont(8, wxSWISS, wxNORMAL,wxNORMAL, false, wxT("MS Shell Dlg")));

	WxCheckBox2 = new wxCheckBox(WxPanel1, ID_WXCHECKBOX2, wxT("Refresh watchlist"), wxPoint(5,312), wxSize(238,13), 0, wxDefaultValidator, wxT("WxCheckBox2"));
	WxCheckBox2->SetFont(wxFont(8, wxSWISS, wxNORMAL,wxNORMAL, false, wxT("MS Shell Dlg")));

	WxPopupMenu1 = new wxMenu(wxT(""));WxPopupMenu1->Append(ID_MNU_TEST_1020, wxT("Refresh"), wxT(""), wxITEM_NORMAL);
	WxPopupMenu1->Append(ID_MNU_ADDTOWATCHLIST_1022, wxT("Add to watchlist"), wxT(""), wxITEM_NORMAL);
	WxPopupMenu1->Append(ID_MNU_COPYADDRESS_1023, wxT("Copy address"), wxT(""), wxITEM_NORMAL);

	WxTimer1 = new wxTimer();
	WxTimer1->SetOwner(this, ID_WXTIMER1);

	WxPopupMenu2 = new wxMenu(wxT(""));WxPopupMenu2->Append(ID_MNU_REMOVE_1026, wxT("Remove"), wxT(""), wxITEM_NORMAL);
	WxPopupMenu2->Append(ID_MNU_CHANGEADDRESS_1027, wxT("Change address"), wxT(""), wxITEM_NORMAL);
	WxPopupMenu2->Append(ID_MNU_CHAGEDESCRIPTION_1028, wxT("Chage description"), wxT(""), wxITEM_NORMAL);
	WxPopupMenu2->Append(ID_MNU_COPYADDRESS_1029, wxT("Copy address"), wxT(""), wxITEM_NORMAL);

	SetTitle(wxT("lsearch"));
	SetIcon(wxNullIcon);
	SetSize(8,8,523,496);
	Center();
	
	////GUI Items Creation End
	dlg_proc_selector = new procselDlg(NULL);

	WxComboBox1->SetSize(wxSize(187,25));
	WxComboBox2->SetSize(wxSize(187,25));

	//Add columns to Found list
	WxListCtrl1->InsertColumn(0, _T("Address"), wxLIST_FORMAT_LEFT, 94);
    WxListCtrl1->InsertColumn(1, _T("Value"), wxLIST_FORMAT_LEFT, 93);

	//Add columns to table list
    WxListCtrl2->InsertColumn(0, _T("Description"), wxLIST_FORMAT_LEFT, 200);
	WxListCtrl2->InsertColumn(1, _T("Address"), wxLIST_FORMAT_LEFT, 103);
    WxListCtrl2->InsertColumn(2, _T("Value"), wxLIST_FORMAT_LEFT, 100);
    WxListCtrl2->InsertColumn(3, _T("Type"), wxLIST_FORMAT_LEFT, 100);

	//Select first choice of comboboxes
	WxComboBox1->SetSelection(1, 2);

	//Create memory reading class
	mem = new Cmemutil();

	//Set progress bar to 100 max
	WxGauge1->SetRange(100);
	Wxgauge1=WxGauge1; //BAD HACK
}

void lsearchFrm::OnClose(wxCloseEvent& event)
{
	dlg_proc_selector->Destroy();
	Destroy();
}

/*
 * WxBitmapButton1Click
 */
void lsearchFrm::WxBitmapButton1Click(wxCommandEvent& event)
{
	//Open process
	wxString tmp;

	//Show selector
	dlg_proc_selector->ShowModal();

	proc_id = dlg_proc_selector->GetPID();
	proc_name = dlg_proc_selector->GetName();

	//Check if a PID was selected
	if(proc_id == 0){
		return;
	}

	//Check if the process is avaible
	if(ptrace(PTRACE_ATTACH, proc_id, NULL, NULL) == -1){
		proc_id = 0;
		proc_name = _T("");
		perror("ptrace");
		wxMessageBox(_T("Can't open selected process!\n No permissions?"), _T("Error"), wxICON_ERROR);
		WxButton1->Enable(false);
	}else{
		wait(NULL);
		ptrace(PTRACE_DETACH, proc_id, NULL, NULL);
		WxButton1->Enable(true);
	}

	//Set proc name/id label
	tmp.Printf(_T(" - %d"), proc_id);
	WxStaticText1->SetLabel(proc_name + tmp);
}

/*
 * WxListCtrl1RightClick
 */
void lsearchFrm::WxListCtrl1RightClick(wxListEvent& event)
{
	//Address list right click
	wxPoint t = wxGetMousePosition();

	PopupMenu(WxPopupMenu1, ScreenToClient(t));
}

/*
 * WxButton1Click
 */
void lsearchFrm::WxButton1Click(wxCommandEvent& event)
{
	//First scan button
	bool ret;

	//Determine scan type
	//Save: scan type, data type
	//Disable: data type combo
	//Enable: reset scan button, add more options to scan type
	//Perform scan

	scan_type = WxComboBox1->GetSelection();
	data_type = WxComboBox2->GetSelection();

	if(scan_type < 0 || data_type < 0){
		return;
	}

	if(WxEdit1->GetValue().Length() < 1){
		wxMessageBox(_T("Please enter a value to search!"), _T("Error"), wxICON_ERROR);
		return;
	}

	if(!mem->SaveMemory(proc_id)){
		wxMessageBox(_T("Error while reading memory!"), _T("Error"), wxICON_ERROR);
		return;
	}

	//Read
	switch(scan_type){
		case 0:
			//Exact value
			ret = ScanExact();
		break;

		case 1:
			//bigger than
		break;

		case 2:
			//smaller than
		break;

		case 4:
			//Unknown
		break;
	}
	
	if(!ret){
		wxMessageBox(_T("Error while reading memory!"), _T("Error"), wxICON_ERROR);
	}

	WxButton1->Enable(false);
	WxButton2->Enable(true);
	WxComboBox2->Enable(false);
}

/*
 * WxButton2Click
 */
void lsearchFrm::WxButton2Click(wxCommandEvent& event)
{
	//next scan button
	bool ret;

	scan_type = WxComboBox1->GetSelection();

	if(scan_type < 0){
		return;
	}

	//Read
	switch(scan_type){
		case 0:
			//Exact value
			ret = ReScanExact();
		break;

		case 1:
			//bigger than
		break;

		case 2:
			//smaller than
		break;

		case 4:
			//Unknown
		break;
	}

	if(!ret){
		wxMessageBox(_T("Error while reading memory!"), _T("Error"), wxICON_ERROR);
	}
}

bool lsearchFrm::ScanExact()
{
	Tfounditem res;
	wxString tstr;
	unsigned int i,t,blocksize;
	unsigned long memcount = 0;
	int addrcount = 0;
	int progress;
	char data_1, tdata_1;
	short int data_2, tdata_2;
	long data_4, tdata_4;
	string data_s;
	int slen;

	if(WxCheckBox1->IsChecked()){
		data_4 = strtoll(wxstr_to_str(WxEdit1->GetValue()).c_str(), NULL, 16); 
	}else{
		WxEdit1->GetValue().ToLong(&data_4);
	}

	data_2 = (short int) data_4;
	data_1 = (char) data_2;
	data_s = wxstr_to_str(WxEdit1->GetValue());

	res.type = data_type;

	switch(data_type){
		//Search Byte
		case 0:
		printf("Searching byte (1 byte): %i\n", data_1);
			for(i=0; i<mem->memblocks.size(); i++){

				//Unaligned search
				for(t=0; t<=mem->memblocks[i].size-1; t++){
					tdata_1 = mem->memblocks[i].data[t];
				//	memcpy(&tdata_1, &mem->memblocks[i].data[t], 1);
					memcount++;

					if(tdata_1 == data_1){
						res.data_1 = tdata_1;
						res.addr = mem->memblocks[i].start + t;
						found.push_back(res);

						addrcount++;
						//Update "Found" label
						tstr.Printf(_T("Found: %i\n"), addrcount);
						WxStaticText2->SetLabel(tstr);
						wxYield();
					}

					//Update Progress bar
					if( (t%10000) == 0){
						progress = 50 + (50 * memcount) / mem->size;
						WxGauge1->SetValue(progress);
						wxYield();
					}
				}
			}
		break;

		//Search short (2 bytes)
		case 1:
			printf("Searching short (2 bytes): %i\n", data_2);
			for(i=0; i<mem->memblocks.size(); i++){

				//Unaligned search
				for(t=0; t<=mem->memblocks[i].size-2; t++){
					memcpy(&tdata_2, &mem->memblocks[i].data[t], 2);
					memcount++;

					if(tdata_2 == data_2){
						res.data_2 = tdata_2;
						res.addr = mem->memblocks[i].start + t;
						found.push_back(res);

						addrcount++;
						//Update "Found" label
						tstr.Printf(_T("Found: %i\n"), addrcount);
						WxStaticText2->SetLabel(tstr);
						wxYield();
					}

					//Update Progress bar
					if( (t%10000) == 0){
						progress = 50 + (50 * memcount) / mem->size;
						WxGauge1->SetValue(progress);
						wxYield();
					}
				}
			}
		break;

		//Search long (4 bytes)
		case 2:
			printf("Searching long (4 bytes): %i\n", data_4);
			for(i=0; i<mem->memblocks.size(); i++){

				//Unaligned search
				for(t=0; t<=mem->memblocks[i].size-4; t++){
					memcpy(&tdata_4, &mem->memblocks[i].data[t], 4);
					memcount++;

					if(tdata_4 == data_4){
						res.data_4 = tdata_4;
						res.addr = mem->memblocks[i].start + t;
						found.push_back(res);

						addrcount++;
						//Update "Found" label
						tstr.Printf(_T("Found: %i\n"), addrcount);
						WxStaticText2->SetLabel(tstr);
						wxYield();
					}

					//Update Progress bar
					if( (t%10000) == 0){
						progress = 50 + (50 * memcount) / mem->size;
						WxGauge1->SetValue(progress);
						wxYield();
					}
				}
			}
		break;

		//Search String
		case 3:
			slen = data_s.size();
			printf("Searching string : %s %i\n", data_s.c_str(), data_s.size());
			for(i=0; i<mem->memblocks.size(); i++){

				//Unaligned search
				for(t=0; t<=mem->memblocks[i].size-slen; t++){
					memcount++;
					
					if(memcmp(&mem->memblocks[i].data[t], data_s.c_str(), slen) == 0){
						res.data_s = data_s;
						res.addr = mem->memblocks[i].start + t;
						found.push_back(res);

						addrcount++;
						//Update "Found" label
						tstr.Printf(_T("Found: %i\n"), addrcount);
						WxStaticText2->SetLabel(tstr);
						wxYield();
					}

					//Update Progress bar
					if( (t%10000) == 0){
						progress = 50 + (50 * memcount) / mem->size;
						WxGauge1->SetValue(progress);
						wxYield();
					}
				}
			}


		break;
	}

	WxGauge1->SetValue(100);
	UpdateFoundList();

	return true;
}

bool lsearchFrm::ReScanExact()
{
	Tfounditem res;
	char data_1, tdata_1;
	short int data_2, tdata_2;
	long data_4, tdata_4;
	string data_s, tdata_s;
	char buf[2048];

	WxEdit1->GetValue().ToLong(&data_4);
	data_2 = (short int) data_4;
	data_1 = (char) data_2;

	data_s = wxstr_to_str(WxEdit1->GetValue());

	vector<Tfounditem> refound;
	unsigned int i;

	//open proc and update
	if(ptrace(PTRACE_ATTACH, proc_id, NULL, NULL) == -1){
		wxMessageBox(_T("Error reading process memory!"), _T("Error"), wxICON_ERROR);
		return false;
	}
	wait(NULL);

	for(i=0; i<found.size(); i++){
		switch(found[i].type){
			//1 byte
			case 0:
				tdata_1 = (char) ptrace(PTRACE_PEEKDATA, proc_id, found[i].addr, NULL);
				if(tdata_1 == data_1){
					res.data_1 = data_1;
					res.type = found[i].type;
					res.addr = found[i].addr;
					refound.push_back(res);
				}
			break;

			//2 bytes
			case 1:
				tdata_2 = (short int) ptrace(PTRACE_PEEKDATA, proc_id, found[i].addr, NULL);
				if(tdata_2 == data_2){
					res.data_2 = data_2;
					res.type = found[i].type;
					res.addr = found[i].addr;
					refound.push_back(res);
				}
			break;

			//4 bytes
			case 2:
				tdata_4 = ptrace(PTRACE_PEEKDATA, proc_id, found[i].addr, NULL);
				if(tdata_4 == data_4){
					res.data_4 = data_4;
					res.type = found[i].type;
					res.addr = found[i].addr;
					refound.push_back(res);
				}
			break;

			char t;
			//String
			case 3:
				printf("DZ: %i\n",data_s.size());
				printf("Sarch: %s\n",data_s.c_str());
/*
				for(i=0; i<data_s.size(); i++){
					t = (char) ptrace(PTRACE_PEEKDATA, proc_id, found[i].addr+i, NULL);
					perror("ptrace");
					printf("%c ", t);
					tdata_s += t;
				}printf("\n");
*/
				getdata(proc_id, found[i].addr, buf, data_s.size());

				printf("%s %s\n",data_s.c_str(), tdata_s.c_str());
				if(memcmp(buf, data_s.c_str(), data_s.size()) == 0){
					res.data_s = data_s;
					res.type = found[i].type;
					res.addr = found[i].addr;
					refound.push_back(res);
				}
			break;

		}
	}

	ptrace(PTRACE_DETACH, proc_id, NULL, NULL);
	found = refound;
	UpdateFoundList();

	return true;
}

void lsearchFrm::UpdateFoundList()
{
	unsigned int i;
	WxListCtrl1->DeleteAllItems();

	for(i=0; i<found.size(); i++){
		WxListCtrl1->InsertItem(i, void_to_wxstr(found[i].addr));

		switch(found[i].type){
			//1 byte
			case 0:
				WxListCtrl1->SetItem(i, 1, int_to_wxstr((int)found[i].data_1));	
			break;

			//2 bytes
			case 1:
				WxListCtrl1->SetItem(i, 1, int_to_wxstr((int)found[i].data_2));				
			break;

			//4 bytes
			case 2:
				WxListCtrl1->SetItem(i, 1, int_to_wxstr(found[i].data_4));
			break;

			//String
			case 3:
				WxListCtrl1->SetItem(i, 1, str_to_wxstr(found[i].data_s));
			break;
		}
	}
}

/*
--------------------------------------------------------------------------------
					PopUp foundlist functions
--------------------------------------------------------------------------------
*/

/*
 * Mnutest1020Click
 */
void lsearchFrm::Mnutest1020Click(wxCommandEvent& event)
{
	//popup foundlist - refresh
	unsigned int i;

	//open proc and update
	if(ptrace(PTRACE_ATTACH, proc_id, NULL, NULL) == -1){
		wxMessageBox(_T("Error reading process memory!"), _T("Error"), wxICON_ERROR);
		return;
	}
	wait(NULL);

	for(i=0; i<found.size(); i++){
		switch(found[i].type){
			//1 byte
			case 0:
				found[i].data_1 = (char) ptrace(PTRACE_PEEKDATA, proc_id, found[i].addr, NULL);
			break;

			//2 bytes
			case 1:
				found[i].data_2 = (short int) ptrace(PTRACE_PEEKDATA, proc_id, found[i].addr, NULL);
			break;

			//4 bytes
			case 2:
				found[i].data_4 = ptrace(PTRACE_PEEKDATA, proc_id, found[i].addr, NULL);
			break;
		
			//TODO: String!!
		}
	}

	ptrace(PTRACE_DETACH, proc_id, NULL, NULL);

	UpdateFoundList();
}

/*
 * Mnuaddtowatchlist1022Click
 */
void lsearchFrm::Mnuaddtowatchlist1022Click(wxCommandEvent& event)
{
	//popup foundlist - Add to watch list
	wxTextEntryDialog *dlg_desc;
	dlg_desc = new wxTextEntryDialog(this, _T("Enter description:"), _T("Add to watchlist"), _T(""), wxOK | wxCENTRE, wxDefaultPosition); 
	Twatchitem t;


	long item = -1;

 	item = WxListCtrl1->GetNextItem(item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);

	if(item == -1){
		return;
	}

	t.type = found[item].type;
	t.addr = found[item].addr;
	t.data_4 = found[item].data_4;
	t.data_2 = found[item].data_2;
	t.data_1 = found[item].data_1;	
	t.data_s = found[item].data_s;

	dlg_desc->ShowModal();
	t.desc = wxstr_to_str(dlg_desc->GetValue());

	watch.push_back(t);
	UpdateWatchList();
}




/*
 * Mnucopyaddress1023Click
 */
void lsearchFrm::Mnucopyaddress1023Click(wxCommandEvent& event)
{	
	//popup foundlist - copy address
	long item = -1;
	wxString tstr;

 	item = WxListCtrl1->GetNextItem(item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
	if(item == -1){
		return;
	}

	tstr = WxListCtrl1->GetItemText(item);

	if(wxTheClipboard->Open()){
		wxTheClipboard->SetData( new wxTextDataObject(tstr) );
		wxTheClipboard->Close();
	}

}


void lsearchFrm::UpdateWatchList()
{
	unsigned int i;

	//open proc and update
	if(ptrace(PTRACE_ATTACH, proc_id, NULL, NULL) == -1){
		//wxMessageBox(_T("Error reading process memory!"), _T("Error"), wxICON_ERROR);
		return;
	}
	wait(NULL);

	WxListCtrl2->DeleteAllItems();

	for(i=0; i<watch.size(); i++){
		WxListCtrl2->InsertItem(i, str_to_wxstr(watch[i].desc));
		WxListCtrl2->SetItem(i, 1, void_to_wxstr(watch[i].addr));
		switch(watch[i].type){
			case 0:
				watch[i].data_1 = (char) ptrace(PTRACE_PEEKDATA, proc_id, watch[i].addr, NULL);
				WxListCtrl2->SetItem(i, 2, int_to_wxstr(watch[i].data_1));
				WxListCtrl2->SetItem(i, 3, _T("1 byte"));
			break;

			case 1:
				watch[i].data_2 = (short int) ptrace(PTRACE_PEEKDATA, proc_id, watch[i].addr, NULL);
				WxListCtrl2->SetItem(i, 2, int_to_wxstr(watch[i].data_2));
				WxListCtrl2->SetItem(i, 3, _T("2 bytes"));
			break;

			case 2: 
				watch[i].data_4 = ptrace(PTRACE_PEEKDATA, proc_id, watch[i].addr, NULL);
				WxListCtrl2->SetItem(i, 2, int_to_wxstr(watch[i].data_4));
				WxListCtrl2->SetItem(i, 3, _T("4 bytes"));
			break;

			//TODO: STRING!!!
		}
	}

	ptrace(PTRACE_DETACH, proc_id, NULL, NULL);
}

/*
 * WxButton3Click
 */
void lsearchFrm::WxButton3Click(wxCommandEvent& event)
{
	//reset button	
	WxButton1->Enable(true);
	WxButton2->Enable(false);
	
	WxComboBox2->Enable(true);

	WxStaticText2->SetLabel(_T("Found: 0"));
	WxGauge1->SetValue(0);
	ClearFoundList();
}

void lsearchFrm::ClearFoundList()
{
	found.clear();
	WxListCtrl1->DeleteAllItems();
}

void lsearchFrm::ClearWatchList()
{
	watch.clear();
	WxListCtrl2->DeleteAllItems();
}

/*
 * WxTimer1Timer
 */
void lsearchFrm::WxTimer1Timer(wxTimerEvent& event)
{
	//Update watchlist timer
	UpdateWatchList();
}

/*
 * WxCheckBox2Click
 */
void lsearchFrm::WxCheckBox2Click(wxCommandEvent& event)
{
	if(WxCheckBox2->IsChecked()){
		WxTimer1->Start();
	}else{
		WxTimer1->Stop();
	}

}

/*
 * WxListCtrl2RightClick
 */
void lsearchFrm::WxListCtrl2RightClick(wxListEvent& event)
{
	//watchlist popupmenu show
	//Address list right click
	wxPoint t = wxGetMousePosition();

	PopupMenu(WxPopupMenu2, ScreenToClient(t));
}

/*
 * Mnuremove1026Click
 */
void lsearchFrm::Mnuremove1026Click(wxCommandEvent& event)
{
	//watchlist popup remove address
	long item = -1;
	wxString tstr;
	vector<Twatchitem>::iterator i;
	int n=0;

 	item = WxListCtrl2->GetNextItem(item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
	if(item == -1){
		return;
	}

	for(i=watch.begin(); i<watch.end(); i++){
		if(n==item){
			watch.erase(i);
			break;
		}
		n++;
	}

	UpdateWatchList();
	
}
