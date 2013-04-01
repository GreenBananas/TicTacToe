/*
 * TouchableSprite.h
 *
 *  Created on: Mar 31, 2013
 *      Author: mapa17@posgrado.upv.es
 */

#ifndef TOUCHABLESPRITE_H_
#define TOUCHABLESPRITE_H_

#include <CCTouchDelegateProtocol.h>
#include <CCSprite.h>

USING_NS_CC;

NS_CC_BEGIN
class CCTouch;
class CCEvent;
NS_CC_END

class TouchableSprite : public CCSprite, public CCTargetedTouchDelegate
{
public:
	static TouchableSprite* create(const char* fileName, void *pCallback(CCTouch*) );

	//TouchableSprite(void);
    //virtual ~TouchableSprite(void);
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

protected:
	bool _wasTouched(CCTouch *pTouch);
	void (*callback)(CCTouch*);

	static int ID;

};

#endif /* TOUCHABLESPRITE_H_ */
