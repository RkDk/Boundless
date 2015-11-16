//
//  BNDEntityManager.cpp
//  Boundless
//
//  Created by Rick Chou on 10/3/15.
//  Copyright © 2015 Rick Chou. All rights reserved.
//

#include "BNDEntityManager.hpp"

void CBNDEntityManager::DrawAllEntitiesShadowBase( CDrawContext * pDrawContext, CTextureImage * pixImage )
{
    
    for( int i = 0; i < m_vDrawList.size(); i++ )
    {
        
        DrawAllEntitiesAtDepthShadowBase( pDrawContext, pixImage, i );
        
        //    m_vDrawList[i].clear();
        
        
    }
    
}

int CBNDEntityManager::DrawAllEntitiesAtDepthShadowBase( CDrawContext * pDrawContext, CTextureImage * pixImage, int i ) {
    
    std::vector< CWorldEntity * >::iterator iter = m_vDrawList[i].begin();
    int c = 0;
    
    for( ; iter != m_vDrawList[i].end(); iter++ )
    {
        
        CWorldEntity * e = ( *iter );
        Vector3< float > pos = e->GetPos();
        Vector2< float > size = e->GetScaledSize();

        glActiveTexture( GL_TEXTURE1 );
        CSprite spr = e->GetSprite();
        spr.BindFrame( 0 );
        glActiveTexture( GL_TEXTURE0 );

        pDrawContext->DrawMaterial( *pixImage, pos.GetX(), pos.GetY(), size.GetX(), size.GetY(), 1.0f, 0.0f, 0.0f, 1.0f );
        
    }
    
    return c;
    
}
