#include "utils/collision_box.hpp"
using namespace std;
using namespace vcl;
using namespace Collision;

/******* instantiate virtual functions for different types of collision box *****/

// rectangle
void rectangle::update_position(const vec3& translation){
    for(int i=0;i<4;i++)
        kp[i] += translation;
    c += translation;
}

void rectangle::update_position(const mat3& rotation){
    for(int i=0;i<4;i++)
        kp[i] = rotation*(kp[i]-c)+c;
}

bool rectangle::collide_border(float L, float W){
    for(int i=0;i<4;i++){
        float x = kp[i].x;
        float y = kp[i].y;
        if(x<-L || x>L || y<-W || y>W)
            return true;
    }
    return false;
}

bool rectangle::contains(const vec3& p){
    // detect if p is in A
    // by using cross products
    if(cross(p-kp[0], kp[1]-kp[2]).z * 
       cross(p-kp[1], kp[1]-kp[2]).z <=0 &&
       cross(p-kp[0], kp[0]-kp[1]).z * 
       cross(p-kp[3], kp[0]-kp[1]).z <=0)
       return true;

    return false;
}

vector<vec3>& rectangle::get_kp(){
    return kp;
}


