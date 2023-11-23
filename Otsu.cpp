// Otsu.cpp: plik implementacji
//

//#include "pch.h"
#include "stdafx.h"
#include "PO1.h"
#include "Otsu.h"
#include "afxdialogex.h"


// Okno dialogowe Otsu

IMPLEMENT_DYNAMIC(Otsu, CDialogEx)

Otsu::Otsu(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

Otsu::~Otsu()
{
}

void Otsu::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Otsu, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// Procedury obsługi komunikatów Otsu
void Otsu::OnPaint(){

	CPaintDC dc(this);
	CRect dst;
	HDC ctx = ::GetDC(this->m_hWnd);
	POINT topLeft, bottomRight;
	float maxValue = -FLT_MAX;
	HBRUSH pink = CreateSolidBrush(RGB(255, 20, 147)), aqua = CreateSolidBrush(RGB(0, 255, 255));


	for (int i = 0; i < 256; i++)
		if (values[i] > maxValue) maxValue = values[i];

	for (int i = 0; i < 256; i++) {
		topLeft.y = height - ((float)values[i] / maxValue) * height;
		topLeft.x = i + 50;
		bottomRight.x = i + 51;
		bottomRight.y = height;

		if (i == p)
		{
			// Straight line
			topLeft.y = height - 1000;
			dst.SetRect(topLeft, bottomRight);
			::FillRect(ctx, dst, pink);
		}
		else
		{
			dst.SetRect(topLeft, bottomRight);
			::FillRect(ctx, dst, aqua);
		}
	}

}

BOOL Otsu::OnInitDialog() {
	CDialogEx::OnInitDialog();
	SetWindowPos(NULL, 0, 0, 1200, height * 1.1, SWP_NOMOVE | SWP_NOZORDER);

	return TRUE;
}