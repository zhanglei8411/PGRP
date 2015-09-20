// InitParaDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Afxdlgs.h"
#include "PGRP_20111122.h"
#include "InitParaDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInitParaDlg dialog


CInitParaDlg::CInitParaDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInitParaDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInitParaDlg)
	m_Init_Start_X = 0;
	m_Init_Start_Y = 0;
	m_Init_Target_X = 0;
	m_Init_Target_Y = 0;
	m_Search_Range = 0;
	m_K_LI_Block = 0.0f;
	m_BranOff_Ramodn = 0.0f;
	m_Age_BranOff = 0;
	m_K1 = 0.0f;
	m_K2 = 0.0f;
	m_K3 = 0.0f;
	m_MapName = _T("");
	//}}AFX_DATA_INIT
}


void CInitParaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInitParaDlg)
	DDX_Text(pDX, IDC_EDIT1, m_Init_Start_X);
	DDX_Text(pDX, IDC_EDIT2, m_Init_Start_Y);
	DDX_Text(pDX, IDC_EDIT3, m_Init_Target_X);
	DDX_Text(pDX, IDC_EDIT4, m_Init_Target_Y);
	DDX_Text(pDX, IDC_EDIT5, m_Search_Range);
	DDX_Text(pDX, IDC_EDIT6, m_K_LI_Block);
	DDX_Text(pDX, IDC_EDIT7, m_BranOff_Ramodn);
	DDX_Text(pDX, IDC_EDIT8, m_Age_BranOff);
	DDX_Text(pDX, IDC_EDIT9, m_K1);
	DDX_Text(pDX, IDC_EDIT10, m_K2);
	DDX_Text(pDX, IDC_EDIT11, m_K3);
	DDX_Text(pDX, IDC_STATIC_Mapname, m_MapName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInitParaDlg, CDialog)
	//{{AFX_MSG_MAP(CInitParaDlg)
	ON_BN_CLICKED(IDC_BUTTON_Read_Init, OnBUTTONReadInit)
	ON_BN_CLICKED(IDC_BUTTON_Save_Init, OnBUTTONSaveInit)
	ON_BN_CLICKED(IDC_BUTTON_LoadMap, OnBUTTONLoadMap)
	ON_BN_CLICKED(IDC_BUTTON_Defult, OnBUTTONDefult)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInitParaDlg message handlers


void CInitParaDlg::OnBUTTONReadInit() 
{
	// TODO: Add your control notification handler code here
	CFile file;
	CFileException e;
	CFileDialog dlg(TRUE, "*.p", NULL, OFN_HIDEREADONLY,
							"Coordinate File (*.p)|*.p|All Files (*.*)|*.*||");	// 文件打开对话框
	if (dlg.DoModal()!=IDOK)		// 如果没有选择文件，返回
		return;
	
	if(!file.Open(dlg.GetPathName(), CFile::modeRead, &e))	// 如果打开文件失败，返回
	{
		CString str;
		str.Format("打开文件失败！错误码：%u",e.m_cause);
		MessageBox(str, "警告", MB_OK | MB_ICONWARNING);
		return;
	}

	CArchive ar(&file, CArchive::load);	// 构造CArchive对象
	
	ar >> m_MapName >> m_Init_Start_X >> m_Init_Start_Y >> m_Init_Target_X >> m_Init_Target_Y;
	ar >> m_Search_Range >> m_Age_BranOff >> m_K_LI_Block >> m_BranOff_Ramodn >> m_K1 >> m_K2 >> m_K3;	// 读取起点和终点的x和y坐标值
	ar.Close();
	file.Close();
	UpdateData(FALSE);	// 更新显示
}

void CInitParaDlg::OnBUTTONSaveInit() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);		// 获取新的坐标值
	CFile file;
	CFileException e;
	CFileDialog dlg(FALSE, "*.p", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
							"Coordinate File (*.p)|*.p|All Files (*.*)|*.*||");	// 文件保存对话框
	if (dlg.DoModal()!=IDOK) 		// 如果没有选择文件，返回
		return;
	
	if(!file.Open(dlg.GetPathName(), CFile::modeCreate | CFile::modeWrite, &e)) 	// 如果打开文件失败，返回
	{
		CString str;
		str.Format("打开文件失败！错误码：%u",e.m_cause);
		MessageBox(str, "警告", MB_OK | MB_ICONWARNING);
		return;
	}

	CArchive ar(&file, CArchive::store);
	
	ar << m_MapName << m_Init_Start_X << m_Init_Start_Y << m_Init_Target_X << m_Init_Target_Y;;	// 保存x和y坐标值
	ar << m_Search_Range << m_Age_BranOff << m_K_LI_Block << m_BranOff_Ramodn << m_K1 << m_K2 << m_K3;
	ar.Close();
	file.Close();
}

extern CString g_Map_Name;
void CInitParaDlg::OnBUTTONLoadMap() 
{
	// TODO: Add your control notification handler code here
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY,"All    files   (*.*)|*.*|| ",NULL   );
	dlg.DoModal();
	UpdateData(TRUE);
	m_MapName=dlg.GetFileName();	
	g_Map_Name=m_MapName;
	UpdateData(FALSE);
}

void CInitParaDlg::OnBUTTONDefult() 
{
	// Get the Config File
	CFile file;
	CFileException e;
	if(!file.Open("a1.p", CFile::modeRead, &e))	// 如果打开文件失败，返回
	{
		CString str;
		str.Format("打开文件失败！错误码：%u",e.m_cause);
		MessageBox(str, "警告", MB_OK | MB_ICONWARNING);
		return;
	}

	CArchive ar(&file, CArchive::load);	// 构造CArchive对象
	
	ar >> m_MapName >> m_Init_Start_X >> m_Init_Start_Y >> m_Init_Target_X >> m_Init_Target_Y;
	ar >> m_Search_Range >> m_Age_BranOff >> m_K_LI_Block >> m_BranOff_Ramodn >> m_K1 >> m_K2 >> m_K3;	// 读取起点和终点的x和y坐标值
	ar.Close();
	file.Close();
	UpdateData(FALSE);	// 更新显示

}
