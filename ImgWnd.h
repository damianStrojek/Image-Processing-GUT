#pragma once
#include "Dib.h"

// CImgWnd

class CImgWnd : public CWnd
{
	DECLARE_DYNAMIC(CImgWnd)

public:
	CImgWnd();
	virtual ~CImgWnd();
	Dib imageFile;
	bool isImageLoaded;

	BOOL Create(const RECT& rect, CWnd* pParentWnd, UINT nID);

protected:


protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};

