/***************************************************************
 * Name:      mohr_2dMain.h
 * Purpose:   Defines Application Frame
 * Author:     ()
 * Created:   2014-02-27
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef MOHR_2DMAIN_H
#define MOHR_2DMAIN_H

//(*Headers(mohr_2dDialog)
#include <wx/checkbox.h>
#include <wx/dialog.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/panel.h>
#include <wx/slider.h>
#include "MyGLCanvas.h"
#include <wx/stattext.h>
#include <wx/textctrl.h>
//*)

class mohr_2dDialog: public wxDialog
{
    public:

        mohr_2dDialog(wxWindow* parent,wxWindowID id = -1);
        virtual ~mohr_2dDialog();

    private:

        //(*Handlers(mohr_2dDialog)
        void OnQuit(wxCommandEvent& event);
        void OnSlider1CmdScroll(wxScrollEvent& event);
        void OnbtnUpdateTensorClick(wxCommandEvent& event);
        void OnbtnResetRotClick(wxCommandEvent& event);
        void OnbtnRotEigenClick(wxCommandEvent& event);
        void OnRefresh3DViews(wxCommandEvent& event);
        void OnbtnSaveSnapClick(wxCommandEvent& event);
        void OnbtnAnimateClick(wxCommandEvent& event);
        //*)

		void updateMatrixAnd3DViews();
		void updateMatrixAnd3DViewsIndepRot();


        //(*Identifiers(mohr_2dDialog)
        static const long ID_STATICTEXT3;
        static const long ID_TEXTCTRL1;
        static const long ID_STATICTEXT4;
        static const long ID_TEXTCTRL2;
        static const long ID_STATICTEXT5;
        static const long ID_TEXTCTRL3;
        static const long ID_BUTTON1;
        static const long ID_STATICTEXT6;
        static const long ID_STATICTEXT7;
        static const long ID_STATICTEXT8;
        static const long ID_STATICTEXT9;
        static const long ID_STATICTEXT10;
        static const long ID_STATICTEXT11;
        static const long ID_STATICTEXT12;
        static const long ID_STATICTEXT13;
        static const long ID_STATICTEXT14;
        static const long ID_STATICTEXT15;
        static const long ID_STATICTEXT16;
        static const long ID_STATICTEXT17;
        static const long ID_STATICTEXT18;
        static const long ID_STATICTEXT19;
        static const long ID_STATICTEXT20;
        static const long ID_STATICTEXT21;
        static const long ID_STATICTEXT22;
        static const long ID_STATICTEXT23;
        static const long ID_STATICTEXT24;
        static const long ID_STATICTEXT25;
        static const long ID_TEXTCTRL4;
        static const long ID_STATICTEXT1;
        static const long ID_SLIDER1;
        static const long ID_STATICTEXT2;
        static const long ID_BUTTON2;
        static const long ID_BUTTON3;
        static const long ID_CHECKBOX1;
        static const long ID_CHECKBOX2;
        static const long ID_BUTTON4;
        static const long ID_BUTTON5;
        static const long ID_PANEL1;
        //*)

        //(*Declarations(mohr_2dDialog)
        wxTextCtrl* edSigmaY;
        wxStaticText* lbTr20;
        wxFlexGridSizer* FlexGridSizer1;
        wxButton* btnAnimate;
        wxStaticText* lbT21;
        wxFlexGridSizer* flexgridOpenGLs;
        wxButton* btnResetRot;
        wxStaticText* lbT01;
        wxStaticText* lbT22;
        wxStaticText* lbTr11;
        CMyGLCanvas* m_plotEllipse;
        wxCheckBox* cbFaceComponents;
        wxStaticText* lbTr01;
        CMyGLCanvas* m_plotHairy;
        wxStaticText* lbTr12;
        wxStaticText* lbT11;
        wxTextCtrl* edTauXY;
        wxStaticText* StaticText1;
        wxStaticText* lbTr02;
        CMyGLCanvas* m_plotCube;
        wxStaticText* StaticText3;
        wxStaticText* lbTr21;
        wxStaticText* lbT20;
        wxSlider* slRot;
        wxButton* btnSaveSnap;
        wxStaticText* lbTr00;
        wxStaticText* lbTr10;
        wxStaticText* lbT02;
        wxStaticText* lbRot;
        wxStaticText* lbT12;
        wxButton* btnRotEigen;
        wxStaticText* StaticText4;
        wxStaticText* StaticText5;
        wxTextCtrl* edSigmaX;
        wxStaticText* StaticText2;
        wxStaticText* lbT00;
        wxButton* btnUpdateTensor;
        wxStaticText* StaticText6;
        wxCheckBox* cbViewCompound;
        wxPanel* panelOpenGLs;
        wxStaticText* lbTr22;
        wxTextCtrl* edEigen;
        wxStaticText* lbT10;
        CMyGLCanvas* m_plotMohr;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // MOHR_2DMAIN_H
