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

#include "GameOverScene.h"
#include "HelloWorldScene.h"
#include "MainMenuScene.h"
#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <ChString.h>



USING_NS_CC;
using namespace std;
unsigned int score;
Scene* GameOver::createScene(unsigned int _score)
{
    score = _score;
    auto scene = Scene::create();

    auto layer = GameOver::create();
    scene->addChild(layer);
    return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in GameOverScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameOver::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto winSize = Director::getInstance()->getWinSize();

    UserDefault* def = UserDefault::getInstance();
    auto highScore = def->getIntegerForKey("HIGHSCORE",0);
    if (score>highScore) {
        highScore = score;
        def->setIntegerForKey("HIGHSCORE", highScore);
    }
    def->flush();


    auto title1 = Label::createWithTTF("Game Over", "fonts/FlappyBirdy.ttf", visibleSize.height * 0.15);

    title1->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height * 0.85 + origin.y);
    title1->setColor(Color3B::WHITE);
    addChild(title1);
    string strScore = StringUtils::format("Score: %d", score);
    auto labelScore = Label::createWithTTF(strScore.c_str(), "fonts/Marker Felt.ttf", visibleSize.height * 0.05);
    labelScore->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height * 0.75 + origin.y);
    labelScore->setColor(Color3B::RED);
    addChild(labelScore);

    auto retryItem = MenuItemImage::create(
        "retry.png",
        "clickedRetry.png",
        CC_CALLBACK_1(GameOver::GoToHelloWorld, this));
    retryItem->setPosition(visibleSize.width / 2 - origin.x*1.5, visibleSize.height * 0.365 + origin.y);

    auto menuItem = MenuItemImage::create(
        "menu.png",
        "clickedMenu.png",
        CC_CALLBACK_1(GameOver::GoToMainMenu, this));
    menuItem->setPosition(visibleSize.width / 2 + origin.x*3, visibleSize.height * 0.35 + origin.y);
    auto menu = Menu::create(retryItem, menuItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    string _highScore = StringUtils::format("Best Score: %d", highScore);
    auto labelHighScore = Label::createWithTTF(_highScore.c_str(), "fonts/Marker Felt.ttf", visibleSize.height * 0.05);
    labelHighScore->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height * 0.65 + origin.y);
    labelHighScore->setColor(Color3B::BLUE);
    addChild(labelHighScore);

    

    return true;
}

void GameOver::GoToHelloWorld(cocos2d::Ref* sender) {
    auto scene = HelloWorld::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(0.2, scene));
}
void GameOver::GoToMainMenu(cocos2d::Ref* sender) {
    auto scene = MainMenu::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(0.2, scene));
}
