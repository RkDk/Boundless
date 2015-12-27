//
//  LuaContext.hpp
//  Boundless
//
//  Created by Rick Chou on 10/3/15.
//  Copyright © 2015 Rick Chou. All rights reserved.
//

#ifndef LuaContext_h
#define LuaContext_h

#include "BNDEntityManager.hpp"

class CLuaContext : public CGameContext< CBNDEntityManager > {
  
public:
    
    virtual void CreateLightSpot( float, float, int, int, int ) = 0;
    
};

#endif /* LuaContext_h */
