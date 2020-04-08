/***************************************************************
 * Name:      mohr_2dApp.cpp
 * Purpose:   Code for Application Class
 * Author:     ()
 * Created:   2014-02-27
 * Copyright:  ()
 * License:
 **************************************************************/

#include "mohr_2dApp.h"

//(*AppHeaders
#include "mohr_2dMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(mohr_2dApp);

bool mohr_2dApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	mohr_2dDialog Dlg(0);
    	SetTopWindow(&Dlg);
    	Dlg.ShowModal();
    	wxsOK = false;
    }
    //*)
    return wxsOK;

}
