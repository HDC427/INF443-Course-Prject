#include "utils/shadow.hpp"

#include "vcl/opengl/opengl.hpp"


GLuint depthMapFBO;
GLuint depthMap;

void setup_depth_FBO(GLuint *depthMapFBO, GLuint *depthMap){
    /*! @brief set up depthMapFBO and attach depthMap to it
     *  later use `create_shadow_map` with deptheMapFBO and drawables to create depthMap
     *  then depthMap can be used as a texture 
     * */
    glGenFramebuffers(1, depthMapFBO); 
    glGenTextures(1, depthMap);
    glBindTexture(GL_TEXTURE_2D, *depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
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

void create_shadow_map(GLuint depthMapFBO, mesh_drawable &obj, camera_scene &light_source ,GLuint shader_shadow){
    /*! @brief draw obj from the point of view of light_source to create a shadow map
     *  @param depthMapFBO: set up with `setup_depth_FBO`
     *  @param light_source: take advantage of the similarity between light source and camara
     *  @param shader: shoulb be set to a shader for shadow drawing, like shaders["shadow"]
     */ 
    glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glClear(GL_DEPTH_BUFFER_BIT);
    draw(obj, light_source, shader_shadow);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
