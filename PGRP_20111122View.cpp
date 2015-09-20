// PGRP_20111122View.cpp : implementation of the CPGRP_20111122View class
//

#include "stdafx.h"
#include "PGRP_20111122.h"
#include "PGRP_20111122Doc.h"
#include "PGRP_20111122View.h"
#include "InitParaDlg.h"
#include "ResultInfoDlg.h"
#include "MapDlg.h"
#include "PGRP.h"
#include "windows.h"
#include <iostream>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPGRP_20111122View

IMPLEMENT_DYNCREATE(CPGRP_20111122View, CView)

BEGIN_MESSAGE_MAP(CPGRP_20111122View, CView)
	//{{AFX_MSG_MAP(CPGRP_20111122View)
	ON_COMMAND(IDC_PGRP_Init, OnPGRPInit)
	ON_COMMAND(IDC_PGRP_Run, OnPGRPRun)
	ON_COMMAND(ID_Menu_Show_Result, OnMenuShowResult)
	ON_WM_CHAR()
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_Map_Custom, OnMapCustom)
	ON_COMMAND(ID_PGRP_Calculation_Flag, OnPGRPCalculationFlag)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPGRP_20111122View construction/destruction

CPGRP_20111122View::CPGRP_20111122View()
{
	// TODO: add construction code here
	g_Init_Start_X=0;
	g_Init_Start_Y=0;
	g_Init_Target_X=100;
	g_Init_Target_Y=100;
	m_Calculation_Flag=NOTCALCULATE;

}

CPGRP_20111122View::~CPGRP_20111122View()
{
}

BOOL CPGRP_20111122View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CPGRP_20111122View drawing
extern UT8  g_Map[MAP_WIDTH][MAP_HEIGHT];

void CPGRP_20111122View::OnDraw(CDC* pDC)
{
	CPGRP_20111122Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	UINT i=0,j=0;
	for (i=1;i<MAP_WIDTH;i++){
		for (j=1;j<MAP_HEIGHT;j++){
			BITMAP bitmap;
			CBitmap bm;
			if (g_Map[i][j]==CELL_IS_BLANK)
				bm.LoadBitmap(BMP_BLANK);
			else if (g_Map[i][j]==CELL_IS_OBSTACLE)
				bm.LoadBitmap(BMP_OBSTACLE);
			else if (g_Map[i][j]==CELL_IS_PLANT_BUD)
				bm.LoadBitmap(BMP_BUD);
			else if (g_Map[i][j]==CELL_IS_PLANT_STEM)
				bm.LoadBitmap(BMP_STEM);
			else if (g_Map[i][j]==CELL_IS_START)
				bm.LoadBitmap(BMP_START);
			else if (g_Map[i][j]==CELL_IS_TARGET)
				bm.LoadBitmap(BMP_TARGET);
			else if (g_Map[i][j]==CELL_IS_PATH)
				bm.LoadBitmap(BMP_PATH);
			else if (g_Map[i][j]==CELL_IS_DEAD_BUD)
				bm.LoadBitmap(BMP_DEADBUD);
			bm.GetBitmap(&bitmap);
			CDC dcMem;
			dcMem.CreateCompatibleDC(pDC);
			dcMem.SelectObject(&bm);
			pDC->BitBlt(i*8-8,j*8-8,8,8,&dcMem,0,0,SRCCOPY);
	
			//pDC->Rectangle(i*5,j*5,i*5+5,j*5+5);
		}
	}
	
}

/////////////////////////////////////////////////////////////////////////////
// CPGRP_20111122View printing

BOOL CPGRP_20111122View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPGRP_20111122View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPGRP_20111122View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CPGRP_20111122View diagnostics

#ifdef _DEBUG
void CPGRP_20111122View::AssertValid() const
{
	CView::AssertValid();
}

