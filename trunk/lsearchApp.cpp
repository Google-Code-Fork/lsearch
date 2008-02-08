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
// Name:        lsearchApp.cpp
// Author:      ZioNz
// Created:     12/22/2007 10:38:06 PM
// Description: 
//
//---------------------------------------------------------------------------

#include "lsearchApp.h"
#include "lsearchFrm.h"

IMPLEMENT_APP(lsearchFrmApp)

lsearchFrm *main_frame;

bool lsearchFrmApp::OnInit()
{
    lsearchFrm* frame = new lsearchFrm(NULL);
    SetTopWindow(frame);
    frame->Show();

	main_frame = frame;
    return true;
}
 
int lsearchFrmApp::OnExit()
{
	return 0;
}
