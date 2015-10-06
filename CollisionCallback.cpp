//
//  CollisionCallback.cpp
//  Boundless
//
//  Created by Rick Chou on 10/5/15.
//  Copyright © 2015 Rick Chou. All rights reserved.
//

#include "CollisionCallback.hpp"


void CCollisionCallback::BeginContact( CCollisionContact & pCollisionContact ) {
    
    CEntity * entityA = static_cast< CEntity * >( pCollisionContact.GetObjectA() );
    CEntity * entityB = static_cast< CEntity * >( pCollisionContact.GetObjectB() );
    
    CEntity * entities[] = { entityA, entityB };
    
    int entityTypeA = entityA->GetClassTypeID();
    int entityTypeB = entityB->GetClassTypeID();
    int entityTypes = ( entityTypeA | entityTypeB );

    
    if( entityTypes & ENTTYPE::DAMAGE && entityTypes & ENTTYPE::ENEMY ) {
        std::stringstream ss;
        ss << entityTypes;
        Log::Log( ss.str());
        Log::Log( "COLLISION");
        
        CEntity * mainEnt = nullptr;
        CEntity * subEnt = nullptr;
        
        if( entityTypeA & ENTTYPE::DAMAGE ) {
            mainEnt = entityB;
            subEnt = entityA;
        } else {
            mainEnt = entityA;
            subEnt = entityB;
        }
        
        
        m_pContext->HandleEntityContact( mainEnt, mainEnt->GetClassTypeID(), subEnt, subEnt->GetClassTypeID() );
        
    }
    
    
}

