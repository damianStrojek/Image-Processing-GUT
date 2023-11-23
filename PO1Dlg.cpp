
// PO1Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "PO1.h"
#include "PO1Dlg.h"
#include "ParamsDlg.h"
#include "afxdialogex.h"
#include "cmath"
#include <vector>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define IMG_WND_ID_IN	100
#define IMG_WND_ID_OUT	101
#define ABOVE_ZERO 127
# define M_PI 3.14159265358979323846

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNMReleasedcaptureSlider1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButton1();
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CPODlg dialog

CPODlg::CPODlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPODlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPODlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combo1);
	DDX_Control(pDX, IDC_SLIDER1, sliderControl);
}

BEGIN_MESSAGE_MAP(CPODlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_LOAD, &CPODlg::OnBnClickedButtonLoad)
	ON_BN_CLICKED(IDC_BUTTON_PROCESS, &CPODlg::OnBnClickedButtonProcess)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CPODlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_PARAMS, &CPODlg::OnBnClickedButtonParams)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CPODlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON1, &CPODlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CPODlg message handlers

BOOL CPODlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	CRect rDlg(7, 7, 407, 407);
	MapDialogRect(rDlg);

	m_imgIN.Create(rDlg, this, IMG_WND_ID_IN);

	rDlg = CRect(530, 7, 930, 407);
	MapDialogRect(rDlg);

	m_imgOUT.Create(rDlg, this, IMG_WND_ID_OUT);

	m_combo1.AddString(L"1-CONVERT-TO-GREYSCALE");
	m_combo1.AddString(L"1-SET-BRIGHTNESS");
	m_combo1.AddString(L"1-SET-CONTRAST");
	m_combo1.AddString(L"1-EXPONENTIATION");
	m_combo1.AddString(L"1-NEGATIVE");

	m_combo1.AddString(L"2-THRESHOLDING");
	m_combo1.AddString(L"2-ITERATIVE-THRESHOLDING");
	m_combo1.AddString(L"2-GRADIENT-THRESHOLDING");
	m_combo1.AddString(L"2-OTSU-THRESHOLDING");

	m_combo1.AddString(L"3-AVERAGE-FILTER");
	m_combo1.AddString(L"3-GAUSS-FILTER");
	m_combo1.AddString(L"3-SOBEL-FIRST-FILTER");
	m_combo1.AddString(L"3-SOBEL-SECOND-FILTER");
	m_combo1.AddString(L"3-LAPLACIAN-FILTER");
	m_combo1.AddString(L"3-SHARPENING-FILTER");

	// Absent on the fourth labs

	m_combo1.AddString(L"5-HOUGH");
	m_combo1.AddString(L"5-HOUGH-SLIDER");

	m_combo1.AddString(L"6-FOURIER-AMPLITUDE");
	m_combo1.AddString(L"6-FOURIER-PHASE");
	m_combo1.AddString(L"6-FOURIER-HAMMING-EYE");

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPODlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPODlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPODlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// MessageBox(L"Now what?", L";-)", MB_OK);
void CPODlg::OnBnClickedButtonLoad()
{
	WCHAR strFilter[] = { L"Image Files (*.bmp)|*.bmp|All Files (*.*)|*.*||" };

	CFileDialog FileDlg(TRUE, NULL, NULL, 0, strFilter);

	if (FileDlg.DoModal() == IDOK) {
		m_imgIN.isImageLoaded = m_imgIN.imageFile.LoadDIB(FileDlg.GetPathName());
		
		// Force the refresh of context in window
		InvalidateRect(NULL);
	}
};

