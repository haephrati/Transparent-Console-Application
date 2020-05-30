// TConsoleDoc.cpp : implementation of the CTConsoleDoc class
//

#include "stdafx.h"
#include "TConsole.h"

#include "TConsoleDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTConsoleDoc

IMPLEMENT_DYNCREATE(CTConsoleDoc, CDocument)

BEGIN_MESSAGE_MAP(CTConsoleDoc, CDocument)
END_MESSAGE_MAP()


// CTConsoleDoc construction/destruction

CTConsoleDoc::CTConsoleDoc()
{
	// TODO: add one-time construction code here

}

CTConsoleDoc::~CTConsoleDoc()
{
}

BOOL CTConsoleDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CTConsoleDoc serialization

void CTConsoleDoc::Serialize(CArchive& ar)
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


// CTConsoleDoc diagnostics

#ifdef _DEBUG
void CTConsoleDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTConsoleDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CTConsoleDoc commands
