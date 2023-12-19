#include "../stdafx.h"
//
#include "Canvas.h"

Canvas::Canvas() {}

Canvas::Canvas(HWND hwnd) {
    RECT rc;
    GetClientRect(hwnd, &rc);
    this->p_hwnd = hwnd;
    // 创建绘图基础
    HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &(this->m_fac));
    if (SUCCEEDED(hr)) {
        // 创建着色目标
        this->m_fac->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(hwnd, D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top)), &(this->m_render));
        D2D1_SIZE_F size = {0, 0};

        this->m1 = D2D1::Matrix3x2F::Translation(size);
        this->bufM1 = D2D1::Matrix3x2F::Translation(size);
        // 创建画线样式
        this->m_render->CreateSolidColorBrush(D2D1::ColorF(255, 255, 255, 1.0f), &(this->pen));
        // 创建填充样式
        this->m_render->CreateSolidColorBrush(D2D1::ColorF(255, 255, 255, 1.0f), &(this->brush));
        /*float deash[] = { 5.0f,1.0f,5.0f,10.0f };
        //创建边框样式
        this->m_fac->CreateStrokeStyle(D2D1::StrokeStyleProperties(D2D1_CAP_STYLE_FLAT,
                D2D1_CAP_STYLE_FLAT,
                D2D1_CAP_STYLE_ROUND,
                D2D1_LINE_JOIN_MITER,
                10.0f,
                D2D1_DASH_STYLE_CUSTOM,
                0.0f), deash, ARRAYSIZE(deash), &(this->m_lineStyle));*/
        // 创建img进程
        CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, __uuidof(this->m_imgFac), (LPVOID*)&(this->m_imgFac));
        // 创建字体基础
        DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&this->m_writeFac));
        this->m_writeFac->CreateTextFormat(L"SimHei", NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 16, L"en-US", &this->m_forMat);

    } else {
        MessageBox(NULL, TEXT("错误"), TEXT(""), MB_OK);
    }
}
void Canvas::clear() {
    this->m_render->Clear(D2D1::ColorF(D2D1::ColorF::White));
    // this->m_render->SetTransform(D2D1::Matrix3x2F::Identity());
}
void Canvas::stroke() {
    //	this->m_render->DrawLine()
    this->m_render->DrawGeometry(this->m_path, this->pen, this->lineWidth, this->m_lineStyle);
};
void Canvas::fill() { this->m_render->FillGeometry(this->m_path, this->brush); }
void Canvas::releasePath() {
    SafeRelease(&(this->m_slink));
    SafeRelease(&(this->m_path));
}
void Canvas::strokeStyle(UINT32 hex, FLOAT alpha) { this->pen->SetColor(D2D1::ColorF(hex, alpha)); }
void Canvas::setLineStyle(int model) {
    this->lineStyle = model;
    SafeRelease(&(this->m_lineStyle));
    if (this->lineStyle == 1) {
        float deash[] = {5.0f, 1.0f, 5.0f, 10.0f};
        // 创建边框样式
        this->m_fac->CreateStrokeStyle(
            D2D1::StrokeStyleProperties(D2D1_CAP_STYLE_FLAT, D2D1_CAP_STYLE_FLAT, D2D1_CAP_STYLE_ROUND, D2D1_LINE_JOIN_MITER, 10.0f, D2D1_DASH_STYLE_CUSTOM, 0.0f), deash, ARRAYSIZE(deash),
            &(this->m_lineStyle));
    }
}
void Canvas::initPath(D2D1_FILL_MODE mode) {
    this->releasePath();
    this->m_fac->CreatePathGeometry(&(this->m_path));
    HRESULT hr = this->m_path->Open(&(this->m_slink));
    m_slink->SetFillMode(mode);
}
void Canvas::beginPath(int x, int y) { this->m_slink->BeginFigure(D2D1::Point2F(x, y), D2D1_FIGURE_BEGIN_FILLED); }

void Canvas::closePath(D2D1_FIGURE_END type) {
    this->m_slink->EndFigure(type);
    this->m_slink->Close();
}

void Canvas::addPoint(int x, int y) { this->m_slink->AddLine(D2D1::Point2F(x, y)); };
void Canvas::addPoint(D2D1_POINT_2F point) { this->m_slink->AddLine(point); }

