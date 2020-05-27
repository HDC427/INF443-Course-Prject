#pragma once

#include <vector>
#include "vcl/math/math.hpp"
using namespace std;
using namespace vcl;

namespace Collision
{

struct collision_box 
{
    vec3 c = {0,0,0};
    vector<vec3> kp;

    virtual void update_position(const vec3& translation) = 0;
    virtual void update_position(const mat3& rotation) = 0;

    virtual bool collide_border(float L, float W) = 0;
    virtual bool contains(const vec3& p) = 0;

    virtual vector<vec3>& get_kp() = 0;
};

struct rectangle: collision_box
{
    
    /******** functions *********/
    rectangle(){};

    rectangle(vec3 p00, vec3 p01, vec3 p10, vec3 p11){
        kp = vector<vec3>(4);
        kp[0]=p00;
        kp[1]=p01;
        kp[2]=p10;
        kp[3]=p11;
    }

    void update_position(const vec3& translation);
    void update_position(const mat3& rotation);

    bool collide_border(float L, float W);
    bool contains(const vec3& p);

    vector<vec3>& get_kp();
};

bool detect(const vec3 &p, const rectangle *A);
bool detect(const rectangle *A, const rectangle *B);

} // namespace Collision



