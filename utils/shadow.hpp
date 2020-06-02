#pragma once

#include "vcl/wrapper/glfw/glfw.hpp"
#include "vcl/shape/shape.hpp"
#include "vcl/interaction/camera/camera.hpp"
#include <GLFW/glfw3.h>

#define SHADOW_WIDTH  1024
#define SHADOW_HEIGHT 1024 

void setup_depth_FBO(GLuint *depthMapFBO, GLuint *depthMap);