void Canvas::addBezier(D2D1_POINT_2F start, D2D1_POINT_2F center, D2D1_POINT_2F end) { this->m_slink->AddBezier(D2D1::BezierSegment(start, center, end)); };
void Canvas::addArc(int x, int y, int xSize, int ySize, int angle, D2D1_SWEEP_DIRECTION angleFx, D2D1_ARC_SIZE size) {
    this->m_slink->AddArc(D2D1::ArcSegment(D2D1::Point2F(x, y), D2D1::SizeF(xSize, ySize), angle, angleFx, size));
};
void Canvas::fillStyle(UINT32 hex, FLOAT alpha) { this->brush->SetColor(D2D1::ColorF(hex, alpha)); };
void Canvas::beginDraw() { //
    this->m_render->BeginDraw();
}
void Canvas::closeDraw() { //
    this->m_render->EndDraw();
}
void Canvas::fillRect(int x, int y, int width, int height) { this->m_render->FillRectangle(D2D1::RectF(x, y, x + width, y + height), this->brush); }
void Canvas::drawRect(int x, int y, int width, int height) {
    this->initPath();
    this->beginPath(x, y);
    this->addPoint(x + width, y);
    this->addPoint(x + width, y + height);
    this->addPoint(x, y + height);
    this->closePath(D2D1_FIGURE_END_CLOSED);
    this->stroke();
    this->releasePath();
}
void Canvas::drawArc(int x, int y, int xWidth, int yWidth) {
    D2D1_ELLIPSE circle1 = D2D1::Ellipse(D2D1::Point2F(x, y), xWidth, yWidth);
    ID2D1EllipseGeometry* l_ellipse = NULL;
    this->m_fac->CreateEllipseGeometry(circle1, &l_ellipse);
    this->m_render->DrawGeometry(l_ellipse, this->pen, this->lineWidth, this->m_lineStyle);
    SafeRelease(&l_ellipse);
};

void Canvas::fillArc(int x, int y, int xWidth, int yWidth) {
    D2D1_ELLIPSE circle1 = D2D1::Ellipse(D2D1::Point2F(x, y), xWidth, yWidth);
    ID2D1EllipseGeometry* l_ellipse = NULL;
    this->m_fac->CreateEllipseGeometry(circle1, &l_ellipse);
    this->m_render->FillGeometry(l_ellipse, this->brush);
    SafeRelease(&l_ellipse);
};

