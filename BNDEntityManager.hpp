//
//  BNDEntityManager.hpp
//  Boundless
//
//  Created by Rick Chou on 10/3/15.
//  Copyright © 2015 Rick Chou. All rights reserved.
//

#ifndef EntityManager_hpp
#define EntityManager_hpp

#include "SoraIncludes.h"
#include "DrawContext.h"

class CBNDEntityManager : public CEntityManager {
    
public:
    
    void DrawAllEntitiesShadowBase( CDrawContext * , CTextureImage * );
    int DrawAllEntitiesAtDepthShadowBase( CDrawContext * , CTextureImage * , int );

};

#endif /* EntityManager_hpp */
