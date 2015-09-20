// PGRP_20111122Doc.h : interface of the CPGRP_20111122Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PGRP_20111122DOC_H__AE2A34D1_C666_41E9_92FF_1399B9CA2A76__INCLUDED_)
#define AFX_PGRP_20111122DOC_H__AE2A34D1_C666_41E9_92FF_1399B9CA2A76__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CPGRP_20111122Doc : public CDocument
{
protected: // create from serialization only
	CPGRP_20111122Doc();
	DECLARE_DYNCREATE(CPGRP_20111122Doc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPGRP_20111122Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPGRP_20111122Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPGRP_20111122Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PGRP_20111122DOC_H__AE2A34D1_C666_41E9_92FF_1399B9CA2A76__INCLUDED_)
