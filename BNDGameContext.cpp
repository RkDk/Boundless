//
//  BNDGameContext.cpp
//  Boundless
//
//  Created by Rick Chou on 10/3/15.
//  Copyright © 2015 Rick Chou. All rights reserved.
//

#include "BNDGameContext.hpp"

void CBNDLevelEditorCallback::HandleEntityCreation( CLevelEntityInfo & e ) {
    
}

void CBNDGameContext::Initialize() {
    
    m_bGameActive = true;
    m_pPlayerEntity = nullptr;
    
    m_Quadtree.CreateTree( 0, 0, DEFAULT_SCREEN_WIDTH * 4, 0 );
    m_CollisionCallback.SetContext( this );
    
    LoadResources( "data/resources.res" );
    
    m_pGraphicsContext->LoadShaderProgram( "data/shaders/shadowocclusion_vertex.v", "data/shaders/shadowocclusion_fragment.f" );
    m_pGraphicsContext->LoadShaderProgram( "data/shaders/shadow_vertex.v", "data/shaders/shadow_fragment.f" );
    m_pGraphicsContext->LoadShaderProgram( "data/shaders/shadowbase_vertex.v", "data/shaders/shadowbase_fragment.f" );
    m_pGraphicsContext->LoadShaderProgram( "data/shaders/shadowscene_vertex.v", "data/shaders/shadowscene_fragment.f" );
    m_pGraphicsContext->LoadShaderProgram( "data/shaders/lights_vertex.v", "data/shaders/lights_fragment.f" );
    //m_pGraphicsContext->LoadShaderProgram( "data/shaders/shadowveil_vertex.v", "data/shaders/shadowveil_fragment.f" );
    
    //Init camera
    float xoffset = 0.35f;
    float yoffset = 0.35f;
    m_GameCamera.SetCameraType( CAMTYPE::BOX );
    m_GameCamera.SetBoxBounds( DEFAULT_SCREEN_WIDTH * xoffset, DEFAULT_SCREEN_HEIGHT * yoffset, DEFAULT_SCREEN_WIDTH * ( 1.0f - xoffset ), DEFAULT_SCREEN_HEIGHT * ( 1.0f - yoffset ) );
    
    //Set relevant level pointers and refs
    m_LevelEditorCallback.SetGameContext( this );
    m_GameLevel.SetEditorCallback( &m_LevelEditorCallback );
    m_LevelEditor.SetLevel( &m_GameLevel );
    m_LevelEditor.SetCamera( &m_GameCamera );
    
    //Init level editor
    m_LevelEditor.SetWindowSize( DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT );
    m_LevelEditor.SetPixelImage( GetTexture( "data/textures/pixel.png" ) );
    m_LevelEditor.NewTileMenu( TextureFactory(), "Textures", "data/textures/world/Ch1Tiles/" );
    
    InitAllShaders();
    m_pGraphicsContext->UseShader( 0 );
    
}

void CBNDGameContext::LoadLevel( std::string path ) {
 
    m_GameLevel.Load( path, TextureFactory() );
    m_GameLevel.UpdateSpatialTree( &m_Quadtree );
    
    
}

void CBNDGameContext::DrawLevel() {
    
    m_GameLevel.Draw( m_pDrawContext );
    
}

bool CBNDGameContext::GetBoolean( std::string name ) {
    
    return false;
    
}

void CBNDGameContext::CreateLightSpot( float x, float y, int r, int g, int b ) {
    
}

void CBNDGameContext::UpdateAllEntities() {
    
    
    boost::ptr_vector< CEntityObject > * entityObjs = &m_pEntityManager->GetEntityObjects();

    for( boost::ptr_vector< CEntityObject >::iterator i = entityObjs->begin();
        i != entityObjs->end(); i++ ) {
        
        if( ( *i ).GetContent()->IsActive() ) {
            
            ( *i ).GetContent()->Update();
        }
        
    }
    
}

