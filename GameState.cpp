//
//  GameState.cpp
//  Boundless
//
//  Created by Rick Chou on 10/3/15.
//  Copyright © 2015 Rick Chou. All rights reserved.
//

#include "GameState.hpp"

void CGameState::Init() {
    
    m_bInit = true;
    
}

void CGameState::PostInit() {
    
    m_bPostInit = true;
    
    m_pPlayerSprite = nullptr;
    m_pPlayer = nullptr;

    m_pPlayer = m_pGameContext->CreateEntity_Player( 300.0f, 300.0f );
    m_pPlayer->SetScale( 4.0f, 4.0f );
}

void CGameState::OnStateSwitch() {
    
}

void CGameState::Input() {
    
    m_GameInput.Poll();
    auto eventType = m_GameInput.EventType();
    
    if( eventType == SDL_QUIT ) {
        
        m_bContinue = false;
        
    }
    
}

void CGameState::Think() {
    
    m_pGameContext->Think();

}

void CGameState::Draw() {
    
    m_pGameContext->GraphicsContext()->ClearBuffer();
    
    static CTextureImage * ground = GetTexture( "data/textures/world/testground1.png" );
    
   
    if( ground ) {
        
        for( int y = 0; y < 20; y++ ) {
            for( int x = 0; x < 20; x++ ) {
                m_pGameContext->DrawContext()->DrawMaterial( *ground, x * 84, y * 84, 84, 84, 1.0f, 1.0f, 1.0f, 1.0f );
            }
        }
        
        
    }
    
    m_pGameContext->EntityManager()->DrawAllEntities();
    
    
    m_pGameContext->GraphicsContext()->SwapBuffers();
    
}

