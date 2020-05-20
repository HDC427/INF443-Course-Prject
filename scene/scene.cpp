
#include "scene.hpp"
#include "utils/models.hpp"

#include <random>

// Add vcl namespace within the current one - Allows to use function from vcl library without explicitely preceeding their name with vcl::
using namespace vcl;


/** This function is called before the beginning of the animation loop
    It is used to initialize all part-specific data */
void scene_model::setup_data(std::map<std::string,GLuint>& shaders, scene_structure& , gui_structure& )
{
    set_up_static_models();
    set_up_truck(Truck, shaders["mesh"]);
}


/** This function is called at each frame of the animation loop.
    It is used to compute time-varying argument and perform data data drawing */
void scene_model::frame_draw(std::map<std::string,GLuint>& shaders, scene_structure& scene, gui_structure& gui)
{
    dt = timer.update();
    draw_static_models(shaders, scene, gui);

    Truck.update_local_to_global_coordinates();
    draw(Truck, scene.camera);
}


void scene_model::keyboard_input(scene_structure& scene, GLFWwindow* window, int key, int scancode, int action, int mods){
    
    vec3 orientation = Truck["body"].transform.rotation*vec3(-1,0,0);
    const float v = dt*3;

    switch (key)
    {
    case GLFW_KEY_UP:
        Truck["body"].transform.translation += 0.1*v*orientation;
        Truck["front_left_tire"].transform.rotation = {1,0,0, 0,1,0, 0,0,1}; 
        Truck["front_right_tire"].transform.rotation = {1,0,0, 0,1,0, 0,0,1}; 
        Truck["back_left_wheel"].transform.rotation = Truck["back_left_wheel"].transform.rotation*rotation_from_axis_angle_mat3({0,-1,0}, v); 
        Truck["front_left_wheel"].transform.rotation = Truck["front_left_wheel"].transform.rotation*rotation_from_axis_angle_mat3({0,-1,0}, v); 
        Truck["back_right_wheel"].transform.rotation = Truck["back_right_wheel"].transform.rotation*rotation_from_axis_angle_mat3({0,-1,0}, v); 
        Truck["front_right_wheel"].transform.rotation = Truck["front_right_wheel"].transform.rotation*rotation_from_axis_angle_mat3({0,-1,0}, v); 
        break;

    case GLFW_KEY_DOWN:
        Truck["body"].transform.translation -= 0.1*v*orientation; 
        Truck["front_left_tire"].transform.rotation = {1,0,0, 0,1,0, 0,0,1}; 
        Truck["front_right_tire"].transform.rotation = {1,0,0, 0,1,0, 0,0,1};
        Truck["back_left_wheel"].transform.rotation = Truck["back_left_wheel"].transform.rotation*rotation_from_axis_angle_mat3({0,-1,0}, -v); 
        Truck["front_left_wheel"].transform.rotation = Truck["front_left_wheel"].transform.rotation*rotation_from_axis_angle_mat3({0,-1,0}, -v); 
        Truck["back_right_wheel"].transform.rotation = Truck["back_right_wheel"].transform.rotation*rotation_from_axis_angle_mat3({0,-1,0}, -v); 
        Truck["front_right_wheel"].transform.rotation = Truck["front_right_wheel"].transform.rotation*rotation_from_axis_angle_mat3({0,-1,0}, -v);  
        break;

    case GLFW_KEY_LEFT:
        Truck["body"].transform.rotation = Truck["body"].transform.rotation*rotation_from_axis_angle_mat3({0,0,1},v); 
        Truck["front_left_tire"].transform.rotation = rotation_from_axis_angle_mat3({0,0,1}, 3.14/4); 
        Truck["front_right_tire"].transform.rotation = rotation_from_axis_angle_mat3({0,0,1}, 3.14/4); 
        Truck["front_left_wheel"].transform.rotation = Truck["front_left_wheel"].transform.rotation*rotation_from_axis_angle_mat3({0,-1,0}, v); 
        Truck["front_right_wheel"].transform.rotation = Truck["front_right_wheel"].transform.rotation*rotation_from_axis_angle_mat3({0,-1,0}, v); 
        break;

    case GLFW_KEY_RIGHT:
        Truck["body"].transform.rotation = Truck["body"].transform.rotation*rotation_from_axis_angle_mat3({0,0,1},-v); 
        Truck["front_left_tire"].transform.rotation = rotation_from_axis_angle_mat3({0,0,1}, -3.14/4); 
        Truck["front_right_tire"].transform.rotation = rotation_from_axis_angle_mat3({0,0,1}, -3.14/4); 
        Truck["front_left_wheel"].transform.rotation = Truck["front_left_wheel"].transform.rotation*rotation_from_axis_angle_mat3({0,-1,0}, v); 
        Truck["front_right_wheel"].transform.rotation = Truck["front_right_wheel"].transform.rotation*rotation_from_axis_angle_mat3({0,-1,0}, v); 
        break;

    default:
        break;
    }
}

