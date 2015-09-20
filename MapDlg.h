#if !defined(AFX_MAPDLG_H__0219E991_DD2E_462A_83BF_7C2C7B082581__INCLUDED_)
#define AFX_MAPDLG_H__0219E991_DD2E_462A_83BF_7C2C7B082581__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MapDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMapDlg dialog

class CMapDlg : public CDialog
{
// Construction
public:
	CMapDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMapDlg)
	enum { IDD = IDD_DIALOG4 };
	CButton	m_GetPoint_BmpButtom;
	UINT	m_Circle_Center;
	UINT	m_Circle_Radius;
	CString	m_Map_Name;
	UINT	m_Rect1_X;
	UINT	m_Rect1_Y;
	UINT	m_Rect2_X;
	UINT	m_Rect2_Y;
	UINT	m_Circle_Center_X;
	UINT	m_Circle_Center_Y;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMapDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMapDlg)
	afx_msg void OnMapEditCircle();
	afx_msg void OnGetPoint();
	afx_msg void OnMapSave();
	afx_msg void OnBUTTONLoadMap();
	afx_msg void OnMapEditRec();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAPDLG_H__0219E991_DD2E_462A_83BF_7C2C7B082581__INCLUDED_)
