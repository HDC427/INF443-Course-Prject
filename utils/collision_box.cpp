#include "utils/collision_box.hpp"
using namespace vcl;
using namespace Collision;

/******* instantiate virtual functions for different types of collision box *****/

// rectangle
void rectangle::update_position(const vec3& translation){
    p[0][0] += translation;
    p[0][1] += translation;
    p[1][0] += translation;
    p[1][1] += translation;
    c += translation;
}

void rectangle::update_position(const mat3& rotation){
    p[0][0] = rotation*(p[0][0]-c)+c;
    p[0][1] = rotation*(p[0][1]-c)+c;
    p[1][0] = rotation*(p[1][0]-c)+c;
    p[1][1] = rotation*(p[1][1]-c)+c;
}

bool rectangle::collide_border(float L, float W){
    for(int i=0;i<2;i++)
        for(int j=0;j<2;j++){
            float x = p[i][j].x;
            float y = p[i][j].y;
            if(x<-L || x>L || y<-W || y>W)
                return true;
        }
    return false;
}

vec3 rectangle::get_p(){
    return p[0][0];
}