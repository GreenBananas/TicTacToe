/*
 * MonkeyRush.h
 *
 *  Created on: Mar 31, 2013
 *      Author: mapa17@posgrado.upv.es
 */

#ifndef MONKEYRUSH_H_
#define MONKEYRUSH_H_

#include "cocos2d.h"
#include <CCDrawNode.h>
#include <CCGeometry.h>

class MonkeyRush : public cocos2d::CCLayer //, public cocos2d::CCDrawNode
{
public:

	//Parameterize the game
	static const int GridWidth 		= 4;
	static const int GridHeight 	= 6;


	typedef enum _TildState { EMPTY, MONKEY, FIRE, INVALID } TildState;
	typedef enum _ClickState { MONKEY_CLICK, FIREMONKEY, INITIAL_DIALOG, RESET_GAME } ClickState;

	typedef struct { unsigned int x; unsigned int y; } GridPos;

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();

    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    void onFireManMonkeyClick( CCObject* pSender );

    //bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    //void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

    void draw();

    void setClickState( MonkeyRush::ClickState state) { this->currentClickState = state; };
    MonkeyRush::ClickState getClickState( ) { return this->currentClickState; };

    // implement the "static node()" method manually
    CREATE_FUNC(MonkeyRush);

protected:
    cocos2d::CCSprite* 	pDialogBox;
    cocos2d::CCSprite*	pOKDialog;

    cocos2d::CCSprite* _climbingMonkeySprite;
    cocos2d::CCSprite* _TreeFireSprite;
    cocos2d::CCSprite* _WinDialog;
    cocos2d::CCSprite* _LoseDialog;
    cocos2d::CCArray*	_monkeys;
    cocos2d::CCArray*	_TreeFires;


    cocos2d::CCSize		visibleSize;
    cocos2d::CCPoint	origin;

    float cw, ch;	//Cell width and cell height. Will be calculated in _initGame();

    void _startTheGame();
    void _addNewMonkey( cocos2d::CCPoint positon );
    void _extinguishFire( cocos2d::CCPoint positon );
    GridPos _Position2GridCell ( float x, float y );
    cocos2d::CCPoint _getCellCenter( GridPos cp );
    void _setCellState( GridPos cell, TildState state);
    MonkeyRush::TildState _getCellState( GridPos cell );
    bool _logic_testValidMonkeyCell( GridPos cell );
    void _logic_SpawnNewTreeFire( );
    bool _logic_checkWinCondition();
    bool _logic_checkLoosCondition();

    void _Win();
    void _Lose();
    void _resetGame();


    ClickState currentClickState;
    TildState grid[GridWidth][GridHeight];
    cocos2d::CCObject* gridReferences[GridWidth][GridHeight];

    unsigned int nFireMonkeys;

    void _initGame();
    void _initVariables();
    void _loadScene();
};

#endif /* MONKEYRUSH_H_ */
