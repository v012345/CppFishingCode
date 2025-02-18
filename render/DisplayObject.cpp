#include "../stdafx.h"

#include "DisplayObject.h"

DisplayObject::DisplayObject() {
    this->g_x = this->x;
    this->g_y = this->y;
}

DisplayObject::DisplayObject(float x, float y) {
    this->x = x;
    this->y = y;
    this->g_x = this->x;
    this->g_y = this->y;
}

// 判断鼠标是否在此对象中
bool DisplayObject::inRect(POINT* mouse) { //
    bool isHitX = mouse->x >= this->g_x && mouse->x <= this->g_x + this->getWidth();
    bool isHitY = mouse->y > this->g_y && mouse->y <= this->g_y + this->getHeight();
    return isHitX && isHitY;
}

void DisplayObject::setId(string id) { //
    this->id = id;
}

Sprite* DisplayObject::getChildById(string id) {
    for (unsigned int i = 0; i < this->children.size(); i++) {
        if (this->children[i]->id == id) { //
            return this->children[i];
        }
    }
    return NULL;
}

int DisplayObject::addChild(Sprite* child) {
    child->parent = (Sprite*)this;
    this->children.push_back(child);
    child->initG_x();
    child->initG_y();
    return this->children.size();
}

void DisplayObject::initG_x() {
    if (this->parent == NULL) {
        this->g_x = this->x;
    } else {
        this->g_x = this->parent->g_x + this->x;
    }
    for (unsigned int i = 0; i < this->children.size(); i++) { //
        this->children[i]->initG_x();
    }
}

void DisplayObject::initG_y() {
    if (this->parent == NULL) {
        this->g_y = this->y;
    } else {
        this->g_y = this->parent->g_y + this->y;
    }

    for (unsigned int i = 0; i < this->children.size(); i++) { //
        this->children[i]->initG_y();
    }
}

void DisplayObject::setX(float x) {
    this->x = x;
    this->initG_x();
}

void DisplayObject::setY(float y) {
    this->y = y;
    this->initG_y();
}

void DisplayObject::setX(int x) {
    this->x = x;
    this->initG_x();
}
void DisplayObject::setY(int y) {
    this->y = y;
    this->initG_y();
}

int DisplayObject::removeChild(Sprite* child) {
    vector<Sprite*>::iterator it = find((this->children).begin(), (this->children).end(), child);
    this->children.erase(it);
    if (child->parent != NULL) { //
        child->parent = NULL;
    }
    return this->children.size();
}

float DisplayObject::getWidth() { //
    return this->width * this->zoom;
}

float DisplayObject::getHeight() { //
    return this->height * this->zoom;
}

void DisplayObject::render(App* app) {
    if (this->visible) {
        for (unsigned int i = 0; i < this->children.size(); i++) { //
            this->children[i]->render(app);
        }
    }
}

DisplayObject::~DisplayObject() {
    for (unsigned int i = 0; i < this->children.size(); i++) { //
        delete this->children[i];
    }
}