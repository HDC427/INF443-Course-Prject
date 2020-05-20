#include "utils/models.hpp"

using namespace vcl;

mesh_drawable Floor, Wall, wheel;
hierarchy_mesh_drawable Truck;
GLuint Texture_wood, Texture_wheel;

void set_up_static_models(){
    Texture_wood = create_texture_gpu( image_load_png("textures/Wood.png") );
    Texture_wheel = create_texture_gpu( image_load_png("textures/Wheel.png"));

    Floor = mesh_primitive_quad();
    Floor.texture_id = Texture_wood;
    Wall = mesh_primitive_quad({-0.5, 0.5, 0}, {0.5, 0.5, 0}, {0.5, 0.5, 1}, {-0.5, 0.5, 1});
}

void draw_static_models(std::map<std::string,GLuint>& shaders, scene_structure& scene, gui_structure& gui){
    draw(Floor, scene.camera, shaders["mesh"]);
    Wall.uniform.transform.rotation = {1,0,0, 0,1,0, 0,0,1};
    draw(Wall, scene.camera, shaders["mesh"]);
    Wall.uniform.transform.rotation = {0,-1,0, 1,0,0, 0,0,1};
    draw(Wall, scene.camera, shaders["mesh"]);
}

void set_up_truck(hierarchy_mesh_drawable& Truck, GLuint shader){
    const float S = 0.1;

    mesh_drawable body = mesh_primitive_parallelepiped({-S,-S/2,0}, {2*S,0,0}, {0,S,0}, {0,0,S/2});
    body.uniform.color = {0,1,0};
    Truck.add(body, "body");

    mesh_drawable tire = mesh_primitive_cylinder(S/5, {0,0,0}, {0,S/10,0}, 20, 20);
    mesh_drawable wheel = mesh_primitive_disc(S/5, {0,0,0}, {0,-1,0});
    wheel.texture_id = Texture_wheel;
    tire.uniform.color = {0,0,0};

    Truck.add(tire, "back_left_tire", "body", {0,-S/2-S/10,0});
    Truck.add(wheel, "back_left_wheel", "back_left_tire");

    tire.uniform.transform.rotation = {1,0,0, 0,-1,0, 0,0,1};
    Truck.add(tire, "back_right_tire", "body", {0,S/2+S/10,0});
    Truck.add(wheel, "back_right_wheel", "back_right_tire");

    Truck["body"].transform.translation = {0,0,S/5};
    Truck.update_local_to_global_coordinates();

    Truck.set_shader_for_all_elements(shader);
}