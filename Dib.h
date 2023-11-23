#pragma once
class Dib
{
public:

	bool LoadDIB(CString pathToFile);
	bool PaintDIB(HDC context, CRect targetRect, CRect sourceRect);
	bool CreateGreyscaleDIB(CRect imageSize, int xPPM, int yPPM);
	bool GetPixel1(int x, int y);
	BYTE GetPixel8(int x, int y);
	RGBTRIPLE GetPixel24(int x, int y);
	bool SetPixel8(int x, int y, BYTE val);
	bool SaveDIB(CString pathToFile);
	void CreateHistogram1bit();
	int CreateHistogram8bit();
	void CreateHistogram24bit();

	CString filePath;
	BITMAPINFO* bitmapInfo = nullptr;
	BITMAPINFOHEADER bitmapInfoHeader;
	BITMAPFILEHEADER bitmapFileHeader;

	int histogram8[256], maxHistogram8 = 0;
	int histogram24[3][256], maxHistogram24[3], sumHistogram24[3], maxHistogram24Brightness = 0, histogram24Brightness[256];
	int histogram1[2][950], maxHistogram1[2];
	int pictureThresholding = -1;

	// Used in the process of reading Bitmap Info		
	BYTE* arrayPointer;
	int bytesInOneLine;

	Dib();
	~Dib();
};