void Canvas::rotate(int angle, int x, int y) {
    this->m1 = this->m1 * D2D1::Matrix3x2F::Rotation(angle, D2D1::Point2F(x, y));
    this->m_render->SetTransform(this->m1);
};
void Canvas::scale(int zoom, int x, int y) {
    RECT rc;
    GetClientRect(this->p_hwnd, &rc);
    D2D1_SIZE_F size = {(FLOAT)zoom, (FLOAT)zoom};
    this->m1 = this->m1 * D2D1::Matrix3x2F::Scale(size, D2D1::Point2F(x, y));
    this->m_render->SetTransform(this->m1);
};
void Canvas::skew(int angleX, int angleY, int x, int y) {
    this->m1 = this->m1 * D2D1::Matrix3x2F::Skew(angleX, angleY, D2D1::Point2<FLOAT>(x, y));
    this->m_render->SetTransform(this->m1);
};
void Canvas::trisition(int x, int y) {
    if (x != 0) {}
    D2D1_SIZE_F size = {(FLOAT)x, (FLOAT)y};
    this->m1 = this->m1 * D2D1::Matrix3x2F::Translation(size);
    this->m_render->SetTransform(this->m1);
};
void Canvas::save() { this->bufM1 = this->m1; }
void Canvas::restore() {
    this->m1 = this->bufM1;
    this->m_render->SetTransform(this->bufM1);
}
void Canvas::getTextInfo(LPWSTR txt, D2D1_SIZE_F& size) {
    IDWriteTextLayout* pTextLayout = NULL;
    this->m_writeFac->CreateTextLayout(txt, wcslen(txt), this->m_forMat, 0.0f, 0.0f, &pTextLayout);

    // 获取文本尺寸
    FLOAT fontSize;
    pTextLayout->GetFontSize(0, &fontSize);
    pTextLayout->SetMaxWidth(wcslen(txt) * fontSize * 1.5);

    DWRITE_TEXT_METRICS textMetrics;
    pTextLayout->GetMetrics(&textMetrics);
    size = D2D1::SizeF(ceil(textMetrics.widthIncludingTrailingWhitespace), ceil(textMetrics.height));
    SafeRelease(&pTextLayout);
}
void Canvas::getTextInfo(string txt, D2D1_SIZE_F& size) {

    LPWSTR a = g_chartowchar2(txt.c_str());
    this->getTextInfo(a, size);
}
ID2D1Bitmap* Canvas::getSoucre(WCHAR* url) {
    int index = -1;
    wstring ws1 = url;
    for (int i = 0; i < this->imgName.size(); i++) {
        wstring ws2 = this->imgName[i];
        if (ws2.compare(ws1) == 0) {
            index = i;
            break;
        }
    }
    if (index != -1) {
        return this->imgSource[index];
    } else {
        ID2D1Bitmap* g_bitmap = NULL;
        IWICBitmapDecoder* bitmapdecoder = NULL;
        this->m_imgFac->CreateDecoderFromFilename(url, NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &bitmapdecoder);
        IWICBitmapFrameDecode* pframe = NULL;
        bitmapdecoder->GetFrame(0, &pframe);
        IWICFormatConverter* fmtcovter = NULL;
        this->m_imgFac->CreateFormatConverter(&fmtcovter);
        fmtcovter->Initialize(pframe, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.0f, WICBitmapPaletteTypeCustom);
        this->m_render->CreateBitmapFromWicBitmap(fmtcovter, NULL, &g_bitmap);
        fmtcovter->Release();
        pframe->Release();
        bitmapdecoder->Release();
        this->imgName.push_back(ws1);
        this->imgSource.push_back(g_bitmap);
        return g_bitmap;
    }
}
void Canvas::drawImage(WCHAR* url, int x, int y) {
    ID2D1Bitmap* g_bitmap = this->getSoucre(url);
    D2D1_SIZE_F size = g_bitmap->GetSize();
    D2D_RECT_F imgr = {(FLOAT)x, (FLOAT)y, (FLOAT)x + size.width, (FLOAT)y + size.height};
    this->m_render->DrawBitmap(g_bitmap, imgr);
}
void Canvas::fillImage(WCHAR* url, int x, int y, int width, int height, int srcX, int srcY, float xZoom, float yZoom, int angle) {
    ID2D1Bitmap* img = this->getSoucre(url);
    this->fillImage(img, x, y, width, height, srcX, srcY, xZoom, yZoom, angle);
}
void Canvas::fillImage(ID2D1Bitmap* img, int x, int y, int width, int height, int srcX, int srcY, float xZoom, float yZoom, int angle) {
    this->m_render->CreateBitmapBrush(img, &this->bitmapBrush);
    this->bitmapBrush->SetExtendModeX(D2D1_EXTEND_MODE_WRAP);
    this->bitmapBrush->SetExtendModeY(D2D1_EXTEND_MODE_WRAP);
    D2D1_MATRIX_3X2_F rotation = D2D1::Matrix3x2F::Rotation(angle, D2D1::Point2F(0, 0));
    this->bitmapBrush->SetTransform(D2D1::Matrix3x2F::Translation(D2D1::Size<FLOAT>(srcX, srcY)) * D2D1::Matrix3x2F::Scale(D2D1::Size(xZoom, yZoom)) * rotation);
    this->m_render->FillRectangle(D2D1::RectF(x, y, x + width, y + height), this->bitmapBrush);
}
void Canvas::drawImage(ID2D1Bitmap* img, int x, int y) {
    D2D1_SIZE_F size = img->GetSize();
    D2D_RECT_F imgr = {(FLOAT)x, (FLOAT)y, (FLOAT)x + size.width, (FLOAT)y + size.height};
    this->m_render->DrawBitmap(img, imgr);
}
void Canvas::drawImage(WCHAR* url, int x, int y, int width, int height) {
    ID2D1Bitmap* g_bitmap = this->getSoucre(url);
    D2D_RECT_F imgr = {(FLOAT)x, (FLOAT)y, (FLOAT)x + width, (FLOAT)y + height};
    this->m_render->DrawBitmap(g_bitmap, imgr);
}
void Canvas::drawImage(ID2D1Bitmap* img, int x, int y, int width, int height) {
    D2D1_SIZE_F size = img->GetSize();
    D2D_RECT_F imgr = {(FLOAT)x, (FLOAT)y, (FLOAT)x + width, (FLOAT)y + height};
    this->m_render->DrawBitmap(img, imgr);
}
void Canvas::drawImage(WCHAR* url, int x, int y, int width, int height, int srcX, int srcY, int srcWidth, int srcHeight) {
    ID2D1Bitmap* g_bitmap = this->getSoucre(url);
    D2D_RECT_F imgr = {(FLOAT)x, (FLOAT)y, (FLOAT)x + width, (FLOAT)y + height};
    D2D_RECT_F srcImg = {(FLOAT)srcX, (FLOAT)srcY, (FLOAT)srcX + srcWidth, (FLOAT)srcY + srcHeight};
    this->m_render->DrawBitmap(g_bitmap, imgr, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, &srcImg);
}
void Canvas::drawImage(ID2D1Bitmap* img, int x, int y, int width, int height, int srcX, int srcY, int srcWidth, int srcHeight) {
    D2D_RECT_F imgr = {(FLOAT)x, (FLOAT)y, (FLOAT)x + width, (FLOAT)y + height};
    D2D_RECT_F srcImg = {(FLOAT)srcX, (FLOAT)srcY, (FLOAT)srcX + srcWidth, (FLOAT)srcY + srcHeight};
    this->m_render->DrawBitmap(img, imgr, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, &srcImg);
}
void Canvas::drawImage(ID2D1Bitmap* img, int x, int y, int width, int height, u_rect* frame) {
    D2D_RECT_F imgr = {(FLOAT)x, (FLOAT)y, (FLOAT)x + width, (FLOAT)y + height};
    D2D_RECT_F srcImg = {(FLOAT)frame->x, (FLOAT)frame->y, (FLOAT)frame->x + frame->width, (FLOAT)frame->y + frame->height};
    this->m_render->DrawBitmap(img, imgr, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, &srcImg);
};
void Canvas::drawImage(WCHAR* url, int x, int y, int zoom) { this->drawImage(url, x, y, zoom, zoom); }
void Canvas::drawImage(ID2D1Bitmap* img, int x, int y, int zoom) { this->drawImage(img, x, y, zoom, zoom); }

