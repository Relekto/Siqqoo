#pragma once
#include "Globals.h"

namespace PixelProcessors {
	bool findPixelOnScreen(POINT minPoint, POINT maxPoint, COLORREF targetColor, Globals::Point& pointResult);
	HBITMAP GetScreenBmp(HDC hdc, RECT captureArea);
	bool IsColorMatch(COLORREF color1, COLORREF color2, int tolerance = 1);
	Globals::ItemType2 AnalyzeSlot2(RECT slotRect, COLORREF whiteBorder, COLORREF whiteBorder2, COLORREF yellowBorder, COLORREF redBorder, COLORREF high, COLORREF middle, COLORREF low);

}