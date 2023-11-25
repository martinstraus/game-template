#include <stdio.h>
#include <stdlib.h>
#include <GL/freeglut.h>

#define false 0
#define true 1

#define KEY_SPACEBAR ' '
#define KEY_ESCAPE 27

typedef unsigned int bool;

typedef struct PointI {
    int x, y;
} PointI;

typedef struct SizeI {
    int width, height;
} SizeI;

typedef struct PointF {
    int x, y;
} PointF;

typedef struct SizeF {
    int width, height;
} SizeF;

typedef struct Window {
    char* title;
    SizeI size;
    int id;
} Window;

typedef struct Game {
    long time;
    int speed;
    bool paused;
    bool exit;
    Window window;
} Game;

Game GAME;

void updateWorld() {

}

void tick() {
    if (!GAME.paused) {
        GAME.time++;
        updateWorld();
        glutPostRedisplay();
    }
    glutTimerFunc(GAME.speed, tick, 0);
}


void keyboardCallack(unsigned char key, int x, int y) {
    switch (key) {
        case KEY_SPACEBAR: 
            GAME.paused = GAME.paused ? false : true;
            glutPostRedisplay();
            break;
        case KEY_ESCAPE: 
            GAME.exit = true;
            break;
    }
}

void idleCallback() {
    if (GAME.exit) {
        glutDestroyWindow(GAME.window.id);
        exit(0);
    }
}

void mouseMoveCallback(int x, int y) {
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Place the code to render your game here.

    glutSwapBuffers();
}

void initGraphics() {
    int argc = 0;
    glutInit(&(argc), NULL);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(GAME.window.size.width, GAME.window.size.height);
    GAME.window.id = glutCreateWindow(GAME.window.title);
    // Set orthographic projection with viewport
    gluOrtho2D(0, GAME.window.size.width, 0, GAME.window.size.height); 

    glutTimerFunc(GAME.speed, tick, 0);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboardCallack);
    glutIdleFunc(idleCallback);
    glutPassiveMotionFunc(mouseMoveCallback);

    glClear(GL_COLOR_BUFFER_BIT);
}

void run() {
    glutMainLoop();
}

void initWorld() {

}

int main(int argc, char** argv) {
    GAME = (Game) {};
    GAME.window.title = "Sample game";
    GAME.window.size = (SizeI) {800, 600};
    initWorld();
    initGraphics();
    run();
    return 0;
}
