#include "PixelProcessors.h"

bool PixelProcessors::findPixelOnScreen(POINT minPoint, POINT maxPoint, COLORREF targetColor, Globals::Point& pointResult)
{

    int width = maxPoint.x - minPoint.x;
    int height = maxPoint.y - minPoint.y;

    HDC hdcScreen = GetDC(NULL);

    HDC hdcMem = CreateCompatibleDC(hdcScreen);

    HBITMAP hBitmap = CreateCompatibleBitmap(hdcScreen, width, height);
    SelectObject(hdcMem, hBitmap);

    BitBlt(hdcMem, 0, 0, width, height, hdcScreen, minPoint.x, minPoint.y, SRCCOPY);

    BITMAPINFO bitmapInfo;
    bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bitmapInfo.bmiHeader.biWidth = width;
    bitmapInfo.bmiHeader.biHeight = -height;
    bitmapInfo.bmiHeader.biPlanes = 1;
    bitmapInfo.bmiHeader.biBitCount = 32;
    bitmapInfo.bmiHeader.biCompression = BI_RGB;

    int bufferSize = width * height * 4;
    BYTE* buffer = new BYTE[bufferSize];

    GetDIBits(hdcMem, hBitmap, 0, height, buffer, &bitmapInfo, DIB_RGB_COLORS);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int pixelIndex = (y * width + x) * 4;
            BYTE b = buffer[pixelIndex];
            BYTE g = buffer[pixelIndex + 1];
            BYTE r = buffer[pixelIndex + 2];
            if (r == GetRValue(targetColor) && g == GetGValue(targetColor) && b == GetBValue(targetColor)) {
                pointResult = Globals::Point(x + minPoint.x, y + minPoint.y);
                delete[] buffer;
                DeleteObject(hBitmap);
                DeleteDC(hdcMem);
                ReleaseDC(NULL, hdcScreen);
                return true;
            }
        }
    }

    pointResult = Globals::Point(150, 900);
    delete[] buffer;
    DeleteObject(hBitmap);
    DeleteDC(hdcMem);
    ReleaseDC(NULL, hdcScreen);

    return false;
}

HBITMAP PixelProcessors::GetScreenBmp(HDC hdc, RECT captureArea) {
    int width = captureArea.right - captureArea.left;
    int height = captureArea.bottom - captureArea.top;

    HDC hCaptureDC = CreateCompatibleDC(hdc);
    HBITMAP hBitmap = CreateCompatibleBitmap(hdc, width, height);
    HGDIOBJ hOld = SelectObject(hCaptureDC, hBitmap);
    BOOL bOK = BitBlt(hCaptureDC, 0, 0, width, height, hdc, captureArea.left, captureArea.top, SRCCOPY | CAPTUREBLT);

    SelectObject(hCaptureDC, hOld);
    DeleteDC(hCaptureDC);
    return hBitmap;
}

bool PixelProcessors::IsColorMatch(COLORREF color1, COLORREF color2, int tolerance) {
    int r1 = GetRValue(color1), g1 = GetGValue(color1), b1 = GetBValue(color1);
    int r2 = GetRValue(color2), g2 = GetGValue(color2), b2 = GetBValue(color2);

    return abs(r1 - r2) <= tolerance &&
        abs(g1 - g2) <= tolerance &&
        abs(b1 - b2) <= tolerance;
}


Globals::ItemType2 PixelProcessors::AnalyzeSlot2(
    RECT slotRect, COLORREF whiteBorder, COLORREF whiteBorder2,
    COLORREF yellowBorder, COLORREF redBorder,
    COLORREF high, COLORREF middle, COLORREF low) {

    HDC hDC = GetDC(NULL);
    HBITMAP hBitmap = GetScreenBmp(hDC, slotRect);

    BITMAPINFO MyBMInfo = { 0 };
    MyBMInfo.bmiHeader.biSize = sizeof(MyBMInfo.bmiHeader);

    // Get bitmap information
    if (!GetDIBits(hDC, hBitmap, 0, 0, NULL, &MyBMInfo, DIB_RGB_COLORS)) {
        std::cerr << "Failed to get bitmap info!\n";
        return Globals::EMPTY2;
    }

    // Allocate memory for pixels
    BYTE* lpPixels = new BYTE[MyBMInfo.bmiHeader.biSizeImage];
    MyBMInfo.bmiHeader.biCompression = BI_RGB;

    if (!GetDIBits(hDC, hBitmap, 0, MyBMInfo.bmiHeader.biHeight, (LPVOID)lpPixels, &MyBMInfo, DIB_RGB_COLORS)) {
        std::cerr << "Failed to capture pixels!\n";
        delete[] lpPixels;
        return Globals::EMPTY2;
    }

    bool borderMatch = false;
    int width = slotRect.right - slotRect.left;
    int height = slotRect.bottom - slotRect.top;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int pixelIndex = 4 * ((y * width) + x);
            BYTE b = lpPixels[pixelIndex];
            BYTE g = lpPixels[pixelIndex + 1];
            BYTE r = lpPixels[pixelIndex + 2];

            COLORREF pixelColor = RGB(r, g, b);

            // Check colors
            if (IsColorMatch(pixelColor, high)) {
                delete[] lpPixels;
                DeleteObject(hBitmap);
                ReleaseDC(NULL, hDC);
                return Globals::HIGH;
            }

            if (IsColorMatch(pixelColor, middle)) {
                delete[] lpPixels;
                DeleteObject(hBitmap);
                ReleaseDC(NULL, hDC);
                return Globals::MIDDLE;
            }

            if (IsColorMatch(pixelColor, low)) {
                delete[] lpPixels;
                DeleteObject(hBitmap);
                ReleaseDC(NULL, hDC);
                return Globals::LOW;
            }

            if (IsColorMatch(pixelColor, whiteBorder) ||
                IsColorMatch(pixelColor, whiteBorder2) ||
                IsColorMatch(pixelColor, redBorder) ||
                IsColorMatch(pixelColor, yellowBorder)) {
                borderMatch = true;
            }
        }
    }

    delete[] lpPixels;
    DeleteObject(hBitmap);
    ReleaseDC(NULL, hDC);
    if (borderMatch) return Globals::ITEM2;
    return Globals::EMPTY2;
}
