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

#include "MainMenuScene.h"
#include "HelloWorldScene.h"
#include "AudioEngine.h"
#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <ChString.h>
#include "Definitions.h"


USING_NS_CC;
using namespace std;

Sprite *backGroundMainMenu;
Scene* MainMenu::createScene()
{
    auto scene = Scene::createWithPhysics();

    //trong luc = 0
    scene->getPhysicsWorld()->setGravity(Vec2(0, 0));

    auto layer = MainMenu::create();
    scene->addChild(layer);
    return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in MainMenuScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MainMenu::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto winSize = Director::getInstance()->getWinSize();

    a = "123";

    ///////////////////////////////
    //// 3. add your codes below...

    //// add a label shows "Hello World"
    //// create and initialize a label

    int randInt = RandomHelper::random_int(1, 6);
    std::string s = std::to_string(randInt);
    /**str1 = "Background";
    *str1 = *str1 +s+ ".png";
    auto background1 = Sprite::create(*str1);*/
    string backGround;
    UserDefault* def = UserDefault::getInstance();
    auto _intBackGround = def->getIntegerForKey("intBack", 1);
    if (_intBackGround == 1) {
        backGround = "Background1.png";
    }
    else if (_intBackGround == 2) {
        backGround = "Background2.png";
    }
    else if (_intBackGround == 3) {
        backGround = "Background3.png";
    }
    else if (_intBackGround == 4) {
        backGround = "Background4.png";
    }
    else if (_intBackGround == 5) {
        backGround = "Background5.png";
    }
    else if (_intBackGround == 6) {
        backGround = "Background6.png";
    }
    else
    {
        _intBackGround = 1;
        backGround = "Background1.png";
    }
    def->setIntegerForKey("intBack", _intBackGround);
    def->flush();

    


    backGroundMainMenu = Sprite::create(backGround); 
    backGroundMainMenu->setPosition(Vec2(visibleSize.width  + origin.x, visibleSize.height *0.5 + origin.y));
    backGroundMainMenu->setAnchorPoint(Vec2(0.5,0.5));
    float rx = visibleSize.width*2 / backGroundMainMenu->getContentSize().width;
    float ry = visibleSize.height / backGroundMainMenu->getContentSize().height;
    backGroundMainMenu->setScale(rx, ry);
    addChild(backGroundMainMenu, 0);

    
    //Create Animate Bird

    auto _intBird = def->getIntegerForKey("intBird", 1);
    CCLOG("%d", _intBird);
    if (_intBird != 1 && _intBird != 2 && _intBird != 3) _intBird = 1;
    string _intB = to_string(_intBird);
    string strBird = "bird";
    strBird +=  _intB;

    string strBirdPng = strBird + ".png";
    SpriteBatchNode* spriteNode = SpriteBatchNode::create(strBirdPng);  
    string strPlist = strBird + ".plist";
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(strPlist);
    string strBirdFrame = strBird + "-1.png";
    bird1 = Sprite::createWithSpriteFrameName(strBirdFrame);
    bird1->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height *0.60 + origin.y));
    bird1->setScale(2.5);
    

    spriteNode->addChild(bird1);
    this->addChild(spriteNode);
    string strBirdFly = strBird + "-";
    auto animateFly = Animate::create(MainMenu::createAnimation(strBirdFly, 4, 0.15));
    animateFly->retain();
    bird1->runAction(RepeatForever::create(animateFly));


    auto title = Label::createWithTTF("Flappy Bird", "fonts/FlappyBirdy.ttf", visibleSize.height * 0.15);
    title->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height * 0.75 + origin.y);
    title->setColor(Color3B::WHITE);
    addChild(title);

    auto playItem = MenuItemImage::create(
        "PlayButton.png",
        "ClickedButton.png",
        CC_CALLBACK_1(MainMenu::GoToHelloWorld, this));
    playItem->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height * 0.25 + origin.y);
    auto menu = Menu::create(playItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    auto leftBackGroundItem = MenuItemImage::create(
        "back.png",
        "backClicked.png",
        CC_CALLBACK_1(MainMenu::backBackGround, this));
    leftBackGroundItem->setPosition(visibleSize.width / 2 - origin.x, visibleSize.height * 0.45 + origin.y);
    leftBackGroundItem->setScale(visibleSize.width/25/leftBackGroundItem->getContentSize().width);
    auto rightBackGroundItem = MenuItemImage::create(
        "next.png",
        "nextClicked.png",
        CC_CALLBACK_1(MainMenu::nextBackGround, this));
    rightBackGroundItem->setPosition(visibleSize.width / 2 + origin.x*3, visibleSize.height * 0.45 + origin.y);
    rightBackGroundItem->setScale(visibleSize.width / 25 / leftBackGroundItem->getContentSize().width);
    auto menuChangeBackGround = Menu::create(leftBackGroundItem, rightBackGroundItem, NULL);
    menuChangeBackGround->setPosition(Vec2::ZERO);
    this->addChild(menuChangeBackGround, 1);

    auto changeBack = Sprite::create(backGround);
    changeBack->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height * 0.45 + origin.y);
    changeBack->setScale(visibleSize.width/7.5/changeBack->getContentSize().width);
    addChild(changeBack, 1);

    auto leftBirdItem = MenuItemImage::create(
        "back.png",
        "backClicked.png",
        CC_CALLBACK_1(MainMenu::backBird, this));
    leftBirdItem->setPosition(visibleSize.width / 2 - origin.x, visibleSize.height * 0.6 + origin.y);
    leftBirdItem->setScale(visibleSize.width / 25 / leftBirdItem->getContentSize().width);
    auto rightBirdItem = MenuItemImage::create(
        "next.png",
        "nextClicked.png",
        CC_CALLBACK_1(MainMenu::nextBird, this));
    rightBirdItem->setPosition(visibleSize.width / 2 + origin.x * 3, visibleSize.height * 0.6 + origin.y);
    rightBirdItem->setScale(visibleSize.width / 25 / leftBirdItem->getContentSize().width);
    auto menuChangeBird = Menu::create(leftBirdItem, rightBirdItem, NULL);
    menuChangeBird->setPosition(Vec2::ZERO);
    this->addChild(menuChangeBird, 1);

    return true;
}

