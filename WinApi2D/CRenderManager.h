#pragma once
#include <d2d1.h>
#include <dwrite.h>
#include <wincodec.h>
#pragma comment(lib, "D2D1.lib")
#pragma comment(lib, "Dwrite.lib")

using namespace D2D1;

class CD2DImage;

class CRenderManager
{
	SINGLETON(CRenderManager);

private:
	ID2D1Factory* m_pFactory;
	ID2D1HwndRenderTarget* m_pRenderTarget;
	IDWriteFactory* m_pWriteFactory;
	IWICImagingFactory* m_pImageFactory;
	ID2D1Bitmap* m_pBitmap;

	IDWriteTextFormat* m_pTextFormat;

public:
	void init();

	void RenderImage(CD2DImage* img, float dstX, float dstY, float dstW, float dstH);  // 이미지 불러와서 크기 그대로 그려줌  - 이미지 전체
	void RenderFrame(CD2DImage* img, float dstX, float dstY, float dstW, float dstH,   // 이미지에서 시작위치를 골라서 잘라서 그려줌 - 이미지의 일부
		float srcX, float srcY, float srcW, float srcH);
	void RenderRevFrame(CD2DImage* img, float dstX, float dstY, float dstW, float dstH, // 이미지 반대로 그려지는거 - 그려야할 대상의 위치 - 소스의 x,y,w,h
		float srcX, float srcY, float srcW, float srcH);
					//쓰고 싶은 문자열,위치      폰트 사이즈,컬러
	void RenderText(wstring str, float dstX, float dstY, float dstW, float dstH, float fontSize = 12.f, COLORREF color = RGB(0, 0, 0));
	void RenderRectangle(float dstX, float dstY, float dstW, float dstH, COLORREF color = RGB(0, 0, 0));
	void RenderFillRectangle(float dstX, float dstY, float dstW, float dstH, COLORREF color = RGB(0, 0, 0));
	void RenderEllipse(float dstX, float dstY, float dstW, float dstH, COLORREF color = RGB(0, 0, 0));
	void RenderFillEllipse(float dstX, float dstY, float dstW, float dstH, COLORREF color = RGB(0, 0, 0));

	ID2D1Bitmap* GetBitmap();
	ID2D1HwndRenderTarget* GetRenderTarget();
	IWICImagingFactory* GetImageFactory();
	IDWriteFactory* GetWriteFactory();
};

