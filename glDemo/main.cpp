
#include "core.h"


// global variables

// Window size
const unsigned int initWidth = 512;
const unsigned int initHeight = 512;

// Example variables to change when doing keyboard input

// the position of our object
float x = 0.0f;
float y = 0.0f;

// amount we change x, y when keys are pressed
const float movementSpeed = 0.005f;

// flags to track when a movement key is pressed
bool wPressed = false;
bool sPressed = false;
bool aPressed = false;
bool dPressed = false;


// Function prototypes
void renderScene();

// Rendering function prototypes
void drawShadedTriangle();
void drawStarOutline();
void drawStarShaded();
void drawTank();
void drawSemiCircleStudio();

void resizeWindow(GLFWwindow* window, int width, int height);
void keyboardHandler(GLFWwindow* window, int key, int scancode, int action, int mods);
void updateScene();



int main() {

	//
	// 1. Initialisation
	//
	

	// Initialise glfw and setup window
	glfwInit();

	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
	glfwWindowHint(GLFW_OPENGL_COMPAT_PROFILE, GLFW_TRUE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 1);

	GLFWwindow* window = glfwCreateWindow(initWidth, initHeight, "Real-Time Computer Graphics", NULL, NULL);

	// Check window was created successfully
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window!\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	

	// Set callback functions to handle different events
	glfwSetFramebufferSizeCallback(window, resizeWindow); // resize window callback
	glfwSetKeyCallback(window, keyboardHandler); // Keyboard input callback


	// Initialise glew
	glewInit();

	
	// Setup window's initial size
	resizeWindow(window, initWidth, initHeight);

	// Initialise scene - geometry and shaders etc
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // setup background colour to be black

	// *** setup viewplane to the appropriate size
	gluOrtho2D(-1.1f, 1.1f, -1.1f, 1.1f);

	//
	// 2. Main loop
	// 
	
	// Loop while program is not terminated.
	while (!glfwWindowShouldClose(window)) {

		updateScene();
		renderScene();						// Render into the current buffer
		glfwSwapBuffers(window);			// Displays what was just rendered (using double buffering).

		// Poll events (key presses, mouse events)
		// glfwWaitEvents();				// Use this if no animation.
		// glfwWaitEventsTimeout(1.0/60.0);	// Use this to animate at 60 frames/sec (timing is NOT reliable)
		glfwPollEvents();					// Use this version when animating as fast as possible
	}

	glfwTerminate();
	return 0;
}




// renderScene - function to render the current scene
void renderScene()
{
	// Clear the rendering window
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Render objects here...
	//drawShadedTriangle();
	//drawStarOutline();
	//drawStarShaded();
	//drawTank();
	drawSemiCircleStudio();
}

// Rendering functions

void drawShadedTriangle() {

	glBegin(GL_TRIANGLES);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(-0.5f, -0.5f);
	
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(0.0f, 0.5f);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2f(0.5f, -0.5f);

	glEnd();
}

void drawStarOutline() {

	glBegin(GL_LINE_LOOP);

	glColor3ub(255, 255, 255);
	glVertex2f(0.0, 0.25f);

	glColor3ub(255, 255, 0);
	glVertex2f(0.1f, 0.1f);

	glColor3ub(255, 0, 255);
	glVertex2f(0.25f, 0.08f);

	glColor3ub(255, 0, 0);
	glVertex2f(0.15f, -0.05f);

	glColor3ub(0, 255, 255);
	glVertex2f(0.25f, -0.25f);

	glColor3ub(0, 255, 255);
	glVertex2f(0.0f, -0.125f);

	glColor3ub(231, 170, 25);
	glVertex2f(-0.25f, -0.25f);

	glColor3ub(128, 200, 0);
	glVertex2f(-0.15f, -0.05f);

	glColor3ub(0, 255, 255);
	glVertex2f(-0.25f, 0.08f);

	glColor3ub(200, 90, 221);
	glVertex2f(-0.1f, 0.1f);

	glEnd();
}

void drawStarShaded() {

	glBegin(GL_TRIANGLE_FAN);

	glColor3ub(255, 255, 0);
	glVertex2f(0.0f, 0.0f); // Centre vertex

	glColor3ub(0, 0, 0);
	glVertex2f(0.0, 0.25f); // First boundary vertex
	glVertex2f(0.1f, 0.1f);
	glVertex2f(0.25f, 0.08f);
	glVertex2f(0.15f, -0.05f);
	glVertex2f(0.25f, -0.25f);
	glVertex2f(0.0f, -0.125f);
	glVertex2f(-0.25f, -0.25f);
	glVertex2f(-0.15f, -0.05f);
	glVertex2f(-0.25f, 0.08f);
	glVertex2f(-0.1f, 0.1f);
	glVertex2f(0.0, 0.25f); // Repeat of first boundary vertex to close the loop

	glEnd();
}

void drawTank() {

	// Render body
	glBegin(GL_LINE_LOOP);

	glColor3ub(0, 255, 0); // just set colour once as all vertices will keep this unless changed
	glVertex2f(-0.75f, 0.4f);
	glVertex2f(0.75f, 0.4f);
	glVertex2f(0.75f, -0.4f);
	glVertex2f(-0.75f, -0.4f);

	glEnd();

	// Render gun
	glBegin(GL_LINE_LOOP);

	glColor3ub(255, 0, 0); // just set colour once as all vertices will keep this unless changed
	glVertex2f(-0.5f, 0.3f);
	glVertex2f(0.5f, 0.0f);
	glVertex2f(-0.5f, -0.3f);

	glEnd();
}


// Draw a semi-circle with smooth shading, with red vertices on the inner edge and yellow vertices on the outer edge.
void drawSemiCircleStudio() {

	glShadeModel(GL_SMOOTH);

	glBegin(GL_TRIANGLE_STRIP);

	glColor3ub(255, 0, 0);
	glVertex2f(-0.25f, 0.0f);

	glColor3ub(255, 255, 0);
	glVertex2f(-0.75f, 0.0f);

	glColor3ub(255, 0, 0);
	glVertex2f(-0.216506351f, 0.125f);

	glColor3ub(255, 255, 0);
	glVertex2f(-0.649519053f, 0.375f);

	glColor3ub(255, 0, 0);
	glVertex2f(-0.125, 0.216506351f);

	glColor3ub(255, 255, 0);
	glVertex2f(-0.375f, 0.649519053f);

	glColor3ub(255, 0, 0);
	glVertex2f(0.0f, 0.25f);

	glColor3ub(255, 255, 0);
	glVertex2f(0.0f, 0.75f);

	glColor3ub(255, 0, 0);
	glVertex2f(0.125f, 0.216506351f);

	glColor3ub(255, 255, 0);
	glVertex2f(0.375f, 0.649519053f);

	glColor3ub(255, 0, 0);
	glVertex2f(0.216506351f, 0.125f);

	glColor3ub(255, 255, 0);
	glVertex2f(0.649519053f, 0.375f);

	glColor3ub(255, 0, 0);
	glVertex2f(0.25f, 0.0f);

	glColor3ub(255, 255, 0);
	glVertex2f(0.75f, 0.0f);

	glEnd();
}


// Function to call when window resized
void resizeWindow(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);		// Draw into entire window
}

// Function to call to handle keyboard input
void keyboardHandler(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS) {

		// check which key was pressed...
		switch (key)
		{
			case GLFW_KEY_ESCAPE:
				glfwSetWindowShouldClose(window, true);
				break;

			default:
			{
			}
		}
	}
	else if (action == GLFW_RELEASE) {
		// handle key release events
	}
}


// Function called to animate elements in the scene
void updateScene() {
}

