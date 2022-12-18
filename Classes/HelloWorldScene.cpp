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

#include "HelloWorldScene.h"
#include "GameOverScene.h"
#include "AudioEngine.h"
#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <ChString.h>
#include "MainMenuScene.h"



USING_NS_CC;
using namespace std;

Sprite* bird, *earth;
PhysicsBody* bodyBird;
Scene* scene;
Animate* animateFly;
//string *str;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::createWithPhysics();
    //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    auto visibleSize = Director::getInstance()->getVisibleSize();

    //*str = *strBackGround;

    //trong luc 
    scene->getPhysicsWorld()->setGravity(Vec2(0, -visibleSize.height*0.8));

    auto layer = HelloWorld::create();
    layer->setPhysicsWorld(scene->getPhysicsWorld());
    scene->addChild(layer);
    return scene;
}
void HelloWorld::setPhysicsWorld(cocos2d::PhysicsWorld* m_world) {
    world = m_world;
}
// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto winSize = Director::getInstance()->getWinSize();
    auto touchLisener = EventListenerTouchOneByOne::create();
    touchLisener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchLisener, this);

    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    ///////////////////////////////
    //// 3. add your codes below...

    //// add a label shows "Hello World"
    //// create and initialize a label

    //background
    auto scrollBackground = MoveBy::create(20.0, Vec2(-visibleSize.width * 2, 0));

    UserDefault* def = UserDefault::getInstance();
    auto randInt = def->getIntegerForKey("intBack");
    
    std::string s = std::to_string(randInt);
    string strb = "Background";
    strb = strb +s+ ".png";
    background = Sprite::create(strb);
    background->setPosition(Vec2(visibleSize.width  + origin.x, visibleSize.height *0.5 + origin.y));
    background->setAnchorPoint(Vec2(0.5,0.5));
    float rx = visibleSize.width*2 / background->getContentSize().width;
    float ry = visibleSize.height / background->getContentSize().height;
    background->setScale(rx, ry);
    addChild(background, 0);
    background->runAction(RepeatForever::create(scrollBackground));

    //Earth
    auto scrollEarth = MoveBy::create(5.0, Vec2(-visibleSize.width * 2, 0));
    earth = Sprite::create("E1.png");
    earth->setPosition(Vec2(origin.x, origin.y));
    earth->setAnchorPoint(Vec2(0, 0));
    earth->setScale(rx*0.75, ry*0.75);
    auto bodyEarth = PhysicsBody::createBox(earth->getContentSize());
    bodyEarth->setDynamic(false);
    bodyEarth->setCollisionBitmask(5);
    bodyEarth->setContactTestBitmask(true);
    earth->setPhysicsBody(bodyEarth);
    addChild(earth, 3);
    earth->runAction(RepeatForever::create(scrollEarth));

    auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT,3);
    edgeBody->setCollisionBitmask(1);
    edgeBody->setContactTestBitmask(true);
    auto edgeNode = Node::create();
    edgeNode->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    edgeNode->setPhysicsBody(edgeBody);
    addChild(edgeNode);

    //Create Animate Bird
    auto _intBird = def->getIntegerForKey("intBird");
    string _intB = to_string(_intBird);
    string strBird = "bird";
    strBird += _intB;

    string strBirdPng = strBird + ".png";
    SpriteBatchNode* spriteNode = SpriteBatchNode::create(strBirdPng);
    string strPlist = strBird + ".plist";
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(strPlist);
    string strBirdFrame = strBird + "-1.png";
    bird = Sprite::createWithSpriteFrameName(strBirdFrame);
    bird->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    bird->setScale(2);

    auto bodyBird = PhysicsBody::createBox(bird->getContentSize());
    bodyBird->setGravityEnable(true);
    bodyBird->setContactTestBitmask(true);
    bodyBird->setCollisionBitmask(4);
    bird->setPhysicsBody(bodyBird);
    

    spriteNode->addChild(bird);
    this->addChild(spriteNode);
    string strBirdFly = strBird + "-";
    auto animateFly = Animate::create(MainMenu::createAnimation(strBirdFly, 4, 0.15));
    animateFly->retain();
    animateFly->setTag(2);
    bird->runAction(RepeatForever::create(animateFly));
    auto actDown1 = RotateTo::create(0.7, 90);
    auto actDown = RotateTo::create(0.5, 1);
    bird->runAction(Sequence::create(actDown,actDown1,nullptr));

    string strScore = StringUtils::format("Score: %d", score);
    label = Label::createWithTTF(strScore.c_str(),"fonts/Marker Felt.ttf",visibleSize.height*0.05);
    label->setPosition(visibleSize.width/2+origin.x,visibleSize.height*0.8+origin.y);
    label->setColor(Color3B::RED);
    addChild(label);

    this->scheduleUpdate();
    //pipeMove
    this->schedule(CC_SCHEDULE_SELECTOR(HelloWorld::CreatePipe), 0.0018 * visibleSize.width);

    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(HelloWorld::onContactBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

    return true;
}

void HelloWorld::update(float dt) {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    bird->setPositionX(visibleSize.width / 2 + origin.x);
 
    if (background->getPositionX() <= origin.x) {
        background->setPositionX(visibleSize.width+origin.x);
    }
    if (earth->getPositionX() <= -visibleSize.width*0.375+ origin.x) {
        earth->setPositionX(origin.x);
    }
}

