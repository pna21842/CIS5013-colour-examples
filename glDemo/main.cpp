
#include "core.h"
using namespace std;


// global variables

mt19937 engine;
uniform_real_distribution<float> range;

mt19937 engine2;
uniform_real_distribution<float> range2;

vector<glm::vec2> vertexCoords;
vector<glm::vec4> colourCodes;
vector<float> sizeValue;

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
void randomPoints();
void edgedRectangles();
void blendingBoxes();

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


	random_device rd;
	engine = mt19937(rd());
	range = uniform_real_distribution<float>(-1.0f, 1.0f);

	random_device dr;
	engine2 = mt19937(dr());
	range2 = uniform_real_distribution<float>(-1.0f, 20.0f);

	// Create a openGL vec2 vector object containing 100 elements all initialised to 0.0
	vertexCoords = vector<glm::vec2>(100, glm::vec2(0.0f, 0.0f));
	colourCodes = vector<glm::vec4>(100, glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	sizeValue = vector<float>(100, 0.0f);


	// Iterate 100 times (once for each vertex) and calculate and store the random x and y values
	for (int i = 0; i < 100; i++) {

		float x = range(engine);
		float y = range(engine);

		vertexCoords[i] = glm::vec2(x, y);

		float r = range(engine);
		float g = range(engine);
		float b = range(engine);
		float a = range(engine);

		colourCodes[i] = glm::vec4(r, g, b, a);

		float s = range2(engine2);
		sizeValue[i] = s;
	}


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

	//randomPoints();
	edgedRectangles();
	//blendingBoxes();
}



// Rendering functions

void blendingBoxes() 
{
	glBegin(GL_QUADS);

	glEnd();
}

void edgedRectangles() 
{
	glLineWidth(5.0f);
	glBegin(GL_LINES);

	
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(-0.5f, -0.5f);

	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex2f(0.5f, -0.5f);

	glEnd();

	////////////////////////////

	glLineWidth(10.0f);
	glBegin(GL_LINES);


	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2f(0.5f, 0.5f);

	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex2f(-0.5f, 0.5f);

	glEnd();

	////////////////////////////

	glLineWidth(20.0f);
	glBegin(GL_LINES);


	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex2f(-0.5f, -0.5f);

	glColor3f(1.0f, 0.0f, 1.0f);
	glVertex2f(-0.5f, 0.5f);

	glEnd();

	////////////////////////////

	glLineWidth(2.0f);
	glBegin(GL_LINES);


	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2f(0.5f, -0.5f);

	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex2f(0.5f, 0.5f);

	glEnd();
}

void randomPoints() 
{	
	for (int i = 0; i < 100; i++) {

		glPointSize(sizeValue[i]);
		glColor4f(colourCodes[i].r, colourCodes[i].g, colourCodes[i].b, colourCodes[i].a);
	}


	glBegin(GL_POINTS);

	// Render objects here...
	for (int i = 0; i < 100; i++) {

		glVertex2f(vertexCoords[i].x, vertexCoords[i].y);
	}

	glEnd();
}


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

