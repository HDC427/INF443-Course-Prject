#pragma once

#include "vcl/math/math.hpp"
using namespace vcl;

namespace Collision
{

struct collision_box 
{
    virtual void update_position(const vec3& translation) = 0;
    virtual void update_position(const mat3& rotation) = 0;

    virtual bool collide_border(float L, float W) = 0;

    virtual vec3 get_p() = 0;
};

struct rectangle: collision_box
{
    vec3 c = {0,0,0};
    vec3 p[2][2];

    /******** functions *********/
    rectangle(){};

    rectangle(vec3 p00, vec3 p01, vec3 p10, vec3 p11){
        p[0][0]=p00;
        p[0][1]=p01;
        p[1][0]=p10;
        p[1][1]=p11;
    }

    void update_position(const vec3& translation);
    void update_position(const mat3& rotation);

    bool collide_border(float L, float W);

    vec3 get_p();
};


// struct sollid_mesh: mesh_drawable
// {
//     // extend mesh_drawable to associate a collision box    
//     collision_box *box;

//     /******** functions *********/    
//     sollid_mesh(){};
//     sollid_mesh(const mesh& mesh_cpu): mesh_drawable(mesh_cpu){};

//     void update_collision_box(const vec3& transalation);
//     void update_collision_box(const mat3& rotation);

//     bool collide_border(GLfloat L, GLfloat W);
// };


} // namespace Collision



