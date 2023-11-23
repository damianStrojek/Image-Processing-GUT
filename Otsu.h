#pragma once


// Okno dialogowe Otsu

class Otsu : public CDialogEx
{
	DECLARE_DYNAMIC(Otsu);

public:
	float values[256];
	int p = 0, height = 600;
	Otsu(CWnd* pParent = nullptr);   // konstruktor standardowy
	virtual ~Otsu();

// Dane okna dialogowego
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // obsługa DDX/DDV

	DECLARE_MESSAGE_MAP();

public:
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
};