void Canvas::drawLine(int x, int y, int x2, int y2) {

    if (this->lineStyle == 0) {
        this->m_render->DrawLine(D2D1::Point2<FLOAT>(x, y), D2D1::Point2<FLOAT>(x2, y2), (this->pen), this->lineWidth);
    } else {
        this->m_render->DrawLine(D2D1::Point2<FLOAT>(x, y), D2D1::Point2<FLOAT>(x2, y2), (this->pen), this->lineWidth, this->m_lineStyle);
    }
}
void Canvas::drawText(LPWSTR txt, int x, int y) {
    D2D1_RECT_F layoutRect = D2D1::RectF(x, y, x + 100, y + 100);
    this->m_render->DrawText(txt, wcslen(txt), this->m_forMat, layoutRect, this->pen);
}
void Canvas::drawText(string txt, int x, int y) {
    D2D1_RECT_F layoutRect = D2D1::RectF(x, y, x + 100, y + 100);
    LPWSTR a = g_chartowchar2(txt.c_str());
    this->m_render->DrawText(a, wcslen(a), this->m_forMat, layoutRect, this->pen);
}
void Canvas::drawText(LPWSTR txt, int x, int y, int w, int h) {
    D2D1_RECT_F layoutRect = D2D1::RectF(x, y, x + w, y + h);
    this->m_render->DrawText(txt, wcslen(txt), this->m_forMat, layoutRect, this->pen);
}
void Canvas::drawText(string txt, int x, int y, int w, int h) {
    D2D1_RECT_F layoutRect = D2D1::RectF(x, y, x + w, y + h);
    LPWSTR a = g_chartowchar2(txt.c_str());
    this->m_render->DrawText(a, wcslen(a), this->m_forMat, layoutRect, this->pen);
}
Canvas::~Canvas() {
    SafeRelease(&(this->m_fac));
    SafeRelease(&(this->m_render));
    SafeRelease(&(this->brush));
    SafeRelease(&(this->pen));
    SafeRelease(&(this->bitmapBrush));
    SafeRelease(&(this->m_lineStyle));
    SafeRelease(&(this->m_writeFac));
    SafeRelease(&(this->m_forMat));
    SafeRelease(&(this->m_slink));
    SafeRelease(&(this->m_path));
    for (int i = 0; i < imgSource.size(); i++) { SafeRelease(&(imgSource[i])); }
}
