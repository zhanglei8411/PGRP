// ResultInfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PGRP_20111122.h"
#include "ResultInfoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CResultInfoDlg dialog


CResultInfoDlg::CResultInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CResultInfoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CResultInfoDlg)
	m_Iteration_Times = 0;
	m_MapName = _T("");
	m_PathLength = 0;
	m_StartX = 0;
	m_StartY = 0;
	m_TargetX = 0;
	m_TargetY = 0;
	//}}AFX_DATA_INIT
}


void CResultInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CResultInfoDlg)
	DDX_Text(pDX, IDC_EDIT_Iteration_Times, m_Iteration_Times);
	DDX_Text(pDX, IDC_EDIT_MapName, m_MapName);
	DDX_Text(pDX, IDC_EDIT_PathLength, m_PathLength);
	DDX_Text(pDX, IDC_EDIT_StartX, m_StartX);
	DDX_Text(pDX, IDC_EDIT_StartY, m_StartY);
	DDX_Text(pDX, IDC_EDIT_TargetX, m_TargetX);
	DDX_Text(pDX, IDC_EDIT_TargetY, m_TargetY);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CResultInfoDlg, CDialog)
	//{{AFX_MSG_MAP(CResultInfoDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResultInfoDlg message handlers
