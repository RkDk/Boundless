//
//  Game.h
//  Boundless
//
//  Created by Rick Chou on 10/3/15.
//  Copyright © 2015 Rick Chou. All rights reserved.
//

#ifndef Game_h
#define Game_h

#include "SoraIncludes.h"
#include "BNDGameContext.hpp"
#include "BNDEntityManager.hpp"
#include "Define.hpp"
#include "GameState.hpp"


class CGame
{
    
private:
    
    CGraphicsContext m_GraphicsContext;
    CDrawContext m_DrawContext;
    CSoundContext m_SoundContext;
    CFreeTypeContext m_FTContext;
    CStateMachine m_StateMachine;
    CTextureFactory m_TextureFactory;
    CSoundFactory m_SoundFactory;
    CFontFactory m_FontFactory;
    CBNDEntityManager m_EntityManager;
    CBNDGameContext m_GameContext;
    
public:
    
    CGame();
    ~CGame();
    
};

#endif /* Game_h */
