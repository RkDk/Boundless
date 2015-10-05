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
#include "Define.hpp" 

class CBNDGameContext : public CLuaContext {
  
private:
    
    CWorldEntity * m_pPlayerEntity;
    
    bool m_bGameActive;
    
public:
    
    CWorldEntity * GetPlayer() {
        return m_pPlayerEntity;
    }
    
    CWorldEntity * CreateEntity_Player( float, float );
    
    bool GetBoolean( std::string );
    void Initialize();
    
    void Think();
    
    
};


#endif /* BNDGameContext_hpp */
