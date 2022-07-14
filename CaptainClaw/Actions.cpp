extern int moveDownFlag;

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