void CBNDGameContext::Think() {
    
    if( m_bGameActive ) {
    
        m_Quadtree.Think();
        
        UpdateAllEntities();
        m_CollisionEngine.CheckForQuadTreeCollisions( &m_Quadtree, &m_CollisionCallback );
        
    }
    
    m_pEntityManager->RemoveAllDeletedEntities();
    m_pEntityManager->AddAllQueuedEntities();
    
    m_GameCamera.Think();
    
    
}


CWorldEntity * CBNDGameContext::CreateEntity_Enemy( float x, float y ) {
    
    CAI_IdiotTestEnemy * aic = new CAI_IdiotTestEnemy;
    aic->SetEntityContext( this );
    
    CAIEntity * pEntity = m_pEntityManager->CreateEntity< CAIEntity >( x, y );
    pEntity->AddTexture( GetTexture( "data/textures/enemy/idiot.png" ) );
    
    pEntity->SetMaterialToTexture( 0 );
    pEntity->SetClassTypeID( ENTTYPE::ENEMY );
    
    pEntity->SetCollisionBodyToBoxSprite();
    
    aic->SetTargetEntity( pEntity );
    pEntity->SetAIController( aic );
    
    m_Quadtree.AddEntity( pEntity );
    
    return pEntity;
    
}

CWorldEntity * CBNDGameContext::CreateEntity_Player( float x, float y ) {
    
    if( m_pPlayerEntity ) {
        
        m_pEntityManager->DeleteEntity( m_pPlayerEntity );
        m_pPlayerEntity = nullptr;
        
    }
    
    m_pPlayerEntity = m_pEntityManager->CreateEntity< CWorldEntity >( x, y );
    m_pPlayerEntity->AddTexture( GetTexture( "data/textures/player/player2.png" ) );
    m_pPlayerEntity->AddTexture( GetTexture( "data/textures/player/player2-sideright.png" ) );
    m_pPlayerEntity->AddTexture( GetTexture( "data/textures/player/player2-sideleft.png" ) );
    m_pPlayerEntity->AddTexture( GetTexture( "data/textures/player/player2-sideup.png" ) );
    
    m_pPlayerEntity->SetMaterialToTexture( 0 );
    m_pPlayerEntity->SetClassTypeID( ENTTYPE::PLAYER );
    
    m_pPlayerEntity->SetCollisionBodyToBoxSprite();
    
    m_Quadtree.AddEntity( m_pPlayerEntity );
    
    return m_pPlayerEntity;
    
}

CEnt_DamageBox * CBNDGameContext::CreateEntity_DamageBox( float x, float y, float width, float height, float damage, DMBSource source ) {
    
    
    CEnt_DamageBox * dmbEnt = m_pEntityManager->CreateEntity< CEnt_DamageBox >( x, y );
    
    CBoxCollisionBody * colBody = new CBoxCollisionBody;
    colBody->SetBox( 0.0f, 0.0f, width, height );
    
    dmbEnt->SetCollisionBody( colBody );
    dmbEnt->SetClassTypeID( ENTTYPE::DAMAGE );
    dmbEnt->SetDamageSource( source );
    
    m_Quadtree.AddEntity( dmbEnt );
    
    return dmbEnt;
    
}

void CBNDGameContext::HandleEntityContact( void * pEntA, int entTypeA, void * pEntB, int entTypeB, CCollisionInfo * pData ) {
    
    
    CWorldEntity * entA = static_cast< CWorldEntity * >( pEntA );
    /*
    m_pEntityManager->DeleteEntity( entA );
    */
    
    if( entTypeB & ENTTYPE::WALL ) {
        
        Vector3< float > offset = pData->minTransAxis * pData->minTransDist;
        entA->Displace( offset.GetX(), offset.GetY() );
        
        
    }
    
}

void CBNDGameContext::DrawLevelEditor() {
    
    m_LevelEditor.Draw( m_pDrawContext );
    
}

void CBNDGameContext::DrawQuadTree() {
    
    Vector2< float > pos = m_GameCamera.GetTranslate();
    
    m_pDrawContext->SetTexture( GetTexture( "data/textures/pixel.png" )->GetFrame( 0 ).GetTexture() );
    m_Quadtree.Draw( m_pGraphicsContext->GetDrawContext(), pos.GetX(), pos.GetY() );

}


