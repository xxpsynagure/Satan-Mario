#include "Render.h"
extern int moveDownFlag, level;

void platformCollision(Human &human, Platforms &platform)
{   
    // (human.bottomRight.x - human.topLeft.x) is the size of the human.
    bool collideX = ( human.bottomRight.x >= platform.bottomLeft.x+5 && platform.bottomRight.x-5 >= human.bottomLeft.x ); 

    bool collideY = ( human.bottomRight.y >= platform.bottomLeft.y && platform.bottomRight.y >= human.bottomLeft.y );

    bool collided = collideX && collideY;
    if(collided)
    {
        moveDownFlag = 0;
        // std::cout<<collided<<" - omg\t";
    }
    else
        moveDownFlag = 1;
}

void ladderCollision(Human &human , Ladder &ladder)
{
    bool collideX = ( human.bottomLeft.x >= ladder.bottomLeft.x && human.bottomRight.x <= ladder.bottomRight.x ); 
    // bool collideY = ( human.bottomLeft.y >= ladder.bottomLeft.y && ladder.bottomRight.y >= human.bottomLeft.y );
    // bool collided = collideX && collideY;
    if(collideX)
    {
        moveDownFlag = 1;
        level = 2;
    }
    else

    {
        moveDownFlag = 0;
        level = 1;
    }
}
