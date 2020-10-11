#include <iostream>

#include <string>

#include <fstream>

#include <sstream>

#include <deque>

#include <stack>

#include <GL/glut.h>

#include "Transform.h"

#include "checkers.cpp"


using namespace std;#include "variables.h"


void display() {
    glClearColor(0, 0, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    mat4 mv;

    mv = glm::lookAt(eye, center, up);

    glLoadMatrixf( & mv[0][0]);

    if (2) {
        glUniform1i(enablelighting, true);

        glUniform4fv(lightpos, 2, lightposn);
        glUniform4fv(lightcol, 2, lightcolor);

    } else {
        glUniform1i(enablelighting, false);
    }

    // Transformations for objects, involving translation and scaling
    mat4 sc(1.0), tr(1.0), transf(1.0);
    sc = Transform::scale(sx, sy, 1.0);
    tr = Transform::translate(tx, ty, 0.0);

    transf = mv * tr * sc;

    glLoadMatrixf( & transf[0][0]);

    GLfloat ambient0[4] = {
        0.2,
        0.2,
        0.2,
        1
    };
    GLfloat diffuse0[4] = {
        1.0,
        1.0,
        1.0,
        1
    };
    GLfloat specular0[4] = {
        1,
        1,
        1,
        1
    };
    GLfloat shininess0 = 100;

    glUniform4fv(emissioncol, 1, ambient0);
    glUniform4fv(diffusecol, 1, diffuse0);
    glUniform4fv(specularcol, 1, specular0);
    glUniform1fv(shininesscol, 1, & shininess0);

    glPushMatrix();
    glScalef(1.0, 1.0, 0.025);
    glutSolidCube(1.0);
    glPopMatrix();

    GLfloat diffuse1[] = {
        0.0,
        0.0,
        0.0,
        1
    };

    glUniform4fv(diffusecol, 1, diffuse1);

    //////////////        BOARD DOTS DESIGN         ///////
    GLfloat bdx[] = {
        0.4,
        0.4,
        0.4,
        -0.4,
        -0.4,
        -0.4,
        0.0,
        0.0,
        0.0,
        0.0,
        \
        0.2,
        0.2,
        0.2,
        -0.2,
        -0.2,
        -0.2
    };
    GLfloat bdy[] = {
        -0.4,
        0.0,
        0.4,
        -0.4,
        0.0,
        0.4,
        -0.4,
        -0.2,
        0.2,
        0.4,
        \
        -0.2,
        0.0,
        0.2,
        -0.2,
        0.0,
        0.2
    };

    for (int i = 0; i < 16; i++) {
        glPushMatrix();
        glTranslatef(bdx[i], bdy[i], 0.02);
        glScalef(1.0, 1.0, 0.05);
        glutSolidSphere(0.011, 20, 20);
        glPopMatrix();
    }

    ////////////         BOARD DOTS DESIGN         ///////////

    ///////////          BOARD LINES DESIGN        ///////////

    GLfloat blx[] = {
        -0.4,
        -0.2,
        0.2,
        0.4,
        0.0,
        0.0,
        0.0,
        0.0,
        -0.3,
        0.3,
        0.0,
        0.0
    };
    GLfloat bly[] = {
        0.0,
        0.0,
        0.0,
        0.0,
        -0.4,
        -0.2,
        0.2,
        0.4,
        0.0,
        0.0,
        -0.3,
        0.3
    };
    GLfloat blxsc[] = {
        0.005,
        0.005,
        0.005,
        0.005,
        1.0,
        0.5,
        0.5,
        1.0,
        0.25,
        0.25,
        0.005,
        0.005
    };
    GLfloat blysc[] = {
        1.0,
        0.5,
        0.5,
        1.0,
        0.005,
        0.005,
        0.005,
        0.005,
        0.005,
        0.005,
        0.25,
        0.25
    };

    for (int i = 0; i < 12; i++) {
        glPushMatrix();
        glTranslatef(blx[i], bly[i], 0.01);
        glScalef(blxsc[i], blysc[i], 0.025);
        glutSolidCube(0.8);
        glPopMatrix();
    }

    //////////          BOARD LINES DESIGN        ////////////

    /////////           PLAYER ONE PIECES        ////////////
    GLfloat diffuse2[] = {
        1.0,
        1.0,
        0.0,
        1
    };

    glUniform4fv(diffusecol, 1, diffuse2);

    for (int i = 0; i < 6; i++) {
        glPushMatrix();
        glTranslatef(pl1x[i], pl1y[i], 0.05);
        glScalef(1.0, 1.0, 0.05);
        glutSolidSphere(0.05, 20, 20);
        glPopMatrix();
    }

    /////////           PLAYER ONE PIECES        ////////////

    ////////            PLAYER TWO PIECES        ////////////

    GLfloat diffuse3[] = {
        1.0,
        0.0,
        1.0,
        1
    };

    glUniform4fv(diffusecol, 1, diffuse3);

    for (int i = 0; i < 6; i++) {
        glPushMatrix();
        glTranslatef(pl2x[i], pl2y[i], 0.05);
        glScalef(1.0, 1.0, 0.05);
        glutSolidSphere(0.05, 20, 20);
        glPopMatrix();
    }

    ///////             PLAYER TWO PIECES        ////////////

    //////              BOARD CURRENT CURSOR     /////////////
    GLfloat diffuse4[] = {
        0.0,
        1.0,
        0.0,
        1
    };
    glUniform4fv(diffusecol, 1, diffuse4);

    glPushMatrix();
    glTranslatef(b.curPlace -> x, b.curPlace -> y, 0.06);
    glScalef(1.0, 1.0, 0.05);
    glutSolidSphere(0.02, 20, 20);
    glPopMatrix();

    //////              BOARD CURRENT CURSOR     /////////////

    glutSwapBuffers();
}
