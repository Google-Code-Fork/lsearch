#ifndef _wx_util_H
#define	_wx_util_H

#include <iostream>
#include "wx/wx.h"

using namespace std;

wxString str_to_wxstr(string t,int modo=1);
wxString void_to_wxstr(long mem_addr);
wxString int_to_wxstr(int valor);

string wxstr_to_str(wxString s);
int wxstr_to_int(wxString s);


#endif

