#include "gfx3D_330.h"

gfx3D init(const char* name, unsigned int w, unsigned int h, vec4 ccol, const char** btex, unsigned int nbtex, const char** bassets, unsigned int nbassets) {

  gfx3D gfx;
  gfx.scr_width = w;
  gfx.scr_height = h;
  gfx.r = ccol.x;
  gfx.g = ccol.y;
  gfx.b = ccol.z;
  gfx.a = ccol.w;

  gfx.texture_counter = 0;

  // glfw: initialize and configure
  // ------------------------------
  glfwInit();

  // glfw window creation
  // --------------------
  GLFWwindow* window = glfwCreateWindow(gfx.scr_width, gfx.scr_height, name, NULL, NULL);
  if (window == NULL)
  {
    printf("%s\n", "Failed to create GLFW window");
    glfwTerminate();
    while(1);
  }
  glfwMakeContextCurrent(window);

  // glad: load all OpenGL function pointers
  // ---------------------------------------
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    printf("%s\n", "Failed to initialize GLAD");
    while(1);
  }

  glEnable(GL_BLEND);
  glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
  glfwSwapInterval(0);

  gfx.window = window;

  gfx.main_frame = create_FBO(w, h, &gfx.texture_counter);

  // create main frame buffer and texture
  float verts[] = {
    -1.0f, -1.0f, 0.0f, 0.0f,
     1.0f, -1.0f, 1.0f, 0.0f,
     1.0f,  1.0f, 1.0f, 1.0f,
    -1.0f,  1.0f, 0.0f, 1.0f
  };
  unsigned int inds1[] = {
    0, 1, 2, 2, 3, 0
  };

  glGenBuffers(1, &gfx.main_VBO);
  glGenVertexArrays(1, &gfx.main_VAO);

  glBindVertexArray(gfx.main_VAO);
  glBindBuffer(GL_ARRAY_BUFFER, gfx.main_VBO);
  glBufferData(GL_ARRAY_BUFFER, 16 * sizeof(float), verts, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(0 * sizeof(float)));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  glGenBuffers(1, &gfx.main_IBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gfx.main_IBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), inds1, GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  {
    const char* main_vertex = "#version 330 core\n"
                         "layout(location = 0) in vec2 aPos;\n"
                         "layout(location = 1) in vec2 aTex;\n"
                         "out vec2 oTex;\n"
                         "void main(){\n"
                         "oTex = aTex;\n"
                         "gl_Position = vec4(aPos, 0.0f, 1.0f);\n"
                         "};\n\0";
    const char* main_fragment = "#version 330 core\n"
                         "out vec4 aColor;\n"
                         "in vec2 oTex;\n"
                         "uniform sampler2D main_frame;\n"
                         "void main(){\n"
                         "aColor = texture(main_frame, oTex);\n"
                         "};\n\0";

    gfx.main_shader = create_shader(main_vertex, main_fragment);

    int temp = 0;
    set_uniform(gfx.main_shader, "main_frame", UI, (void*)(&temp));
  }


  // load assets
  {
    texture_unit* u1 = (texture_unit*)malloc(sizeof(texture_unit)); 
    int unit_counter = 1;
    int tex_unit_i = 0;
    u1[0] = create_texture_unit(&gfx.texture_counter);
    gfx.textures = (Texture*)malloc(nbtex * sizeof(Texture));
    for (unsigned int i = 0; i < nbtex; ++i, ++tex_unit_i) {
      int success = load_texture_into_unit(&u1[unit_counter - 1], btex[i], &gfx.texture_counter);
      if (success) {
        gfx.textures[i].index = u1[unit_counter - 1].tex[tex_unit_i].index; 
        gfx.textures[i].ID = u1[unit_counter - 1].tex[tex_unit_i].ID;
        gfx.textures[i].sizes = u1[unit_counter - 1].tex[tex_unit_i].sizes;
        gfx.textures[i].sub_divisions = u1[unit_counter - 1].tex[tex_unit_i].sub_divisions;
        gfx.textures[i].sub_offset = u1[unit_counter - 1].tex[tex_unit_i].sub_offset;
      }
      else {
        u1 = (texture_unit*)realloc(u1, (unit_counter+1) * sizeof(texture_unit));
        u1[unit_counter] = create_texture_unit(&gfx.texture_counter);
        success = load_texture_into_unit(&u1[unit_counter], btex[i], &gfx.texture_counter);
        tex_unit_i = 0;
        gfx.textures[i].index = u1[unit_counter].tex[tex_unit_i].index; 
        gfx.textures[i].ID = u1[unit_counter].tex[tex_unit_i].ID;
        gfx.textures[i].sizes = u1[unit_counter].tex[tex_unit_i].sizes;
        gfx.textures[i].sub_divisions = u1[unit_counter].tex[tex_unit_i].sub_divisions;
        gfx.textures[i].sub_offset = u1[unit_counter].tex[tex_unit_i].sub_offset;
        ++unit_counter;
      }
    }

    for (int i = 0; i < unit_counter; ++i) {
      destroy_texture_unit(u1[i]);
    }
    free(u1);
  }
  
