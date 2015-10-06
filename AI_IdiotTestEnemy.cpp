//
//  AI_IdiotTestEnemy.cpp
//  Boundless
//
//  Created by Rick Chou on 10/4/15.
//  Copyright © 2015 Rick Chou. All rights reserved.
//

#include "AI_IdiotTestEnemy.hpp"

CAI_IdiotTestEnemy::CAI_IdiotTestEnemy() {
    
    m_NextChange = 0;
    
}

void CAI_IdiotTestEnemy::Think() {
    
    if( m_pTargetEntity ) {
        
        if( SDL_GetTicks() > m_NextChange ) {
            
            if( Util::RandomNumber( 1, 4 ) == 2 ) {
                
                m_Speed.Set( 0.0f, 0.0f );
                m_NextChange = SDL_GetTicks() + Util::RandomNumber( 3500, 6000 );
                
            } else {
                
                m_Speed.Set( Util::RandomNumber( -100, 100 ), Util::RandomNumber( -100, 100 ) );
                m_NextChange = SDL_GetTicks() + Util::RandomNumber( 1500, 4000 );
                
            }
            
            Vector3< float > pos = m_pTargetEntity->GetPos();
            
            if( pos.GetX() < 100.0f )
                m_Speed.SetX( fabs( m_Speed.GetX() ) );

            if( pos.GetX() > DEFAULT_SCREEN_WIDTH - 100 )
                m_Speed.SetX( -fabs( m_Speed.GetX() ) );

            if( pos.GetY() < 100.0f )
                m_Speed.SetY( fabs( m_Speed.GetY() ) );
            
            if( pos.GetY() > DEFAULT_SCREEN_HEIGHT - 100 )
                m_Speed.SetY( -fabs( m_Speed.GetY() ) );
            
        }
        
        m_pTargetEntity->Displace2( m_Speed.GetX(), m_Speed.GetY() );
        
    }
    
}