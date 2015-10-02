
#ifdef MAINPROGRAM
#define EXTERN
#else
#define EXTERN extern
#endif

EXTERN int amount; // The amount of rotation for each arrow press
EXTERN vec3 eye; // The (regularly updated) vector coordinates of the eye
EXTERN vec3 up;  // The (regularly updated) vector coordinates of the up

// Initialize Player one Pices
EXTERN GLfloat pl1x[6];
EXTERN GLfloat pl1y[6];
EXTERN GLfloat pl2x[6];
EXTERN GLfloat pl2y[6];

#ifdef MAINPROGRAM
Board b;
int player = 1;
vec3 eyeinit(0.0,0.0,5.0) ; // Initial eye position, also for resets
vec3 upinit(0.0,1.0,0.0) ; // Initial up position, also for resets
int amountinit = 5; // Initial step amount for camera movement
vec3 center(0.0,0.0,0.0) ; // Center look at point
int w = 600, h = 400 ; // width and height
float fovy = 90.0 ; // For field of view
#else
EXTERN int player;
EXTERN Board b;
EXTERN vec3 eyeinit ;
EXTERN vec3 upinit ;
EXTERN vec3 center ;
EXTERN int amountinit;
EXTERN int w, h ;
EXTERN float fovy ;



#endif

EXTERN GLuint vertexshader, fragmentshader, shaderprogram ; // shaders
static enum {view, translate, scale} transop ; // which operation to transform
enum shape {cube, sphere, teapot} ;
EXTERN float sx, sy ; // the scale in x and y
EXTERN float tx, ty ; // the translation in x and y

// Lighting parameter array, similar to that in the fragment shader
EXTERN GLfloat lightposn [4 * 2] ;  // Light Positions
EXTERN GLfloat lightcolor[4 * 2] ; // Light Colors
EXTERN GLfloat lightransf[4 * 2] ; // Lights transformed by modelview
EXTERN int numused ;                     // How many lights are used


EXTERN GLfloat ambient[4] ;
EXTERN GLfloat diffuse[4] ;
EXTERN GLfloat specular[4] ;
EXTERN GLfloat emission[4] ;
EXTERN GLfloat shininess ;






// Variables to set uniform params for lighting fragment shader
EXTERN GLuint lightcol ;
EXTERN GLuint lightpos ;
EXTERN GLuint numusedcol ;
EXTERN GLuint enablelighting ;
EXTERN GLuint ambientcol ;
EXTERN GLuint diffusecol ;
EXTERN GLuint specularcol ;
EXTERN GLuint emissioncol ;
EXTERN GLuint shininesscol ;
