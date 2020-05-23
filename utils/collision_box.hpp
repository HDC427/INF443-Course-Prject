#pragma once

#include "vcl/vcl.hpp"
using namespace vcl;

namespace Collision
{

struct collision_box 
{
    virtual void upgrade_position(affine_transform transform) = 0;
};

struct rectangle: collision_box
{
    vec2 p[2][2];


/******** functions *********/
    rectangle(){};

    rectangle(vec2 p00, vec2 p01, vec2 p10, vec2 p11){
        p[0][0]=p00;
        p[0][1]=p01;
        p[1][0]=p10;
        p[1][1]=p11;
    }

    void upgrade_position(affine_transform transform);
};




struct sollid_heirarchy: hierarchy_mesh_drawable
{
    collision_box *box;
};

} // namespace Collision



