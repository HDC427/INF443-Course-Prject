#include "utils/models.hpp"

using namespace vcl;

mesh_drawable Floor, Wall, Ceiling;
GLuint Texture_wood;

void set_up_static_models(){
    Texture_wood = create_texture_gpu( image_load_png("assets/Wood.png") );
    mesh Floor_cpu = mesh_primitive_quad();
    Floor = mesh(Floor_cpu);
    Floor.texture_id = Texture_wood;
    Wall = mesh(mesh_primitive_quad({-0.5, 0.5, 0}, {0.5, 0.5, 0}, {0.5, 0.5, 1}, {-0.5, 0.5, 1}));
}

void draw_static_models(std::map<std::string,GLuint>& shaders, scene_structure& scene, gui_structure& gui){
    draw(Floor, scene.camera, shaders["mesh"]);
    Wall.uniform.transform.rotation = {1,0,0, 0,1,0, 0,0,1};
    draw(Wall, scene.camera, shaders["mesh"]);
    Wall.uniform.transform.rotation = {0,-1,0, 1,0,0, 0,0,1};
    draw(Wall, scene.camera, shaders["mesh"]);
}