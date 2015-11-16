//
//  Define.hpp
//  Boundless
//
//  Created by Rick Chou on 10/3/15.
//  Copyright © 2015 Rick Chou. All rights reserved.
//

#ifndef Define_h
#define Define_h

#define DEFAULT_SCREEN_WIDTH 1024
#define DEFAULT_SCREEN_HEIGHT 768
#define SET_DEFAULT_CLEARCOLOR() glClearColor( .1f, .1f, .1f, 1.0f )

enum ENTTYPE {

    PLAYER = 0x01,
    ENEMY = 0x02,
    DAMAGE = 0x04
    
};


#endif /* Define_h */
