/***************************************************************
 * Name:      mohr_2dMain.cpp
 * Purpose:   Code for Application Frame
 * Author:     ()
 * Created:   2014-02-27
 * Copyright:  ()
 * License:
 **************************************************************/

#include "mohr_2dMain.h"
#include <wx/msgdlg.h>
#include <wx/textdlg.h>

//(*InternalHeaders(mohr_2dDialog)
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/settings.h>
#include <wx/string.h>
//*)

#include <mrpt/gui/WxUtils.h>
#include <mrpt/img/color_maps.h>
#include <mrpt/opengl/CArrow.h>
#include <mrpt/opengl/CAxis.h>
#include <mrpt/opengl/CBox.h>
#include <mrpt/opengl/CDisk.h>
#include <mrpt/opengl/CEllipsoid2D.h>
#include <mrpt/opengl/CPointCloud.h>
#include <mrpt/opengl/CSetOfObjects.h>
#include <mrpt/opengl/CSimpleLine.h>
#include <mrpt/opengl/CSphere.h>
#include <mrpt/opengl/CText3D.h>
#include <mrpt/opengl/stock_objects.h>

#include <Eigen/Dense>

using namespace mrpt;
using mrpt::img::TColor;
using mrpt::img::TColorf;
using namespace mrpt::poses;
using namespace mrpt::opengl;
using namespace mrpt::math;

CSetOfObjects::Ptr gl_cube_faces;
CArrow::Ptr        gl_cube_t_xf, gl_cube_t_xr;
CArrow::Ptr        gl_cube_t_yf, gl_cube_t_yr;

CSetOfObjects::Ptr gl_face_stress_total;
CSetOfObjects::Ptr gl_face_stress_components;

mrpt::opengl::CDisk::Ptr gl_mohr_C13, gl_mohr_C23, gl_mohr_C12;
mrpt::opengl::CDisk::Ptr gl_mohr_C13b, gl_mohr_C23b,
    gl_mohr_C12b;  // Circle "borders"
mrpt::opengl::CSetOfObjects::Ptr gl_mohr_pt_x, gl_mohr_pt_y, gl_mohr_pt_z;

CSetOfObjects::Ptr gl_hairy_box;
CSetOfObjects::Ptr gl_hairy_arrows;

CEllipsoid2D::Ptr  gl_ellipsoid;
CSetOfObjects::Ptr gl_ellipsoid_axis;

mrpt::math::CMatrixFixed<double, 3, 3> eVecs;
std::vector<double>                    eVals;

double W = 1.0;  // Cube width

bool isCapturing = false;

//(*IdInit(mohr_2dDialog)
const long mohr_2dDialog::ID_STATICTEXT3  = wxNewId();
const long mohr_2dDialog::ID_TEXTCTRL1    = wxNewId();
const long mohr_2dDialog::ID_STATICTEXT4  = wxNewId();
const long mohr_2dDialog::ID_TEXTCTRL2    = wxNewId();
const long mohr_2dDialog::ID_STATICTEXT5  = wxNewId();
const long mohr_2dDialog::ID_TEXTCTRL3    = wxNewId();
const long mohr_2dDialog::ID_BUTTON1      = wxNewId();
const long mohr_2dDialog::ID_STATICTEXT6  = wxNewId();
const long mohr_2dDialog::ID_STATICTEXT7  = wxNewId();
const long mohr_2dDialog::ID_STATICTEXT8  = wxNewId();
const long mohr_2dDialog::ID_STATICTEXT9  = wxNewId();
const long mohr_2dDialog::ID_STATICTEXT10 = wxNewId();
const long mohr_2dDialog::ID_STATICTEXT11 = wxNewId();
const long mohr_2dDialog::ID_STATICTEXT12 = wxNewId();
const long mohr_2dDialog::ID_STATICTEXT13 = wxNewId();
const long mohr_2dDialog::ID_STATICTEXT14 = wxNewId();
const long mohr_2dDialog::ID_STATICTEXT15 = wxNewId();
const long mohr_2dDialog::ID_STATICTEXT16 = wxNewId();
const long mohr_2dDialog::ID_STATICTEXT17 = wxNewId();
const long mohr_2dDialog::ID_STATICTEXT18 = wxNewId();
const long mohr_2dDialog::ID_STATICTEXT19 = wxNewId();
const long mohr_2dDialog::ID_STATICTEXT20 = wxNewId();
const long mohr_2dDialog::ID_STATICTEXT21 = wxNewId();
const long mohr_2dDialog::ID_STATICTEXT22 = wxNewId();
const long mohr_2dDialog::ID_STATICTEXT23 = wxNewId();
const long mohr_2dDialog::ID_STATICTEXT24 = wxNewId();
const long mohr_2dDialog::ID_STATICTEXT25 = wxNewId();
const long mohr_2dDialog::ID_TEXTCTRL4    = wxNewId();
const long mohr_2dDialog::ID_STATICTEXT1  = wxNewId();
const long mohr_2dDialog::ID_SLIDER1      = wxNewId();
const long mohr_2dDialog::ID_STATICTEXT2  = wxNewId();
const long mohr_2dDialog::ID_BUTTON2      = wxNewId();
const long mohr_2dDialog::ID_BUTTON3      = wxNewId();
const long mohr_2dDialog::ID_CHECKBOX1    = wxNewId();
const long mohr_2dDialog::ID_CHECKBOX2    = wxNewId();
const long mohr_2dDialog::ID_BUTTON4      = wxNewId();
const long mohr_2dDialog::ID_BUTTON5      = wxNewId();
const long mohr_2dDialog::ID_PANEL1       = wxNewId();
//*)

BEGIN_EVENT_TABLE(mohr_2dDialog, wxDialog)
//(*EventTable(mohr_2dDialog)
//*)
END_EVENT_TABLE()