void CPODlg::OnBnClickedButtonProcess()
{
	CString sOption;
	m_combo1.GetLBText(m_combo1.GetCurSel(), sOption);

	if (sOption == L"1-CONVERT-TO-GREYSCALE")
	{
		CPaintDC dc(this);
		
		CRect sourceRect;
		BYTE grayscale;
		POINT bof, eof;
		bof.x = 0, bof.y = 0;
		eof.x = m_imgIN.imageFile.bitmapInfoHeader.biWidth, eof.y = m_imgIN.imageFile.bitmapInfoHeader.biHeight;

		// Create empty bitmap file inside m_imgOUT
		sourceRect.SetRect(bof, eof);
		m_imgOUT.imageFile.CreateGreyscaleDIB(sourceRect, GetDeviceCaps(dc.GetSafeHdc(), HORZRES), GetDeviceCaps(dc.GetSafeHdc(), HORZRES));
		
		// Initialize empty m_imgOUT with proper colors
		for (int y = 0; y < eof.y; y++) {

			for (int x = 0; x < eof.x; x++) {

				grayscale = 0;

				if ((m_imgIN.imageFile.bitmapInfoHeader.biBitCount == 1)
					&& (m_imgIN.imageFile.GetPixel1(x, y)))
				{
					grayscale = 255;
				}
				else if (m_imgIN.imageFile.bitmapInfoHeader.biBitCount == 8)
				{
					grayscale = m_imgIN.imageFile.GetPixel8(x, y);
				}
				else if (m_imgIN.imageFile.bitmapInfoHeader.biBitCount == 24)
				{
					RGBTRIPLE pixelRGB = m_imgIN.imageFile.GetPixel24(x, y);
					// From a slide
					grayscale = 0.299 * pixelRGB.rgbtRed + 0.587 * pixelRGB.rgbtGreen + 0.114 * pixelRGB.rgbtBlue;
				}

				m_imgOUT.imageFile.SetPixel8(x, y, grayscale);

			}

		}

		m_imgOUT.isImageLoaded = true;
		// Force the refresh of context in window
		InvalidateRect(NULL);
	}
	else if (sOption == L"1-SET-BRIGHTNESS") {

		CPaintDC dc(this);

		CRect sourceRectangle;
		POINT bof, eof;
		int brightness;
		int brightnessSlider = sliderControl.GetPos();

		bof.x = 0, bof.y = 0;
		eof.x = m_imgIN.imageFile.bitmapInfoHeader.biWidth, eof.y = m_imgIN.imageFile.bitmapInfoHeader.biHeight;

		sourceRectangle.SetRect(bof, eof);

		m_imgOUT.imageFile.CreateGreyscaleDIB(sourceRectangle, GetDeviceCaps(dc.GetSafeHdc(), HORZRES), GetDeviceCaps(dc.GetSafeHdc(), HORZRES));

		for (int y = 0; y < eof.y; y++)
		{
			for (int x = 0; x < eof.x; x++)
			{
				if (m_imgIN.imageFile.bitmapInfoHeader.biBitCount == 8)
				{
					brightness = m_imgIN.imageFile.GetPixel8(x, y) + brightnessSlider;
					if (brightness < 0) brightness = 0;
					if (brightness > 255) brightness = 255;
					m_imgOUT.imageFile.SetPixel8(x, y, brightness);
				}
				else
				{
					MessageBox(L"Not 8 biBitCount", L";-)", MB_OK);
				}
			}
		}
	
		m_imgOUT.isImageLoaded = true;
		// Force the refresh of context in window
		InvalidateRect(NULL);
	}
	else if (sOption == L"1-SET-CONTRAST") {

		CPaintDC dc(this);

		CRect sourceRectangle;
		POINT bof, eof;
		float contrast;
		float contrastSlider = (float)sliderControl.GetPos() / 10;
		float contrastOffset = 127 * contrastSlider - 127;

		bof.x = 0, bof.y = 0;
		eof.x = m_imgIN.imageFile.bitmapInfoHeader.biWidth, eof.y = m_imgIN.imageFile.bitmapInfoHeader.biHeight;

		sourceRectangle.SetRect(bof, eof);

		m_imgOUT.imageFile.CreateGreyscaleDIB(sourceRectangle, GetDeviceCaps(dc.GetSafeHdc(), HORZRES), GetDeviceCaps(dc.GetSafeHdc(), HORZRES));

		for (int y = 0; y < eof.y; y++)
		{
			for (int x = 0; x < eof.x; x++)
			{
				if (m_imgIN.imageFile.bitmapInfoHeader.biBitCount == 8)
				{
					contrast = m_imgIN.imageFile.GetPixel8(x, y) * contrastSlider;
					contrast = contrast - contrastOffset;
					m_imgOUT.imageFile.SetPixel8(x, y, LimitInterval(contrast));
				}
				else
				{
					MessageBox(L"Not 8 biBitCount", L";-)", MB_OK);
				}
			}
		}

		m_imgOUT.isImageLoaded = true;
		// Force the refresh of context in window
		InvalidateRect(NULL);
	}
	else if (sOption == L"1-EXPONENTIATION") {

		CPaintDC dc(this);

		CRect sourceRectangle;
		POINT bof, eof;
		float exponentiation;
		float expSlider = (float)sliderControl.GetPos() / 10;

		bof.x = 0, bof.y = 0;
		eof.x = m_imgIN.imageFile.bitmapInfoHeader.biWidth, eof.y = m_imgIN.imageFile.bitmapInfoHeader.biHeight;

		sourceRectangle.SetRect(bof, eof);

		m_imgOUT.imageFile.CreateGreyscaleDIB(sourceRectangle, GetDeviceCaps(dc.GetSafeHdc(), HORZRES), GetDeviceCaps(dc.GetSafeHdc(), HORZRES));

		for (int y = 0; y < eof.y; y++)
		{
			for (int x = 0; x < eof.x; x++)
			{
				if (m_imgIN.imageFile.bitmapInfoHeader.biBitCount == 8)
				{
					exponentiation = std::pow(m_imgIN.imageFile.GetPixel8(x, y) / 255.0, expSlider);
					m_imgOUT.imageFile.SetPixel8(x, y, LimitInterval(exponentiation * 255));
				}
				else
				{
					MessageBox(L"Not 8 biBitCount", L";-)", MB_OK);
				}
			}
		}

		m_imgOUT.isImageLoaded = true;
		// Force the refresh of context in window
		InvalidateRect(NULL);
	}
	else if (sOption == L"1-NEGATIVE") {

		CPaintDC dc(this);

		CRect rectangleIn;
		POINT bof, eof;
		float negative;

		bof.x = 0, bof.y = 0;
		eof.x = m_imgIN.imageFile.bitmapInfoHeader.biWidth, eof.y = m_imgIN.imageFile.bitmapInfoHeader.biHeight;

		rectangleIn.SetRect(bof, eof);

		m_imgOUT.imageFile.CreateGreyscaleDIB(rectangleIn, GetDeviceCaps(dc.GetSafeHdc(), HORZRES), GetDeviceCaps(dc.GetSafeHdc(), HORZRES));

		for (int y = 0; y < eof.y; y++)
		{
			for (int x = 0; x < eof.x; x++)
			{
				if (m_imgIN.imageFile.bitmapInfoHeader.biBitCount == 8)
				{
					negative = 255 - m_imgIN.imageFile.GetPixel8(x, y);
					m_imgOUT.imageFile.SetPixel8(x, y, LimitInterval(negative));
				}
				else
				{
					MessageBox(L"Not 8 biBitCount", L";-)", MB_OK);
				}
			}
		}

		m_imgOUT.isImageLoaded = true;
		// Force the refresh of context in window
		InvalidateRect(NULL);
	}
	else if (sOption == L"2-THRESHOLDING") {
		
		CPaintDC dc(this);

		CRect rectangleIn;
		POINT bof, eof;
		int currentValue = 0, position;
		float thresholdingSlider = (float)sliderControl.GetPos() / 10;

		bof.x = 0, bof.y = 0;
		eof.x = m_imgIN.imageFile.bitmapInfoHeader.biWidth, eof.y = m_imgIN.imageFile.bitmapInfoHeader.biHeight;

		rectangleIn.SetRect(bof, eof);

		m_imgOUT.imageFile.CreateGreyscaleDIB(rectangleIn, GetDeviceCaps(dc.GetSafeHdc(), HORZRES), GetDeviceCaps(dc.GetSafeHdc(), HORZRES));
		m_imgIN.imageFile.pictureThresholding = (float)sliderControl.GetPos();

		for (int y = 0; y < eof.y; y++)
		{
			for (int x = 0; x < eof.x; x++)
			{
				if (m_imgIN.imageFile.bitmapInfoHeader.biBitCount == 8)
				{
					currentValue = m_imgIN.imageFile.GetPixel8(x, y);

					if (m_imgIN.imageFile.pictureThresholding > currentValue)
						currentValue = 0;
					else
						currentValue = 255;
				}

				m_imgOUT.imageFile.SetPixel8(x, y, currentValue);
			}
		}

		m_imgOUT.isImageLoaded = true;
		// Force the refresh of context in window
		InvalidateRect(NULL);
	}
	else if (sOption == L"2-ITERATIVE-THRESHOLDING") {

		CPaintDC dc(this);

		CRect rectangleIn;
		POINT bof, eof;
		int pixel, newValue = 0;
		auto average1 = 0, average2 = 0;
		int point1 = 127, point2 = 140, const epsilon = 1;

		bof.x = 0, bof.y = 0;
		eof.x = m_imgIN.imageFile.bitmapInfoHeader.biWidth, eof.y = m_imgIN.imageFile.bitmapInfoHeader.biHeight;

		rectangleIn.SetRect(bof, eof);

		m_imgIN.imageFile.CreateHistogram8bit();
		m_imgOUT.imageFile.CreateGreyscaleDIB(rectangleIn, GetDeviceCaps(dc.GetSafeHdc(), HORZRES), GetDeviceCaps(dc.GetSafeHdc(), HORZRES));
		
		if (m_imgIN.imageFile.bitmapInfoHeader.biBitCount == 8)
		{
			while (std::abs(point1 - point2) > epsilon)
			{
				// Average value of micro 0
				average1 = getAverageValueFromHistogram(0, point1);
				// Average value of micro 1
				average2 = getAverageValueFromHistogram(point1, 256);
				point2 = point1;
				// New value of threshold
				point1 = (average1 + average2) / 2;
			}

			histogram.p = point2;

			for (int y = 0; y < eof.y; y++)
			{
				for (int x = 0; x < eof.x; x++)
				{
					pixel = m_imgIN.imageFile.GetPixel8(x, y);
					if (pixel > point1) newValue = 255;
					else newValue = 0;
					m_imgOUT.imageFile.SetPixel8(x, y, newValue);
				}
			}
		}

		m_imgOUT.isImageLoaded = true;
		// Force the refresh of context in window
		InvalidateRect(NULL);
	}
	else if (sOption == L"2-GRADIENT-THRESHOLDING") {

		CPaintDC dc(this);

		CRect rectangleIn;
		POINT bof, eof;
		int pixel, newValue = 0;
		auto average1 = 0, average2 = 0;
		double gx = 0, gy = 0, gmax = 0, topEquation = 0, bottomEquation = 0, thresholdPoint = 0;

		bof.x = 0, bof.y = 0;
		eof.x = m_imgIN.imageFile.bitmapInfoHeader.biWidth, eof.y = m_imgIN.imageFile.bitmapInfoHeader.biHeight;

		rectangleIn.SetRect(bof, eof);

		m_imgIN.imageFile.CreateHistogram8bit();
		m_imgOUT.imageFile.CreateGreyscaleDIB(rectangleIn, GetDeviceCaps(dc.GetSafeHdc(), HORZRES), GetDeviceCaps(dc.GetSafeHdc(), HORZRES));

		if (m_imgIN.imageFile.bitmapInfoHeader.biBitCount == 8)
		{
			for (int y = 1; y < eof.y - 1; y++)
			{
				for (int x = 1; x < eof.x - 1; x++)
				{
					pixel = m_imgIN.imageFile.GetPixel8(x, y);
					// Variables of gradient
					gx = m_imgIN.imageFile.GetPixel8(x + 1, y) - m_imgIN.imageFile.GetPixel8(x - 1, y);
					gy = m_imgIN.imageFile.GetPixel8(x, y + 1) - m_imgIN.imageFile.GetPixel8(x, y - 1);

					// Max from both
					gmax = max(gx, gy);

					// Calculate the equation of G(x,y)
					topEquation += pixel * gmax;
					bottomEquation += gmax;
				}
			}

			// Calculate the value of threshold point
			thresholdPoint = topEquation / bottomEquation;

			for (int y = 0; y < eof.y; y++)
			{
				for (int x = 0; x < eof.x; x++)
				{
					pixel = m_imgIN.imageFile.GetPixel8(x, y);

					if (pixel > thresholdPoint)
						m_imgOUT.imageFile.SetPixel8(x, y, 255);
					else
						m_imgOUT.imageFile.SetPixel8(x, y, 0);
				}
			}

			histogram.p = thresholdPoint;
		}

		m_imgOUT.isImageLoaded = true;
		// Force the refresh of context in window
		InvalidateRect(NULL);
	}
	else if (sOption == L"2-OTSU-THRESHOLDING") {
		
		CPaintDC dc(this);
		
		CRect rectangleIn;
		POINT bof, eof;
		int pixel, newValue = 0;

		bof.x = 0, bof.y = 0;
		eof.x = m_imgIN.imageFile.bitmapInfoHeader.biWidth, eof.y = m_imgIN.imageFile.bitmapInfoHeader.biHeight;

		rectangleIn.SetRect(bof, eof);

		m_imgIN.imageFile.CreateHistogram8bit();
		m_imgOUT.imageFile.CreateGreyscaleDIB(rectangleIn, GetDeviceCaps(dc.GetSafeHdc(), HORZRES), GetDeviceCaps(dc.GetSafeHdc(), HORZRES));

		if (m_imgIN.imageFile.bitmapInfoHeader.biBitCount == 8)
		{

			float n = eof.x * eof.y, varianceMin = 0;
			int bestThresholdValue = -1;

			for (int t = 0; t <= 255; t++) {

				// Sum of pixel brightness below threshold
				int	belowSum = 0;
				// Average pixel brightness below threshold
				float belowAverageSum = 0;
				// Probability of being in class nr 0
				float probability0 = 0;

				// Sum of pixel brightness above threshold
				int aboveSum = 0;
				// Average pixel brightness above threshold
				float aboveAverageSum = 0;
				// Probability of being in class nr 1
				float probability1 = 0;


				for (int i = 0; i <= t; i++) {

					float pi = float(m_imgIN.imageFile.histogram8[i]) / n;
					belowSum += m_imgIN.imageFile.histogram8[i];
					belowAverageSum += i * pi;
					probability0 += pi;
				}

				for (int i = t + 1; i <= 255; i++) {
					float pi = float(m_imgIN.imageFile.histogram8[i]) / n;
					aboveSum += m_imgIN.imageFile.histogram8[i];
					aboveAverageSum += i * pi;
					probability1 += pi;
				}

				if (probability0 > 0) belowAverageSum /= probability0;
				if (probability1 > 0) aboveAverageSum /= probability1;
				
				// Brightness variance in both classes
				float varianceBoth = 0;
				for (int i = 0; i <= t; i++) {
					varianceBoth += pow(i - belowAverageSum, 2) * m_imgIN.imageFile.histogram8[i] / n;
				}
				for (int i = t + 1; i <= 255; i++) {
					varianceBoth += pow(i - aboveAverageSum, 2) * m_imgIN.imageFile.histogram8[i] / n;
				}

				if (bestThresholdValue == -1) {
					bestThresholdValue = t;
					varianceMin = varianceBoth;
				}
				else {
					// Lower variance equals better threshold
					if (varianceBoth < varianceMin) {
						bestThresholdValue = t;
						varianceMin = varianceBoth;
					}
				}
				otsu.values[t] = 1.0 / varianceBoth;
			}

			histogram.p = bestThresholdValue;
			otsu.p = bestThresholdValue;

			for (int y = 0; y < eof.y; y++)
			{
				for (int x = 0; x < eof.x; x++)
				{
					pixel = m_imgIN.imageFile.GetPixel8(x, y);
					if (pixel > bestThresholdValue) newValue = 255;
					else newValue = 0;
					m_imgOUT.imageFile.SetPixel8(x, y, newValue);
				}
			}
		}

		m_imgOUT.isImageLoaded = true;
		// Force the refresh of context in window
		InvalidateRect(NULL);
		otsu.DoModal();
	}
	else if (sOption == L"3-AVERAGE-FILTER") {
		
		CPaintDC dc(this);

		CRect rectangleIn;
		POINT bof, eof;
		int points[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 }, brightness = 0, sumMask = 0;
		int mask[3][3] = {{1, 1, 1,},{1, 1, 1,},{1, 1, 1,}};

		bof.x = 0, bof.y = 0;
		eof.x = m_imgIN.imageFile.bitmapInfoHeader.biWidth, eof.y = m_imgIN.imageFile.bitmapInfoHeader.biHeight;

		rectangleIn.SetRect(bof, eof);

		m_imgOUT.imageFile.CreateGreyscaleDIB(rectangleIn, GetDeviceCaps(dc.GetSafeHdc(), HORZRES), GetDeviceCaps(dc.GetSafeHdc(), HORZRES));

		//		(x-1, y-1)		(x, y-1)		(x+1, y-1)
		//		(x-1, y)		(x, y)			(x+1, y)
		//		(x-1, y+1)		(x, y+1)		(x+1, y+1)
		//	
		//		p0				p1				p2
		//		p3				p4				p5
		//		p6				p7				p8

		if (m_imgIN.imageFile.bitmapInfoHeader.biBitCount == 8)
		{
			for (int y = 0; y < eof.y; y++)
			{
				for (int x = 0; x < eof.x; x++)
				{
					brightness = 0;
					sumMask = 0;

					if (x <= 0 || y <= 0 || x >= eof.x - 1 || y >= eof.y - 1)
						m_imgOUT.imageFile.SetPixel8(x, y, ClipValue(m_imgIN.imageFile.GetPixel8(x, y)));
					
					for (int i = -1; i < 2; i++)
					{
						for (int j = -1; j < 2; j++)
						{
							brightness += (int)(m_imgIN.imageFile.GetPixel8(x + j, y + i)) * mask[j + 1][i + 1];
							sumMask += mask[i + 1][j + 1];
						}
					}
					brightness = brightness / sumMask;
					brightness = ClipValue(brightness);
					m_imgOUT.imageFile.SetPixel8(x, y, brightness);
				}
			}
		}

		m_imgOUT.isImageLoaded = true;
		// Force the refresh of context in window
		InvalidateRect(NULL);
	}
	else if (sOption == L"3-GAUSS-FILTER") {

		CPaintDC dc(this);

		CRect rectangleIn;
		POINT bof, eof;
		int points[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 }, brightness = 0, sumMask = 0;
		int mask[3][3] = {{1, 4, 1,},{4, 12, 4,},{1, 4, 1,}};

		bof.x = 0, bof.y = 0;
		eof.x = m_imgIN.imageFile.bitmapInfoHeader.biWidth, eof.y = m_imgIN.imageFile.bitmapInfoHeader.biHeight;

		rectangleIn.SetRect(bof, eof);

		m_imgOUT.imageFile.CreateGreyscaleDIB(rectangleIn, GetDeviceCaps(dc.GetSafeHdc(), HORZRES), GetDeviceCaps(dc.GetSafeHdc(), HORZRES));

		//		(x-1, y-1)		(x, y-1)		(x+1, y-1)
		//		(x-1, y)		(x, y)			(x+1, y)
		//		(x-1, y+1)		(x, y+1)		(x+1, y+1)
		//	
		//		p0				p1				p2
		//		p3				p4				p5
		//		p6				p7				p8

		if (m_imgIN.imageFile.bitmapInfoHeader.biBitCount == 8)
		{
			for (int y = 0; y < eof.y; y++)
			{
				for (int x = 0; x < eof.x; x++)
				{
					brightness = 0;
					sumMask = 0;

					if (x <= 0 || y <= 0 || x >= eof.x - 1 || y >= eof.y - 1)
						m_imgOUT.imageFile.SetPixel8(x, y, ClipValue(m_imgIN.imageFile.GetPixel8(x, y)));

					// Calculate to set the apropriate brightness
					for (int i = -1; i < 2; i++)
					{
						for (int j = -1; j < 2; j++)
						{
							brightness += (int)(m_imgIN.imageFile.GetPixel8(x + j, y + i)) * mask[j + 1][i + 1];
							sumMask += mask[i + 1][j + 1];
						}
					}

					brightness = brightness / sumMask;
					brightness = ClipValue(brightness);
					m_imgOUT.imageFile.SetPixel8(x, y, brightness);
				}
			}
		}

		m_imgOUT.isImageLoaded = true;
		// Force the refresh of context in window
		InvalidateRect(NULL);
	}
	else if (sOption == L"3-SOBEL-FIRST-FILTER") {

		CPaintDC dc(this);

		CRect rectangleIn;
		POINT bof, eof;
		int points[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 }, brightness = 0;
		int mask[3][3] = {{1, 2, 1,},{0, 0, 0,},{-1, -2, -1,}};

		bof.x = 0, bof.y = 0;
		eof.x = m_imgIN.imageFile.bitmapInfoHeader.biWidth, eof.y = m_imgIN.imageFile.bitmapInfoHeader.biHeight;

		rectangleIn.SetRect(bof, eof);

		m_imgOUT.imageFile.CreateGreyscaleDIB(rectangleIn, GetDeviceCaps(dc.GetSafeHdc(), HORZRES), GetDeviceCaps(dc.GetSafeHdc(), HORZRES));

		//		(x-1, y-1)		(x, y-1)		(x+1, y-1)
		//		(x-1, y)		(x, y)			(x+1, y)
		//		(x-1, y+1)		(x, y+1)		(x+1, y+1)
		//	
		//		p0				p1				p2
		//		p3				p4				p5
		//		p6				p7				p8

		if (m_imgIN.imageFile.bitmapInfoHeader.biBitCount == 8)
		{
			for (int y = 0; y < eof.y; y++)
			{
				for (int x = 0; x < eof.x; x++)
				{
					brightness = 0;

					if (x <= 0 || y <= 0 || x >= eof.x - 1 || y >= eof.y - 1)
						m_imgOUT.imageFile.SetPixel8(x, y, ClipValue(m_imgIN.imageFile.GetPixel8(x, y) + ABOVE_ZERO));

					// Calculate to set the apropriate brightness
					for (int i = -1; i < 2; i++)
						for (int j = -1; j < 2; j++)
							brightness += (int)(m_imgIN.imageFile.GetPixel8(x + j, y + i)) * mask[j + 1][i + 1];

					brightness += ABOVE_ZERO;
					brightness = ClipValue(brightness);
					m_imgOUT.imageFile.SetPixel8(x, y, brightness);
				}
			}
		}

		m_imgOUT.isImageLoaded = true;
		// Force the refresh of context in window
		InvalidateRect(NULL);
	}
	else if (sOption == L"3-SOBEL-SECOND-FILTER") {

		CPaintDC dc(this);

		CRect rectangleIn;
		POINT bof, eof;
		int points[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 }, brightness = 0;
		int mask[3][3] =  {{-1, 0, 1,},{-2, 0, 2,},{-1, 0, 1,}};

		bof.x = 0, bof.y = 0;
		eof.x = m_imgIN.imageFile.bitmapInfoHeader.biWidth, eof.y = m_imgIN.imageFile.bitmapInfoHeader.biHeight;

		rectangleIn.SetRect(bof, eof);

		m_imgOUT.imageFile.CreateGreyscaleDIB(rectangleIn, GetDeviceCaps(dc.GetSafeHdc(), HORZRES), GetDeviceCaps(dc.GetSafeHdc(), HORZRES));

		//		(x-1, y-1)		(x, y-1)		(x+1, y-1)
		//		(x-1, y)		(x, y)			(x+1, y)
		//		(x-1, y+1)		(x, y+1)		(x+1, y+1)
		//	
		//		p0				p1				p2
		//		p3				p4				p5
		//		p6				p7				p8

		if (m_imgIN.imageFile.bitmapInfoHeader.biBitCount == 8)
		{
			for (int y = 0; y < eof.y; y++)
			{
				for (int x = 0; x < eof.x; x++)
				{
					brightness = 0;

					if (x <= 0 || y <= 0 || x >= eof.x - 1 || y >= eof.y - 1)
						m_imgOUT.imageFile.SetPixel8(x, y, ClipValue(m_imgIN.imageFile.GetPixel8(x, y) + ABOVE_ZERO));

					// Calculate to set the apropriate brightness
					for (int i = -1; i < 2; i++)
						for (int j = -1; j < 2; j++)
							brightness += (int)(m_imgIN.imageFile.GetPixel8(x + j, y + i)) * mask[j + 1][i + 1];

					brightness += ABOVE_ZERO;
					brightness = ClipValue(brightness);
					m_imgOUT.imageFile.SetPixel8(x, y, brightness);
				}
			}
		}

		m_imgOUT.isImageLoaded = true;
		// Force the refresh of context in window
		InvalidateRect(NULL);
	}
	else if (sOption == L"3-LAPLACIAN-FILTER") {

		CPaintDC dc(this);

		CRect rectangleIn;
		POINT bof, eof;
		int points[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 }, brightness = 0;
		int mask[3][3] = {{-2, 1, -2,},{1, 4, 1,},{-2, 1, -2,}};

		bof.x = 0, bof.y = 0;
		eof.x = m_imgIN.imageFile.bitmapInfoHeader.biWidth, eof.y = m_imgIN.imageFile.bitmapInfoHeader.biHeight;

		rectangleIn.SetRect(bof, eof);

		m_imgOUT.imageFile.CreateGreyscaleDIB(rectangleIn, GetDeviceCaps(dc.GetSafeHdc(), HORZRES), GetDeviceCaps(dc.GetSafeHdc(), HORZRES));

		//		(x-1, y-1)		(x, y-1)		(x+1, y-1)
		//		(x-1, y)		(x, y)			(x+1, y)
		//		(x-1, y+1)		(x, y+1)		(x+1, y+1)
		//	
		//		p0				p1				p2
		//		p3				p4				p5
		//		p6				p7				p8

		if (m_imgIN.imageFile.bitmapInfoHeader.biBitCount == 8)
		{
			for (int y = 0; y < eof.y; y++)
			{
				for (int x = 0; x < eof.x; x++)
				{
					brightness = 0;

					if (x <= 0 || y <= 0 || x >= eof.x - 1 || y >= eof.y - 1)
						m_imgOUT.imageFile.SetPixel8(x, y, ClipValue(m_imgIN.imageFile.GetPixel8(x, y) + ABOVE_ZERO));

					// Calculate to set the apropriate brightness
					for (int i = -1; i < 2; i++)
						for (int j = -1; j < 2; j++)
							brightness += (int)(m_imgIN.imageFile.GetPixel8(x + j, y + i)) * mask[j + 1][i + 1];

					brightness += ABOVE_ZERO;
					brightness = ClipValue(brightness);
					m_imgOUT.imageFile.SetPixel8(x, y, brightness);
				}
			}
		}

		m_imgOUT.isImageLoaded = true;
		// Force the refresh of context in window
		InvalidateRect(NULL);
	}
	else if (sOption == L"3-SHARPENING-FILTER") {

		CPaintDC dc(this);

		CRect rectangleIn;
		POINT bof, eof;
		int points[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 }, brightness = 0, sumMask = 0;
		int mask[3][3] = { {0, -1, 0,},{-1, 5, -1,},{0, -1, 0,} };

		bof.x = 0, bof.y = 0;
		eof.x = m_imgIN.imageFile.bitmapInfoHeader.biWidth, eof.y = m_imgIN.imageFile.bitmapInfoHeader.biHeight;

		rectangleIn.SetRect(bof, eof);

		m_imgOUT.imageFile.CreateGreyscaleDIB(rectangleIn, GetDeviceCaps(dc.GetSafeHdc(), HORZRES), GetDeviceCaps(dc.GetSafeHdc(), HORZRES));

		//		(x-1, y-1)		(x, y-1)		(x+1, y-1)
		//		(x-1, y)		(x, y)			(x+1, y)
		//		(x-1, y+1)		(x, y+1)		(x+1, y+1)
		//	
		//		p0				p1				p2
		//		p3				p4				p5
		//		p6				p7				p8

		if (m_imgIN.imageFile.bitmapInfoHeader.biBitCount == 8)
		{
			for (int y = 0; y < eof.y; y++)
			{
				for (int x = 0; x < eof.x; x++)
				{
					brightness = 0;

					if (x <= 0 || y <= 0 || x >= eof.x - 1 || y >= eof.y - 1)
						m_imgOUT.imageFile.SetPixel8(x, y, ClipValue(m_imgIN.imageFile.GetPixel8(x, y) + ABOVE_ZERO));

					// Calculate to set the apropriate brightness
					for (int i = -1; i < 2; i++)
						for (int j = -1; j < 2; j++)
							brightness += (int)(m_imgIN.imageFile.GetPixel8(x + j, y + i)) * mask[j + 1][i + 1];

					brightness = ClipValue(brightness);
					m_imgOUT.imageFile.SetPixel8(x, y, brightness);
				}
			}
		}

		m_imgOUT.isImageLoaded = true;
		// Force the refresh of context in window
		InvalidateRect(NULL);
	}
	else if (sOption == L"5-HOUGH") {
		
		// For each x,y we use ro = x * cos(theta) + y * sin(theta)
		// we take theta in the loop from 0 to 360
		CPaintDC dc(this);

		int fileWidth = m_imgIN.imageFile.bitmapInfoHeader.biWidth,
			fileHeight = m_imgIN.imageFile.bitmapInfoHeader.biHeight;
		int fileWidthHalf = fileWidth / 2, fileHeightHalf = fileHeight / 2;
		int size = fileWidth * fileHeight;
		bool isWhite = false;

		int ro = 0,
			roMax = pow(pow(fileWidth, 2) + pow(fileHeight, 2), 0.5),
			thetaSize = 360;

		// Creating the accumulator
		std::vector<std::vector<int>> accumulator;
		accumulator.resize(thetaSize);

		for (auto& row : accumulator) row.resize(roMax);
		
		CRect rectangleIn;
		POINT bof, eof;

		bof.x = 0, bof.y = 0;
		eof.x = thetaSize, eof.y = roMax;

		rectangleIn.SetRect(bof, eof);

		m_imgOUT.imageFile.CreateGreyscaleDIB(rectangleIn, GetDeviceCaps(dc.GetSafeHdc(), HORZRES), GetDeviceCaps(dc.GetSafeHdc(), HORZRES));

		for (int x = 0; x < fileWidth; x++) {
			for (int y = 0; y < fileHeight; y++) {
				// If isWhite we don't care
				isWhite = m_imgIN.imageFile.GetPixel1(x, y);
				if (isWhite) continue;

				// Moving across the image
				int movedX = x - fileWidthHalf;
				int movedY = y - fileHeightHalf;

				// Calculating the value for accumulator
				for (int theta = 0; theta < thetaSize; theta++) {
					ro = movedX * cos(CalculateRadian(theta)) + movedY * sin(CalculateRadian(theta));

					if (ro < 0 || ro > roMax)
						continue;

					accumulator[theta][ro] += 1;
				}
			}
		}

		// Calculating the best looking line in the image
		int maxValueAccumulated = 0, minValueAccumulated = 255;

		for (int y = 0; y < accumulator.size(); y++) {
			for (int x = 0; x < accumulator[0].size(); x++) {
				maxValueAccumulated = max(ClipValue(accumulator[y][x]), maxValueAccumulated);
				minValueAccumulated = min(ClipValue(accumulator[y][x]), minValueAccumulated);
			}
		}

		for (int y = 0; y < accumulator.size(); y++) {
			for (int x = 0; x < accumulator[0].size(); x++) {
				int value = ClipValue(accumulator[y][x]);
				int scaledValue = value * 255 / (maxValueAccumulated - minValueAccumulated);
				
				m_imgOUT.imageFile.SetPixel8(y, x, 255 - scaledValue);
			}
		}

		m_imgOUT.isImageLoaded = true;
		// Force the refresh of context in window
		InvalidateRect(NULL);
	}
	else if (sOption == L"5-HOUGH-SLIDER") {

		// For each x,y we use ro = x * cos(theta) + y * sin(theta)
		// we take theta in the loop from 0 to 360
		CPaintDC dc(this);

		int fileWidth = m_imgIN.imageFile.bitmapInfoHeader.biWidth,
			fileHeight = m_imgIN.imageFile.bitmapInfoHeader.biHeight;
		int fileWidthHalf = fileWidth / 2, fileHeightHalf = fileHeight / 2;
		int size = fileWidth * fileHeight;
		bool isWhite = false;
		int thetaValue = sliderControl.GetPos();

		int ro = 0,
			roMax = pow(pow(fileWidth, 2) + pow(fileHeight, 2), 0.5),
			thetaSize = 360;

		// Creating the accumulator
		std::vector<std::vector<int>> accumulator;
		accumulator.resize(thetaSize);

		for (auto& row : accumulator) row.resize(roMax);

		CRect rectangleIn;
		POINT bof, eof;

		bof.x = 0, bof.y = 0;
		eof.x = thetaSize, eof.y = roMax;

		rectangleIn.SetRect(bof, eof);

		m_imgOUT.imageFile.CreateGreyscaleDIB(rectangleIn, GetDeviceCaps(dc.GetSafeHdc(), HORZRES), GetDeviceCaps(dc.GetSafeHdc(), HORZRES));

		for (int x = 0; x < fileWidth; x++) {
			for (int y = 0; y < fileHeight; y++) {
				// If isWhite we don't care
				isWhite = m_imgIN.imageFile.GetPixel1(x, y);
				if (isWhite) continue;

				// Moving across the image
				int movedX = x - fileWidthHalf;
				int movedY = y - fileHeightHalf;

				// Calculating the value for accumulator
				for (int theta = 0; theta < thetaSize; theta += thetaValue) {
					ro = movedX * cos(CalculateRadian(theta)) + movedY * sin(CalculateRadian(theta));

					if (ro < 0 || ro > roMax)
						continue;

					for (int j = 0; j < thetaValue; j++) {
						if (theta + j >= thetaSize) break;
						accumulator[theta + j][ro] += 1;
					}
				}
			}
		}

		// Calculating the best looking line in the image
		int maxValueAccumulated = 0, minValueAccumulated = 255;

		for (int y = 0; y < accumulator.size(); y++) {
			for (int x = 0; x < accumulator[0].size(); x++) {
				maxValueAccumulated = max(ClipValue(accumulator[y][x]), maxValueAccumulated);
				minValueAccumulated = min(ClipValue(accumulator[y][x]), minValueAccumulated);
			}
		}

		for (int y = 0; y < accumulator.size(); y++) {
			for (int x = 0; x < accumulator[0].size(); x++) {
				int value = ClipValue(accumulator[y][x]);
				int scaledValue = value * 255 / (maxValueAccumulated - minValueAccumulated);

				m_imgOUT.imageFile.SetPixel8(y, x, 255 - scaledValue);
			}
		}

		m_imgOUT.isImageLoaded = true;
		// Force the refresh of context in window
		InvalidateRect(NULL);
	}
	else if (sOption == L"6-FOURIER-AMPLITUDE") {

		CPaintDC dc(this);

		int fileWidth = m_imgIN.imageFile.bitmapInfoHeader.biWidth,
			fileHeight = m_imgIN.imageFile.bitmapInfoHeader.biHeight;
		int fileWidthHalf = fileWidth / 2, fileHeightHalf = fileHeight / 2;
		int size = fileWidth * fileHeight, transformedPixel, pixel;

		CRect rectangleIn;
		POINT bof, eof;

		bof.x = 0, bof.y = 0;
		eof.x = m_imgIN.imageFile.bitmapInfoHeader.biWidth, eof.y = m_imgIN.imageFile.bitmapInfoHeader.biHeight;

		rectangleIn.SetRect(bof, eof);

		m_imgOUT.imageFile.CreateGreyscaleDIB(rectangleIn, GetDeviceCaps(dc.GetSafeHdc(), HORZRES), GetDeviceCaps(dc.GetSafeHdc(), HORZRES));

		float alpha = 0.53836;
		float beta = 1 - alpha;

		float N = pow(pow(fileWidth, 2) + pow(fileHeight, 2), 0.5);
		float r, n, w;

		// Hamming's eye
		for (int x = 0; x < fileWidth; x++) {
			for (int y = 0; y < fileHeight; y++) {

				pixel = m_imgIN.imageFile.GetPixel8(x, y);

				r = pow(pow(x - fileWidthHalf, 2) + pow(y - fileHeightHalf, 2), 0.5);

				n = N / 2 - r;

				w = alpha - beta * cos((2 * M_PI * n) / (N - 1));

				transformedPixel = pixel * w;

				m_imgOUT.imageFile.SetPixel8(x, y, transformedPixel);
			}
		}

		long double maxAmplitude = -FLT_MAX, minAmplitude = FLT_MAX, realPartSum = 0, imaginaryPartSum = 0, currentAmplitude;

		long double* amplitudes = new long double[size];

		for (int u = 0; u < fileWidth; u++) {
			for (int v = 0; v < fileHeight; v++) {

				realPartSum = 0, imaginaryPartSum = 0;

				for (int x = 0; x < fileWidth; x++) {
					for (int y = 0; y < fileHeight; y++) {
						realPartSum += long double(m_imgOUT.imageFile.GetPixel8(x, y)) * cos(2 * M_PI * ((long double(u * x) / long double(fileWidth)) + (long double(v * y) / long double(fileHeight))));
						imaginaryPartSum -= long double(m_imgOUT.imageFile.GetPixel8(x, y)) * sin(2 * M_PI * ((long double(u * x) / long double(fileWidth)) + (long double(v * y) / long double(fileHeight))));
					}
				}

				currentAmplitude = pow(pow(realPartSum, 2) + pow(imaginaryPartSum, 2), 0.5);
				// Scale the values to 0..255
				currentAmplitude = log(1 + currentAmplitude);

				if (currentAmplitude > maxAmplitude) maxAmplitude = currentAmplitude;
				if (currentAmplitude < minAmplitude) minAmplitude = currentAmplitude;

				amplitudes[fileWidth * v + u] = currentAmplitude;
			}
		}

		for (int x = 0; x < fileWidth; x++) {
			for (int y = 0; y < fileHeight; y++) {
				long double val = (amplitudes[fileWidth * y + x] - minAmplitude) / (maxAmplitude - minAmplitude);
				val *= 255;
				m_imgOUT.imageFile.SetPixel8(x, y, BYTE(val));
			}
		}

		int xOffset = (fileWidth + (fileWidth % 2)) / 2,
			yOffset = (fileHeight + (fileHeight % 2)) / 2;

		BYTE pixelOne, pixelTwo;

		for (int x = 0; x < xOffset; x++) {
			for (int y = 0; y < yOffset; y++) {

				pixelOne = m_imgOUT.imageFile.GetPixel8(x, y);
				pixelTwo = m_imgOUT.imageFile.GetPixel8(x + xOffset - 1, y + yOffset - 1);

				m_imgOUT.imageFile.SetPixel8(x, y, pixelTwo);
				m_imgOUT.imageFile.SetPixel8(x + xOffset - 1, y + yOffset - 1, pixelOne);
			}
		}

		for (int x = xOffset; x < fileWidth; x++) {
			for (int y = 0; y < yOffset; y++) {

				pixelOne = m_imgOUT.imageFile.GetPixel8(x, y);
				pixelTwo = m_imgOUT.imageFile.GetPixel8(x - xOffset, y + yOffset - 1);

				m_imgOUT.imageFile.SetPixel8(x, y, pixelTwo);
				m_imgOUT.imageFile.SetPixel8(x - xOffset, y + yOffset - 1, pixelOne);
			}
		}

		m_imgOUT.isImageLoaded = true;
		// Force the refresh of context in window
		InvalidateRect(NULL);
	}
	else if (sOption == L"6-FOURIER-PHASE") {

		CPaintDC dc(this);

		int fileWidth = m_imgIN.imageFile.bitmapInfoHeader.biWidth,
			fileHeight = m_imgIN.imageFile.bitmapInfoHeader.biHeight;
		int fileWidthHalf = fileWidth / 2, fileHeightHalf = fileHeight / 2;
		int size = fileWidth * fileHeight, transformedPixel, pixel;

		CRect rectangleIn;
		POINT bof, eof;

		bof.x = 0, bof.y = 0;
		eof.x = m_imgIN.imageFile.bitmapInfoHeader.biWidth, eof.y = m_imgIN.imageFile.bitmapInfoHeader.biHeight;

		rectangleIn.SetRect(bof, eof);

		m_imgOUT.imageFile.CreateGreyscaleDIB(rectangleIn, GetDeviceCaps(dc.GetSafeHdc(), HORZRES), GetDeviceCaps(dc.GetSafeHdc(), HORZRES));

		float alpha = 0.53836;
		float beta = 1 - alpha;
		float N = pow(pow(fileWidth, 2) + pow(fileHeight, 2), 0.5);
		float r, n, w;

		// Hamming's eye
		for (int x = 0; x < fileWidth; x++) {
			for (int y = 0; y < fileHeight; y++) {

				pixel = m_imgIN.imageFile.GetPixel8(x, y);

				r = pow(pow(x - fileWidthHalf, 2) + pow(y - fileHeightHalf, 2), 0.5);

				n = N / 2 - r;

				w = alpha - beta * cos((2 * M_PI * n) / (N - 1));

				transformedPixel = pixel * w;

				m_imgOUT.imageFile.SetPixel8(x, y, transformedPixel);
			}
		}

		long double maxPhase = -FLT_MAX, minPhase = FLT_MAX, realPartSum = 0, imaginaryPartSum = 0, currentPhase;

		long double* phases = new long double[size];

		for (int u = 0; u < fileWidth; u++) {
			for (int v = 0; v < fileHeight; v++) {

				realPartSum = 0, imaginaryPartSum = 0;

				for (int x = 0; x < fileWidth; x++) {
					for (int y = 0; y < fileHeight; y++) {
						realPartSum += long double(m_imgOUT.imageFile.GetPixel8(x, y)) * cos(2 * M_PI * ((long double(u * x) / long double(fileWidth)) + (long double(v * y) / long double(fileHeight))));
						imaginaryPartSum -= long double(m_imgOUT.imageFile.GetPixel8(x, y)) * sin(2 * M_PI * ((long double(u * x) / long double(fileWidth)) + (long double(v * y) / long double(fileHeight))));
					}
				}

				if (realPartSum < 0.001) {
					if (imaginaryPartSum > 0) currentPhase = M_PI / 2;
					else currentPhase = -M_PI / 2;
				}
				else currentPhase = atan(imaginaryPartSum / realPartSum);

				if (currentPhase > maxPhase) maxPhase = currentPhase;
				if (currentPhase < minPhase) minPhase = currentPhase;

				phases[fileWidth * v + u] = currentPhase;
			}
		}

		for (int x = 0; x < fileWidth; x++) {
			for (int y = 0; y < fileHeight; y++) {
				long double val = (phases[fileWidth * y + x] + (M_PI/2)) / M_PI;
				val *= 255;
				m_imgOUT.imageFile.SetPixel8(x, y, BYTE(val));
			}
		}

		int xOffset = (fileWidth + (fileWidth % 2)) / 2,
			yOffset = (fileHeight + (fileHeight % 2)) / 2;

		BYTE pixelOne, pixelTwo;

		for (int x = 0; x < xOffset; x++) {
			for (int y = 0; y < yOffset; y++) {

				pixelOne = m_imgOUT.imageFile.GetPixel8(x, y);
				pixelTwo = m_imgOUT.imageFile.GetPixel8(x + xOffset - 1, y + yOffset - 1);

				m_imgOUT.imageFile.SetPixel8(x, y, pixelTwo);
				m_imgOUT.imageFile.SetPixel8(x + xOffset - 1, y + yOffset - 1, pixelOne);
			}
		}

		for (int x = xOffset; x < fileWidth; x++) {
			for (int y = 0; y < yOffset; y++) {

				pixelOne = m_imgOUT.imageFile.GetPixel8(x, y);
				pixelTwo = m_imgOUT.imageFile.GetPixel8(x - xOffset, y + yOffset - 1);

				m_imgOUT.imageFile.SetPixel8(x, y, pixelTwo);
				m_imgOUT.imageFile.SetPixel8(x - xOffset, y + yOffset - 1, pixelOne);
			}
		}

		m_imgOUT.isImageLoaded = true;
		// Force the refresh of context in window
		InvalidateRect(NULL);
	}
	else if (sOption == L"6-FOURIER-HAMMING-EYE") {

		CPaintDC dc(this);

		int fileWidth = m_imgIN.imageFile.bitmapInfoHeader.biWidth,
			fileHeight = m_imgIN.imageFile.bitmapInfoHeader.biHeight;
		int fileWidthHalf = fileWidth / 2, fileHeightHalf = fileHeight / 2;
		int size = fileWidth * fileHeight, transformedPixel, pixel;

		CRect rectangleIn;
		POINT bof, eof;

		bof.x = 0, bof.y = 0;
		eof.x = m_imgIN.imageFile.bitmapInfoHeader.biWidth, eof.y = m_imgIN.imageFile.bitmapInfoHeader.biHeight;

		rectangleIn.SetRect(bof, eof);

		m_imgOUT.imageFile.CreateGreyscaleDIB(rectangleIn, GetDeviceCaps(dc.GetSafeHdc(), HORZRES), GetDeviceCaps(dc.GetSafeHdc(), HORZRES));

		float alpha = 0.53836;
		float beta = 1 - alpha;
		float N = pow(pow(fileWidth, 2) + pow(fileHeight, 2), 0.5);
		float r, n, w;

		// Hamming's eye
		for (int x = 0; x < fileWidth; x++) {
			for (int y = 0; y < fileHeight; y++) {

				pixel = m_imgIN.imageFile.GetPixel8(x, y);

				r = pow(pow(x - fileWidthHalf, 2) + pow(y - fileHeightHalf, 2), 0.5);

				n = N / 2 - r;

				w = alpha - beta * cos((2 * M_PI * n) / (N - 1));

				transformedPixel = pixel * w;

				m_imgOUT.imageFile.SetPixel8(x, y, transformedPixel);
			}
		}

		m_imgOUT.isImageLoaded = true;
		// Force the refresh of context in window
		InvalidateRect(NULL);
	}
};