cocos2d::Animation* MainMenu::createAnimation(std::string prefixName, int pFrameOder, float delay) {
    Vector<SpriteFrame*> animFrames;
    //tao frame
    for (int i = 1; i <= pFrameOder; i++) {
        char buffer[20] = { 0 };
        sprintf(buffer,"%d.png",i);
        //CCLOG("%s",buffer);
        string str = prefixName + buffer;//Name sprite in spriteSheet
        //tao frame va add vao vecter
        auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
        animFrames.pushBack(frame);
    }
   auto animation = Animation::createWithSpriteFrames(animFrames, delay);
    return animation;
    
}
void MainMenu::GoToHelloWorld(cocos2d::Ref* sender) {
    
    auto scene = HelloWorld::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(0.2, scene));
}
void MainMenu::backBackGround(cocos2d::Ref* sender) {
    UserDefault* def = UserDefault::getInstance();
    auto _intBackGround = def->getIntegerForKey("intBack");
    _intBackGround --;
    if (_intBackGround <= 0) _intBackGround = 6;
    else if (_intBackGround >= 7) _intBackGround = 1;
    def->setIntegerForKey("intBack", _intBackGround);

    auto scene = MainMenu::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(0.2, scene));
}
void MainMenu::nextBackGround(cocos2d::Ref* sender) {
    UserDefault* def = UserDefault::getInstance();
    auto _intBackGround = def->getIntegerForKey("intBack");
    _intBackGround ++;
    if (_intBackGround <= 0) _intBackGround = 6;
    else if (_intBackGround >= 7) _intBackGround = 1;
    def->setIntegerForKey("intBack", _intBackGround);
    std::string s = std::to_string(_intBackGround);
    auto scene = MainMenu::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(0.2, scene));
}
void MainMenu::backBird(cocos2d::Ref* sender) {
    UserDefault* def = UserDefault::getInstance();
    auto _intBird = def->getIntegerForKey("intBird");
    _intBird--;
    if (_intBird <= 0) _intBird = 3;
    def->setIntegerForKey("intBird", _intBird);

    auto scene = MainMenu::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(0.1, scene));
}
void MainMenu::nextBird(cocos2d::Ref* sender) {
    UserDefault* def = UserDefault::getInstance();
    auto _intBird = def->getIntegerForKey("intBird");
    _intBird++;
    if (_intBird >= 4) _intBird = 1;
    def->setIntegerForKey("intBird", _intBird);
    std::string s = std::to_string(_intBird);
    auto scene = MainMenu::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(0.1, scene));
}


