#include "../stdafx.h"

#include "Sprite.h"
Sprite::Sprite(int x, int y) {
    this->x = x;
    this->y = y;
    this->initG_x();
    this->initG_y();
}
Sprite::Sprite(App* app, WCHAR* url, string spriteType, int w2, int h2) {
    this->img = app->mCanvas->getSoucre(url);
    if (w2 == -1) {
        this->width = (int)this->img->GetSize().width;
    } else {
        this->width = w2;
    }
    if (h2 == -1) {
        this->height = (int)this->img->GetSize().height;
    } else {
        this->height = h2;
    }
}
Sprite::Sprite(App* app, ID2D1Bitmap* url, string spriteType, int w2, int h2) {
    this->img = url;
    if (w2 == -1) {
        this->width = (int)this->img->GetSize().width;
    } else {
        this->width = w2;
    }
    if (h2 == -1) {
        this->height = (int)this->img->GetSize().height;
    } else {
        this->height = h2;
    }
}
float Sprite::getTxtWidth(App* app) {
    D2D1_SIZE_F size = {0, 0};
    //	string d = this->txt;
    LPWSTR d = g_chartowchar2(this->txt.c_str());
    app->mCanvas->getTextInfo(d, size);
    return size.width;
};
float Sprite::getTxtHeight(App* app) {
    D2D1_SIZE_F size = {0, 0};
    LPWSTR d = g_chartowchar2(this->txt.c_str());
    app->mCanvas->getTextInfo(d, size);
    return size.height;
};
Sprite::~Sprite() {}
void Sprite::setNowFrame(unsigned int nowFrame) { //
    if (this->frameArr.size() <= this->mNowFrame) { //
        cout << "jjj" << endl;
    }
    this->mNowFrame = nowFrame;
}
unsigned int Sprite::getNowFrame() { //
    if (this->frameArr.size() <= this->mNowFrame) { //
        cout << "jjj" << endl;
    }

    return this->mNowFrame;
}
void Sprite::render(App* app) {
    if (!this->visible) { return; }
    if (this->spriteType == "animateSprite") {
        unsigned int len = this->frameArr.size();
        if (this->speedNowTime + app->msTime >= this->speedTime) {
            this->speedNowTime = 0;
            if (this->getNowFrame() < len - 1) {
                this->setNowFrame(this->getNowFrame() + 1);
            } else {
                if (this->loop > 0) { this->loop--; }
                if (this->loop == 0) {

                    this->amtEnd(this);
                } else {
                    this->setNowFrame(0);
                }
            }
        } else {
            this->speedNowTime += app->msTime;
        }
        if (len >= 0) {

            this->frame = &(this->frameArr[this->getNowFrame()]);

        } else {
            this->frame = NULL;
        }
    }
    int x1 = 0;
    int y1 = 0;
    // 绘制自己的变换情况
    app->mCanvas->save();
    if (this->angle != 0) { //
        app->mCanvas->rotate(this->angle, this->g_x + this->getWidth() * this->pivot.x, this->g_y + this->getHeight() * this->pivot.y);
    }

    if (this->frame != NULL) {

        app->mCanvas->drawImage(this->img, this->g_x + x1, this->g_y + y1, this->width * this->zoom, this->height * this->zoom, this->frame);
    } else if (this->spriteType == "fillSprite") {
        app->mCanvas->fillImage(this->img, this->g_x + x1, this->g_y + y1, this->width * this->zoom, this->height * this->zoom);
    } else if (this->spriteType == "textSprite") {
        app->mCanvas->strokeStyle(this->rgb, this->alpha);
        app->mCanvas->drawText(this->txt, this->g_x, this->g_y, this->width, this->height);
    } else {
        app->mCanvas->drawImage(this->img, this->g_x + x1, this->g_y + y1, this->width * this->zoom, this->height * this->zoom);
    }
    app->mCanvas->restore();
    // 递归绘制所有子元素
    unsigned int len = this->children.size();
    for (unsigned int i = 0; i < len; i++) {
        if (this->children[i]->children.size() > 0) { this->children[i]->render(app); }
    }
}