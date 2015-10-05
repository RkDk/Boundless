//
//  BNDGameContext.cpp
//  Boundless
//
//  Created by Rick Chou on 10/3/15.
//  Copyright © 2015 Rick Chou. All rights reserved.
//

#include "BNDGameContext.hpp"

void CBNDGameContext::Initialize() {
    
    m_bGameActive = true;
    m_pPlayerEntity = nullptr;
    
    LoadResources( "data/resources.res" );
    
    InitAllShaders();
    m_pGraphicsContext->UseShader( 0 );
    
}

bool CBNDGameContext::GetBoolean( std::string name ) {
    
    return false;
    
}

void CBNDGameContext::Think() {
    
    if( m_bGameActive ) {
        
        
    }
    
    m_pEntityManager->RemoveAllDeletedEntities();
    m_pEntityManager->AddAllQueuedEntities();
    
    
}

CWorldEntity * CBNDGameContext::CreateEntity_Player( float x, float y ) {
    
    if( m_pPlayerEntity ) {
        
        delete m_pPlayerEntity;
        m_pPlayerEntity = nullptr;
        
    }
    
    m_pPlayerEntity = m_pEntityManager->CreateEntity< CWorldEntity >( x, y );
    m_pPlayerEntity->SetMaterial( GetTexture( "data/textures/player/player2.png" ) );
    m_pPlayerEntity->SetCollisionBodyToBoxSprite();
    
    return m_pPlayerEntity;
    
}