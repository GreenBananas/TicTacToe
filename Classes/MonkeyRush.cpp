/*
 * MonkeyRush.cpp
 *
 *  Created on: Mar 31, 2013
 *      Author: mapa17@posgrado.upv.es
 */

#include "MonkeyRush.h"
#include "AppMacros.h"
#include "TouchableSprite.h"

#include <vector>
#include <string>
USING_NS_CC;


CCScene* MonkeyRush::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();

    // 'layer' is an autorelease object
    MonkeyRush *layer = MonkeyRush::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MonkeyRush::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

    this->visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    this->origin = CCDirector::sharedDirector()->getVisibleOrigin();

//    CCFileUtils* pFileUtils = CCFileUtils::sharedFileUtils();
//    std::vector<std::string> searchPaths;
//    searchPaths.push_back( "./Resources/" );
//    pFileUtils->setSearchPaths( searchPaths );

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(MonkeyRush::menuCloseCallback));

	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    CCLog("Trying log ....");
    CCLabelTTF* pLabel = CCLabelTTF::create("MonkeyRush", "Arial", TITLE_FONT_SIZE);

    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(pLabel, 1);

    // add "HelloWorld" splash screen"
    CCSprite* pSprite = CCSprite::create("BlackBackground.png");

    // position the sprite on the center of the screen
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);

    this->pDialogBox = CCSprite::create("GreetingDialog.png");
    this->pDialogBox->setPosition( ccp(visibleSize.width/2 + origin.x, (visibleSize.height*0.50) + origin.y) );

    this->pOKDialog = CCMenuItemImage::create( "OkButton.png", "OkButton.png", this, menu_selector(MonkeyRush::onDialogOKPress) );
    this->pOKDialog->setPosition( ccp(pDialogBox->getPositionX(), pDialogBox->boundingBox().getMinY() ) );

    this->addChild( this->pDialogBox, 2);
    this->addChild( this->pOKDialog, 3);

    this->setTouchEnabled(true);

    //this->schedule( schedule_selector(HelloWorld::updateGame) );
    CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this,0);

//
//
//	this->setTouchEnabled(true);
//
//	_targets = new CCArray;
//	_projectiles = new CCArray;
//
//	// use updateGame instead of update, otherwise it will conflit with SelectorProtocol::update
//	// see http://www.cocos2d-x.org/boards/6/topics/1478
//	this->schedule( schedule_selector(HelloWorld::updateGame) );

	//CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("background-music-aac.wav", true);


    return true;
}


void MonkeyRush::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
	CCLog("Got some touch!");

	// First touch will remove the Dialog and the game can start
	if( this->pDialogBox != NULL )
	{
		this->removeChild(this->pOKDialog, true);
		this->removeChild(this->pDialogBox, true);

		this->pDialogBox = NULL;
		this->pOKDialog = NULL;

		this->_startTheGame();
	}
}

void MonkeyRush :: _startTheGame()
{
//	this->schedule( schedule_selector(HelloWorld::gameLogic), 1.0 );
//	this->schedule( schedule_selector(HelloWorld::updateGame) );

	CCLog("Starting the game ...");

	CCSprite* firstMonkey = CCSprite::create("monkey.png");
	if( !firstMonkey->isVisible() )
		CCLog("Loading sprite failed!");

	firstMonkey->setPosition( ccp( this->visibleSize.width/2 + this->origin.x, this->origin.y + (firstMonkey->boundingBox().size.height / 2) ) );
	this->addChild( firstMonkey, 2);
}

void MonkeyRush::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void MonkeyRush::onDialogOKPress(CCObject* pSender)
{
	printf("Pressing OK!");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
