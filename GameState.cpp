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
    m_pPlayer = nullptr;
    m_pGameVars = &m_pGameContext->GameVars();
    
    m_ShadowOcclusionFBO.Init( 512, 1 );
    m_SceneFBO.Init( DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT );
    m_ShadowObjectsFBO.Init( DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT );
    m_DynamicShadowFBO.Init( DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT );
    m_DynamicShadowCopyFBO.Init( DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT );
    m_AmbientLightingFBO.Init( DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT );
    m_EntityFBO.Init( DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT );
    m_SceneFBO.Init( DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT );
    
    //m_ShadowsFBO.Init( DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT );
    //m_LightsFBO.Init( DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT );
    
    CWorldEntity * e = m_pGameContext->CreateEntity_Enemy( 510.0f, 200.0f );
    e->SetScale( 8.0f, 8.0f );
    e->SetCollisionBodyToBoxSprite();
    e->UpdateSpatialTreeEntitySize();
    
    m_pPlayer = m_pGameContext->CreateEntity_Player( 300.0f, 300.0f );
    m_pPlayer->SetScale( 5.0f, 5.0f );
    m_pPlayer->SetCollisionBodyToBoxSprite();
    m_pPlayer->UpdateSpatialTreeEntitySize();
    

    for( int j = 0; j < 4; j++ ) {
        CLightSpot l;
        l.SetColor( 1.0f, 1.0f, 1.0f, 1.0f );
        l.SetWorldPos( j * 300.0f, 10.0f );
    m_LightSpots.push_back( l );
    }
    
    testLevel.Load( "data/level.txt", m_pGameContext->TextureFactory() );
    
}

void CGameState::OnStateSwitch() {
    
}

void CGameState::Input() {
    
    m_GameInput.Poll();
    auto eventType = m_GameInput.EventType();

    if( m_GameInput.KeyDown( SDL_SCANCODE_W ) ) {
        
        m_pPlayer->SetMaterialToTexture( 3 );
        m_pPlayer->Displace2( 0.0f, -m_pGameVars->m_PlayerYSpeed );
    
    }
    
    if( m_GameInput.KeyDown( SDL_SCANCODE_A ) ) {
        
        m_pPlayer->SetMaterialToTexture( 2 );
        m_pPlayer->Displace2( -m_pGameVars->m_PlayerXSpeed, 0.0f );
        
    }
    
    if( m_GameInput.KeyDown( SDL_SCANCODE_S ) ) {
    
        m_pPlayer->SetMaterialToTexture( 0 );
        m_pPlayer->Displace2( 0.0f, m_pGameVars->m_PlayerYSpeed );
    
    }
    
    if( m_GameInput.KeyDown( SDL_SCANCODE_D ) ) {
    
        m_pPlayer->SetMaterialToTexture( 1 );
        m_pPlayer->Displace2( m_pGameVars->m_PlayerYSpeed, 0.0f );
    
    }
    
    if( m_GameInput.KeyDown( SDL_SCANCODE_J ) ) {
        
        Vector3< float > pos = m_pPlayer->GetPos();
        m_pGameContext->CreateEntity_DamageBox( pos.GetX(), pos.GetY(), 100.0f, 100.0f, 100.0f, DMBSource::PLAYER );
        
    }

    if( m_GameInput.EventType() == SDL_KEYDOWN ) {
        
        if( m_GameInput.KeyDownOnce( SDLK_ESCAPE ) ) {
            
            m_bContinue = false;
            
        }
        
    }
    
    
    if( eventType == SDL_QUIT ) {
        
        m_bContinue = false;
        
    }
    
}

void CGameState::Think() {
    
    m_pGameContext->Think();

}

