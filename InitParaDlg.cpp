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
							"Coordinate File (*.p)|*.p|All Files (*.*)|*.*||");	// �ļ��򿪶Ի���
	if (dlg.DoModal()!=IDOK)		// ���û��ѡ���ļ�������
		return;
	
	if(!file.Open(dlg.GetPathName(), CFile::modeRead, &e))	// ������ļ�ʧ�ܣ�����
	{
		CString str;
		str.Format("���ļ�ʧ�ܣ������룺%u",e.m_cause);
		MessageBox(str, "����", MB_OK | MB_ICONWARNING);
		return;
	}

	CArchive ar(&file, CArchive::load);	// ����CArchive����
	
	ar >> m_MapName >> m_Init_Start_X >> m_Init_Start_Y >> m_Init_Target_X >> m_Init_Target_Y;
	ar >> m_Search_Range >> m_Age_BranOff >> m_K_LI_Block >> m_BranOff_Ramodn >> m_K1 >> m_K2 >> m_K3;	// ��ȡ�����յ��x��y����ֵ
	ar.Close();
	file.Close();
	UpdateData(FALSE);	// ������ʾ
}

void CInitParaDlg::OnBUTTONSaveInit() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);		// ��ȡ�µ�����ֵ
	CFile file;
	CFileException e;
	CFileDialog dlg(FALSE, "*.p", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
							"Coordinate File (*.p)|*.p|All Files (*.*)|*.*||");	// �ļ�����Ի���
	if (dlg.DoModal()!=IDOK) 		// ���û��ѡ���ļ�������
		return;
	
	if(!file.Open(dlg.GetPathName(), CFile::modeCreate | CFile::modeWrite, &e)) 	// ������ļ�ʧ�ܣ�����
	{
		CString str;
		str.Format("���ļ�ʧ�ܣ������룺%u",e.m_cause);
		MessageBox(str, "����", MB_OK | MB_ICONWARNING);
		return;
	}

	CArchive ar(&file, CArchive::store);
	
	ar << m_MapName << m_Init_Start_X << m_Init_Start_Y << m_Init_Target_X << m_Init_Target_Y;;	// ����x��y����ֵ
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
	if(!file.Open("a1.p", CFile::modeRead, &e))	// ������ļ�ʧ�ܣ�����
	{
		CString str;
		str.Format("���ļ�ʧ�ܣ������룺%u",e.m_cause);
		MessageBox(str, "����", MB_OK | MB_ICONWARNING);
		return;
	}

	CArchive ar(&file, CArchive::load);	// ����CArchive����
	
	ar >> m_MapName >> m_Init_Start_X >> m_Init_Start_Y >> m_Init_Target_X >> m_Init_Target_Y;
	ar >> m_Search_Range >> m_Age_BranOff >> m_K_LI_Block >> m_BranOff_Ramodn >> m_K1 >> m_K2 >> m_K3;	// ��ȡ�����յ��x��y����ֵ
	ar.Close();
	file.Close();
	UpdateData(FALSE);	// ������ʾ

}
