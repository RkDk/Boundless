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
#include "GameVars.hpp"
#include "Define.hpp" 
#include "AI_IdiotTestEnemy.hpp" 
#include "CollisionCallback.hpp"
#include "Ent_DamageBox.hpp"

class CBNDGameContext : public CLuaContext {
  
private:
    
    CSpatialQuadTree m_Quadtree;
    CCollisionCallback m_CollisionCallback;
    CCollisionEngine m_CollisionEngine;
    
    CWorldEntity * m_pPlayerEntity;
    CGameVars m_GameVars;
    
    bool m_bGameActive;
    
public:
    
    CWorldEntity * GetPlayer() {
        return m_pPlayerEntity;
    }
    
    CGameVars & GameVars() {
        return m_GameVars;
    }
    
    void HandleEntityContact( void *, int, void *, int );
    
    CEnt_DamageBox * CreateEntity_DamageBox( float, float, float, float, float, DMBSource );
    CWorldEntity * CreateEntity_Enemy( float, float );
    CWorldEntity * CreateEntity_Player( float, float );
    
    bool GetBoolean( std::string );
    void Initialize();
    
    void UpdateAllEntities();
    void Think();
    
    void DrawQuadTree();
    
    
};


#endif /* BNDGameContext_hpp */
