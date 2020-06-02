#pragma once

#include "vcl/vcl.hpp"
#include "collision_box.hpp"
#include "main/helper_scene/helper_scene.hpp"

using namespace vcl;

/*******static models********/
#define S_ROOM 1
#define SHADOW_WIDTH  1024
#define SHADOW_HEIGHT 1024
extern mesh_drawable wall_0, wall_1;
void set_up_static_models(std::map<std::string,GLuint>& shaders);
void create_shadow(hierarchy_mesh_drawable& Truck, GLuint depthMapFBO, camera_scene &light_source, GLuint shader_shadow);

void draw_static_models(camera_scene& camera, GLuint shader, camera_scene& room_light, GLuint texture_room_light);
void draw_scene(hierarchy_mesh_drawable& Truck, camera_scene& camera, GLuint shader, camera_scene& room_light, GLuint texture_room_light);
/*******mobile models********/
#define S_TRUCK 5

void set_up_truck(hierarchy_mesh_drawable& Truck, GLuint shader);
