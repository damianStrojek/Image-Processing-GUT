
// PO1Dlg.h : header file
//

#pragma once
#include "ImgWnd.h"
#include "afxwin.h"
#include "Histogram.h"
#include "Otsu.h"


// CPODlg dialog
class CPODlg : public CDialogEx
{
	// Construction
public:
	CPODlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_PO1_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	CImgWnd m_imgIN;
	CImgWnd m_imgOUT;

	CComboBox m_combo1;
	Histogram histogram;
	Otsu otsu;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	float LimitInterval(int);
	int ClipValue(const int);
	void DrawHistogram(int);
	double CPODlg::getAverageValueFromHistogram(int, int);
	float CPODlg::CalculateRadian(int degree);

public:
	afx_msg void OnBnClickedButtonLoad();
	afx_msg void OnBnClickedButtonProcess();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonParams();
	CSliderCtrl sliderControl;
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedButton1();
};