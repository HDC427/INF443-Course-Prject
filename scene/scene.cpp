
#include "scene.hpp"
#include "utils/models.hpp"
#include <iostream>
#include <random>

// Add vcl namespace within the current one - Allows to use function from vcl library without explicitely preceeding their name with vcl::
using namespace vcl;

/** This function is called before the beginning of the animation loop
    It is used to initialize all part-specific data */
void scene_model::setup_data(std::map<std::string,GLuint>& shaders, scene_structure& , gui_structure& gui)
{
    room_light.translation = {0,0,45};
    room_light.orientation = {1,0,0, 0,1,0, 0,0,-1};
    room_light.perspective = perspective_structure( 40*3.14f/180, 1, 0.01f, 500.0f);
    setup_depth_FBO(&room_FBO, &room_shadow, gui);
    
    set_up_static_models(shaders);
    
    set_up_truck(Truck, shaders["mesh"]);
}

/*! @brief set up depthMapFBO and attach depthMap to it
*  later use deptheMapFBO and drawables to create depthMap
*  then depthMap can be used as a texture id
* */
void scene_model::setup_depth_FBO(GLuint *depthMapFBO, GLuint *depthMap, gui_structure& gui){
    int width, height;
    glfwGetWindowSize(gui.window, &width, &height);

    glGenFramebuffers(1, depthMapFBO); 
    glGenTextures(1, depthMap);
    glBindTexture(GL_TEXTURE_2D, *depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // attach depth texture as FBO's depth buffer
    glBindFramebuffer(GL_FRAMEBUFFER, *depthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, *depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

/** This function is called at each frame of the animation loop.
    It is used to compute time-varying argument and perform data data drawing */
void scene_model::frame_draw(std::map<std::string,GLuint>& shaders, scene_structure& scene, gui_structure& gui)
{
    dt = timer.update();
    
    // glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
    create_shadow(Truck, room_FBO, room_light, shaders["shadow"]);
    // draw_scene(Truck, scene.camera, shaders["mesh"], room_light, room_shadow);
    draw_static_models(scene.camera, shaders["mesh"], room_light, room_shadow);

    Truck.update_local_to_global_coordinates();
    
    draw(Truck, scene.camera);

    uniform(shaders["mesh"], "room_light_on", gui.room_light);
    
    uniform(shaders["mesh"], "truck_light_on",gui.truck_light);
    uniform(shaders["mesh"], "truck_light", Truck["body"].transform.translation+truck_orientation*0.8+vec3(0,0,S_TRUCK/4));
    uniform(shaders["mesh"], "orientation", truck_orientation);
}




void scene_model::keyboard_input(scene_structure& scene, GLFWwindow* window, int key, int scancode, int action, int mods){
    
    truck_orientation = Truck["body"].transform.rotation*vec3(-2.5*S_TRUCK,0,0);
    const float v = dt*4;
    const float L = 50;
    const float W = 50;

    switch (key)
    {
    case GLFW_KEY_UP:
        Truck["body"].transform.translation += v*truck_orientation;
        Truck["body"].element.update_collision_box(v*truck_orientation);
        if(Truck["body"].element.collide_border(L, W) ||
           Truck["body"].element.collides_with(wall_0)||
           Truck["body"].element.collides_with(wall_1)){
            Truck["body"].transform.translation -= v*truck_orientation;
            Truck["body"].element.update_collision_box(-v*truck_orientation);
        }
        Truck["front_left_tire"].transform.rotation = {1,0,0, 0,1,0, 0,0,1}; 
        Truck["front_right_tire"].transform.rotation = {1,0,0, 0,1,0, 0,0,1}; 
        Truck["back_left_wheel"].transform.rotation = Truck["back_left_wheel"].transform.rotation*rotation_from_axis_angle_mat3({0,-1,0}, v); 
        Truck["front_left_wheel"].transform.rotation = Truck["front_left_wheel"].transform.rotation*rotation_from_axis_angle_mat3({0,-1,0}, v); 
        Truck["back_right_wheel"].transform.rotation = Truck["back_right_wheel"].transform.rotation*rotation_from_axis_angle_mat3({0,-1,0}, v); 
        Truck["front_right_wheel"].transform.rotation = Truck["front_right_wheel"].transform.rotation*rotation_from_axis_angle_mat3({0,-1,0}, v); 
        break;

    case GLFW_KEY_DOWN:
        Truck["body"].transform.translation -= v*truck_orientation; 
        Truck["body"].element.update_collision_box(-v*truck_orientation);
        if(Truck["body"].element.collide_border(L, W) ||
           Truck["body"].element.collides_with(wall_0)||
           Truck["body"].element.collides_with(wall_1)){
            Truck["body"].transform.translation += v*truck_orientation;
            Truck["body"].element.update_collision_box(v*truck_orientation);
        }
        Truck["front_left_tire"].transform.rotation = {1,0,0, 0,1,0, 0,0,1}; 
        Truck["front_right_tire"].transform.rotation = {1,0,0, 0,1,0, 0,0,1};
        Truck["back_left_wheel"].transform.rotation = Truck["back_left_wheel"].transform.rotation*rotation_from_axis_angle_mat3({0,-1,0}, -v); 
        Truck["front_left_wheel"].transform.rotation = Truck["front_left_wheel"].transform.rotation*rotation_from_axis_angle_mat3({0,-1,0}, -v); 
        Truck["back_right_wheel"].transform.rotation = Truck["back_right_wheel"].transform.rotation*rotation_from_axis_angle_mat3({0,-1,0}, -v); 
        Truck["front_right_wheel"].transform.rotation = Truck["front_right_wheel"].transform.rotation*rotation_from_axis_angle_mat3({0,-1,0}, -v);  
        break;

    case GLFW_KEY_LEFT:
        Truck["body"].transform.rotation = Truck["body"].transform.rotation*rotation_from_axis_angle_mat3({0,0,1},v); 
        Truck["body"].element.update_collision_box(rotation_from_axis_angle_mat3({0,0,1},v));
        if(Truck["body"].element.collide_border(L, W) ||
           Truck["body"].element.collides_with(wall_0)||
           Truck["body"].element.collides_with(wall_1)){
            Truck["body"].transform.rotation = Truck["body"].transform.rotation*rotation_from_axis_angle_mat3({0,0,1},-v); 
            Truck["body"].element.update_collision_box(rotation_from_axis_angle_mat3({0,0,1},-v));
        }
        Truck["front_left_tire"].transform.rotation = rotation_from_axis_angle_mat3({0,0,1}, 3.14/4); 
        Truck["front_right_tire"].transform.rotation = rotation_from_axis_angle_mat3({0,0,1}, 3.14/4); 
        Truck["front_left_wheel"].transform.rotation = Truck["front_left_wheel"].transform.rotation*rotation_from_axis_angle_mat3({0,-1,0}, v); 
        Truck["front_right_wheel"].transform.rotation = Truck["front_right_wheel"].transform.rotation*rotation_from_axis_angle_mat3({0,-1,0}, v); 
        break;

    case GLFW_KEY_RIGHT:
        Truck["body"].transform.rotation = Truck["body"].transform.rotation*rotation_from_axis_angle_mat3({0,0,1},-v); 
        Truck["body"].element.update_collision_box(rotation_from_axis_angle_mat3({0,0,1},-v));
        if(Truck["body"].element.collide_border(L, W) ||
           Truck["body"].element.collides_with(wall_0)||
           Truck["body"].element.collides_with(wall_1)){
            Truck["body"].transform.rotation = Truck["body"].transform.rotation*rotation_from_axis_angle_mat3({0,0,1},v); 
            Truck["body"].element.update_collision_box(rotation_from_axis_angle_mat3({0,0,1},v));
        }
        Truck["front_left_tire"].transform.rotation = rotation_from_axis_angle_mat3({0,0,1}, -3.14/4); 
        Truck["front_right_tire"].transform.rotation = rotation_from_axis_angle_mat3({0,0,1}, -3.14/4); 
        Truck["front_left_wheel"].transform.rotation = Truck["front_left_wheel"].transform.rotation*rotation_from_axis_angle_mat3({0,-1,0}, v); 
        Truck["front_right_wheel"].transform.rotation = Truck["front_right_wheel"].transform.rotation*rotation_from_axis_angle_mat3({0,-1,0}, v); 
        break;

    default:
        break;
    }
}