mohr_2dDialog::mohr_2dDialog(wxWindow* parent, wxWindowID id)
{
  //(*Initialize(mohr_2dDialog)
  wxFlexGridSizer* FlexGridSizer8;
  wxGridSizer*     GridSizer1;
  wxFlexGridSizer* FlexGridSizer2;
  wxGridSizer*     GridSizer2;
  wxFlexGridSizer* FlexGridSizer7;
  wxFlexGridSizer* FlexGridSizer6;
  wxFlexGridSizer* FlexGridSizer3;
  wxFlexGridSizer* FlexGridSizer5;

  Create(
      parent, id, _("Demo: Mohr 2D"), wxDefaultPosition, wxDefaultSize,
      wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER | wxCLOSE_BOX | wxMAXIMIZE_BOX |
          wxMINIMIZE_BOX | wxMAXIMIZE | wxFRAME_SHAPED,
      _T("id"));
  FlexGridSizer1 = new wxFlexGridSizer(4, 1, 0, 0);
  FlexGridSizer1->AddGrowableCol(0);
  FlexGridSizer1->AddGrowableRow(3);
  FlexGridSizer2 = new wxFlexGridSizer(1, 4, 0, 0);
  FlexGridSizer2->AddGrowableCol(3);
  FlexGridSizer5 = new wxFlexGridSizer(4, 2, 0, 0);
  StaticText2    = new wxStaticText(
      this, ID_STATICTEXT3, _("sigma_nx="), wxDefaultPosition, wxDefaultSize, 0,
      _T("ID_STATICTEXT3"));
  FlexGridSizer5->Add(
      StaticText2, 1,
      wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 5);
  edSigmaX = new wxTextCtrl(
      this, ID_TEXTCTRL1, _("2"), wxDefaultPosition, wxDefaultSize, 0,
      wxDefaultValidator, _T("ID_TEXTCTRL1"));
  FlexGridSizer5->Add(
      edSigmaX, 1, wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL,
      5);
  StaticText3 = new wxStaticText(
      this, ID_STATICTEXT4, _("sigma_ny="), wxDefaultPosition, wxDefaultSize, 0,
      _T("ID_STATICTEXT4"));
  FlexGridSizer5->Add(
      StaticText3, 1,
      wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 5);
  edSigmaY = new wxTextCtrl(
      this, ID_TEXTCTRL2, _("3"), wxDefaultPosition, wxDefaultSize, 0,
      wxDefaultValidator, _T("ID_TEXTCTRL2"));
  FlexGridSizer5->Add(
      edSigmaY, 1, wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL,
      5);
  StaticText4 = new wxStaticText(
      this, ID_STATICTEXT5, _("tau_xy="), wxDefaultPosition, wxDefaultSize, 0,
      _T("ID_STATICTEXT5"));
  FlexGridSizer5->Add(
      StaticText4, 1,
      wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 5);
  edTauXY = new wxTextCtrl(
      this, ID_TEXTCTRL3, _("1"), wxDefaultPosition, wxDefaultSize, 0,
      wxDefaultValidator, _T("ID_TEXTCTRL3"));
  FlexGridSizer5->Add(
      edTauXY, 1, wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL,
      5);
  FlexGridSizer5->Add(
      -1, -1, 1, wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL,
      5);
  btnUpdateTensor = new wxButton(
      this, ID_BUTTON1, _("Update tensor"), wxDefaultPosition, wxDefaultSize, 0,
      wxDefaultValidator, _T("ID_BUTTON1"));
  btnUpdateTensor->SetDefault();
  FlexGridSizer5->Add(
      btnUpdateTensor, 1,
      wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 5);
  FlexGridSizer2->Add(
      FlexGridSizer5, 1,
      wxALL | wxEXPAND | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL,
      0);
  FlexGridSizer6 = new wxFlexGridSizer(1, 2, 0, 0);
  FlexGridSizer6->AddGrowableRow(0);
  StaticText5 = new wxStaticText(
      this, ID_STATICTEXT6, _("T="), wxDefaultPosition, wxDefaultSize, 0,
      _T("ID_STATICTEXT6"));
  FlexGridSizer6->Add(
      StaticText5, 1,
      wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 5);
  GridSizer1 = new wxGridSizer(3, 3, 0, 0);
  lbT00      = new wxStaticText(
      this, ID_STATICTEXT7, _("   0.000  "), wxDefaultPosition, wxDefaultSize,
      0, _T("ID_STATICTEXT7"));
  GridSizer1->Add(
      lbT00, 1, wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 5);
  lbT01 = new wxStaticText(
      this, ID_STATICTEXT8, _("0"), wxDefaultPosition, wxDefaultSize, 0,
      _T("ID_STATICTEXT8"));
  GridSizer1->Add(
      lbT01, 1, wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 5);
  lbT02 = new wxStaticText(
      this, ID_STATICTEXT9, _("0"), wxDefaultPosition, wxDefaultSize, 0,
      _T("ID_STATICTEXT9"));
  GridSizer1->Add(
      lbT02, 1, wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 5);
  lbT10 = new wxStaticText(
      this, ID_STATICTEXT10, _("0"), wxDefaultPosition, wxDefaultSize, 0,
      _T("ID_STATICTEXT10"));
  GridSizer1->Add(
      lbT10, 1, wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 5);
  lbT11 = new wxStaticText(
      this, ID_STATICTEXT11, _("0"), wxDefaultPosition, wxDefaultSize, 0,
      _T("ID_STATICTEXT11"));
  GridSizer1->Add(
      lbT11, 1, wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 5);
  lbT12 = new wxStaticText(
      this, ID_STATICTEXT12, _("0"), wxDefaultPosition, wxDefaultSize, 0,
      _T("ID_STATICTEXT12"));
  GridSizer1->Add(
      lbT12, 1, wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 5);
  lbT20 = new wxStaticText(
      this, ID_STATICTEXT13, _("0"), wxDefaultPosition, wxDefaultSize, 0,
      _T("ID_STATICTEXT13"));
  GridSizer1->Add(
      lbT20, 1, wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 5);
  lbT21 = new wxStaticText(
      this, ID_STATICTEXT14, _("0"), wxDefaultPosition, wxDefaultSize, 0,
      _T("ID_STATICTEXT14"));
  GridSizer1->Add(
      lbT21, 1, wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 5);
  lbT22 = new wxStaticText(
      this, ID_STATICTEXT15, _("0"), wxDefaultPosition, wxDefaultSize, 0,
      _T("ID_STATICTEXT15"));
  GridSizer1->Add(
      lbT22, 1, wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 5);
  FlexGridSizer6->Add(
      GridSizer1, 1,
      wxALL | wxEXPAND | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL,
      0);
  FlexGridSizer2->Add(
      FlexGridSizer6, 1,
      wxALL | wxEXPAND | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL,
      0);
  FlexGridSizer7 = new wxFlexGridSizer(1, 2, 0, 0);
  FlexGridSizer7->AddGrowableRow(0);
  StaticText6 = new wxStaticText(
      this, ID_STATICTEXT16, _("T\'="), wxDefaultPosition, wxDefaultSize, 0,
      _T("ID_STATICTEXT16"));
  FlexGridSizer7->Add(
      StaticText6, 1,
      wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 5);
  GridSizer2 = new wxGridSizer(3, 3, 0, 0);
  lbTr00     = new wxStaticText(
      this, ID_STATICTEXT17, _("   0.000  "), wxDefaultPosition, wxDefaultSize,
      0, _T("ID_STATICTEXT17"));
  GridSizer2->Add(
      lbTr00, 1, wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL,
      5);
  lbTr01 = new wxStaticText(
      this, ID_STATICTEXT18, _("0"), wxDefaultPosition, wxDefaultSize, 0,
      _T("ID_STATICTEXT18"));
  GridSizer2->Add(
      lbTr01, 1, wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL,
      5);
  lbTr02 = new wxStaticText(
      this, ID_STATICTEXT19, _("0"), wxDefaultPosition, wxDefaultSize, 0,
      _T("ID_STATICTEXT19"));
  GridSizer2->Add(
      lbTr02, 1, wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL,
      5);
  lbTr10 = new wxStaticText(
      this, ID_STATICTEXT20, _("0"), wxDefaultPosition, wxDefaultSize, 0,
      _T("ID_STATICTEXT20"));
  GridSizer2->Add(
      lbTr10, 1, wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL,
      5);
  lbTr11 = new wxStaticText(
      this, ID_STATICTEXT21, _("0"), wxDefaultPosition, wxDefaultSize, 0,
      _T("ID_STATICTEXT21"));
  GridSizer2->Add(
      lbTr11, 1, wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL,
      5);
  lbTr12 = new wxStaticText(
      this, ID_STATICTEXT22, _("0"), wxDefaultPosition, wxDefaultSize, 0,
      _T("ID_STATICTEXT22"));
  GridSizer2->Add(
      lbTr12, 1, wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL,
      5);
  lbTr20 = new wxStaticText(
      this, ID_STATICTEXT23, _("0"), wxDefaultPosition, wxDefaultSize, 0,
      _T("ID_STATICTEXT23"));
  GridSizer2->Add(
      lbTr20, 1, wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL,
      5);
  lbTr21 = new wxStaticText(
      this, ID_STATICTEXT24, _("0"), wxDefaultPosition, wxDefaultSize, 0,
      _T("ID_STATICTEXT24"));
  GridSizer2->Add(
      lbTr21, 1, wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL,
      5);
  lbTr22 = new wxStaticText(
      this, ID_STATICTEXT25, _("0"), wxDefaultPosition, wxDefaultSize, 0,
      _T("ID_STATICTEXT25"));
  GridSizer2->Add(
      lbTr22, 1, wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL,
      5);
  FlexGridSizer7->Add(
      GridSizer2, 1,
      wxALL | wxEXPAND | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL,
      0);
  FlexGridSizer2->Add(
      FlexGridSizer7, 1,
      wxALL | wxEXPAND | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL,
      0);
  edEigen = new wxTextCtrl(
      this, ID_TEXTCTRL4, wxEmptyString, wxDefaultPosition, wxDefaultSize,
      wxTE_MULTILINE | wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL4"));
  edEigen->SetMinSize(wxSize(-1, 180));
  wxFont edEigenFont = wxSystemSettings::GetFont(wxSYS_OEM_FIXED_FONT);
  if (!edEigenFont.Ok())
    edEigenFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
  edEigenFont.SetPointSize(6);
  edEigen->SetFont(edEigenFont);
  FlexGridSizer2->Add(
      edEigen, 1,
      wxALL | wxEXPAND | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL,
      5);
  FlexGridSizer1->Add(
      FlexGridSizer2, 1,
      wxALL | wxEXPAND | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL,
      0);
  FlexGridSizer3 = new wxFlexGridSizer(2, 3, 0, 0);
  StaticText1    = new wxStaticText(
      this, ID_STATICTEXT1, _("Rotation:"), wxDefaultPosition, wxDefaultSize, 0,
      _T("ID_STATICTEXT1"));
  FlexGridSizer3->Add(
      StaticText1, 1,
      wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 5);
  slRot = new wxSlider(
      this, ID_SLIDER1, 0, -3600, 3600, wxDefaultPosition, wxSize(600, 25),
      wxSL_AUTOTICKS, wxDefaultValidator, _T("ID_SLIDER1"));
  // slRot->SetTickFreq(100);
  slRot->SetPageSize(100);
  slRot->SetLineSize(100);
  slRot->SetTick(5);
  FlexGridSizer3->Add(
      slRot, 1, wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 5);
  lbRot = new wxStaticText(
      this, ID_STATICTEXT2, _("Rot_z=0 deg"), wxDefaultPosition, wxDefaultSize,
      0, _T("ID_STATICTEXT2"));
  FlexGridSizer3->Add(
      lbRot, 1, wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 5);
  btnResetRot = new wxButton(
      this, ID_BUTTON2, _("Reset"), wxDefaultPosition, wxDefaultSize, 0,
      wxDefaultValidator, _T("ID_BUTTON2"));
  FlexGridSizer3->Add(
      btnResetRot, 1,
      wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 5);
  btnRotEigen = new wxButton(
      this, ID_BUTTON3, _("Principal axes"), wxDefaultPosition, wxDefaultSize,
      0, wxDefaultValidator, _T("ID_BUTTON3"));
  FlexGridSizer3->Add(
      btnRotEigen, 1, wxALL | wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 5);
  FlexGridSizer1->Add(
      FlexGridSizer3, 1,
      wxALL | wxEXPAND | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL,
      0);
  FlexGridSizer8 = new wxFlexGridSizer(1, 6, 0, 0);
  cbViewCompound = new wxCheckBox(
      this, ID_CHECKBOX1, _("View face total stress"), wxDefaultPosition,
      wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
  cbViewCompound->SetValue(true);
  FlexGridSizer8->Add(
      cbViewCompound, 1,
      wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 5);
  cbFaceComponents = new wxCheckBox(
      this, ID_CHECKBOX2, _("View face components"), wxDefaultPosition,
      wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
  cbFaceComponents->SetValue(true);
  FlexGridSizer8->Add(
      cbFaceComponents, 1,
      wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 5);
  btnSaveSnap = new wxButton(
      this, ID_BUTTON4, _("Snapshot"), wxDefaultPosition, wxDefaultSize, 0,
      wxDefaultValidator, _T("ID_BUTTON4"));
  FlexGridSizer8->Add(
      btnSaveSnap, 1,
      wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 5);
  btnAnimate = new wxButton(
      this, ID_BUTTON5, _("Generate animation"), wxDefaultPosition,
      wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON5"));
  FlexGridSizer8->Add(
      btnAnimate, 1,
      wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 5);
  FlexGridSizer1->Add(
      FlexGridSizer8, 1,
      wxALL | wxEXPAND | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL,
      0);
  panelOpenGLs = new wxPanel(
      this, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL,
      _T("ID_PANEL1"));
  flexgridOpenGLs = new wxFlexGridSizer(2, 2, 0, 0);
  flexgridOpenGLs->AddGrowableCol(0);
  flexgridOpenGLs->AddGrowableCol(1);
  flexgridOpenGLs->AddGrowableRow(0);
  flexgridOpenGLs->AddGrowableRow(1);
  m_plotCube = new CMyGLCanvas(
      panelOpenGLs, 2000, wxDefaultPosition, wxSize(300, 250), wxTAB_TRAVERSAL,
      _T("2000"));
  flexgridOpenGLs->Add(
      m_plotCube, 1,
      wxALL | wxEXPAND | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL,
      1);
  m_plotMohr = new CMyGLCanvas(
      panelOpenGLs, 2001, wxDefaultPosition, wxSize(300, 250), wxTAB_TRAVERSAL,
      _T("2001"));
  flexgridOpenGLs->Add(
      m_plotMohr, 1,
      wxALL | wxEXPAND | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL,
      1);
  m_plotHairy = new CMyGLCanvas(
      panelOpenGLs, 2002, wxDefaultPosition, wxSize(300, 250), wxTAB_TRAVERSAL,
      _T("2002"));
  flexgridOpenGLs->Add(
      m_plotHairy, 1,
      wxALL | wxEXPAND | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL,
      1);
  m_plotEllipse = new CMyGLCanvas(
      panelOpenGLs, 2003, wxDefaultPosition, wxSize(300, 250), wxTAB_TRAVERSAL,
      _T("2003"));
  flexgridOpenGLs->Add(
      m_plotEllipse, 1,
      wxALL | wxEXPAND | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL,
      1);
  panelOpenGLs->SetSizer(flexgridOpenGLs);
  flexgridOpenGLs->Fit(panelOpenGLs);
  flexgridOpenGLs->SetSizeHints(panelOpenGLs);
  FlexGridSizer1->Add(
      panelOpenGLs, 1,
      wxALL | wxEXPAND | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL,
      0);
  SetSizer(FlexGridSizer1);
  FlexGridSizer1->Fit(this);
  FlexGridSizer1->SetSizeHints(this);
  Center();

  Connect(
      ID_BUTTON1, wxEVT_COMMAND_BUTTON_CLICKED,
      (wxObjectEventFunction)&mohr_2dDialog::OnbtnUpdateTensorClick);
  Connect(
      ID_SLIDER1, wxEVT_COMMAND_SLIDER_UPDATED,
      (wxObjectEventFunction)&mohr_2dDialog::OnSlider1CmdScroll);
  Connect(
      ID_BUTTON2, wxEVT_COMMAND_BUTTON_CLICKED,
      (wxObjectEventFunction)&mohr_2dDialog::OnbtnResetRotClick);
  Connect(
      ID_BUTTON3, wxEVT_COMMAND_BUTTON_CLICKED,
      (wxObjectEventFunction)&mohr_2dDialog::OnbtnRotEigenClick);
  Connect(
      ID_CHECKBOX1, wxEVT_COMMAND_CHECKBOX_CLICKED,
      (wxObjectEventFunction)&mohr_2dDialog::OnRefresh3DViews);
  Connect(
      ID_BUTTON4, wxEVT_COMMAND_BUTTON_CLICKED,
      (wxObjectEventFunction)&mohr_2dDialog::OnbtnSaveSnapClick);
  Connect(
      ID_BUTTON5, wxEVT_COMMAND_BUTTON_CLICKED,
      (wxObjectEventFunction)&mohr_2dDialog::OnbtnAnimateClick);
  //*)

  // Init 3D scenes:
  // ---------------------------------------

  // ===============================================
  {
    // 3D cube:
    COpenGLScene::Ptr scene = COpenGLScene::Create();

    {
      mrpt::opengl::CAxis::Ptr axis = mrpt::opengl::CAxis::Create();
      axis->setAxisLimits(-20, -20, 0, 20, 20, 0);
      axis->setLineWidth(1);
      axis->setColor(0.7, 0.7, 0.7);
      scene->insert(axis);
    }

    {
      gl_cube_faces = mrpt::opengl::CSetOfObjects::Create();

      // +-X
      {
        mrpt::opengl::CSimpleLine::Ptr obj =
            mrpt::opengl::CSimpleLine::Create(W, -W, 0, W, W, 0, 2.0f);
        obj->setColor_u8(TColor(0xff, 0x00, 0x00));
        gl_cube_faces->insert(obj);
      }
      {
        mrpt::opengl::CSimpleLine::Ptr obj =
            mrpt::opengl::CSimpleLine::Create(-W, -W, 0, -W, W, 0, 2.0f);
        obj->setColor_u8(TColor(0xff, 0x00, 0x00));
        gl_cube_faces->insert(obj);
      }

      // +-Y
      {
        mrpt::opengl::CSimpleLine::Ptr obj =
            mrpt::opengl::CSimpleLine::Create(-W, W, 0, W, W, 0, 2.0f);
        obj->setColor_u8(TColor(0x00, 0xff, 0x00));
        gl_cube_faces->insert(obj);
      }
      {
        mrpt::opengl::CSimpleLine::Ptr obj =
            mrpt::opengl::CSimpleLine::Create(-W, -W, 0, W, -W, 0, 2.0f);
        obj->setColor_u8(TColor(0x00, 0xff, 0x00));
        gl_cube_faces->insert(obj);
      }

      scene->insert(gl_cube_faces);
    }

    // Arrows for total stress on each face:
    {
      gl_face_stress_total = CSetOfObjects::Create();

      // +X
      gl_cube_t_xf = mrpt::opengl::CArrow::Create();
      gl_cube_t_xf->setColor(1, 0, 0);
      gl_cube_t_xf->setHeadRatio(0.1f);
      gl_face_stress_total->insert(gl_cube_t_xf);
      // -X
      gl_cube_t_xr = mrpt::opengl::CArrow::Create();
      gl_cube_t_xr->setColor(1, 0, 0);
      gl_cube_t_xr->setHeadRatio(0.1f);
      gl_face_stress_total->insert(gl_cube_t_xr);

      // +Y
      gl_cube_t_yf = mrpt::opengl::CArrow::Create();
      gl_cube_t_yf->setColor(0, 1, 0);
      gl_cube_t_yf->setHeadRatio(0.1f);
      gl_face_stress_total->insert(gl_cube_t_yf);
      // -Y
      gl_cube_t_yr = mrpt::opengl::CArrow::Create();
      gl_cube_t_yr->setColor(0, 1, 0);
      gl_cube_t_yr->setHeadRatio(0.1f);
      gl_face_stress_total->insert(gl_cube_t_yr);

      gl_cube_faces->insert(gl_face_stress_total);
      // scene->insert(gl_face_stress_total);
    }

    // Face stress components:
    {
      gl_face_stress_components = CSetOfObjects::Create();

      gl_cube_faces->insert(gl_face_stress_components);
    }

    scene->getViewport()->setCustomBackgroundColor(TColorf(1.0f, 1.0f, 1.0f));
    m_plotCube->setOpenGLSceneRef(scene);
    m_plotCube->setCameraProjective(false);
    m_plotCube->Refresh();
  }

  // ===============================================
  {
    // "Hairy Ball"
    COpenGLScene::Ptr scene = COpenGLScene::Create();

    if (0)
    {
      mrpt::opengl::CAxis::Ptr axis = mrpt::opengl::CAxis::Create();
      axis->setAxisLimits(-5 * W, -5 * W, 0, 5 * W, 5 * W, 0);
      axis->setLineWidth(1);
      axis->setColor(0.7, 0.7, 0.7);
      scene->insert(axis);
    }

    if (0)
    {  // 3D:
      CSphere::Ptr obj = CSphere::Create(W, 20, 20);
      obj->setColor_u8(TColor(0x00, 0x00, 0xff));  //,0x50 ) );
      scene->insert(obj);
    }
    else
    {
      // 2D:
      CDisk::Ptr obj = CDisk::Create(W, 0.9 * W);
      obj->setColor_u8(TColor(0x00, 0x00, 0xff));  //,0x50 ) );
      scene->insert(obj);
    }

    gl_hairy_box = CSetOfObjects::Create();
    {
      mrpt::opengl::CBox::Ptr obj = mrpt::opengl::CBox::Create(
          TPoint3D(-W, -W, -W), TPoint3D(W, W, W), true /*wireframe*/, 1.0f);
      obj->setColor(0.4, 0.4, 0.4, 0.8);
      gl_hairy_box->insert(obj);
    }
    {
      mrpt::opengl::CText::Ptr obj = mrpt::opengl::CText::Create("X");
      obj->setColor(0.4, 0.4, 0.4, 0.8);
      obj->setLocation(1.05, 0.0, 0.0);
      gl_hairy_box->insert(obj);
    }
    {
      mrpt::opengl::CText::Ptr obj = mrpt::opengl::CText::Create("Y");
      obj->setColor(0.4, 0.4, 0.4, 0.8);
      obj->setLocation(0.0, 1.05, 0.0);
      gl_hairy_box->insert(obj);
    }
    scene->insert(gl_hairy_box);

    gl_hairy_arrows = mrpt::opengl::CSetOfObjects::Create();
    scene->insert(gl_hairy_arrows);

    scene->getViewport()->setCustomBackgroundColor(TColorf(1.0f, 1.0f, 1.0f));
    m_plotHairy->setOpenGLSceneRef(scene);
    m_plotHairy->setCameraProjective(false);
    m_plotHairy->setZoomDistance(3);
    m_plotHairy->Refresh();
  }

  // ===============================================
  {
    // Mohr circles:
    mrpt::opengl::COpenGLScene::Ptr scene =
        mrpt::opengl::COpenGLScene::Create();

    // Circles BEHIND (first) the axis, to emulate the "holes" with white
    // circles: 13:
    gl_mohr_C13 = CDisk::Create(1.0, 0.0);
    gl_mohr_C13->setColor(0.6, 0.6, 0.6);
    scene->insert(gl_mohr_C13);
    //
    gl_mohr_C13b = CDisk::Create(1.0, 0.99);
    gl_mohr_C13b->setColor(0, 0, 0);
    scene->insert(gl_mohr_C13b);

    // 23:
    gl_mohr_C23 = CDisk::Create(1.0, 0.0);
    gl_mohr_C23->setColor(1.0, 1.0, 1.0);
    scene->insert(gl_mohr_C23);
    //
    gl_mohr_C23b = CDisk::Create(1.0, 0.99);
    gl_mohr_C23b->setColor(0, 0, 0);
    scene->insert(gl_mohr_C23b);

    // 12:
    gl_mohr_C12 = CDisk::Create(1.0, 0.0);
    gl_mohr_C12->setColor(1.0, 1.0, 1.0);
    scene->insert(gl_mohr_C12);
    //
    gl_mohr_C12b = CDisk::Create(1.0, 0.99);
    gl_mohr_C12b->setColor(0, 0, 0);
    scene->insert(gl_mohr_C12b);

    // Points for each face:
    {
      gl_mohr_pt_x                       = CSetOfObjects::Create();
      mrpt::opengl::CPointCloud::Ptr obj = mrpt::opengl::CPointCloud::Create();
      obj->insertPoint(0, 0, 0);
      obj->setPointSize(10);
      obj->setColor(1, 0, 0);
      gl_mohr_pt_x->insert(obj);

      mrpt::opengl::CText3D::Ptr txt = mrpt::opengl::CText3D::Create();
      txt->setString(" X");
      txt->setScale(0.2);
      txt->setColor(1, 0, 0);
      gl_mohr_pt_x->insert(txt);
      scene->insert(gl_mohr_pt_x);
    }

    {
      gl_mohr_pt_y                       = CSetOfObjects::Create();
      mrpt::opengl::CPointCloud::Ptr obj = mrpt::opengl::CPointCloud::Create();
      obj->insertPoint(0, 0, 0);
      obj->setPointSize(10);
      obj->setColor(0, 1, 0);
      gl_mohr_pt_y->insert(obj);

      mrpt::opengl::CText3D::Ptr txt = mrpt::opengl::CText3D::Create();
      txt->setString(" Y");
      txt->setScale(0.2);
      txt->setColor(0, 1, 0);
      gl_mohr_pt_y->insert(txt);
      scene->insert(gl_mohr_pt_y);
    }

    {
      gl_mohr_pt_z                       = CSetOfObjects::Create();
      mrpt::opengl::CPointCloud::Ptr obj = mrpt::opengl::CPointCloud::Create();
      obj->insertPoint(0, 0, 0);
      obj->setPointSize(10);
      obj->setColor(0, 0, 1);
      gl_mohr_pt_z->insert(obj);

      mrpt::opengl::CText3D::Ptr txt = mrpt::opengl::CText3D::Create();
      txt->setString(" Z");
      txt->setScale(0.2);
      txt->setColor(0, 0, 1);
      gl_mohr_pt_z->insert(txt);
      scene->insert(gl_mohr_pt_z);
    }

    {
      mrpt::opengl::CAxis::Ptr axis = mrpt::opengl::CAxis::Create();
      axis->setAxisLimits(-20, -20, 0, 20, 20, 0);
      axis->setColor_u8(TColor(0x00, 0x00, 0x00));
      axis->enableTickMarks();
      axis->setFrequency(1.0f);
      axis->setLineWidth(1);
      scene->insert(axis);
    }

    scene->getViewport()->setCustomBackgroundColor(TColorf(1.0f, 1.0f, 1.0f));
    m_plotMohr->setOpenGLSceneRef(scene);
    m_plotMohr->setCameraProjective(false);
    m_plotMohr->Refresh();
  }

  // ===============================================
  {
    // "Ellipsoid"
    COpenGLScene::Ptr scene = COpenGLScene::Create();

    {
      mrpt::opengl::CAxis::Ptr axis = mrpt::opengl::CAxis::Create();
      axis->setAxisLimits(-5 * W, -5 * W, 0, 5 * W, 5 * W, 0);
      axis->setLineWidth(1);
      axis->setColor(0.7, 0.7, 0.7);
      scene->insert(axis);
    }

    gl_ellipsoid = CEllipsoid2D::Create();
    gl_ellipsoid->set2DsegmentsCount(100);
    gl_ellipsoid->setColor(0, 0, 1, 0.6);
    scene->insert(gl_ellipsoid);

    gl_ellipsoid_axis = mrpt::opengl::stock_objects::CornerXYZSimple(1, 3);
    scene->insert(gl_ellipsoid_axis);

    scene->getViewport()->setCustomBackgroundColor(TColorf(1.0f, 1.0f, 1.0f));
    m_plotEllipse->setOpenGLSceneRef(scene);
    m_plotEllipse->setCameraProjective(false);
    m_plotEllipse->setZoomDistance(5);
    m_plotEllipse->Refresh();
  }

  updateMatrixAnd3DViewsIndepRot();
  updateMatrixAnd3DViews();
}

mohr_2dDialog::~mohr_2dDialog()
{
  //(*Destroy(mohr_2dDialog)
  //*)
}

void mohr_2dDialog::OnQuit(wxCommandEvent& event) { Close(); }

void mohr_2dDialog::OnSlider1CmdScroll(wxScrollEvent& event)
{
  this->updateMatrixAnd3DViews();
}

// =========================================================================
CMyGLCanvas::CMyGLCanvas(
    wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size,
    long style, const wxString& name)
    : CWxGLCanvasBase(parent, id, pos, size, style, name)
{
  CamaraParams c = cameraParams();

  c.cameraPointingX    = 0;
  c.cameraPointingY    = 0;
  c.cameraPointingZ    = 0;
  c.cameraZoomDistance = 20;
  c.cameraElevationDeg = 90;
  c.cameraAzimuthDeg   = -90;
  c.cameraIsProjective = true;

  setCameraParams(c);
}

CMyGLCanvas::~CMyGLCanvas() {}

void CMyGLCanvas::OnRenderError(const wxString& str) {}

void CMyGLCanvas::OnPreRender()
{
  mrpt::opengl::COpenGLViewport::Ptr gl_view =
      getOpenGLSceneRef()->getViewport("small-view");
  if (gl_view)
  {
    mrpt::opengl::CCamera& view_cam = gl_view->getCamera();

    view_cam.setAzimuthDegrees(this->getAzimuthDegrees());
    view_cam.setElevationDegrees(this->getElevationDegrees());
    view_cam.setZoomDistance(4);
  }
}

void CMyGLCanvas::OnPostRenderSwapBuffers(double At, wxPaintDC& dc) {}

void CMyGLCanvas::OnPostRender()
{
  // Show credits on the screen? renderTextBitmap(20, 20, "" );
}

void CMyGLCanvas::OnUserManuallyMovesCamera(
    float new_cameraPointingX, float new_cameraPointingY,
    float new_cameraPointingZ, float new_cameraZoomDistance,
    float new_cameraElevationDeg, float new_cameraAzimuthDeg)
{
  switch (this->GetId())
  {
    case 2000:  // mohr_2dDialog::ID_GLCANVAS_CUBE:
      setZoomDistance(new_cameraZoomDistance);
      break;

    case 2001:  // mohr_2dDialog::ID_GLCANVAS_MOHR
      setCameraPointing(
          new_cameraPointingX, new_cameraPointingY, getCameraPointingZ());
      setZoomDistance(new_cameraZoomDistance);
      break;

    default:
      setCameraPointing(
          new_cameraPointingX, new_cameraPointingY, new_cameraPointingZ);
      setZoomDistance(new_cameraZoomDistance);
      setAzimuthDegrees(new_cameraElevationDeg);
      setElevationDegrees(new_cameraAzimuthDeg);
      break;
  };
}

void mohr_2dDialog::OnbtnUpdateTensorClick(wxCommandEvent& event)
{
  updateMatrixAnd3DViewsIndepRot();
  // updateMatrixAnd3DViews();
}

void mohr_2dDialog::updateMatrixAnd3DViewsIndepRot()
{
  double t_xx = 0, t_yy = 0, t_xy = 0;

  this->edSigmaX->GetValue().ToDouble(&t_xx);
  this->edSigmaY->GetValue().ToDouble(&t_yy);
  this->edTauXY->GetValue().ToDouble(&t_xy);

  // Fill tensor:
  mrpt::math::CMatrixFixed<double, 3, 3> tensor;
  tensor.setZero();
  tensor(0, 0) = t_xx;
  tensor(0, 1) = t_xy;
  tensor(1, 0) = t_xy;
  tensor(1, 1) = t_yy;

  // Set in text:
  lbT00->SetLabel(wxString::Format(_("%.03f"), tensor(0, 0)));
  lbT01->SetLabel(wxString::Format(_("%.03f"), tensor(0, 1)));
  lbT02->SetLabel(wxString::Format(_("%.03f"), tensor(0, 2)));
  lbT10->SetLabel(wxString::Format(_("%.03f"), tensor(1, 0)));
  lbT11->SetLabel(wxString::Format(_("%.03f"), tensor(1, 1)));
  lbT12->SetLabel(wxString::Format(_("%.03f"), tensor(1, 2)));
  lbT20->SetLabel(wxString::Format(_("%.03f"), tensor(2, 0)));
  lbT21->SetLabel(wxString::Format(_("%.03f"), tensor(2, 1)));
  lbT22->SetLabel(wxString::Format(_("%.03f"), tensor(2, 2)));

  // eigen:
  tensor.eig(eVecs, eVals);

  CPose3D eigenPos;
  eigenPos.setRotationMatrix(eVecs);

  // eigen report:
  {
    wxString s;
    s += wxString::Format(_("Principal stress values:\n"));
    for (int i = 0; i < 3; i++)
      s += wxString::Format(_(" s_%i = %6.03f\n"), i + 1, eVals[2 - i]);

    s += wxString::Format(
        _("Principal axes: (ang_z=%5.02fdeg, ang_y=%5.02fdeg, "
          "ang_x=%5.02fdeg)\n"),
        RAD2DEG(eigenPos.yaw()), RAD2DEG(eigenPos.pitch()),
        RAD2DEG(eigenPos.roll()));
    for (int i = 0; i < 3; i++)
      s += wxString::Format(
          _(" axis_%i = [%6.03f,%6.03f,%6.03f] ang_x=%5.02fdeg, "
            "ang_y=%5.02fdeg, ang_z=%5.02fdeg\n"),
          i + 1, eVecs(0, 2 - i), eVecs(1, 2 - i), eVecs(2, 2 - i),
          RAD2DEG(acos(eVecs(0, 2 - i))) * sign(eVecs(1, 2 - i)),
          RAD2DEG(acos(eVecs(1, 2 - i))), RAD2DEG(acos(eVecs(2, 2 - i))));
    edEigen->SetValue(s);
  }

  // Update hairy ball arrows:
  // ----------------------------
  gl_hairy_arrows->clear();

  std::multimap<double, CArrow*> lstArrows;  // module -> Arrows

  const double ARROW_LEN = 0.3;

  double pitch = 0;
  for (double yaw = -M_PI; yaw < M_PI; yaw += M_PI * 2 / 40)
  {
    const mrpt::poses::CPose3D posNormal(0, 0, 0, yaw, pitch, 0.0);
    // const mrpt::math::CMatrixDouble33 ROT =
    // mrpt::poses::CPose3D(0,0,0,yaw,pitch,0.0).getRotationMatrix();
    // Rotate tensor:
    // const Eigen::Matrix<double,3,3> tensor_rot = ROT * tensor *
    // ROT.transpose();

    const Eigen::Vector3d normal =
        posNormal.getRotationMatrix().transpose().block<3, 1>(0, 0);

    Eigen::Vector3d stress_vec = tensor.asEigen() * normal;

    const double stress_mod        = stress_vec.norm();
    const double normal_stress_val = stress_vec.dot(normal);
    const bool   is_outwards       = normal_stress_val >= 0;

    Eigen::Vector3d stress_vec_n = ARROW_LEN * stress_vec / stress_mod;
    TPoint3D        arrow(stress_vec_n[0], stress_vec_n[1], stress_vec_n[2]);

    TPoint3D pt(W * normal[0], W * normal[1], W * normal[2]);

    TPoint3D arrow0, arrow1;
    if (is_outwards)
    {
      arrow0 = pt;
      arrow1 = pt + arrow;
    }
    else
    {
      arrow0 = pt - arrow;
      arrow1 = pt;
    }

    CArrow::Ptr gl_arrow = CArrow::Create(
        arrow0.x, arrow0.y, arrow0.z, arrow1.x, arrow1.y, arrow1.z, 0.3, 0.01,
        0.03);

    lstArrows.insert(
        std::pair<double, CArrow*>(normal_stress_val, gl_arrow.get()));
    gl_hairy_arrows->insert(gl_arrow);
  }

  // Color map:
  const double maxMod  = lstArrows.rbegin()->first;
  double       minMod  = lstArrows.begin()->first;
  const double minSpan = 0.1 * std::max(std::abs(maxMod), std::abs(minMod));
  double       _s      = 1.0 / std::max(maxMod - minMod, minSpan);
  minMod -= 0.2 / _s;
  _s /= 1.5;

  for (std::multimap<double, CArrow*>::iterator it = lstArrows.begin();
       it != lstArrows.end(); ++it)
  {
    const double normVal = (it->first - minMod) * _s;
    float        r, g, b;
    mrpt::img::colormap(mrpt::img::cmGRAYSCALE, normVal, r, g, b);
    it->second->setColor(r, g, b);
  }

  m_plotHairy->Refresh(false);

  // Update ellipse view:
  // ----------------------------
  {
    // Create def. pos. ellipsoid:
    Eigen::Matrix<double, 3, 3> diag_eVals;
    diag_eVals.setZero();
    double maxEval = 0.0;
    for (int i = 0; i < 3; i++)
      maxEval = std::max(maxEval, std::sqrt(std::abs(eVals[i])));

    for (int i = 0; i < 3; i++)
      diag_eVals(i, i) = std::max(1e-9, std::abs(eVals[i]) / square(maxEval));

    const Eigen::Matrix<double, 3, 3> pos_tensor =
        eVecs.asEigen() * diag_eVals * eVecs.asEigen().transpose();
    auto cov22 = mrpt::math::CMatrixDouble22(pos_tensor.block<2, 2>(0, 0));
    gl_ellipsoid->setCovMatrix(cov22);
  }
  m_plotEllipse->Refresh(false);
}

void mohr_2dDialog::updateMatrixAnd3DViews()
{
  // Visible/invisible:
  gl_face_stress_total->setVisibility(cbViewCompound->GetValue());
  gl_face_stress_components->setVisibility(cbFaceComponents->GetValue());

  // Tensor:
  double t_xx = 0, t_yy = 0, t_xy = 0;

  this->edSigmaX->GetValue().ToDouble(&t_xx);
  this->edSigmaY->GetValue().ToDouble(&t_yy);
  this->edTauXY->GetValue().ToDouble(&t_xy);

  // Fill tensor:
  mrpt::math::CMatrixFixed<double, 3, 3> tensor;
  tensor.setZero();
  tensor(0, 0) = t_xx;
  tensor(0, 1) = t_xy;
  tensor(1, 0) = t_xy;
  tensor(1, 1) = t_yy;

  // Rotation matrix:
  double rot_x = 0;
  double rot_y = 0;
  double rot_z = slRot->GetValue() * 0.1;

  lbRot->SetLabel(wxString::Format(wxT("Rot_z=%.02f deg"), rot_z));

  const Eigen::Matrix3d ROT =
      mrpt::poses::CPose3D(
          0, 0, 0, DEG2RAD(rot_z), DEG2RAD(rot_y), DEG2RAD(rot_x))
          .getRotationMatrix()
          .transpose();

  // Rotate tensor:
  const Eigen::Matrix3d tensor_rot = ROT * tensor.asEigen() * ROT.transpose();

  // Intrinsic components:
  const double snx = tensor_rot(0, 0);
  const double tangx =
      std::sqrt(square(tensor_rot.block<3, 1>(0, 0).norm()) - snx * snx);

  const double sny = tensor_rot(1, 1);
  const double tangy =
      std::sqrt(square(tensor_rot.block<3, 1>(0, 1).norm()) - sny * sny);

  const double snz = tensor_rot(2, 2);
  const double tangz =
      std::sqrt(square(tensor_rot.block<3, 1>(0, 2).norm()) - snz * snz);

  // Set in text:
  lbTr00->SetLabel(wxString::Format(_("%.03f"), tensor_rot(0, 0)));
  lbTr01->SetLabel(wxString::Format(_("%.03f"), tensor_rot(0, 1)));
  lbTr02->SetLabel(wxString::Format(_("%.03f"), tensor_rot(0, 2)));
  lbTr10->SetLabel(wxString::Format(_("%.03f"), tensor_rot(1, 0)));
  lbTr11->SetLabel(wxString::Format(_("%.03f"), tensor_rot(1, 1)));
  lbTr12->SetLabel(wxString::Format(_("%.03f"), tensor_rot(1, 2)));
  lbTr20->SetLabel(wxString::Format(_("%.03f"), tensor_rot(2, 0)));
  lbTr21->SetLabel(wxString::Format(_("%.03f"), tensor_rot(2, 1)));
  lbTr22->SetLabel(wxString::Format(_("%.03f"), tensor_rot(2, 2)));

  // FlexGridSizer1->Fit(this);

  // Update cube view:
  const TPose3D cubePose(
      0, 0, 0, DEG2RAD(rot_z), DEG2RAD(rot_y), DEG2RAD(rot_x));
  gl_cube_faces->setPose(cubePose);

  const double tensor_scale =
      2.0 / std::max(0.0, tensor.array().abs().maxCoeff());

  {
    // X faces
    TPoint3D pt(W, 0, 0);
    TPoint3D arrow(tensor_rot(0, 0), tensor_rot(0, 1), tensor_rot(0, 2));
    arrow *= tensor_scale;
    TPoint3D arrow0, arrow1;
    if (tensor_rot(0, 0) >= 0)
    {
      arrow0 = pt;
      arrow1 = pt + arrow;
    }
    else
    {
      arrow0 = pt - arrow;
      arrow1 = pt;
    }

    gl_cube_t_xf->setArrowEnds(
        arrow0.x, arrow0.y, arrow0.z, arrow1.x, arrow1.y, arrow1.z);
    gl_cube_t_xr->setArrowEnds(
        -arrow0.x, -arrow0.y, -arrow0.z, -arrow1.x, -arrow1.y, -arrow1.z);
  }

  {
    // Y faces
    TPoint3D pt(0, W, 0);
    TPoint3D arrow(tensor_rot(1, 0), tensor_rot(1, 1), tensor_rot(1, 2));
    arrow *= tensor_scale;
    TPoint3D arrow0, arrow1;
    if (tensor_rot(1, 1) >= 0)
    {
      arrow0 = pt;
      arrow1 = pt + arrow;
    }
    else
    {
      arrow0 = pt - arrow;
      arrow1 = pt;
    }

    gl_cube_t_yf->setArrowEnds(
        arrow0.x, arrow0.y, arrow0.z, arrow1.x, arrow1.y, arrow1.z);
    gl_cube_t_yr->setArrowEnds(
        -arrow0.x, -arrow0.y, -arrow0.z, -arrow1.x, -arrow1.y, -arrow1.z);
  }

  m_plotCube->Refresh(false);

  // Update Mohr view:
  // ----------------------------
  // eigen:
  tensor.eig(eVecs, eVals);

  // CPose3D eigenPos; eigenPos.setRotationMatrix(eVecs.transpose());
  // s+= wxString::Format(_(" s_1 = %6.03f\n"), eVals[2] );
  // s+= wxString::Format(_(" s_2 = %6.03f\n"), eVals[1] );
  // s+= wxString::Format(_(" s_3 = %6.03f\n"), eVals[0] );

  const double C13_center = 0.5 * (eVals[2] + eVals[0]);
  const double C13_radius = 0.5 * (eVals[2] - eVals[0]);

  const double C12_center = 0.5 * (eVals[1] + eVals[0]);
  const double C12_radius = 0.5 * (eVals[1] - eVals[0]);

  const double C23_center = 0.5 * (eVals[2] + eVals[1]);
  const double C23_radius = 0.5 * (eVals[2] - eVals[1]);

  gl_mohr_C13->setLocation(C13_center, 0, 0);
  gl_mohr_C13b->setLocation(C13_center, 0, 0);
  gl_mohr_C13->setDiskRadius(C13_radius, 0);
  gl_mohr_C13b->setDiskRadius(
      C13_radius, C13_radius - std::max(0.01, 0.01 * C13_radius));

  gl_mohr_C12->setLocation(C12_center, 0, 0);
  gl_mohr_C12b->setLocation(C12_center, 0, 0);
  gl_mohr_C12->setDiskRadius(C12_radius, 0);
  gl_mohr_C12b->setDiskRadius(
      C12_radius, C12_radius - std::max(0.01, 0.01 * C12_radius));

  gl_mohr_C23->setLocation(C23_center, 0, 0);
  gl_mohr_C23b->setLocation(C23_center, 0, 0);
  gl_mohr_C23->setDiskRadius(C23_radius, 0);
  gl_mohr_C23b->setDiskRadius(
      C23_radius, C23_radius - std::max(0.01, 0.01 * C23_radius));

  // Mohr points:
  gl_mohr_pt_x->setLocation(snx, -tangx, 0.01);
  gl_mohr_pt_y->setLocation(sny, tangy, 0.01);
  gl_mohr_pt_z->setLocation(snz, tangz, 0.01);

  gl_mohr_pt_x->setScale(C13_radius);
  gl_mohr_pt_y->setScale(C13_radius);
  gl_mohr_pt_z->setScale(C13_radius);

  m_plotMohr->Refresh(false);

  // Update "Hairy ball" view:
  // ----------------------------
  gl_hairy_box->setPose(cubePose);
  m_plotHairy->Refresh(false);

  // Update ellipse view:
  // ----------------------------
  gl_ellipsoid_axis->setPose(cubePose);
  m_plotEllipse->Refresh(false);
}

void mohr_2dDialog::OnbtnResetRotClick(wxCommandEvent& event)
{
  slRot->SetValue(0);
  updateMatrixAnd3DViews();
}

void mohr_2dDialog::OnbtnRotEigenClick(wxCommandEvent& event) {}

void mohr_2dDialog::OnRefresh3DViews(wxCommandEvent& event)
{
  updateMatrixAnd3DViews();
}

void mohr_2dDialog::OnbtnSaveSnapClick(wxCommandEvent& event)
{
  isCapturing = true;
  this->Refresh(true);

  // Create a DC for the whole screen area
  wxClientDC dcScreen(panelOpenGLs);

  // Get the size of the screen/DC
  wxCoord screenWidth, screenHeight;
  dcScreen.GetSize(&screenWidth, &screenHeight);

  // Create a Bitmap that will later on hold the screenshot image
  // Note that the Bitmap must have a size big enough to hold the screenshot
  //-1 means using the current default colour depth
  wxBitmap screenshot(screenWidth, screenHeight, -1);

  // Create a memory DC that will be used for actually taking the screenshot
  wxMemoryDC memDC;
  // Tell the memory DC to use our Bitmap
  // all drawing action on the memory DC will go to the Bitmap now
  memDC.SelectObject(screenshot);
  // Blit (in this case copy) the actual screen on the memory DC
  // and thus the Bitmap
  memDC.Blit(
      0,  // Copy to this X coordinate
      0,  // Copy to this Y coordinate
      screenWidth,  // Copy this width
      screenHeight,  // Copy this height
      &dcScreen,  // From where do we copy?
      0,  // What's the X offset in the original DC?
      0  // What's the Y offset in the original DC?
  );
  // Select the Bitmap out of the memory DC by selecting a new
  // uninitialized Bitmap
  memDC.SelectObject(wxNullBitmap);

  static int cnt = 0;
  screenshot.SaveFile(
      mrpt::format("screenshot_%04i.png", cnt++).c_str(), wxBITMAP_TYPE_PNG);
}

void mohr_2dDialog::OnbtnAnimateClick(wxCommandEvent& event)
{
  wxString sRotStart =
      ::wxGetTextFromUser(_("Start rotation (deg):"), _("Animation"), _("0"));
  wxString sRotEnd =
      ::wxGetTextFromUser(_("End rotation (deg):"), _("Animation"), _("0"));
  wxString sSteps = ::wxGetTextFromUser(_("Steps:"), _("Animation"), _("100"));

  double ang0, ang1;
  long   nSteps;
  sRotStart.ToDouble(&ang0);
  sRotEnd.ToDouble(&ang1);
  sSteps.ToLong(&nSteps);

  double ang   = ang0;
  double A_ang = (ang1 - ang0) / nSteps;

  wxCommandEvent ev;

  for (long i = 0; i < nSteps; i++)
  {
    slRot->SetValue(10 * ang);
    updateMatrixAnd3DViews();
    ::wxSafeYield();
    OnbtnSaveSnapClick(ev);
    ang += A_ang;
  }
}
