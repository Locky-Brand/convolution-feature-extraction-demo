#ifndef GL_INC_H
#define GL_INC_H

#if defined GL330

#include "GLAD/glad330.h"
#include "GLFW/glfw3.h"
#include "api_tools.h"

#elif defined GL210

#include "GLAD/glad210.h"
#include <GLFW/glfw3.h>
#include "api_tools.h"

#elif defined SOFT

#else

#include "GLAD/glad.h"
#include <GLFW/glfw3.h>
#include "gl_api/api_tools.h"

#endif

#endif
