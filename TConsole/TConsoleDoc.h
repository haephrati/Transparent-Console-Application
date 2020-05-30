// TConsoleDoc.h : interface of the CTConsoleDoc class
//


#pragma once

class CTConsoleDoc : public CDocument
{
protected: // create from serialization only
	CTConsoleDoc();
	DECLARE_DYNCREATE(CTConsoleDoc)

// Attributes
public:

// Operations
public:

// Overrides
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CTConsoleDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