void CGameState::Draw() {
    
    static CTextureImage * pixel = GetTexture( "data/textures/pixel.png" );
    
    SET_DEFAULT_CLEARCOLOR();
    m_pGameContext->GraphicsContext()->ClearBuffer();
    
    //Clear any FBOs as necessary
    m_DynamicShadowFBO.Clear();
    m_DynamicShadowCopyFBO.Clear();
    
    //Render all objects that will cast a shadow onto FBO.
    m_ShadowObjectsFBO.BeginDrawingToFBO();
    {
        m_pGameContext->GraphicsContext()->UseShader( 3 );
        m_pGameContext->GraphicsContext()->ClearBuffer();
        int l = m_pGameContext->GraphicsContext()->GetShaderUniformLocation( 3, "spriteTex" );
        glUniform1i( l, 1 );
        m_pGameContext->EntityManager()->DrawAllEntitiesShadowBase( m_pGameContext->DrawContext(), pixel );
    }
    m_ShadowObjectsFBO.EndDrawingToFBO();
    
    for( auto iter : m_LightSpots ) {
        
        Vector2< float > lPos( iter.GetWorldPos() );
        
        lPos.Set( lPos.GetX() / DEFAULT_SCREEN_WIDTH, lPos.GetY() / DEFAULT_SCREEN_HEIGHT );
        
        //Create a shadow occlusion texture
        m_ShadowOcclusionFBO.BeginDrawingToFBO();
        {

            glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
            glClear( GL_COLOR_BUFFER_BIT );

            m_pGameContext->GraphicsContext()->UseShader( 1 );
            
            glActiveTexture( GL_TEXTURE1 );
            m_ShadowObjectsFBO.BindTexture();
            
            int l = m_pGameContext->GraphicsContext()->GetShaderUniformLocation( 1, "shadowObjTex" );
            glUniform1i( l, 1 );
            
            l = m_pGameContext->GraphicsContext()->GetShaderUniformLocation( 1, "lightPos" );
            glUniform2f( l, lPos.GetX(), lPos.GetY() );
            
            glActiveTexture( GL_TEXTURE0 );
            m_pGameContext->DrawContext()->DrawMaterial( *pixel, 0.0f, DEFAULT_SCREEN_HEIGHT - 1.0f, 512.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f );
        }
        m_ShadowOcclusionFBO.EndDrawingToFBO();
        
        //Create dynamic shadows from shadow occlusion texture
        m_DynamicShadowFBO.BeginDrawingToFBO();
        {
            glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
            glClear( GL_COLOR_BUFFER_BIT );
            
            m_pGameContext->GraphicsContext()->UseShader( 2 );
            
            glActiveTexture( GL_TEXTURE1 );
            m_ShadowOcclusionFBO.BindTexture();
            
            int l = m_pGameContext->GraphicsContext()->GetShaderUniformLocation( 2, "shadowOccTex" );
            glUniform1i( l, 1 );
            
            l = m_pGameContext->GraphicsContext()->GetShaderUniformLocation( 2, "lightPos" );
            glUniform2f( l, lPos.GetX(), lPos.GetY() );
            
            glActiveTexture( GL_TEXTURE0 );
            m_DynamicShadowCopyFBO.DrawTexture( m_pGameContext->DrawContext() );
            
        }
        m_DynamicShadowFBO.EndDrawingToFBO();
        
        m_DynamicShadowCopyFBO.BeginDrawingToFBO();
            m_pGameContext->GraphicsContext()->UseShader( 0 );
            m_DynamicShadowFBO.DrawTexture( m_pGameContext->DrawContext() );
        m_DynamicShadowCopyFBO.EndDrawingToFBO();
        
        //TODO: Draw ambient lighting
        
    }
    
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

    //Draw entities into FBO
    m_EntityFBO.BeginDrawingToFBO();
        glClear( GL_COLOR_BUFFER_BIT );
        m_pGameContext->GraphicsContext()->UseShader( 0 );
        m_pGameContext->EntityManager()->DrawAllEntities();
    m_EntityFBO.EndDrawingToFBO();
    
    //Draw level into FBO
    m_SceneFBO.BeginDrawingToFBO();
        glClear( GL_COLOR_BUFFER_BIT );
        m_pGameContext->GraphicsContext()->UseShader( 0 );
        testLevel.Draw( m_pGameContext->DrawContext() );
    m_SceneFBO.EndDrawingToFBO();
    
    
    {
    
        m_pGameContext->GraphicsContext()->ClearBuffer();
        
        m_pGameContext->GraphicsContext()->UseShader( 4 );
        
        glActiveTexture( GL_TEXTURE2 );
        m_DynamicShadowFBO.BindTexture();
        
        glActiveTexture( GL_TEXTURE1 );
        m_EntityFBO.BindTexture();
        
        int l = glGetUniformLocation( m_pGameContext->GraphicsContext()->GetShaderIDFromIndex( 4 ), "entityTex" );
        glUniform1i( l, 1 );
        l = glGetUniformLocation( m_pGameContext->GraphicsContext()->GetShaderIDFromIndex( 4 ), "shadowTex" );
        glUniform1i( l, 2 );
        
        glActiveTexture( GL_TEXTURE0 );
        
        m_SceneFBO.DrawTexture( m_pGameContext->DrawContext() );
        
    }
    
    m_pGameContext->GraphicsContext()->SwapBuffers();
    
    /*
    
    
    static CTextureImage * ground = GetTexture( "data/textures/world/testground1.png" );
    static CTextureImage * wall1 = GetTexture( "data/textures/world/testwall1.png" );
    static CTextureImage * wall2 = GetTexture( "data/textures/world/testwall2.png" );
    static CTextureImage * wall3 = GetTexture( "data/textures/world/testwall3.png" );
    static CTextureImage * wall4 = GetTexture( "data/textures/world/testwall4.png" );
    static CTextureImage * wall5 = GetTexture( "data/textures/world/testwall5.png" );
    static CTextureImage * wall6 = GetTexture( "data/textures/world/testwall6.png" );
    static CTextureImage * wall7 = GetTexture( "data/textures/world/testwall7.png" );
    static CTextureImage * level = GetTexture( "data/textures/world/testlevel.png" );
    
    int mx, my;
    
    SDL_GetMouseState( &mx, &my );
    
    float light[] = { ( float )mx / DEFAULT_SCREEN_WIDTH, ( float )my / DEFAULT_SCREEN_HEIGHT };
    
    
    m_SceneFBO.BeginDrawingToFBO();
    
        m_pGameContext->GraphicsContext()->UseShader( 3 );
        m_pGameContext->GraphicsContext()->ClearBuffer();
    
        int l = glGetUniformLocation( m_pGameContext->GraphicsContext()->GetShaderIDFromIndex( 3 ), "texUnit2" );
        glUniform1i( l, 1 );
    
        l = glGetUniformLocation( m_pGameContext->GraphicsContext()->GetShaderIDFromIndex( 3 ), "lightPos" );
        glUniform2f( l, light[0], light[1] );
    
        m_pGameContext->EntityManager()->DrawAllEntitiesShadowBase( m_pGameContext->DrawContext(), pixel );
    
    m_SceneFBO.EndDrawingToFBO();
    
    m_ShadowOcclusionFBO.BeginDrawingToFBO();
    
    m_pGameContext->GraphicsContext()->ClearBuffer();
        m_pGameContext->GraphicsContext()->UseShader( 1 );
    
        glActiveTexture( GL_TEXTURE1 );
        m_SceneFBO.BindTexture();
    
        l = glGetUniformLocation( m_pGameContext->GraphicsContext()->GetShaderIDFromIndex( 1 ), "texUnit2" );
        glUniform1i( l, 1 );

        l = glGetUniformLocation( m_pGameContext->GraphicsContext()->GetShaderIDFromIndex( 1 ), "lightPos" );
        glUniform2f( l, light[0], light[1] );
    
        glActiveTexture( GL_TEXTURE0 );
        m_pGameContext->DrawContext()->DrawMaterial( *pixel, 0.0f, 767.0f, 256.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f );
    m_ShadowOcclusionFBO.EndDrawingToFBO();
    
    m_SceneFBO.BeginDrawingToFBO();
    
        m_pGameContext->GraphicsContext()->UseShader( 0 );
        m_pGameContext->GraphicsContext()->ClearBuffer();
    
        //m_pGameContext->DrawContext()->DrawMaterial( *level, 0.0f, -100.0f, 1000.0f, 1000.0f, 1.0f, 1.0f, 1.0f, 1.0f );
        testLevel.Draw( m_pGameContext->DrawContext() );
        */
         /*
         if( ground ) {
         
             for( int y = 0; y < 20; y++ ) {
                 for( int x = 0; x < 20; x++ ) {
                    m_pGameContext->DrawContext()->DrawMaterial( *ground, x * 84 + 168, 168 + y * 84, 84, 84, 1.0f, 1.0f, 1.0f, 1.0f );
                 }
             }
         
         }
         
         if( wall2 ) {
             for( int x = 0; x < 20; x++ ) {
                m_pGameContext->DrawContext()->DrawMaterial( *wall2, 168 + x * 84, 0, 84, 84, 1.0f, 1.0f, 1.0f, 1.0f );
             }
         }
         
         if( wall1 ) {
             for( int x = 0; x < 20; x++ ) {
                m_pGameContext->DrawContext()->DrawMaterial( *wall1, 168 + x * 84, 84, 84, 84, 1.0f, 1.0f, 1.0f, 1.0f );
             }
         }
         
         m_pGameContext->DrawContext()->DrawMaterial( *wall3, 0, 0, 84, 84, 1.0f, 1.0f, 1.0f, 1.0f );
         m_pGameContext->DrawContext()->DrawMaterial( *wall4, 84, 0, 84, 84, 1.0f, 1.0f, 1.0f, 1.0f );
         m_pGameContext->DrawContext()->DrawMaterial( *wall5, 0, 84, 84, 84, 1.0f, 1.0f, 1.0f, 1.0f );
         m_pGameContext->DrawContext()->DrawMaterial( *wall6, 84, 84, 84, 84, 1.0f, 1.0f, 1.0f, 1.0f );
         
         if( wall7 ) {
         
             for( int x = 0; x < 20; x++ ) {
                m_pGameContext->DrawContext()->DrawMaterial( *wall7, 84, 168 + 84 * x, 84, 84, 1.0f, 1.0f, 1.0f, 1.0f );
                 m_pGameContext->DrawContext()->DrawMaterial( *wall5, 0, 168 + 84 * x, 84, 84, 1.0f, 1.0f, 1.0f, 1.0f );
             }
         }*/ /*
    m_SceneFBO.EndDrawingToFBO();
    
    m_LightsFBO.BeginDrawingToFBO();
        m_pGameContext->GraphicsContext()->ClearBuffer();
        m_pGameContext->GraphicsContext()->UseShader( 5 );
    l = glGetUniformLocation( m_pGameContext->GraphicsContext()->GetShaderIDFromIndex( 5 ), "lightPos" );
    glUniform2f( l, light[0], light[1] );
        m_pGameContext->DrawContext()->DrawMaterial( *pixel, 0, 0, DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT, 1.0f, 0.7f, 0.0f, 1.0f );
    m_LightsFBO.EndDrawingToFBO();

    glClearColor( .1f, .1f, .1f, 0.0f );
    
    m_ShadowsFBO.BeginDrawingToFBO();
        m_pGameContext->GraphicsContext()->ClearBuffer();
        
        m_pGameContext->GraphicsContext()->UseShader( 2 );
        
        glActiveTexture( GL_TEXTURE1 );
        m_ShadowOcclusionFBO.BindTexture();
        
        l = glGetUniformLocation( m_pGameContext->GraphicsContext()->GetShaderIDFromIndex( 2 ), "texUnit2" );
        glUniform1i( l, 1 );
    
        l = glGetUniformLocation( m_pGameContext->GraphicsContext()->GetShaderIDFromIndex( 2 ), "lightPos" );
        glUniform2f( l, light[0], light[1] );
    
        glActiveTexture( GL_TEXTURE0 );
        m_pGameContext->DrawContext()->DrawMaterial( *pixel, 0, 0, DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT, 1.0f, 1.0f, 1.0f, 1.0f );
    m_ShadowsFBO.EndDrawingToFBO();

    glClearColor( .1f, .1f, .1f, 1.0f );
    
    m_pGameContext->GraphicsContext()->ClearBuffer();
    
    m_pGameContext->GraphicsContext()->UseShader( 4 );
    
    glActiveTexture( GL_TEXTURE2 );
    m_LightsFBO.BindTexture();
    
    glActiveTexture( GL_TEXTURE1 );
    m_ShadowsFBO.BindTexture();
    
    l = glGetUniformLocation( m_pGameContext->GraphicsContext()->GetShaderIDFromIndex( 4 ), "texUnit2" );
    glUniform1i( l, 1 );
    l = glGetUniformLocation( m_pGameContext->GraphicsContext()->GetShaderIDFromIndex( 4 ), "texUnit3" );
    glUniform1i( l, 2 );
    
    glActiveTexture( GL_TEXTURE0 );
    
    m_SceneFBO.DrawTexture( m_pGameContext->DrawContext() );
    
    m_pGameContext->GraphicsContext()->UseShader( 0 );
    
    m_pGameContext->EntityManager()->DrawAllEntities();

    
    
    CMatrix< float > mat;
    mat.Identity();
    mat.Scale( 2.0f, 10.0f, 1.0f );
    mat.Translate( 0.0f, m_ShadowOcclusionFBO.GetHeight() + 30.0f, 0.0f );
   // m_ShadowOcclusionFBO.DrawTexture( m_pGameContext->DrawContext(), &mat );
    
    
        //m_pGameContext->DrawQuadTree();
    
    
    
    m_pGameContext->GraphicsContext()->SwapBuffers();
    */
    
}

