#include "mesh_drawable.hpp"

#include "vcl/opengl/opengl.hpp"

namespace vcl
{


mesh_drawable::mesh_drawable()
    :data(),uniform(),shader(0),texture_id(0)
{}

mesh_drawable::mesh_drawable(const mesh& mesh_arg, GLuint shader_arg, GLuint texture_id_arg)
    :data(mesh_arg),uniform(),shader(shader_arg),texture_id(texture_id_arg)
{}

void mesh_drawable::clear()
{
    data.clear();
}

void mesh_drawable::update_position(const vcl::buffer<vec3>& new_position)
{
    data.update_position(new_position);
}

void mesh_drawable::update_normal(const vcl::buffer<vec3>& new_normal)
{
    data.update_normal(new_normal);
}


void draw(const mesh_drawable& drawable, const camera_scene& camera)
{
    draw(drawable, camera, drawable.shader, drawable.texture_id);
}

void draw(const mesh_drawable& drawable, const camera_scene& camera, GLuint shader)
{
    draw(drawable, camera, shader, drawable.texture_id);
}


void draw(const mesh_drawable& drawable, const camera_scene& camera, GLuint shader, GLuint texture_id)
{
    // If shader is, skip display
    if(shader==0)
        return ;

    // Check that the shader is a valid one
    if( glIsProgram(shader)==GL_FALSE ) {
        std::cout<<"No valid shader set to display mesh: skip display"<<std::endl;
        return;
    }

    // Switch shader program only if necessary
    GLint current_shader = 0;
    glGetIntegerv(GL_CURRENT_PROGRAM, &current_shader); opengl_debug();
    if(shader!=GLuint(current_shader))
        glUseProgram(shader); opengl_debug();

    // Bind texture only if id != 0
    if(texture_id!=0) {
        assert(glIsTexture(texture_id));
        glBindTexture(GL_TEXTURE_2D, texture_id);  opengl_debug();
    }

    // Send all uniform values to the shader
    uniform(shader, "rotation", drawable.uniform.transform.rotation);            opengl_debug();
    uniform(shader, "translation", drawable.uniform.transform.translation);      opengl_debug();
    uniform(shader, "color", drawable.uniform.color);                            opengl_debug();
    uniform(shader, "color_alpha", drawable.uniform.color_alpha);                opengl_debug();
    uniform(shader, "scaling", drawable.uniform.transform.scaling);              opengl_debug();
    uniform(shader, "scaling_axis", drawable.uniform.transform.scaling_axis);    opengl_debug();

    uniform(shader,"perspective",camera.perspective.matrix());         opengl_debug();
    uniform(shader,"view",camera.view_matrix());                       opengl_debug();
    uniform(shader,"camera_position",camera.camera_position());        opengl_debug();

    uniform(shader, "ambiant", drawable.uniform.shading.ambiant);      opengl_debug();
    uniform(shader, "diffuse", drawable.uniform.shading.diffuse);      opengl_debug();
    uniform(shader, "specular", drawable.uniform.shading.specular);    opengl_debug();
    uniform(shader, "specular_exponent", drawable.uniform.shading.specular_exponent); opengl_debug();

    vcl::draw(drawable.data); opengl_debug();

    if(texture_id!=0){
        image_raw white{1,1,image_color_type::rgba,{255,255,255,255}};
        GLuint texture_white = create_texture_gpu(white);
        glBindTexture(GL_TEXTURE_2D, texture_white);
    }
}


void mesh_drawable::update_collision_box(const vec3& translation){
    box->update_position(translation);
}

void mesh_drawable::update_collision_box(const mat3& rotation){
    box->update_position(rotation);
}

bool mesh_drawable::collide_border(GLfloat L, GLfloat W){
    return box->collide_border(L, W);
}

bool mesh_drawable::collides_with(const mesh_drawable& obj){
    vector<vec3> A_kp = box->get_kp();
    vector<vec3> B_kp = obj.box->get_kp();

    for(auto p: A_kp)
        if(obj.box->contains(p)) {
            return true;
        }

    for(auto p: B_kp)
        if(box->contains(p)) {
            return true;
        }
    return false;
}

}
