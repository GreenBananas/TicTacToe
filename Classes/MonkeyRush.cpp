/*
 * MonkeyRush.cpp
 *
 *  Created on: Mar 31, 2013
 *      Author: mapa17@posgrado.upv.es
 */

#include "MonkeyRush.h"
#include "AppMacros.h"

#include <vector>
#include <string>


#include <ccTypes.h>
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

    //CCLayer* pLayer = new GameLayer(); //It will be debug layer :)
	//this->addChild(pLayer);//Alse you can set here Z order.
	//pLayer->release();

    this->visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    this->origin = CCDirector::sharedDirector()->getVisibleOrigin();

    this->_initGame();
    this->_loadScene();

    return true;
}

void MonkeyRush::_initGame()
{
	for(int i=0; i < MonkeyRush::GridWidth ; i++){
		for(int j=0; j < MonkeyRush::GridHeight; j++){
			this->grid[i][j] = MonkeyRush::EMPTY;
		}
	}

	float w = this->visibleSize.width;
	float h = this->visibleSize.height;

	CCLog("Scene Origin %f %f", this->origin.x, this->origin.y );

	this->cw = w / MonkeyRush::GridWidth;
	this->ch = h / MonkeyRush::GridHeight;

}

void MonkeyRush::_loadScene()
{
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

	this->pOKDialog = CCSprite::create( "OkButton.png" );
	this->pOKDialog->setPosition( ccp(pDialogBox->getPositionX(), pDialogBox->boundingBox().getMinY() ) );

	this->addChild( this->pDialogBox, 2);
	this->addChild( this->pOKDialog, 3);

	this->_climbingMonkeySprite = CCSprite::create("climingMonkey.png");
	//Note: stupid hack, if not done, the texture of the sprite can not be used;Probably because of optimization its not loaded before setting it
	this->addChild( this->_climbingMonkeySprite, -1);
	this->_monkeys = new CCArray;

	this->_TreeFireSprite = CCSprite::create("fire2.png");
	//Note: stupid hack, if not done, the texture of the sprite can not be used;Probably because of optimization its not loaded before setting it
	this->addChild( this->_TreeFireSprite, -1);
	this->_TreeFires =  new CCArray;

	this->_WinDialog = CCSprite::create("WinDialog.png");
	this->_WinDialog->setPosition( ccp(visibleSize.width/2 + origin.x, (visibleSize.height*0.50) + origin.y) );
	this->addChild( this->_WinDialog, 2);
	this->_WinDialog->setVisible( false );

	this->_LoseDialog = CCSprite::create("LoseDialog.png");
	this->_LoseDialog->setPosition( ccp(visibleSize.width/2 + origin.x, (visibleSize.height*0.50) + origin.y) );
	this->addChild( this->_LoseDialog, 2);
	this->_LoseDialog->setVisible( false );

	//this->setTouchMode( kCCTouchesAllAtOnce );

	this->setTouchEnabled(true);
}

void MonkeyRush::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
	static bool resetGameOnTouch = false;

	CCTouch* pTouch = (CCTouch*)( touches->anyObject() );

	// First touch will remove the Dialog and the game can start
	if( this->pDialogBox != NULL )
	{
		this->removeChild(this->pOKDialog, true);
		this->removeChild(this->pDialogBox, true);

		this->pDialogBox = NULL;
		this->pOKDialog = NULL;

		this->_startTheGame();
	}
	else
	{
		if( resetGameOnTouch )
		{
			this->_resetGame();
			resetGameOnTouch = false;
		}
		else
		{
			this->_addNewMonkey( pTouch->getLocation() );
			if ( this->_logic_checkWinCondition( ) ){
				this->_Win();
				resetGameOnTouch = true;
			} else	if( this->_logic_checkLoosCondition( ) ){
				this->_Lose();
				resetGameOnTouch = true;
			} else {
				// If not, just spawn a fire
				this->_logic_SpawnNewTreeFire();
			}
		}
	}
}

void MonkeyRush :: draw()
{

	CCLayer::draw();
	//red line from bottom left to top right corner
	ccDrawColor4F(1.0f, 0.0f, 0.0f, 1.0f);
	ccDrawLine(ccp(0,0), ccp(200, 200));
	//CCLog("Drawing ...");
}

void MonkeyRush :: _startTheGame()
{
//	this->schedule( schedule_selector(HelloWorld::gameLogic), 1.0 );
//	this->schedule( schedule_selector(HelloWorld::updateGame) );

	CCLog("Starting the game ...");

	CCSprite* firstMonkey = CCSprite::create("monkey.png");
	if( !firstMonkey->isVisible() )
		CCLog("Loading sprite failed!");

	CCPoint posFirstMonkey = CCPoint( this->visibleSize.width/2 + this->origin.x, this->origin.y + (firstMonkey->boundingBox().size.height / 2) );
	firstMonkey->setPosition( posFirstMonkey );
	this->addChild( firstMonkey, 2);
	GridPos gp = this->_Position2GridCell( posFirstMonkey.x, posFirstMonkey.y );
	this->_setCellState( gp, MONKEY );

}