void CPODlg::OnBnClickedButtonSave()
{
	WCHAR strFilter[] = { L"Image Files (*.bmp)|*.bmp|All Files (*.*)|*.*||" };

	CFileDialog FileDlg(FALSE, NULL, NULL, 0, strFilter);

	if (FileDlg.DoModal() == IDOK)
		m_imgOUT.imageFile.SaveDIB(FileDlg.GetPathName());
};

void CPODlg::OnBnClickedButtonParams()
{
	CParamsDlg paramsDlg;
	CString s;

	if (paramsDlg.DoModal() == IDOK)
	{
		s = paramsDlg.m_sParams;
	}
}

void CPODlg::OnCbnSelchangeCombo1()
{
	CString sOption;
	m_combo1.GetLBText(m_combo1.GetCurSel(), sOption);
	if (sOption == L"1-SET-BRIGHTNESS")
	{
		sliderControl.SetRange(-100, 100, true);
		sliderControl.SetPos(0);
	}
	if (sOption == L"1-SET-CONTRAST")
	{
		sliderControl.SetRange(1, 50, true);
		sliderControl.SetPos(1);
	}
	if (sOption == L"1-EXPONENTIATION")
	{
		sliderControl.SetRange(1, 30, true);
		sliderControl.SetPos(1);
	}
	if (sOption == L"5-HOUGH-SLIDER")
	{
		sliderControl.SetRange(1, 20, true);
		sliderControl.SetPos(1);
	}
}

