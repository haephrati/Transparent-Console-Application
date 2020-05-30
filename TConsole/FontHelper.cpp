// FontHelper.cpp: implementation of the CFontHelper class.
// Created by Ahmad Yassin
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "FontHelper.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFontHelper::CFontHelper()
{
	// initialize with default values for INI/Registry and font description
	DefaultInit();

}

// this constructor will automatically try to load the font description 
// from the INI/Registry

CFontHelper::CFontHelper(LPCTSTR szSection, LPCTSTR szEntry)
{
	// defensive programming
	ASSERT((szSection != NULL) && (_tcslen(szSection) > 0));
	ASSERT((szEntry != NULL) && (_tcslen(szEntry) > 0));

	m_szSection = szSection;
	m_szEntry = szEntry;

	// set default values
	DefaultFontInit();

	// try to load the saved description 
	Restore();

}

CFontHelper::~CFontHelper()
{
	// don't forget to delete the current font
	if (m_hFont != NULL)
		::DeleteObject(m_hFont);

}

// set the logical font information as "Lucida Sans Unicode" size 8
void CFontHelper::DefaultFontInit()
{
	// define the logical parameters for the default font
	m_LogFont.lfHeight = -11; // size 8
	m_LogFont.lfWidth = 0;
	m_LogFont.lfEscapement = 0;
	m_LogFont.lfOrientation = 0;
	m_LogFont.lfWeight = FW_NORMAL;
	m_LogFont.lfItalic = 0;
	m_LogFont.lfUnderline = 0;
	m_LogFont.lfStrikeOut = 0;
	m_LogFont.lfCharSet = 0;
	m_LogFont.lfOutPrecision = OUT_STRING_PRECIS;
	m_LogFont.lfClipPrecision = CLIP_STROKE_PRECIS;
	m_LogFont.lfQuality = DEFAULT_QUALITY;
	m_LogFont.lfPitchAndFamily = FF_SWISS | VARIABLE_PITCH;
	_tcscpy(m_LogFont.lfFaceName, _T("Lucida Sans Unicode"));

	// create the associated font 
	CreateFont();

}

// set the logical font information and INI/Registry access to default values
void CFontHelper::DefaultInit()
{
	// set default font settings as "Lucida Sans Unicode" size 8
	DefaultFontInit();

	// default saving section/entry
	m_szSection = _T("Settings");
	m_szEntry = _T("Font");

}

BOOL CFontHelper::ChooseFont()
{
	CHOOSEFONT choosefont;
	LOGFONT LogFont = m_LogFont;

	// fill in the data needed for the Windows common font dialog 
	choosefont.lStructSize = sizeof(CHOOSEFONT);
	choosefont.hwndOwner = ::GetActiveWindow();
	choosefont.hDC = 0;
	choosefont.lpLogFont = &LogFont;
	choosefont.iPointSize = 0;
	choosefont.Flags = CF_SCREENFONTS|CF_INITTOLOGFONTSTRUCT;
	choosefont.rgbColors = 0;
	choosefont.lCustData = 0;
	choosefont.lpfnHook = 0;
	choosefont.lpTemplateName = NULL;
	choosefont.hInstance = 0;
	choosefont.lpszStyle = 0;
	choosefont.nFontType = SCREEN_FONTTYPE;
	choosefont.nSizeMin = 0;
	choosefont.nSizeMax = 0;

	// use COMMDLG function to get new font selection from user
	if (::ChooseFont(&choosefont) != FALSE)
	{
		// keep track of the current font
		m_LogFont = LogFont;

		// create a Windows font according to the logical information
		CreateFont();
		return TRUE;
	}
	else
		return FALSE;

}

// create the associated font 
HFONT CFontHelper::CreateFont()
{
	HFONT hFont = ::CreateFontIndirect(&m_LogFont);

	if (hFont == NULL)
	{
		// GetLastError(); can be used to understand why the font was not created
		TRACE("Impossible to create font\n");
	}

	// don't forget to delete the current font
	if (m_hFont != NULL)
		::DeleteObject(m_hFont);

	// store the font (event if the creation has failed)
	m_hFont = hFont;

	return hFont;

}

// return the logical font description for the wrapped font
LOGFONT CFontHelper::GetLogFont(LOGFONT& LogFont)
{
	LogFont = m_LogFont;
	return LogFont;
}

// return the wrapped font
HFONT CFontHelper::GetFontHandle()
{
	return m_hFont;
}

void CFontHelper::SetSectionName(LPCTSTR szSection)
{
	// defensive programming
	ASSERT((szSection != NULL) && (_tcslen(szSection) > 0));
	m_szSection = szSection;

}

void CFontHelper::SetEntryName(LPCTSTR szEntry)
{
	// defensive programming
	ASSERT((szEntry != NULL) && (_tcslen(szEntry) > 0));
	m_szEntry = szEntry;

}

void CFontHelper::Save()
{
	// SetSectionName() must be called before this method is used
	// SetEntryName() must be called before this method is used
	ASSERT(m_szSection.GetLength() > 0);
	ASSERT(m_szEntry.GetLength() > 0);

	// save the logical font description
	CString strBuffer;
	strBuffer.Format("%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d",
					m_LogFont.lfHeight,
					m_LogFont.lfWidth,
					m_LogFont.lfEscapement,
					m_LogFont.lfOrientation,
					m_LogFont.lfWeight,
					m_LogFont.lfItalic,
					m_LogFont.lfUnderline,
					m_LogFont.lfStrikeOut,
					m_LogFont.lfCharSet,
					m_LogFont.lfOutPrecision,
					m_LogFont.lfClipPrecision,
					m_LogFont.lfQuality,
					m_LogFont.lfPitchAndFamily);

	AfxGetApp()->WriteProfileString (m_szSection, m_szEntry + _T("_Desc"), strBuffer);

	// save the font name
	AfxGetApp()->WriteProfileString (m_szSection, m_szEntry + _T("_Name"), m_LogFont.lfFaceName);

}

// get the logical font from the INI/Registry
void CFontHelper::Restore()
{
	// SetSectionName() must be called before this method is used
	// SetEntryName() must be called before this method is used
	ASSERT(m_szSection.GetLength() > 0);
	ASSERT(m_szEntry.GetLength() > 0);

	// get font description from INI/Registry
	CString strBuffer = AfxGetApp()->GetProfileString(m_szSection, m_szEntry + _T("_Desc"));

	// nothing is saved 
	// --> keep the current font
	if (strBuffer.IsEmpty())
		return;

	LOGFONT LogFont;
	int cRead = _stscanf (strBuffer, "%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d",
						&LogFont.lfHeight,
						&LogFont.lfWidth,
						&LogFont.lfEscapement,
						&LogFont.lfOrientation,
						&LogFont.lfWeight,
						&LogFont.lfItalic,
						&LogFont.lfUnderline,
						&LogFont.lfStrikeOut,
						&LogFont.lfCharSet,
						&LogFont.lfOutPrecision,
						&LogFont.lfClipPrecision,
						&LogFont.lfQuality,
						&LogFont.lfPitchAndFamily);

	if (cRead != 13)
	{
		TRACE("Restore(): Invalid Registry/INI file entry\n");
		return;
	}

	// get the font name
	strBuffer = AfxGetApp()->GetProfileString(m_szSection, m_szEntry + _T("_Name"));
	if (strBuffer.GetLength() <= 0)
		return;

	_tcscpy(LogFont.lfFaceName, strBuffer);

	// take into account the loaded logical font description
	m_LogFont = LogFont;

	// create the associated font 
	CreateFont();

}
