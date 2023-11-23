#pragma once
#include "Dib.h"

// Okno dialogowe Histogram

class Histogram : public CDialogEx
{
	DECLARE_DYNAMIC(Histogram);

public:
	int bitCount, height = 600, p = 0;
	Dib imgIn;
	bool show;

	Histogram(CWnd* pParent = nullptr);   // konstruktor standardowy
	virtual ~Histogram();

// Dane okna dialogowego
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // obsługa DDX/DDV

	DECLARE_MESSAGE_MAP();

public:
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
};
