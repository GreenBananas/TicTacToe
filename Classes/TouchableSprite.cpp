/*
 * TouchableSprite.cpp
 *
 *  Created on: Mar 31, 2013
 *      Author: mapa17@posgrado.upv.es
 */

#include "TouchableSprite.h"


#include "stdio.h"
#include "CCDirector.h"
#include "CCTouchDispatcher.h"

USING_NS_CC;

int TouchableSprite::ID = 0;

TouchableSprite* TouchableSprite::create(const char* fileName, void *pCallback(CCTouch*) )
{

	//"Dont use this, is not working! It misses the callback handilng ..."
	throw std::exception();

	//TouchableSprite* pS = (TouchableSprite*) TouchableSprite::create( fileName );
	TouchableSprite* pTS = new TouchableSprite();
	pTS->initWithFile( fileName );

	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate( pTS, TouchableSprite::ID, true );
	TouchableSprite::ID++;

	pTS->callback = pCallback;

	CCLog("Created new touchableSprite ...");
	return pTS;
}


bool TouchableSprite::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	CCLog("In ccTouchBegan");
	if( this->_wasTouched( pTouch ) )
	{
		CCLog("Wujuu, i was touched");
		try{
			this->callback(pTouch);
		} catch ( std::exception& e)
		{
			CCLog("Calling callback failed! Reason [%s] ", e.what() );
		}
		return true;
	}
	return false;
};

bool TouchableSprite::_wasTouched(CCTouch *pTouch)
{
	CCPoint click = pTouch->getLocation();
	float x,y,w,h;

	x = this->boundingBox().origin.x;
	y = this->boundingBox().origin.y;
	w = this->boundingBox().size.width;
	h = this->boundingBox().size.height;

	CCLog("Click [%f %f]", click.x, click.y);

	if( (click.x >= x) && (click.x <= x+w) )
		if( (click.y >= y) && (click.y <= y+h)  )
			return true;

	return false;
}

void TouchableSprite::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	CCLog("In ENDED!!");
};
