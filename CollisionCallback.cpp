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
    
    CEntity * mainEnt = nullptr;
    CEntity * subEnt = nullptr;
    
    int entityTypeA = entityA->GetClassTypeID();
    int entityTypeB = entityB->GetClassTypeID();
    int entityTypes = ( entityTypeA | entityTypeB );
    
    bool doCallBack = false;
    
    if( entityTypes & ENTTYPE::DAMAGE && entityTypes & ENTTYPE::ENEMY ) {

        mainEnt = nullptr;
        subEnt = nullptr;
        
        if( entityTypeA & ENTTYPE::DAMAGE ) {
            mainEnt = entityB;
            subEnt = entityA;
        } else {
            mainEnt = entityA;
            subEnt = entityB;
        }
        
        doCallBack = true;
        
        
    }
    
    if( entityTypes & ENTTYPE::WALL || entityTypes & ENTTYPE::WALL ) {
        
        mainEnt = ( entityTypeA & ENTTYPE::WALL )? entityB : entityA;
        subEnt = ( entityTypeB & ENTTYPE::WALL ) ? entityB : entityA;
        
        doCallBack = true;
        
    }
    
    if( doCallBack )
        m_pContext->HandleEntityContact( mainEnt, mainEnt->GetClassTypeID(), subEnt, subEnt->GetClassTypeID(), pCollisionContact.GetCollisionInfo() );
    
    
}

