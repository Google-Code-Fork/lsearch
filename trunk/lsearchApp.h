//---------------------------------------------------------------------------
//
// Name:        lsearchApp.h
// Author:      ZioNz
// Created:     12/22/2007 10:38:06 PM
// Description: 
//
//---------------------------------------------------------------------------

#ifndef __LSEARCHFRMApp_h__
#define __LSEARCHFRMApp_h__

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
#else
	#include <wx/wxprec.h>
#endif

class lsearchFrmApp : public wxApp
{
	public:
		bool OnInit();
		int OnExit();
};

#endif
