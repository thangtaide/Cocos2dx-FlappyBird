/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __MAINMENU_SCENE_H__
#define __MAINMENU_SCENE_H__

#include "cocos2d.h"
using namespace cocos2d;
class MainMenu : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    static cocos2d::Animation* createAnimation(std::string prefixName, int pFrameOder, float delay);
    virtual bool init();
    
    CREATE_FUNC(MainMenu);
    static std::string tempStr;
    void setStr(std::string _str);
    std::string getStr();
    //static int intBackGround;
private:
    void GoToHelloWorld(cocos2d::Ref* sender);
    void nextBackGround(cocos2d::Ref* sender);
    void backBackGround(cocos2d::Ref* sender);
    void nextBird(cocos2d::Ref* sender);
    void backBird(cocos2d::Ref* sender);
     //cocos2d::Animation* animation;
     Sprite* bird1;
};

#endif // __GAMEOVER_SCENE_H__
