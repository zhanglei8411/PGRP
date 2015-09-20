#if !defined(AFX_RESULTINFODLG_H__27B81726_0C0F_41E9_8794_FCC3A89B7DF7__INCLUDED_)
#define AFX_RESULTINFODLG_H__27B81726_0C0F_41E9_8794_FCC3A89B7DF7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ResultInfoDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CResultInfoDlg dialog

class CResultInfoDlg : public CDialog
{
// Construction
public:
	CResultInfoDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CResultInfoDlg)
	enum { IDD = IDD_DIALOG2 };
	UINT	m_Iteration_Times;
	CString	m_MapName;
	UINT	m_PathLength;
	UINT	m_StartX;
	UINT	m_StartY;
	UINT	m_TargetX;
	UINT	m_TargetY;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResultInfoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CResultInfoDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RESULTINFODLG_H__27B81726_0C0F_41E9_8794_FCC3A89B7DF7__INCLUDED_)
