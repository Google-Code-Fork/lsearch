#include <iostream>
#include "wx/wx.h"

#include "wx_util.h"

using namespace std;

wxString str_to_wxstr(string t,int modo){
    if(modo=1){
        return wxString(t.c_str(),wxConvUTF7);
    }
        
    return wxString(t.c_str(),wxConvUTF8);            
}

wxString int_to_wxstr(int valor){
    wxString tmp;
    tmp.Printf(_T("%i"),valor);
    
    return tmp;
}

wxString void_to_wxstr(long mem_addr){
    string tmp;
    char buf[512];
    
    sprintf(buf,"%p",mem_addr);
    tmp=buf;
    
    return str_to_wxstr(tmp,1);
}


string wxstr_to_str(wxString s){
	char *buf;
	buf=(char*)malloc((unsigned int)s.Len() + 8);

	sprintf(buf,"%s", (const char*) wxConvCurrent->cWX2MB(s));

	string rs=buf;

	free(buf);

	return rs;
}

int wxstr_to_int(wxString s){
    long tmp;
    s.ToLong(&tmp);
    return (int)tmp;
}



