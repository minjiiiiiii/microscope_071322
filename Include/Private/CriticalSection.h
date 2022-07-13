#ifndef __CRITICAL_SECTION_H__
#define __CRITICAL_SECTION_H__

#if defined (_WIN32)

#pragma once
#include <windows.h>

#else

#include <pthread.h>

#endif

#include <misc.h>

// class CWizCriticalSection
class CWizCriticalSection
{
public:
// Constructors:
//	CWizCriticalSection(void){ }; //RICKY - PUT THIS BACK ?
	CWizCriticalSection (BOOL bInit = TRUE);
// Destructor:
	~CWizCriticalSection(void);

public:
// Operations:
	void Begin()
	{
		if (!m_bInited)
			Init();
		LOCK(&m_cCriticalSection);
	 }
	void End  () { UNLOCK (&m_cCriticalSection); }
protected:
// Implementation
	void	Init();
// Members:
	BOOL			m_bInited;
	CRITICAL_SECTION	m_cCriticalSection;
};

/////////////////////////////////////////////////////////////////////////////
class CWizCritSect
{
public:
// Constructors:
	CWizCritSect (CWizCriticalSection& rCriticalSection)
		: m_rCriticalSection (rCriticalSection),
		  m_bStillIn(TRUE)
	{
		m_rCriticalSection.Begin();
	}
// Destructor:
	~CWizCritSect()
	{
		if (m_bStillIn)
			m_rCriticalSection.End();
	}

	CWizCritSect& operator = (CWizCritSect&){ _ASSERT(0); return *this;}

	void Enough()
	{
		if (m_bStillIn)
			m_rCriticalSection.End();
		m_bStillIn = FALSE;
	}
protected:
// Members:
	CWizCriticalSection&	m_rCriticalSection;
	BOOL					m_bStillIn;
};

#endif // __CRITICAL_SECTION_H__
