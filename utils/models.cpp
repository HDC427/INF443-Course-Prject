#include "utils/models.hpp"
#include <vector>

using namespace vcl;
using namespace std;
/******* Static models ********/
#pragma region static_models
vector<mesh_drawable*> static_models;

mesh_drawable surface0;
mesh_drawable surface1;
mesh_drawable surface2;
mesh_drawable surface3;
mesh_drawable surface4;
mesh_drawable surface5;
mesh_drawable wall_0;
mesh_drawable wall_1;
mesh_drawable table;
mesh_drawable window1;
mesh_drawable window2;

mesh_drawable computer1;
mesh_drawable computer2;
mesh_drawable computer3;
mesh_drawable computer4;
GLuint texture_id;
GLuint texture_id_table;
GLuint texture_id_window1;
GLuint texture_id_window2;
GLuint texture_id_computer;
/***************************/

void set_up_static_models(std::map<std::string,GLuint>& shaders){

    static_models.push_back(&surface0);
    static_models.push_back(&surface1);
    static_models.push_back(&surface2);
    static_models.push_back(&surface3);
    static_models.push_back(&surface4);
    static_models.push_back(&surface5);
    static_models.push_back(&wall_0);
    static_models.push_back(&wall_1);
    static_models.push_back(&table);
    static_models.push_back(&window1);
    static_models.push_back(&window2);
    static_models.push_back(&computer1);
    static_models.push_back(&computer2);
    static_models.push_back(&computer3);

    mesh quadrangle1;
    mesh quadrangle2;
    mesh quadrangle3;
    mesh quadrangle4;
    mesh quadrangle5;
    mesh wall_0_cpu;
    mesh wall_1_cpu;
    quadrangle1.position = { {-50,-50,50}, {50,-50,50}, {50,-50,0}, {-50,-50,0} };
    quadrangle2.position = { {50,-50,0}, {50,-50,50}, {50,50,50}, {50,50,0} };
    quadrangle3.position = { {-50,50,0}, {50,50,0}, {50,50,25}, {-50,50,25},{-20,50,25} ,{-15,50,25}, {-15,50,50} ,{-20,50,50} };
    quadrangle4.position = { {-50,-50,50}, {-50,-50,0}, {-50,50,0}, {-50,50,50} };
    quadrangle5.position = { {-50,-50,50}, {50,-50,50}, {50,50,50}, {-50,50,50} };
    wall_0_cpu.position  = { {-20,-50,0},{-15,-50,0},{-15,10,0},{-20,10,0},{-20,-50,50},{-15,-50,50},{-15,10,50},{-20,10,50} };
    wall_1_cpu.position  = { {-20,35,0},{-15,35,0},{-15,50,0},{-20,50,0},{-20,35,50},{-15,35,50},{-15,50,50},{-20,50,50} };

    quadrangle1.connectivity = { {0,1,2}, {0,2,3} };
    quadrangle2.connectivity = { {0,1,2}, {0,2,3} };
    quadrangle3.connectivity = { {0,1,2}, {0,2,3},{4,5,6} ,{4,6,7} };
    quadrangle4.connectivity = { {0,1,2}, {0,2,3} };
    quadrangle5.connectivity = { {0,1,2}, {0,2,3} };
    wall_0_cpu.connectivity  = { {1,2,6},{1,6,5},{2,3,7},{2,7,6},{3,0,4},{3,4,7} };
    wall_1_cpu.connectivity  = { {0,1,5},{0,5,4},{1,2,6},{1,6,5},{3,0,4},{3,4,7} };

    surface1 = mesh_drawable(quadrangle1);
    surface2 = mesh_drawable(quadrangle2);
    surface3 = mesh_drawable(quadrangle3);
    surface4 = mesh_drawable(quadrangle4);
    surface5 = mesh_drawable(quadrangle5);
    wall_0   = mesh_drawable(wall_0_cpu);
    wall_1   = mesh_drawable(wall_1_cpu);
    // color of the shape
    surface1.uniform.color = { 1.0f, 1.0f, 1.0f };
    surface2.uniform.color = { 1.0f, 1.0f, 1.0f };
    surface3.uniform.color = { 1.0f, 1.0f, 1.0f };
    surface4.uniform.color = { 1.0f, 1.0f, 1.0f };
    surface5.uniform.color = { 1.0f, 1.0f, 1.0f };
    wall_0.uniform.color   = { 1.0f, 1.0f, 1.0f };
    wall_1.uniform.color   = { 1.0f, 1.0f, 1.0f };
    // for collision detection
    wall_0.box = new Collision::rectangle({-20,-50,0},{-15,-50,0},{-15,10,0},{-20,10,0});
    wall_1.box = new Collision::rectangle({-20, 35,0},{-15, 35,0},{-15,50,0},{-20,50,0});

    // Floor
    mesh surface_cpu;
    surface_cpu.position = { {-50,-50,0}, { 50,-50,0}, { 50, 50,0}, {-50, 50,0} };
    surface_cpu.texture_uv = { {0,1}, {1,1}, {1,0}, {0,0} };
    surface_cpu.connectivity = { {0,1,2}, {0,2,3} };
    surface0 = surface_cpu;
    texture_id = create_texture_gpu(image_load_png("textures/Wood.png"));
    surface0.texture_id = texture_id;

    // Table
    mesh table_cpu;
    table_cpu.position = { {-15,37,23},{50,37,23},{50,50,23},{-15,50,23},{-15,37,25},{50,37,25},{50,50,25},{-15,50,25} };
    table_cpu.texture_uv = { {1,0}, {1,1}, {0,1}, {0,0},{0,0},{0,1},{1,1},{1,0} };
    table_cpu.connectivity = { {0,1,2},{0,2,3},{0,1,5},{0,5,4},{4,5,6},{4,6,7} };
    texture_id_table = create_texture_gpu(image_load_png("textures/table.png"));
    table = table_cpu;
    table.texture_id = texture_id_table;

    // Window1
    mesh window1_cpu;
    window1_cpu.position = { {-15,50,25},{50,50,25},{50,50,50},{-15,50,50} };
    window1_cpu.texture_uv = { {0,1}, {1,1}, {1,0}, {0,0} };
    window1_cpu.connectivity = { {0,1,2},{0,2,3} };
    texture_id_window1 = create_texture_gpu(image_load_png("textures/window_1.png"));
    window1 = window1_cpu;
    window1.texture_id = texture_id_window1;

    // Window2
    mesh window2_cpu;
    window2_cpu.position = { {-50,50,25},{-20,50,25},{-20,50,50},{-50,50,50} };
    window2_cpu.texture_uv = { {0,1}, {1,1}, {1,0}, {0,0} };
    window2_cpu.connectivity = { {0,1,2},{0,2,3} };
    texture_id_window2 = create_texture_gpu(image_load_png("textures/window_1.png"));
    window2 = window2_cpu;
    window2.texture_id = texture_id_window2;

    // Computer
    mesh computer1_cpu;
    mesh computer2_cpu;
    mesh computer3_cpu;
    mesh computer4_cpu;
    computer1_cpu.position = { {0,40,25},{5,40,25},{5,42,25},{0,42,25},{0,40,26},{5,40,26},{5,42,26},{0,42,26} };
    computer2_cpu.position = { {1.5,40.5,26},{3.5,40.5,26},{3.5,41.5,26},{1.5,41.5,26},{1.5,40.5,30},{3.5,40.5,30},{3.5,41.5,30},{1.5,41.5,30} };
    computer3_cpu.position = { {1.5,40,28},{3.5,40,28},{3.5,40.5,28},{1.5,40.5,28},{1.5,40,29},{3.5,40,29},{3.5,40.5,29},{1.5,40.5,29} };
    computer4_cpu.position = { {-5,40,27},{10,40,27},{10,40.5,27},{-5,40.5,27}, {-5,40,35},{10,40,35},{10,40.5,35},{-5,40.5,35} };
    computer4_cpu.texture_uv = { {0,1},{1,1},{0,0},{0,0},{0,0},{1,0},{0,0},{0,0} };
    computer1_cpu.connectivity = { {3,2,1},{3,1,0},{0,1,5},{0,5,4},{1,2,6},{1,6,5},{2,3,7},{2,7,6},{3,0,4},{3,4,7},{4,5,6},{4,6,7} };
    computer2_cpu.connectivity = { {3,2,1},{3,1,0},{0,1,5},{0,5,4},{1,2,6},{1,6,5},{2,3,7},{2,7,6},{3,0,4},{3,4,7},{4,5,6},{4,6,7} };
    computer3_cpu.connectivity = { {3,2,1},{3,1,0},{0,1,5},{0,5,4},{1,2,6},{1,6,5},{2,3,7},{2,7,6},{3,0,4},{3,4,7},{4,5,6},{4,6,7} };
    computer4_cpu.connectivity = { {3,2,1},{3,1,0},{0,1,5},{0,5,4},{1,2,6},{1,6,5},{2,3,7},{2,7,6},{3,0,4},{3,4,7},{4,5,6},{4,6,7} };
    computer1 = computer1_cpu;
    computer2 = computer2_cpu;
    computer3 = computer3_cpu;
    computer1.shader = shaders["mesh"];
    computer2.shader = shaders["mesh"];
    computer3.shader = shaders["mesh"];
    computer1.uniform.color = { 0.0,0.0,0.0 };
    computer2.uniform.color = { 0.0,0.0,0.0 };
    computer3.uniform.color = { 0.0,0.0,0.0 };
    computer4 = computer4_cpu;
    // texture_id_computer = create_texture_gpu(image_load_png("texures/computer.png"));
    // computer4.texture_id = texture_id_computer;
}

