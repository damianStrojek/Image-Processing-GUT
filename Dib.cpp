#include "stdafx.h"
#include "Dib.h"

Dib::Dib() {

}

Dib::~Dib() {
	// free existing pointer to avoid memory leaks
	if (bitmapInfo != nullptr)
		HeapFree(GetProcessHeap(), NULL, bitmapInfo);
};

// Load images from BMP files
bool Dib::LoadDIB(CString pathToFile) {

	CFile file;
	filePath = pathToFile;
	if (filePath == "") return false;

	// Read Bitmap File Header
	file.Open(filePath, CFile::modeReadWrite);
	file.Read(&bitmapFileHeader, sizeof(BITMAPFILEHEADER));

	// Read information about size of our image
	DWORD fileSizeInfo = (bitmapFileHeader.bfSize) - sizeof(bitmapFileHeader);
	if (bitmapInfo != nullptr) HeapFree(GetProcessHeap(), NULL, bitmapInfo);

	// Allocate the memory
	bitmapInfo = (BITMAPINFO*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, fileSizeInfo);

	// Read Bitmap Info
	file.Read(bitmapInfo, fileSizeInfo);
	arrayPointer = (BYTE*)bitmapInfo + bitmapFileHeader.bfOffBits - sizeof(bitmapFileHeader);
	file.Close();

	bitmapInfoHeader = ((BITMAPINFO*)bitmapInfo)->bmiHeader;
	// Read number of bytes in one line using the algorithm
	bytesInOneLine = ((bitmapInfoHeader.biBitCount * bitmapInfoHeader.biWidth + 31) / 32) * 4;

	return true;
};

// Show image loaded by loadDIB()
bool Dib::PaintDIB(HDC context, CRect targetRect, CRect sourceRect) {

	// Create and initialize parameters of source and target
	int sourceX = 0, sourceY = 0,
		sourceWidth = bitmapInfoHeader.biWidth, sourceHeight = bitmapInfoHeader.biHeight;
	int targetX = 0, targetY = 0,
		targetWidth = targetRect.Width(), targetHeight = targetRect.Height();

	BYTE* pointerToByteArray = arrayPointer;
	BITMAPINFO* pointerToBitmapInfo = bitmapInfo;

	// If width of the source image is lower than source height than we have to recalculate the width
	if (sourceWidth < sourceHeight) {
		double proportion = (double)sourceHeight / (double)targetHeight;
		targetWidth = sourceWidth * (1 / proportion);
	}
	// If height of the source image is lower than source width than we have to recalculate the height
	else {
		double proportion = (double)sourceWidth / (double)targetWidth;
		targetHeight = sourceHeight * (1 / proportion);
	}

	SetStretchBltMode(context, COLORONCOLOR);

	StretchDIBits(context, targetX, targetY, targetWidth, targetHeight,
		sourceX, sourceY, sourceWidth, sourceHeight,
		pointerToByteArray, pointerToBitmapInfo,
		DIB_RGB_COLORS, SRCCOPY);

	return true;
};

// Create empty 8-bit bitmaps in greyscale
bool Dib::CreateGreyscaleDIB(CRect imageSize, int xPPM, int yPPM) {

	// Initialize empty header of bitmap file
	bitmapFileHeader = BITMAPFILEHEADER();
	bitmapFileHeader.bfReserved1 = 0;
	bitmapFileHeader.bfReserved2 = 0;
	((BYTE*)&bitmapFileHeader.bfType)[0] = 0x42;
	((BYTE*)&bitmapFileHeader.bfType)[1] = 0x4D;

	// Read number of bytes in one line using the algorithm
	bytesInOneLine = ((8 * imageSize.right + 31) / 32) * 4;
	// Bitmap size (number of rows * number of bytes in rows)
	long int bitmapSize = imageSize.bottom * bytesInOneLine;

	// free existing pointer to avoid memory leaks
	if (bitmapInfo != nullptr)
		HeapFree(GetProcessHeap(), NULL, bitmapInfo);

	// Initialize bitmap file
	bitmapInfo = (BITMAPINFO*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD) + bitmapSize);
	bitmapInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitmapInfo->bmiHeader.biWidth = imageSize.right;
	bitmapInfo->bmiHeader.biHeight = imageSize.bottom;
	bitmapInfo->bmiHeader.biPlanes = 1;
	bitmapInfo->bmiHeader.biBitCount = 8;
	bitmapInfo->bmiHeader.biCompression = BI_RGB;

	bitmapInfo->bmiHeader.biSizeImage = 0;
	bitmapInfo->bmiHeader.biXPelsPerMeter = xPPM;
	bitmapInfo->bmiHeader.biYPelsPerMeter = yPPM;
	bitmapInfo->bmiHeader.biClrUsed = 0;

	bitmapInfo->bmiHeader.biClrImportant = 0;

	// Color palette
	for (int i = 0; i < 256; i++) {
		bitmapInfo->bmiColors[i].rgbBlue = i;
		bitmapInfo->bmiColors[i].rgbGreen = i;
		bitmapInfo->bmiColors[i].rgbRed = i;
		bitmapInfo->bmiColors[i].rgbReserved = i;
	}

	// Initialize ending
	bitmapInfoHeader = bitmapInfo->bmiHeader;
	bitmapFileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD);
	bitmapFileHeader.bfSize = bitmapFileHeader.bfOffBits + bitmapSize;
	arrayPointer = (BYTE*)bitmapInfo + bitmapFileHeader.bfOffBits - sizeof(BITMAPFILEHEADER);

	return true;
};