/* debug print loaded textures
  for (int i = 0; i < nbtex; ++i) {
    printf("texture: %s : %d, %d, (%d, %d), (%d, %d), (%f, %f)\n", btex[i], gfx.textures[i].index, gfx.textures[i].ID, gfx.textures[i].sizes.x, gfx.textures[i].sizes.y, gfx.textures[i].sub_divisions.x, gfx.textures[i].sub_divisions.y, gfx.textures[i].sub_offset.x, gfx.textures[i].sub_offset.y);
  }
*/

/* simple textures
  gfx.textures = (Texture*)malloc(nbtex * sizeof(Texture));
  for (int i = 0; i < nbtex; ++i) {
    gfx.textures[i] = load_texture(btex[i], &gfx.texture_counter, cmp_file_ext(btex[i], "png\0"));
  }
*/

  gfx.assets = (asset3D*)malloc(nbassets * sizeof(asset3D));
  for (unsigned int i = 0; i < nbassets; ++i) {
    gfx.assets[i] = load_obj_file(bassets[i]);
  }

  gfx.asset_counter = nbassets;

  // load default assets
  gfx.shapes[0] = load_obj_file("./assets/default/cube.obj\0");
  gfx.shapes[1] = load_obj_file("./assets/default/sphere.obj\0");
  gfx.shapes[2] = load_obj_file("./assets/default/capsule.obj\0");

  return gfx;
}

void end(gfx3D* gfx) {
  free(gfx->textures);

  for (unsigned int i = 0; i < gfx->asset_counter; ++i) {
    delete_asset3D(gfx->assets[i]);
  }

  free(gfx->assets);

  glfwTerminate();
}

void begin_frame(gfx3D gfx) {
  //glBindFramebuffer(GL_FRAMEBUFFER, gfx.main_frame.ID);
  //glClearColor(gfx.r, gfx.g, gfx.b, gfx.a);
  //glEnable(GL_DEPTH_TEST);
  //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void end_frame(gfx3D gfx) {
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  //glEnable(GL_FRAMEBUFFER_SRGB);
  glClearColor(gfx.r, gfx.g, gfx.b, gfx.a);
  glDisable(GL_DEPTH_TEST);
  glClear(GL_COLOR_BUFFER_BIT);

  glBindVertexArray(gfx.main_VAO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gfx.main_IBO);
  glUseProgram(gfx.main_shader);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
  glBindVertexArray(0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glUseProgram(0);

  glfwPollEvents(); // glfwWaitEvents ?
  glfwSwapBuffers(gfx.window);
}

void end_frame_post_process(gfx3D gfx, unsigned int post_process_shader) {
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  //glEnable(GL_FRAMEBUFFER_SRGB);
  glClearColor(gfx.r, gfx.g, gfx.b, gfx.a);
  glDisable(GL_DEPTH_TEST);
  glClear(GL_COLOR_BUFFER_BIT);

  glBindVertexArray(gfx.main_VAO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gfx.main_IBO);
  glUseProgram(post_process_shader);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
  glBindVertexArray(0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glUseProgram(0);

  glfwPollEvents(); // glfwWaitEvents ?
  glfwSwapBuffers(gfx.window);
}

int close_flag(gfx3D gfx, int (*user_events)(gfx3D)) {
  if (user_events != NULL) {
    return user_events(gfx) || glfwWindowShouldClose(gfx.window);
  }
  return glfwWindowShouldClose(gfx.window);
}

void use_anti_aliasing(gfx3D* g) {
  //g->fxaa_shader = create_shader_file("./engine/core/shaders/FXAA_vertex.glsl", "./engine/core/shaders/FXAA_fragment.glsl");
}
