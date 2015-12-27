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

class CBNDLevelEditorCallback : public CLevelEditorCallback {
    
    CLuaContext * m_pGameContext;
    
public:
    
    void SetGameContext( CLuaContext * pGameContext ) {
        m_pGameContext = pGameContext;
    }
    
    void HandleEntityCreation( CLevelEntityInfo & );
    
};

class CBNDGameContext : public CLuaContext {
  
private:
    
    CSpatialQuadTree m_Quadtree;
    CCollisionCallback m_CollisionCallback;
    CCollisionEngine m_CollisionEngine;
    CBNDLevelEditorCallback m_LevelEditorCallback;
    CWorldEntity * m_pPlayerEntity;
    CGameVars m_GameVars;
    
    CLevel m_GameLevel;
    CLevelEditor m_LevelEditor;
    CCamera m_GameCamera;
    
    bool m_bGameActive;
    
public:
    
    void CreateLightSpot( float, float, int, int, int );
    
    CWorldEntity * GetPlayer() {
        return m_pPlayerEntity;
    }
    
    CGameVars & GameVars() {
        return m_GameVars;
    }
    
    CSpatialQuadTree & GetSpatialQuadTree() {
        return m_Quadtree;
    }
    
    CLevel & GetLevel() {
        return m_GameLevel;
    }
    
    CCamera & GetGameCamera() {
        
        return m_GameCamera;
        
    }
    
    CLevelEditor & GetLevelEditor() {
        return m_LevelEditor;
    }
    
    void HandleEntityContact( void *, int, void *, int, CCollisionInfo * );
    
    CEnt_DamageBox * CreateEntity_DamageBox( float, float, float, float, float, DMBSource );
    CWorldEntity * CreateEntity_Enemy( float, float );
    CWorldEntity * CreateEntity_Player( float, float );
    
    void LoadLevel( std::string );
    
    bool GetBoolean( std::string );
    void Initialize();
    
    void UpdateAllEntities();
    void Think();
    
    void DrawLevel();
    void DrawLevelEditor();
    void DrawQuadTree();
    
    
};


#endif /* BNDGameContext_hpp */