void CPGRP_20111122View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPGRP_20111122Doc* CPGRP_20111122View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPGRP_20111122Doc)));
	return (CPGRP_20111122Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPGRP_20111122View message handlers

void CPGRP_20111122View::OnPGRPInit() 
{
	// TODO: Add your command handler code here
	CInitParaDlg dlg;
	dlg.DoModal();
	
}


extern	UT016	g_Search_Range;
extern	F32		g_K_LI_Block;
extern	F32		g_BranOff_Ramdon;
extern	UT016	g_Age_BranOff;
extern	F32		g_K_Vec_Current_LI;
extern	F32		g_K_Vec_Gravity;
extern	F32		g_K_Vec_Last_LI;

extern void Plant_Grow(UT08 pathfinderID,UT016 startX, UT016 startY, UT016 targetX, UT016 targetY);
extern void LoadMapData(void);
extern CString g_Map_Name;
extern UT016	g_Path_Length[MAX_PATH_NUM];
extern UT016	g_Iteration_Times;

void CPGRP_20111122View::OnPGRPRun() 
{
	// TODO: Add your command handler code here
	UINT	Start_X=0;
	UINT	Start_Y=0;
	UINT	Target_X=0;
	UINT	Target_Y=0;
	char	Path_Num=1;
	//Show the Initiate Dialog
	m_InitParaDlg.DoModal();

	g_Map_Name=m_InitParaDlg.m_MapName;	// Define the map name used in the PGRP
	Start_X=m_InitParaDlg.m_Init_Start_X;
	Start_Y=m_InitParaDlg.m_Init_Start_Y;
	Target_X=m_InitParaDlg.m_Init_Target_X;
	Target_Y=m_InitParaDlg.m_Init_Target_X;

	g_Search_Range=m_InitParaDlg.m_Search_Range;	
	g_K_LI_Block=m_InitParaDlg.m_K_LI_Block;
	g_BranOff_Ramdon=m_InitParaDlg.m_BranOff_Ramodn;
	g_Age_BranOff=m_InitParaDlg.m_Age_BranOff;
	g_K_Vec_Current_LI=m_InitParaDlg.m_K1;
	g_K_Vec_Gravity=m_InitParaDlg.m_K2;
	g_K_Vec_Last_LI=m_InitParaDlg.m_K3;

	//Calculate the Path
	LoadMapData();
	Plant_Grow(Path_Num,Start_X,Start_Y,Target_X,Target_Y);	
	
	//Show the result for analysis

	//Update the variables
	m_ShowResultDlg.m_MapName=g_Map_Name;
	m_ShowResultDlg.m_PathLength=g_Path_Length[Path_Num];
	m_ShowResultDlg.m_StartX=Start_X;
	m_ShowResultDlg.m_StartY=Start_Y;
	m_ShowResultDlg.m_TargetX=Target_X;
	m_ShowResultDlg.m_TargetY=Target_Y;
	m_ShowResultDlg.m_Iteration_Times=g_Iteration_Times;

	m_ShowResultDlg.DoModal();

	Invalidate();//Update View

}

void CPGRP_20111122View::OnMenuShowResult() 
{
	// TODO: Add your command handler code here
	m_ShowResultDlg.Create(IDD_DIALOG2,this);
	m_ShowResultDlg.ShowWindow(SW_SHOW);
	
}

void CPGRP_20111122View::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	
	CView::OnChar(nChar, nRepCnt, nFlags);
}


extern UT8  g_Map[MAP_WIDTH][MAP_HEIGHT];
extern CString g_Map_Name;

extern void InitMapDataArray(void);
extern void LoadMapData(void);
extern void SaveMap(CString FileName);
extern void Plant_Grow(UT08 pathfinderID,UT016 startX, UT016 startY, UT016 targetX, UT016 targetY);

void CPGRP_20111122View::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CString str1, str2, str3;
	CString New_Map_Name;
	CPoint tp = point;
	UINT	map_X=0;
	UINT	map_Y=0;
	UINT	Start_X=0;
	UINT	Start_Y=0;
	UINT	Target_X=0;
	UINT	Target_Y=0;
	char	Path_Num=1;
	SYSTEMTIME sys;

	InitMapDataArray();
	LoadMapData();

	Start_X=m_InitParaDlg.m_Init_Start_X;
	Start_Y=m_InitParaDlg.m_Init_Start_Y;
	Target_X=m_InitParaDlg.m_Init_Target_X;
	Target_Y=m_InitParaDlg.m_Init_Target_X;
	
	map_X=UINT(tp.x/8)+1;
	map_Y=UINT(tp.y/8)+1;

	switch(nFlags)
	{
	case 5://鼠标左键 + Shift键 Set the Start Point
		str1.Format("鼠标左键 + Shift键");
		Start_X=map_X;
		Start_Y=map_Y;
		m_InitParaDlg.m_Init_Start_X=Start_X;
		m_InitParaDlg.m_Init_Start_Y=Start_Y;
		break;
	case 9://鼠标左键 + Ctrl键 Set the Target Point
		str1.Format("鼠标左键 + Ctrl键");
		Target_X=map_X;
		Target_Y=map_Y;
		m_InitParaDlg.m_Init_Target_X=Target_X;
		m_InitParaDlg.m_Init_Target_Y=Target_Y;
		break;
	default://鼠标左键 Set the obstacle point or cancel a obstacle point
		str1.Format("鼠标左键");
		if (g_Map[map_X][map_Y]==CELL_IS_OBSTACLE)
			g_Map[map_X][map_Y]=CELL_IS_BLANK;
		else if (g_Map[map_X][map_Y]==CELL_IS_BLANK)
			g_Map[map_X][map_Y]=CELL_IS_OBSTACLE;
		SaveMap(g_Map_Name);
		GetLocalTime(&sys);
		New_Map_Name.Format("Map_%d%d%d_%d%d%d.dat",sys.wYear,sys.wMonth,sys.wDay,sys.wHour,sys.wMinute,sys.wSecond);
		if (CPGRP_20111122View::m_Calculation_Flag==CALCULATE){
			g_Map_Name=New_Map_Name;
			SaveMap(New_Map_Name);
			CPGRP_20111122View::m_Calculation_Flag=NOTCALCULATE;
		}
		break;
	}
	
	str2.Format("光标所在的位置：(X坐标=%d，Y坐标=%d)", tp.x, tp.y);

	str3.Format("光标地图位置：(X坐标=%d，Y坐标=%d)", map_X, map_Y);

	//Calculate the Path
	Plant_Grow(Path_Num,Start_X,Start_Y,Target_X,Target_Y);	
	
	Invalidate();//Update View
	

//	MessageBox("虚拟按键："+str1+"\n\n"+str2+"\n\n"+str3, "鼠标信息");
	
	
	CView::OnLButtonDown(nFlags, point);
}

void CPGRP_20111122View::OnMapCustom() 
{
	// TODO: Add your command handler code here
	m_Map_CustomDlg.DoModal();

}

void CPGRP_20111122View::OnPGRPCalculationFlag() 
{
	// TODO: Add your command handler code here
	m_ModeSelectionDlg.DoModal();
	
}