void MonkeyRush :: _addNewMonkey( CCPoint positon )
{
	CCLog("Will try to add new monkey to [%f %f]", positon.x, positon.y );

	GridPos cell;
	cell = this->_Position2GridCell( positon.x, positon.y );

	CCLog("Found this position to be grid cell [%d %d]", cell.x, cell.y );

	if( this->_logic_testValidMonkeyCell( cell ))
	{
		this->_setCellState( cell, MONKEY );
		CCPoint cellCenter = this->_getCellCenter( cell );

		CCLog("Setting new monkey to [%f %f]", cellCenter.x, cellCenter.y);

		CCTexture2D* tex = this->_climbingMonkeySprite->getTexture();
		CCSprite* nMonkey = CCSprite::createWithTexture( tex );
		nMonkey->setPosition( cellCenter );
		this->addChild( nMonkey, 2);
		this->_monkeys->addObject( nMonkey );
	} else {
		CCLog("Logic says no monkey here!");
	}
}

void MonkeyRush::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

MonkeyRush::GridPos MonkeyRush::_Position2GridCell ( float x, float y )
{
	GridPos gp;

	gp.x = ( x-this->origin.x )  / this->cw; gp.y = (y - this->origin.y) / this->ch;

	return gp;
}

CCPoint MonkeyRush::_getCellCenter( GridPos cp )
{
	CCPoint p;
	p.x = this->origin.x + ( cp.x * this->cw ) + (this->cw / 2.0);
	p.y = this->origin.y + ( cp.y * this->ch ) + (this->ch / 2.0);
	return p;
}

void MonkeyRush::_setCellState( GridPos cell, TildState state)
{
	this->grid[ cell.x ][ cell.y ] = state;
}

MonkeyRush::TildState MonkeyRush::_getCellState( GridPos cell )
{
	if( (cell.x >= 0 ) &&  (cell.x < MonkeyRush::GridWidth ) && (cell.y >= 0 ) &&  (cell.y < MonkeyRush::GridHeight ) )
		return this->grid[ cell.x ][ cell.y ];
	else
		return INVALID;
}

bool MonkeyRush::_logic_testValidMonkeyCell( GridPos cell )
{
	if ( this->_getCellState( cell ) == EMPTY )
	{
		//Only if one of the neighboring cell contains a monkey
		if( this->_getCellState( {cell.x - 1, cell.y} ) == MONKEY )
			return true;
		if( this->_getCellState( {cell.x + 1, cell.y} ) == MONKEY )
			return true;

		if( this->_getCellState( {cell.x, cell.y - 1} ) == MONKEY )
			return true;
		if( this->_getCellState( {cell.x, cell.y + 1} ) == MONKEY )
			return true;

		if( this->_getCellState( {cell.x - 1, cell.y - 1} ) == MONKEY )
			return true;
		if( this->_getCellState( {cell.x - 1, cell.y + 1} ) == MONKEY )
			return true;

		if( this->_getCellState( {cell.x + 1, cell.y - 1} ) == MONKEY )
			return true;
		if( this->_getCellState( {cell.x + 1, cell.y + 1} ) == MONKEY )
			return true;
	}

	return false;
}

void MonkeyRush::_logic_SpawnNewTreeFire( )
{
	bool setFire = false;
	GridPos cell;

	if ( this->_logic_checkLoosCondition() == true )
		return; //If there is no free cell left dont try to set a tree fire

	do{
		cell = { rand() % this->GridWidth , rand() % this->GridHeight };
		if( this->_getCellState( cell ) == EMPTY )
		{
			this->_setCellState( cell, FIRE );
			CCPoint cellCenter = this->_getCellCenter( cell );

			CCLog("Setting new Tree Fire to cell [%d %d] pos [%f %f]", cell.x, cell.y, cellCenter.x, cellCenter.y );

			CCTexture2D* tex = this->_TreeFireSprite->getTexture();
			CCSprite* treeFire = CCSprite::createWithTexture( tex );
			treeFire->setScale( 0.5 );
			treeFire->setPosition( cellCenter );
			this->addChild( treeFire, 2);
			this->_TreeFires->addObject( treeFire );

			setFire = true;
		}
	}	while( !setFire );

}

bool MonkeyRush::_logic_checkWinCondition()
{
	//If there is a monkey on the top row the player won
	for(int i=0; i < MonkeyRush::GridWidth; i++){
		if( this->_getCellState( {i, MonkeyRush::GridHeight-1} ) == MONKEY )
			return true;
	}
	return false;
}

bool MonkeyRush::_logic_checkLoosCondition()
{
	// When there is no free tile left, the user lost
	for(int i=0; i < MonkeyRush::GridWidth; i++){
		for(int j=0; j < MonkeyRush::GridHeight; j++){
			if( this->_getCellState( {i, j} ) == EMPTY )
				return false;
		}
	}
	return true;
}

void MonkeyRush::_Win()
{
	CCLog( "Player won the game!!!" );
	this->_WinDialog->setVisible( true );
}

void MonkeyRush::_Lose()
{
	CCLog( "Player lost the game!!! ");
	this->_LoseDialog->setVisible( true );
}

void MonkeyRush::_resetGame()
{
	CCLog( "Reseting the game ..." );
	while( this->_TreeFires->count() > 0){
		CCNode* p =  (CCNode*) this->_TreeFires->lastObject() ;
		this->_TreeFires->removeLastObject( );
		this->removeChild( p , true);

	}
	while( this->_monkeys->count() > 0){
		CCNode* p = (CCNode*) this->_monkeys->lastObject();
		this->_monkeys->removeLastObject( );
		this->removeChild( p , true);

	}

	for(int i=0; i < MonkeyRush::GridWidth; i++){
		for(int j=0; j < MonkeyRush::GridHeight; j++){
			this->_setCellState( {i, j} , EMPTY );
		}
	}

	this->_WinDialog->setVisible( false );
	this->_LoseDialog->setVisible( false );
}
