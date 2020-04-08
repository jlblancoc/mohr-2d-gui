/* +---------------------------------------------------------------------------+
   |                     Mobile Robot Programming Toolkit (MRPT)               |
   |                          http://www.mrpt.org/                             |
   |                                                                           |
   | Copyright (c) 2005-2014, Individual contributors, see AUTHORS file        |
   | See: http://www.mrpt.org/Authors - All rights reserved.                   |
   | Released under BSD License. See details in http://www.mrpt.org/License    |
   +---------------------------------------------------------------------------+ */

#ifndef MYGLCANVAS_H
#define MYGLCANVAS_H

#include <mrpt/gui/CWxGLCanvasBase.h>

using namespace mrpt::gui;

class CMyGLCanvas : public CWxGLCanvasBase
{
public:
    CMyGLCanvas( wxWindow *parent, wxWindowID id = wxID_ANY,
                 const wxPoint& pos = wxDefaultPosition,
                 const wxSize& size = wxDefaultSize,
                 long style = 0, const wxString& name = _T("CMyGLCanvas") );

	virtual ~CMyGLCanvas();

	void OnPreRender();
	void OnPostRender();
	void OnPostRenderSwapBuffers(double At, wxPaintDC &dc);
	void OnRenderError( const wxString &str );

	virtual void OnUserManuallyMovesCamera(
		float	new_cameraPointingX,
		float 	new_cameraPointingY,
		float 	new_cameraPointingZ,
		float	new_cameraZoomDistance,
		float	new_cameraElevationDeg,
		float	new_cameraAzimuthDeg );


};

#endif // MYGLCANVAS_H

