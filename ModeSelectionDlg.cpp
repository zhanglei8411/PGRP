// ModeSelectionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PGRP_20111122.h"
#include "ModeSelectionDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CModeSelectionDlg dialog


CModeSelectionDlg::CModeSelectionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CModeSelectionDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CModeSelectionDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CModeSelectionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CModeSelectionDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CModeSelectionDlg, CDialog)
	//{{AFX_MSG_MAP(CModeSelectionDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CModeSelectionDlg message handlers
