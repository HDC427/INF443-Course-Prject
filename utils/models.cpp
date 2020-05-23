#include "utils/models.hpp"

using namespace vcl;

mesh_drawable Floor, Wall1, Wall2, wheel;
GLuint Texture_wood, Texture_wheel;

void set_up_static_models(){
    float S = S_ROOM;
    Texture_wood = create_texture_gpu( image_load_png("textures/Wood.png") );
    Texture_wheel = create_texture_gpu( image_load_png("textures/Wheel.png"));

    Floor = mesh_primitive_quad({-S,-S/2,0}, {S,-S/2,0}, {S,S/2,0}, {-S,S/2,0});
    Floor.texture_id = Texture_wood;
    Wall1 = mesh_primitive_quad({-S,S/2,0}, {S,S/2,0}, {S,S/2,S}, {-S,S/2,S});
    Wall2 = mesh_primitive_quad({-S,-S/2,0}, {-S,S/2,0}, {-S,S/2,1}, {-S,-S/2,1});
}

void draw_static_models(std::map<std::string,GLuint>& shaders, scene_structure& scene, gui_structure& gui){
    draw(Floor, scene.camera, shaders["mesh"]);
    draw(Wall1, scene.camera, shaders["mesh"]);
    draw(Wall2, scene.camera, shaders["mesh"]);
}

void set_up_truck(Collision::sollid_heirarchy& Truck, GLuint shader){
    const float S = 0.1;

    mesh_drawable body = mesh_primitive_parallelepiped({-S,-S/2,0}, {2*S,0,0}, {0,S,0}, {0,0,S/2});
    body.uniform.color = {0,1,0};
    Truck.add(body, "body");

    mesh_drawable head = mesh_primitive_parallelepiped({0,-S/2,0}, {-S/2,0,0}, {0,S,0}, {0,0,S});
    head.uniform.color = {0,1,0};
    Truck.add(head, "head", "body", {-S,0,0});

    mesh nose_;
    nose_.position = { {0,-S/2,S/4},{0,-S/2,3*S/4},{-S,-S/2,S/2},{-S,-S/2,0},{-S/2,-S/2,0},{-S/2,-S/2,S/4},
                       {0, S/2,S/4},{0, S/2,3*S/4},{-S, S/2,S/2},{-S, S/2,0},{-S/2, S/2,0},{-S/2, S/2,S/4} };
    nose_.connectivity = { {0,1,2},{0,2,5},{2,4,5},{2,3,4},
                           {6,8,7},{6,11,8},{8,11,10},{8,10,9},
                           {1,8,2},{1,7,8},{2,9,3},{2,8,9}};
    mesh_drawable nose = nose_;
    nose.uniform.color = {0,1,0};
    Truck.add(nose, "nose", "head", {-S/2,0,0});                   

    mesh_drawable tire = mesh_primitive_cylinder(S/4, {0,0,0}, {0,S/10,0}, 20, 20);
    mesh_drawable wheel = mesh_primitive_disc(S/4, {0,0,0}, {0,-1,0});
    wheel.texture_id = Texture_wheel;
    tire.uniform.color = {0,0,0};

    Truck.add(tire, "back_left_tire", "body", {0,-S/2-S/10,0});
    Truck.add(wheel, "back_left_wheel", "back_left_tire");

    Truck.add(tire, "front_left_tire", "nose", {-S/4,-S/2-S/10,0});
    Truck.add(wheel, "front_left_wheel", "front_left_tire");

    tire.uniform.transform.rotation = {1,0,0, 0,-1,0, 0,0,1};
    Truck.add(tire, "back_right_tire", "body", {0,S/2+S/10,0});
    Truck.add(wheel, "back_right_wheel", "back_right_tire");

    Truck.add(tire, "front_right_tire", "nose", {-S/4,S/2+S/10,0});
    Truck.add(wheel, "front_right_wheel", "front_right_tire");

    Truck["body"].transform.translation = {0,0,S/4};
    Truck.update_local_to_global_coordinates();

    Truck.set_shader_for_all_elements(shader);
    
    // set up the collision box
    Truck.box = new Collision::rectangle({-2.5*S,-S/2}, {-2.5*S,S/2}, {S,-S/2}, {S,S/2});
}