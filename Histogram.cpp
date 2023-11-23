// Histogram.cpp: plik implementacji
//

//#include "pch.h"
#include "stdafx.h"
#include "PO1.h"
#include "Histogram.h"
#include "afxdialogex.h"


// Okno dialogowe Histogram

IMPLEMENT_DYNAMIC(Histogram, CDialogEx)

Histogram::Histogram(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}


Histogram::~Histogram()
{
}

void Histogram::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Histogram, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// Procedury obsługi komunikatów Histogram
	void Histogram::OnPaint()
	{

		CPaintDC dc(this);
		CRect dst;
		HDC ctx = ::GetDC(this->m_hWnd);
		POINT topLeft, bottomRight;
		int max = 0, maxB = 0;
		HBRUSH pink = CreateSolidBrush(RGB(255, 20, 147));
		HBRUSH aqua = CreateSolidBrush(RGB(0, 255, 255));

		if (bitCount == 1)
		{
			imgIn.CreateHistogram1bit();

			for (int i = 0; i < 950; i++)
			{
				// Y AXIS
				topLeft.y = height - ((float)imgIn.histogram1[0][i] / imgIn.maxHistogram1[0]) * height;
				topLeft.x = i;
				bottomRight.x = i + 1;
				bottomRight.y = height;
				dst.SetRect(topLeft, bottomRight);
				::FillRect(ctx, dst, CreateSolidBrush(RGB(0, 0, 0)));

				// X AXIS
				topLeft.y = height - ((float)imgIn.histogram1[1][i] / imgIn.maxHistogram1[1]) * height;
				topLeft.x = i + 700;
				bottomRight.x = i + 1 + 700;
				bottomRight.y = height;
				dst.SetRect(topLeft, bottomRight);
				::FillRect(ctx, dst, CreateSolidBrush(RGB(0, 0, 50)));
			}
		}
		else if (bitCount == 8)
		{
			int thresholding = imgIn.CreateHistogram8bit();

			for (int i = 1; i < 255; i++) {
				topLeft.y = height - ((float)imgIn.histogram8[i] / imgIn.maxHistogram8) * height;
				topLeft.x = i;
				bottomRight.x = i + 1;
				bottomRight.y = height;

				if (p > 0 && i == p)
				{
					// Straight line
					topLeft.y = height - imgIn.maxHistogram8;
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
		else if (bitCount == 24)
		{
			imgIn.CreateHistogram24bit();

			for (int i = 0; i < 255; i++)
			{
				// R
				topLeft.y = height - ((float)imgIn.histogram24[0][i] / imgIn.maxHistogram24[0]) * height;
				topLeft.x = i;
				bottomRight.x = i + 1;
				bottomRight.y = height;
				dst.SetRect(topLeft, bottomRight);
				::FillRect(ctx, dst, CreateSolidBrush(RGB(255, 0, 0)));

				// G
				topLeft.y = height - ((float)imgIn.histogram24[1][i] / imgIn.maxHistogram24[1]) * height;
				topLeft.x = i + 255 + 10;
				bottomRight.x = i + 1 + 255 + 10;
				bottomRight.y = height;
				dst.SetRect(topLeft, bottomRight);
				::FillRect(ctx, dst, CreateSolidBrush(RGB(0, 0, 255)));

				// B
				unsigned int max = (imgIn.maxHistogram24[2]);
				if (max > 25000) max = 25000;
				topLeft.y = height - ((float)imgIn.histogram24[2][i] / max) * height;
				topLeft.x = i + 255 * 2 + 20;
				bottomRight.x = i + 1 + 255 * 2 + 20;
				bottomRight.y = height;
				dst.SetRect(topLeft, bottomRight);
				::FillRect(ctx, dst, CreateSolidBrush(RGB(0, 255, 0)));

				if (imgIn.histogram24Brightness[i] > maxB) maxB = imgIn.histogram24Brightness[i];
				topLeft.y = height - ((float)imgIn.histogram24Brightness[i] / imgIn.maxHistogram24Brightness) * height;
				topLeft.x = i + 255 * 3 + 30;
				bottomRight.x = i + 1 + 255 * 3 + 30;
				bottomRight.y = height;
				dst.SetRect(topLeft, bottomRight);
				::FillRect(ctx, dst, CreateSolidBrush(RGB(255, 255, 255)));
			}
		}
	};

	BOOL Histogram::OnInitDialog()
	{

		CDialogEx::OnInitDialog();
		if (bitCount == 8)
			SetWindowPos(NULL, 0, 0, 400, height * 1.1, SWP_NOMOVE | SWP_NOZORDER);
		else
			SetWindowPos(NULL, 0, 0, 1200, height * 1.1, SWP_NOMOVE | SWP_NOZORDER);

		return TRUE;
	};