bool HelloWorld::onContactBegan(PhysicsContact &_contact) {
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    PhysicsBody* a = _contact.getShapeA()->getBody();
    PhysicsBody* b = _contact.getShapeB()->getBody();
    if (a->getCollisionBitmask() == 4 && b->getCollisionBitmask() == 3 ||
        a->getCollisionBitmask() == 3 && b->getCollisionBitmask() == 4) {
        AudioEngine::play2d("sounds/point.mp3");
        score++;
        string strScore = StringUtils::format("Score: %d", score);
        
        label->setString(strScore.c_str());
    }
    else if (a->getCollisionBitmask() == 4 && b->getCollisionBitmask() == 2 ||
        a->getCollisionBitmask() == 2 && b->getCollisionBitmask() == 4) {
        AudioEngine::play2d("sounds/hit.mp3");
        //Director::pause;
        auto sqe = GameOver::createScene(score);
        Director::getInstance()->replaceScene(sqe);
    }
    else if (a->getCollisionBitmask() == 4 && b->getCollisionBitmask() == 5 ||
        a->getCollisionBitmask() == 5 && b->getCollisionBitmask() == 4) {
        AudioEngine::play2d("sounds/die.mp3");
        //Director::pause;
        auto sqe = GameOver::createScene(score);
        Director::getInstance()->replaceScene(sqe);
    }
    return true;
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* unused_event) {
    //bodyBird->setGravityEnable(0);
    auto visibleSize = Director::getInstance()->getVisibleSize();
    AudioEngine::play2d("sounds/wing.mp3");
    bird->getPhysicsBody()->setVelocity(Vec2::ZERO);
    bird->stopAllActionsByTag(1);
    //bird->stopAllActions();
    //bird->runAction(RepeatForever::create(animateFly));
    auto actFly = RotateTo::create(0.15, -30);
    auto actDown = RotateTo::create(0.3, -29);
    auto actDown1 = RotateTo::create(0.5, 90);
    auto fly = MoveBy::create(0.15, Vec2(0, visibleSize.height * 0.1));
    auto spawn1 = Spawn::create(actFly, fly, nullptr);
    auto sequence1 = Sequence::create(spawn1, actDown, actDown1, nullptr);
    sequence1->setTag(1);
    bird->runAction(sequence1);
    //this->schedule(CC_SCHEDULE_SELECTOR(HelloWorld::stopFly),0.3);

    //bodyBird->setGravityEnable(9.8);
    //bird->stopActionByTag(2);
    
    return true;
}

void HelloWorld::CreatePipe(float dt) {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto topPipe = Sprite::create("Pipe-down.png");
    auto botPipe = Sprite::create("Pipe-up.png");
    topPipe->setScale(0.3);
    botPipe->setScale(0.3);

    auto topPhysic = PhysicsBody::createBox(topPipe->getContentSize());
    topPhysic->setCollisionBitmask(2);
    topPhysic->setContactTestBitmask(true);
    topPipe->setPhysicsBody(topPhysic);
    auto botPhysic = PhysicsBody::createBox(botPipe->getContentSize());
    botPhysic->setCollisionBitmask(2);
    botPhysic->setContactTestBitmask(true);
    botPipe->setPhysicsBody(botPhysic);
    topPhysic->setDynamic(false);
    botPhysic->setDynamic(false);

    int random = RandomHelper::random_int(40, 70);
    auto topPipePosition = visibleSize.height * random/100 + topPipe->getContentSize().height *0.15+origin.y;
    topPipe->setPosition(Vec2(visibleSize.width+topPipe->getContentSize().width*0.3,topPipePosition));
    botPipe->setPosition(Vec2(topPipe->getPositionX(), topPipePosition-topPipe->getContentSize().height*0.3-Sprite::create("bird2-0.png")->getContentSize().height*8));
    addChild(topPipe);
    addChild(botPipe);
    auto pipeMove = MoveBy::create(0.01*visibleSize.width,Vec2(-visibleSize.width*1.5, 0));
    auto pipeMove1 = MoveBy::create(0.01 * visibleSize.width, Vec2(-visibleSize.width * 1.5, 0));
    topPipe->runAction(pipeMove);
    botPipe->runAction(pipeMove1);

    auto pointNode = Node::create();
    pointNode->setPosition(Vec2(topPipe->getPositionX(), topPipe->getPositionY() - topPipe->getContentSize().height * 0.15- Sprite::create("bird2-0.png")->getContentSize().height*4));
    auto nodePhysic = PhysicsBody::createBox(Size(1, Sprite::create("bird2-0.png")->getContentSize().height * 8));
    nodePhysic->setDynamic(false);
    nodePhysic->setCollisionBitmask(3);
    nodePhysic->setContactTestBitmask(true);
    pointNode->setPhysicsBody(nodePhysic);
    auto nodeMove = MoveBy::create(0.01 * visibleSize.width, Vec2(-visibleSize.width * 1.5, 0));
    auto finishAction = CallFunc::create([=] {
        removeChild(pointNode);
        //pointNode->removeFromParentAndCleanup(true);
        });

    auto finishActionTop = CallFunc::create([=] {topPipe->removeFromParentAndCleanup(true); });
    auto finishActionBot = CallFunc::create([=] {botPipe->removeFromParentAndCleanup(true); });
    pointNode->runAction(Sequence::create(nodeMove, finishAction, nullptr));
    topPipe->runAction(Sequence::create(pipeMove, finishActionTop, nullptr));
    botPipe->runAction(Sequence::create(pipeMove1, finishActionBot, nullptr));
    addChild(pointNode);

}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
