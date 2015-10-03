//
//  BNDGameContext.hpp
//  Boundless
//
//  Created by Rick Chou on 10/3/15.
//  Copyright © 2015 Rick Chou. All rights reserved.
//

#ifndef BNDGameContext_hpp
#define BNDGameContext_hpp

#include "SoraIncludes.h"
#include "LuaContext.hpp"

class CBNDGameContext : public CLuaContext {
  
private:
    
public:
    
    bool GetBoolean( std::string );
    
    void Initialize();
    
    
};


#endif /* BNDGameContext_hpp */
