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
    
}

void CGameState::Draw() {
    
    m_pGameContext->GraphicsContext()->ClearBuffer();
    
    m_pGameContext->GraphicsContext()->SwapBuffers();
    
}

