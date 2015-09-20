#if !defined(AFX_INITPARADLG_H__0C2CEAD9_A25C_4D61_A4DB_1045B100D0BD__INCLUDED_)
#define AFX_INITPARADLG_H__0C2CEAD9_A25C_4D61_A4DB_1045B100D0BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InitParaDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInitParaDlg dialog

class CInitParaDlg : public CDialog
{
// Construction
public:
	CInitParaDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CInitParaDlg)
	enum { IDD = IDD_DIALOG1 };
	UINT	m_Init_Start_X;
	UINT	m_Init_Start_Y;
	UINT	m_Init_Target_X;
	UINT	m_Init_Target_Y;
	UINT	m_Search_Range;
	float	m_K_LI_Block;
	float	m_BranOff_Ramodn;
	UINT	m_Age_BranOff;
	float	m_K1;
	float	m_K2;
	float	m_K3;
	CString	m_MapName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInitParaDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInitParaDlg)
	afx_msg void OnBUTTONReadInit();
	afx_msg void OnBUTTONSaveInit();
	afx_msg void OnBUTTONLoadMap();
	afx_msg void OnBUTTONDefult();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INITPARADLG_H__0C2CEAD9_A25C_4D61_A4DB_1045B100D0BD__INCLUDED_)
