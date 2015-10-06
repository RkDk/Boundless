//
//  AI_IdiotTestEnemy.hpp
//  Boundless
//
//  Created by Rick Chou on 10/4/15.
//  Copyright © 2015 Rick Chou. All rights reserved.
//

#ifndef AI_IdiotTestEnemy_hpp
#define AI_IdiotTestEnemy_hpp

#include "SoraIncludes.h"
#include "LuaContext.hpp"
#include "Define.hpp"

class CAI_IdiotTestEnemy : public CTemplateAIController< CLuaContext > {
    
private:
    
    long int m_NextChange;
    Vector2< float > m_Speed;
    
public:
    
    void Think();
    
    CAI_IdiotTestEnemy();
    virtual ~CAI_IdiotTestEnemy() { }

};


#endif /* AI_IdiotTestEnemy_hpp */
