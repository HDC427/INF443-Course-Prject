#pragma once

#include "vcl/vcl.hpp"
#include "main/helper_scene/helper_scene.hpp"

using namespace vcl;

/*******static models********/

void set_up_static_models();

void draw_static_models(std::map<std::string,GLuint>& shaders, scene_structure& scene, gui_structure& gui);