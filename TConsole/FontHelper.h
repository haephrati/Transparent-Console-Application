// FontHelper.h: interface for the CFontHelper class.
// Created by Ahmad Yassin.
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FONTHELPER_H__71AC1D69_15EF_4F4F_B819_7F9746A1E217__INCLUDED_)
#define AFX_FONTHELPER_H__71AC1D69_15EF_4F4F_B819_7F9746A1E217__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFontHelper : public CObject  
{
public:
	CFontHelper();
	CFontHelper(LPCTSTR szSection, LPCTSTR szEntry);
	virtual ~CFontHelper();

// public interface
public:
	// 1. data access 
	HFONT CreateFont();
	LOGFONT GetLogFont(LOGFONT& LogFont);
	HFONT GetFontHandle();

	// 2. save/restore
	void Save();
	void Restore();
	void SetSectionName(LPCTSTR szSection);
	void SetEntryName(LPCTSTR szEntry);

	// 3. Windows common font picker dialog
	BOOL ChooseFont();

// internal helpers
protected:
	// 4. default font 
	void DefaultFontInit();
	void DefaultInit();

// internal members
protected:
	HFONT m_hFont;
	LOGFONT m_LogFont;
	CString m_szSection;
	CString m_szEntry;

};

#endif // !defined(AFX_FONTHELPER_H__71AC1D69_15EF_4F4F_B819_7F9746A1E217__INCLUDED_)