// Read pixel values in 1-bit bitmaps
bool Dib::GetPixel1(int x, int y) {

	if (bitmapInfoHeader.biBitCount == 1)
	{
		int shiftByteAmount = x / 8;
		long int bytePosition = y * bytesInOneLine + shiftByteAmount;
		BYTE byte = ((BYTE*)arrayPointer)[bytePosition];
		BYTE pattern = 0x80 >> (x % 8);
		return byte & pattern;
	}

	return false;
};

// Read pixel values in 8-bit bitmaps
BYTE Dib::GetPixel8(int x, int y) {
	if (bitmapInfoHeader.biBitCount == 8)
	{
		// Read number of bytes in one line using the algorithm
		bytesInOneLine = ((bitmapInfoHeader.biBitCount * bitmapInfoHeader.biWidth + 31) / 32) * 4;

		int colorIndex = x + y * (bytesInOneLine);
		BYTE value = ((BYTE*)arrayPointer)[colorIndex];

		return value;
	}

	return false;
};

// Read pixel values in 24-bit bitmaps
RGBTRIPLE Dib::GetPixel24(int x, int y) {
	if (bitmapInfoHeader.biBitCount == 24)
	{
		RGBTRIPLE value;
		int position = 3 * x + y * bytesInOneLine;
		value.rgbtGreen = ((BYTE*)arrayPointer)[position + 1];
		value.rgbtBlue = ((BYTE*)arrayPointer)[position + 2];
		value.rgbtRed = ((BYTE*)arrayPointer)[position];

		return value;
	}

	return RGBTRIPLE();
};

// Set pixel values in 8-bit bitmaps
bool Dib::SetPixel8(int x, int y, BYTE val) {
	if (bitmapInfoHeader.biBitCount == 8)
	{
		// Read number of bytes in one line using the algorithm
		bytesInOneLine = ((bitmapInfoHeader.biBitCount * bitmapInfoHeader.biWidth + 31) / 32) * 4;
		int colorIndex = x + y * (bytesInOneLine);
		((BYTE*)arrayPointer)[colorIndex] = val;
	}

	return false;
};

// Save BMP file
bool Dib::SaveDIB(CString pathToFile) {

	CFile file;
	pathToFile += ".bmp";
	file.Open(pathToFile, CFile::modeCreate | CFile::modeWrite);
	file.Write(&bitmapFileHeader, sizeof(BITMAPFILEHEADER));
	DWORD fileInfoSize = (bitmapFileHeader.bfSize) - sizeof(bitmapFileHeader);
	file.Write(bitmapInfo, fileInfoSize);
	file.Close();

	return true;
};

void Dib::CreateHistogram1bit()
{
	maxHistogram1[0] = 0;
	maxHistogram1[1] = 0;
	for (int i = 0; i < 950; i++)
	{
		histogram1[0][i] = 0;
		histogram1[1][i] = 0;
	}


	for (int y = 0; y < bitmapInfo->bmiHeader.biHeight; y++)
	{
		for (int x = 0; x < bitmapInfo->bmiHeader.biWidth; x++)
		{
			if (!GetPixel1(x, y))
			{
				histogram1[0][y]++;
				histogram1[1][x]++;
			}


			if (histogram1[0][y] > maxHistogram1[0])
				maxHistogram1[0] = histogram1[0][y];

			if (histogram1[1][x] > maxHistogram1[1])
				maxHistogram1[1] = histogram1[1][x];
		}
	}

}

int Dib::CreateHistogram8bit()
{
	maxHistogram8 = 0;
	for (int i = 0; i < 256; i++)
		histogram8[i] = 0;

	for (int y = 0; y < bitmapInfo->bmiHeader.biHeight; y++)
	{
		for (int x = 0; x < bitmapInfo->bmiHeader.biWidth; x++)
		{
			int pixel = GetPixel8(x, y);

			histogram8[pixel]++;

			if (histogram8[pixel] > maxHistogram8)
				maxHistogram8 = histogram8[pixel];
		}
	}
	return this->pictureThresholding;
};

void Dib::CreateHistogram24bit()
{
	for (int i = 0; i < 3; i++)
	{
		maxHistogram24[i] = 0;
		sumHistogram24[i] = 0;
	}
	for (int i = 0; i < 256; i++)
	{
		histogram24[0][i] = 0;			// R
		histogram24[1][i] = 0;			// G
		histogram24[2][i] = 0;			// B
		histogram24Brightness[i] = 0;	// BRIGHT
	}



	for (int y = 0; y < bitmapInfo->bmiHeader.biHeight; y++)
	{
		for (int x = 0; x < bitmapInfo->bmiHeader.biWidth; x++)
		{
			RGBTRIPLE pixel = GetPixel24(x, y);
			// Internet
			int brightness = 0.299 * pixel.rgbtRed + 0.587 * pixel.rgbtGreen + 0.114 * pixel.rgbtBlue;
			histogram24Brightness[brightness]++;

			histogram24[0][pixel.rgbtRed]++;
			histogram24[1][pixel.rgbtGreen]++;
			histogram24[2][pixel.rgbtBlue]++;

			if (histogram24[0][pixel.rgbtRed] > maxHistogram24[0])
				maxHistogram24[0] = histogram24[0][pixel.rgbtRed];
			if (histogram24[1][pixel.rgbtGreen] > maxHistogram24[1])
				maxHistogram24[1] = histogram24[1][pixel.rgbtGreen];
			if (histogram24[2][pixel.rgbtBlue] > maxHistogram24[2])
				maxHistogram24[2] = histogram24[2][pixel.rgbtBlue];
			if (histogram24Brightness[brightness] > maxHistogram24Brightness)
				maxHistogram24Brightness = histogram24Brightness[brightness];
		}
	}
}
