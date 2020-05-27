#pragma once

#include "vcl/vcl.hpp"
#include "collision_box.hpp"
#include "main/helper_scene/helper_scene.hpp"

using namespace vcl;

/*******static models********/
#define S_ROOM 1
extern mesh_drawable wall_0, wall_1;
void set_up_static_models(std::map<std::string,GLuint>& shaders);

void draw_static_models(std::map<std::string,GLuint>& shaders, scene_structure& scene, gui_structure& gui);

/*******mobile models********/
#define S_TRUCK 5

void set_up_truck(hierarchy_mesh_drawable& Truck, GLuint shader);