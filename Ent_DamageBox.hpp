//
//  Ent_DamageBox.hpp
//  Boundless
//
//  Created by Rick Chou on 10/5/15.
//  Copyright © 2015 Rick Chou. All rights reserved.
//

#ifndef Ent_DamageBox_hpp
#define Ent_DamageBox_hpp

#include "SoraIncludes.h"

enum class DMBSource { PLAYER = 0, ENEMY, NONE };

class CEnt_DamageBox : public CWorldEntity {
  
private:
    
    DMBSource m_DmgSource;
    
public:
    
    CEnt_DamageBox() : CWorldEntity(), m_DmgSource( DMBSource::NONE ) {
        
        
    
    }
    
    void SetDamageSource( DMBSource d ) {
        m_DmgSource = d;
    }
    
    DMBSource GetDamageSource() {
        return m_DmgSource;
    }
    
    virtual ~CEnt_DamageBox() { }
    
    void Draw() { }
    
};

#endif /* Ent_DamageBox_hpp */
