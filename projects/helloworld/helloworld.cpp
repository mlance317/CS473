#include <glad/glad.h> //GLAD must be BEFORE GLFW
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>
#include <vector>

//Constants
#define WIN_WIDTH 500
#define WIN_HEIGHT 500

/* Why can't it find what we need?  
 *
 * Need to configure your environment so it knows where these things are!
 * 1) c_cpp_properties:  
 *     a) Ctrl+Shift+P to open the command palette
 *     b) choose/type C/C++: Edit Configuration (JSON) and add the mingw include path to the includePath variable
 * 2) Still can't build!  Need to change tasks.json as well!
 *     a) Add the include path to the tasks.json args variable (for the compiler call) using the -I option.
 *     b) BUT we need the libraries too!  Use the -l option to add opengl32 and glfw3 libraries
 */
//Check intellisense to make sure that glfwInit is defined and you're good--ish
//you also need to add the include path to the tasks.json file so those headers are included.


glm::vec4 clearColor(0.0,0.0,0.0,1.0);
std::vector<bool> flags {false,false,false,false};

//function prototype for callback when user resizes the window.
void framebuffer_size_callback(GLFWwindow* win, int width, int height);

void PrintColor() {
  std::cout << "Color (" << clearColor.r << "," << clearColor.g;
  std::cout << "," << clearColor.b<<")"<<std::endl;
}

//for processing all input
void processInput (GLFWwindow *win) {
  if (glfwGetKey(win,GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(win,true);
  }

  //Collect key info (which key is pressed)
  int currFlag = 0;
  //std::cout << glfwGetKey(win, GLFW_KEY_R);
  
  //
  if ((!flags[0]) && (glfwGetKey(win,GLFW_KEY_R) == GLFW_PRESS)) {
    flags[0] = true;

    clearColor.r += 0.1;

    if (clearColor.r > 1.0){ //reset if value is greater than 1
      clearColor.r = 0;
    }

     
    PrintColor();
  }
  if (glfwGetKey(win, GLFW_KEY_R) == GLFW_RELEASE){
    flags[0] = false;
  }
}



int main() {
  double rgba[]  = {0.7,0.7,0.0,1.0};
  //Initialize GLFW and define the version and profile for OpenGL
  glfwInit();  //initialize GLFW
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3); //Set OpenGL version to 3.3
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //Use Core Profile (vs Immediate)

  //Create a window object (width, height, title, montitor to use for full screen, a window object sharing context if any)
  GLFWwindow* window = glfwCreateWindow(WIN_WIDTH,WIN_HEIGHT,"LearnOpenGL",NULL,NULL);
  //Standard set up a check to make sure that the window was created...show an error message otherwise.
  if (window == NULL) {
    std::cout << "Failed to create GLFW Window"<<std::endl;
    glfwTerminate(); 
    return -1; //return this value indicating something went wrong
  }

  glfwMakeContextCurrent(window); //window created so we can make it the current context
  
  //Get the function pointers for OpenGL
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }


  //define window dimensions
  //first two args set location to the lower left corner of the window
  //third is width
  //fourth is height
  glViewport(0,0,WIN_WIDTH,WIN_HEIGHT);
  //note that if the user resizes the window, the viewport must change too!
  glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);

 
  //without a while loop...the program will run but just create a window and then terminate.
  //glfwWindowShouldClose checks if GLFW has been instructed to close...if so it returns true (exiting the loop).
  while(!glfwWindowShouldClose(window)) {
    glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
    glClear(GL_COLOR_BUFFER_BIT);

    //1. Process Input
    processInput(window);

    //2. Render Scene

    //3. Poll for events
    glfwPollEvents(); //checks for events -- mouse/keyboard input
    
    //4. Swap Buffers
    glfwSwapBuffers(window); //swap the color buffer used to display (drawing to a single buffer causes flickering...double buffer...draw to a hidden one then swap fixes this).
    
  }

  

  glfwTerminate(); //clean/delete GLFW resources
  return 0;
}

void framebuffer_size_callback(GLFWwindow* win, int width, int height) {
  glViewport(0,0,width,height);
}