void CAboutDlg::OnNMReleasedcaptureSlider1(NMHDR* pNMHDR, LRESULT* pResult)
{
	
}

float CPODlg::LimitInterval(const int value)
{
	if (value < 0)
		return 0;
	else if (value > 255)
		return 255;
	else
		return value;
};

int CPODlg::ClipValue(const int value) {
	if (value < 0)
		return 0;
	else if (value > 255)
		return 255;
	else
		return value;
}

double CPODlg::getAverageValueFromHistogram(int start, int end)
{
	int p0 = 0;
	double u0 = 0;

	for (int i = start; i < end; i++)
	{
		u0 += i * m_imgIN.imageFile.histogram8[i];
		p0 += m_imgIN.imageFile.histogram8[i];
	}

	return u0 / p0;
}

void CPODlg::DrawHistogram(int bitCount)
{
	histogram.imgIn.LoadDIB(m_imgIN.imageFile.filePath);
	histogram.bitCount = bitCount;
	histogram.DoModal();
};

void CPODlg::OnBnClickedButton1() {
	DrawHistogram(m_imgIN.imageFile.bitmapInfo->bmiHeader.biBitCount);
};

float CPODlg::CalculateRadian(int degree)
{
	float radian = (float)(2 * degree * M_PI) / (float)(360);
	return radian;
}