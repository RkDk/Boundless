#include "Game.hpp"

CGame::CGame() {
    
    
    Util::FixAppleRelativeDirectory();
    
    Log::ClearLog();
    Log::SetDebugLoggingEnabled( true );
    
    Log::Debug( "=======================APPLICATION INITIALIZING=======================" );
    
    /////////////////////////////////////////////////////
    ///////////Graphics context initialization///////////
    /////////////////////////////////////////////////////
    
    m_GraphicsContext.SetDrawContext( &m_DrawContext );
    
    m_GraphicsContext.CreateHandle( "Boundless", 0, 0, DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT, false );
    m_GraphicsContext.SetDrawMode( DrawMode::DRAW_MODE_2D );
    
    int shaderID = m_GraphicsContext.LoadShaderProgram( "data/shaders/basic_vertex.v", "data/shaders/basic_fragment.f" );
    int width, height;
    
    m_GraphicsContext.GetWindowSize( &width, &height );
    
    m_GraphicsContext.SetClearColor( .1f, .1f, .1f, 1.0f );
    
    SDL_ShowCursor( 0 );
    
    /////////////////////////////////////////////////////
    /////////////Draw context initialization/////////////
    /////////////////////////////////////////////////////
    
    m_DrawContext.UseShaderProgram( shaderID );
    m_DrawContext.Calculate2DProjectionMatrix( width, height );
    m_DrawContext.Bind2DVertexBuffer();
    
    Log::Debug( "Draw Context initialized" );
    
    /////////////////////////////////////////////////////
    ////////Font and sound context initialization////////
    /////////////////////////////////////////////////////
    
    m_FTContext.Init();
    m_FontFactory.SetFontLibrary( m_FTContext.GetLibrary() );
    
    Log::Debug( "Font Context initialized" );
    
    m_SoundContext.Init( 64 );
    m_SoundFactory.SetFMODSystem( m_SoundContext.GetSystem() );
    
    Log::Debug( "Sound Context initialized" );
    
    /////////////////////////////////////////////////////
    /////////////Game context initialization/////////////
    /////////////////////////////////////////////////////
    
    m_GameContext.SetGraphicsContext( &m_GraphicsContext );
    m_GameContext.SetDrawContext( &m_DrawContext );
    m_GameContext.SetEntityManager( &m_EntityManager );
    m_GameContext.SetSoundContext( &m_SoundContext );
    m_GameContext.SetSoundFactory( &m_SoundFactory );
    m_GameContext.SetTextureFactory( &m_TextureFactory );
    m_GameContext.SetFTContext( &m_FTContext );
    m_GameContext.SetFontFactory( &m_FontFactory );
    m_GameContext.Initialize();
    
    Log::Debug( "Game Context initialized" );
    
    /////////////////////////////////////////////////////
    ////////////////////Pre-Game Loop////////////////////
    /////////////////////////////////////////////////////
    
    CGameState * pGameState = new CGameState;
    pGameState->SetGameContext( &m_GameContext );
  
    m_StateMachine.AddState( "GAME", ( CStateBase * )pGameState );
   
    m_StateMachine.SetActiveState( "GAME" );
    
    /////////////////////////////////////////////////////
    //////////////////////Game Loop//////////////////////
    /////////////////////////////////////////////////////
    
    Log::Debug( "State Machine initialized\nStarting main loop" );
    
    while( true )
    {
        
        m_GameContext.BeginFrame();
        
        if( !m_StateMachine.RunState() )
            break;
        
        m_GameContext.EndFrame();
        
    }
    
    Log::Debug( "Exiting main loop" );

}

CGame::~CGame() {

}
