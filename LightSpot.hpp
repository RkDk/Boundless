//
//  LightSpot.hpp
//  Boundless
//
//  Created by Rick Chou on 11/8/15.
//  Copyright © 2015 Rick Chou. All rights reserved.
//

#ifndef LightSpot_hpp
#define LightSpot_hpp

#include "SoraIncludes.h"

class CLightSpot {
  
private:
    
    Vector2< float > m_WorldPos;
    Vector4< float > m_Color;
    
public:
    
    CLightSpot() { }
    
    void SetWorldPos( float x, float y ) {
        m_WorldPos.Set( x, y );
    }
    
    void SetColor( float r, float g, float b, float a ) {
        m_Color.Set( r, g, b, a );
    }
    
    const Vector2< float > & GetWorldPos() {
        return m_WorldPos;
    }
    
    const Vector4< float > GetColor() {
        return m_Color;
    }
    
};

#endif /* LightSpot_hpp */
