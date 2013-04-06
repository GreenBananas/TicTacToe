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


	typedef enum _TildState { EMPTY, MONKEY, FIRE } TildState;
	typedef struct { unsigned int x; unsigned int y; } GridPos;

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();

    // a selector callback
    void menuCloseCallback(CCObject* pSender);

    //bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    //void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

    void draw();

    // implement the "static node()" method manually
    CREATE_FUNC(MonkeyRush);

protected:
    cocos2d::CCSprite* 	pDialogBox;
    cocos2d::CCSprite*	pOKDialog;

    cocos2d::CCSprite* _climbingMonkeySprite;
    cocos2d::CCArray*	_monkeys;

    cocos2d::CCSize		visibleSize;
    cocos2d::CCPoint	origin;

    float cw, ch;	//Cell width and cell height. Will be calculated in _initGame();

    void _startTheGame();
    void _addNewMonkey( cocos2d::CCPoint positon );
    GridPos _Position2GridCell ( float x, float y );
    cocos2d::CCPoint _getCellCenter( GridPos cp );
    void _setCellState( GridPos cell, TildState state);
    MonkeyRush::TildState _getCellState( GridPos cell );
    bool _logic_testValidMonkeyCell( GridPos cell );

    TildState grid[GridWidth][GridHeight];

    void _initGame();
    void _loadScene();
};

#endif /* MONKEYRUSH_H_ */
