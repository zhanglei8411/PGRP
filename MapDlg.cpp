// MapDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PGRP_20111122.h"
#include "PGRP.h"
#include "MapDlg.h"
#include <math.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMapDlg dialog


CMapDlg::CMapDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMapDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMapDlg)
	m_Circle_Radius = 0;
	m_Map_Name = _T("");
	m_Rect1_X = 0;
	m_Rect1_Y = 0;
	m_Rect2_X = 0;
	m_Rect2_Y = 0;
	m_Circle_Center_X = 0;
	m_Circle_Center_Y = 0;
	//}}AFX_DATA_INIT

//	CDialog::OnInitDialog();

//	HBITMAP hBitmap=::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(BMP_GETPOINT));
//	m_GetPoint_BmpButtom.SetBitmap(hBitmap);
}


void CMapDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMapDlg)
	DDX_Text(pDX, IDC_EDIT_Circle_Radius, m_Circle_Radius);
	DDX_Text(pDX, IDC_EDIT_Map_Name, m_Map_Name);
	DDX_Text(pDX, IDC_EDIT_Rect_LUX, m_Rect1_X);
	DDX_Text(pDX, IDC_EDIT_Rect_LUY, m_Rect1_Y);
	DDX_Text(pDX, IDC_EDIT_Rect_RDX, m_Rect2_X);
	DDX_Text(pDX, IDC_EDIT_Rect_RDY, m_Rect2_Y);
	DDX_Text(pDX, IDC_EDIT_Circle_Center_X, m_Circle_Center_X);
	DDX_Text(pDX, IDC_EDIT_Circle_Center_Y, m_Circle_Center_Y);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMapDlg, CDialog)
	//{{AFX_MSG_MAP(CMapDlg)
	ON_BN_CLICKED(IDC_MapEdit_Circle, OnMapEditCircle)
	ON_BN_CLICKED(IDC_GetPoint, OnGetPoint)
	ON_BN_CLICKED(ID_Map_Save, OnMapSave)
	ON_BN_CLICKED(IDC_BUTTON_LoadMap, OnBUTTONLoadMap)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_MapEdit_Rec, OnMapEditRec)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMapDlg message handlers

extern UT8  g_Map[MAP_WIDTH][MAP_HEIGHT];

void CMapDlg::OnMapEditCircle() 
{
	// TODO: Add your control notification handler code here
	UINT i=0,j=0;
	double Distance=0.0;
	UINT Start_X=0, Start_Y=0, End_X=0, End_Y=0;//Search Range

	UpdateData(TRUE);

	Start_X=m_Circle_Center_X-m_Circle_Radius;
	End_X=m_Circle_Center_X+m_Circle_Radius;

	Start_Y=m_Circle_Center_Y-m_Circle_Radius;
	End_Y=m_Circle_Center_Y+m_Circle_Radius;

	for (j=Start_Y;j<=End_Y;j++){
		for (i=Start_X;i<=End_X;i++){
			Distance=sqrt((i-m_Circle_Center_X)*(i-m_Circle_Center_X)+(j-m_Circle_Center_Y)*(j-m_Circle_Center_Y));
			if (Distance<=m_Circle_Radius){
				g_Map[i][j]=CELL_IS_OBSTACLE;
			}
		}
	}
	Invalidate();//Update View
}

void CMapDlg::OnGetPoint() 
{
	// TODO: Add your control notification handler code here
	
}

extern void SaveMap(CString FileName);
void CMapDlg::OnMapSave() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	SaveMap(m_Map_Name);
	MessageBox("New Map: " + m_Map_Name + " Saved", "Save File");
	UpdateData(FALSE);
}

extern CString g_Map_Name;
extern void LoadMapData(void);
void CMapDlg::OnBUTTONLoadMap() 
{
	// TODO: Add your control notification handler code here
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY,"All    files   (*.*)|*.*|| ",NULL   );
	dlg.DoModal();
	UpdateData(TRUE);
	m_Map_Name=dlg.GetFileName();
	g_Map_Name=m_Map_Name;
	LoadMapData();
	Invalidate();//Update View

	UpdateData(FALSE);
}

void CMapDlg::OnMapEditRec() 
{
	// TODO: Add your control notification handler code here
	UINT i=0,j=0;
	UINT Start_X=0, Start_Y=0, End_X=0, End_Y=0;//Search Range

	UpdateData(TRUE);

	Start_X=m_Rect1_X;
	End_X=m_Rect2_X;

	Start_Y=m_Rect1_Y;
	End_Y=m_Rect2_Y;

	for (j=Start_Y;j<=End_Y;j++){
		for (i=Start_X;i<=End_X;i++){
				g_Map[i][j]=CELL_IS_OBSTACLE;
		}
	}
	Invalidate();//Update View

}