void create_shadow(hierarchy_mesh_drawable& Truck, GLuint depthMapFBO, camera_scene &light_source ,GLuint shader_shadow){
    /*! @brief draw obj from the point of view of light_source to create a shadow map
     *  @param depthMapFBO: set up with `setup_depth_FBO`
     *  @param light_source: take advantage of the similarity between light source and camara
     *  @param shader: shoulb be set to a shader for shadow drawing, like shaders["shadow"]
     */
    
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glClear(GL_DEPTH_BUFFER_BIT);
    for(int i=1;i<=10;i++){
        mesh_drawable *obj = static_models[i];
        // uniform(shader_shadow, "rotation", obj->uniform.transform.rotation);            opengl_debug();
        // uniform(shader_shadow, "translation", obj->uniform.transform.translation);      opengl_debug();
        // uniform(shader_shadow, "scaling", obj->uniform.transform.scaling);              opengl_debug();
        // uniform(shader_shadow, "scaling_axis", obj->uniform.transform.scaling_axis);    opengl_debug();

        // uniform(shader_shadow, "view", light_source.view_matrix());                     opengl_debug();
        // uniform(shader_shadow, "perspective", light_source.perspective.matrix());       opengl_debug();
        // draw(obj->data);
        draw(*obj, light_source, shader_shadow, 0);
    }
    // draw(surface0, light_source, shader_shadow, 0);
    draw(Truck, light_source, shader_shadow);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void draw_static_models(camera_scene& camera, GLuint shader, camera_scene& room_light, GLuint texture_room_light){
    glUseProgram(shader);
    glUniform1i(glGetUniformLocation(shader, "texture_room_shadow"), 1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture_room_light);
    for(auto obj: static_models){
        uniform(shader, "room_light_view", room_light.view_matrix());
        uniform(shader, "room_light_perspective", room_light.perspective.matrix());
        
        draw(*obj, camera, shader);
    }
}

#pragma endregion

void set_up_truck(hierarchy_mesh_drawable& Truck, GLuint shader){
    const float S = S_TRUCK;

    mesh_drawable body = mesh_primitive_parallelepiped({-S,-S/2,0}, {2*S,0,0}, {0,S,0}, {0,0,S/2});
    body.uniform.color = {0,1,0};
    body.box = new Collision::rectangle({-2.5*S,-S/2,0}, {-2.5*S,S/2,0}, {S,-S/2,0}, {S,S/2,0});
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
    GLuint Texture_wheel = create_texture_gpu(image_load_png("textures/Wheel.png"));
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
     
}

void draw_scene(hierarchy_mesh_drawable& Truck, camera_scene& camera, GLuint shader, camera_scene& room_light, GLuint texture_room_light){
    glUseProgram(shader);
    for(auto obj: static_models){
        uniform(shader, "room_light_view", room_light.view_matrix());
        uniform(shader, "room_light_perspective", room_light.perspective.matrix());
        glUniform1i(glGetUniformLocation(shader, "texture_room_shadow"), 1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture_room_light);
        draw(*obj, camera, shader);
    }

    Truck.update_local_to_global_coordinates();
    draw(Truck, camera, shader);
}

void create_truck_shadow(hierarchy_mesh_drawable& Truck ,GLuint depthMapFBO, camera_scene &light_source, GLuint shader_shadow){

}