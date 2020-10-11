#include <iostream>

#include <stdlib.h>

#include <string>

#include <fstream>

#include <sstream>

#include <deque>

#include <stack>

#include <GL/glut.h>

#include "checkers.cpp"

#include "shaders.h"

#include "Transform.h"

using namespace std;

// Main variables in the program.
#define MAINPROGRAM#include "variables.h"

void display(void); // prototype for display function.

void reshape(int width, int height) {
    w = width;
    h = height;
    mat4 mv; // just like for lookat

    glMatrixMode(GL_PROJECTION);
    float aspect = w / (float) h, zNear = 0.1, zFar = 99.0;

    // I am changing the projection stuff to be consistent with lookAt
    mv = glm::perspective(fovy, aspect, zNear, zFar);

    glLoadMatrixf( & mv[0][0]);
    glViewport(0, 0, w, h);
}

void printHelp() {
    std::cout << "\npress 'h' to print this message again.\n" <<
        "press 'r' to reset the transformations.\n" <<
        "press 'v' 't' 's' to do view [default], translate, scale.\n" <<
        "press ESC to quit.\n";
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'h':
        printHelp();
        break;
    case 27: // Escape to quit
        exit(0);
        break;
    case 'r': // reset eye and up vectors, scale and translate.
        eye = eyeinit;
        up = upinit;
        amount = amountinit;
        transop = view;
        sx = sy = 1.0;
        tx = ty = 0.0;
        break;
    case 'v':
        transop = view;
        std::cout << "Operation is set to View\n";
        break;
    case 't':
        transop = translate;
        std::cout << "Operation is set to Translate\n";
        break;
    case 'c':
        transop = scale;
        std::cout << "Operation is set to Scale\n";
        break;
    case 'd':
        b.rightPress();
        break;
    case 'a':
        b.leftPress();
        break;
    case 'w':
        b.upPress();
        break;
    case 's':
        b.downPress();
        break;
    case 'p':
        if (b.placePiece()) {
            b.isAnimate = true;
            break;
        }
        case 'm':
            if (b.moveFrom == NULL) {
                b.moveFrom = b.curPlace;
            } else {
                b.moveTo = b.curPlace;
                b.isMove = true;
                b.move();
            }
            break;
        case '/':
            b.remove();
            break;
    }
    glutPostRedisplay();
}

void animate() {
    b.animate_helper();
}

void specialKey(int key, int x, int y) {
    switch (key) {
    case 100: //left
        if (transop == view) Transform::left(amount, eye, up);
        else if (transop == scale) sx -= amount * 0.01;
        else if (transop == translate) tx -= amount * 0.01;
        break;
    case 101: //up
        if (transop == view) Transform::up(amount, eye, up);
        else if (transop == scale) sy += amount * 0.01;
        else if (transop == translate) ty += amount * 0.01;
        break;
    case 102: //right
        if (transop == view) Transform::left(-amount, eye, up);
        else if (transop == scale) sx += amount * 0.01;
        else if (transop == translate) tx += amount * 0.01;
        break;
    case 103: //down
        if (transop == view) Transform::up(-amount, eye, up);
        else if (transop == scale) sy -= amount * 0.01;
        else if (transop == translate) ty -= amount * 0.01;
        break;
    }
    glutPostRedisplay();
}

void init() {
    // Initialize shaders
    vertexshader = initshaders(GL_VERTEX_SHADER, "shaders/light.vert.glsl");
    fragmentshader = initshaders(GL_FRAGMENT_SHADER, "shaders/light.frag.glsl");
    shaderprogram = initprogram(vertexshader, fragmentshader);
    enablelighting = glGetUniformLocation(shaderprogram, "enablelighting");
    lightpos = glGetUniformLocation(shaderprogram, "lightposn");
    lightcol = glGetUniformLocation(shaderprogram, "lightcolor");
    numusedcol = glGetUniformLocation(shaderprogram, "numused");
    ambientcol = glGetUniformLocation(shaderprogram, "ambient");
    diffusecol = glGetUniformLocation(shaderprogram, "diffuse");
    specularcol = glGetUniformLocation(shaderprogram, "specular");
    emissioncol = glGetUniformLocation(shaderprogram, "emission");
    shininesscol = glGetUniformLocation(shaderprogram, "shininess");
}

int main(int argc, char * argv[]) {

    // Initialize Player 1 and 2 PIECES
    GLfloat dis = -0.4;
    for (int i = 0; i < 6; i++) {
        pl1x[i] = dis;
        pl2x[i] = dis;
        dis += 0.16;
        pl1y[i] = -0.6;
        pl2y[i] = 0.6;
    }

    sx = sy = 1.0; // keyboard controlled scales in x and y
    tx = ty = 0.0;

    eyeinit = vec3(0, -2, 2);
    center = vec3(0, 0, 0);
    upinit = vec3(0, 1, 1);
    upinit = Transform::upvector(upinit, center - eyeinit);
    fovy = 30;
    w = 500;
    h = 500;

    eye = eyeinit;
    up = upinit;
    amount = amountinit;
    sx = sy = 1.0; // keyboard controlled scales in x and y
    tx = ty = 0.0; // keyboard controllled translation in x and y

    glutInit( & argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutCreateWindow("Checkers");
    init();
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display);
    glutSpecialFunc(specialKey);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);
    glutReshapeWindow(w, h);

    glutIdleFunc(animate);
    printHelp();
    glutMainLoop();
    return 0;
}
