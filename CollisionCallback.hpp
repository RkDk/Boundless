//
//  CollisionCallback.hpp
//  Boundless
//
//  Created by Rick Chou on 10/5/15.
//  Copyright © 2015 Rick Chou. All rights reserved.
//

#ifndef CollisionCallback_hpp
#define CollisionCallback_hpp

#include "SoraIncludes.h"
#include "Define.hpp"
#include <sstream>

class CCollisionCallback : public CCollisionListener {
    
    CEntityContext * m_pContext;
    
public:
    
    void BeginContact( CCollisionContact & );
    
    
    void SetContext( CEntityContext * pContext ) {
        
        m_pContext = pContext;
        
    }
    
    CCollisionCallback() : CCollisionListener(), m_pContext( nullptr ) {
        
        
        
    }
    
};


#endif /* CollisionCallback_hpp */
