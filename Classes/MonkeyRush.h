/*
 * MonkeyRush.h
 *
 *  Created on: Mar 31, 2013
 *      Author: mapa17@posgrado.upv.es
 */

#ifndef MONKEYRUSH_H_
#define MONKEYRUSH_H_

#include "cocos2d.h"

class MonkeyRush : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();

    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    void onDialogOKPress(CCObject* pSender);

    // implement the "static node()" method manually
    CREATE_FUNC(MonkeyRush);
};

#endif /* MONKEYRUSH_H_ */
