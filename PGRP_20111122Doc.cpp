// PGRP_20111122Doc.cpp : implementation of the CPGRP_20111122Doc class
//

#include "stdafx.h"
#include "PGRP_20111122.h"
#include "PGRP_20111122Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPGRP_20111122Doc

IMPLEMENT_DYNCREATE(CPGRP_20111122Doc, CDocument)

BEGIN_MESSAGE_MAP(CPGRP_20111122Doc, CDocument)
	//{{AFX_MSG_MAP(CPGRP_20111122Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPGRP_20111122Doc construction/destruction

CPGRP_20111122Doc::CPGRP_20111122Doc()
{
	// TODO: add one-time construction code here

}

CPGRP_20111122Doc::~CPGRP_20111122Doc()
{
}

BOOL CPGRP_20111122Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CPGRP_20111122Doc serialization

void CPGRP_20111122Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CPGRP_20111122Doc diagnostics

#ifdef _DEBUG
void CPGRP_20111122Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPGRP_20111122Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPGRP_20111122Doc commands
