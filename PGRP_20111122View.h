// PGRP_20111122View.h : interface of the CPGRP_20111122View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PGRP_20111122VIEW_H__5193FF2E_72EA_4BAE_A615_6A0967BE99FD__INCLUDED_)
#define AFX_PGRP_20111122VIEW_H__5193FF2E_72EA_4BAE_A615_6A0967BE99FD__INCLUDED_

#include "ResultInfoDlg.h"	// Added by ClassView
#include "InitParaDlg.h"	// Added by ClassView
#include "ModeSelectionDlg.h"	// Added by ClassView
#include "MapDlg.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#define CALCULATE		1
#define NOTCALCULATE	0

#endif // _MSC_VER > 1000


class CPGRP_20111122View : public CView
{
protected: // create from serialization only
	CPGRP_20111122View();
	DECLARE_DYNCREATE(CPGRP_20111122View)

// Attributes
public:
	CPGRP_20111122Doc* GetDocument();

	int g_Init_Start_X;
	int g_Init_Start_Y;
	int g_Init_Target_X;
	int g_Init_Target_Y;


// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPGRP_20111122View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	CMapDlg m_Map_CustomDlg;
	CModeSelectionDlg m_ModeSelectionDlg;
	char m_Calculation_Flag;
	CInitParaDlg m_InitParaDlg;
	CResultInfoDlg m_ShowResultDlg;
	virtual ~CPGRP_20111122View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPGRP_20111122View)
	afx_msg void OnPGRPInit();
	afx_msg void OnPGRPRun();
	afx_msg void OnMenuShowResult();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMapCustom();
	afx_msg void OnPGRPCalculationFlag();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in PGRP_20111122View.cpp
inline CPGRP_20111122Doc* CPGRP_20111122View::GetDocument()
   { return (CPGRP_20111122Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PGRP_20111122VIEW_H__5193FF2E_72EA_4BAE_A615_6A0967BE99FD__INCLUDED_)
