#pragma once

class Eventer
{
public:
	Eventer(void);
	virtual ~Eventer(void);
	virtual void PerformAction(const CString& strCmd) = 0;
	virtual void PerformSpecialAction(UINT nAction) = 0;
};
