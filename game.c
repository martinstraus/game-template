#include <stdio.h>
#include <stdlib.h>
#include <GL/freeglut.h>

#define false 0
#define true 1

#define KEY_SPACEBAR ' '
#define KEY_ESCAPE 27

typedef unsigned int bool;

typedef struct PointI {
    int row, column;
} PointI;

typedef struct SizeI {
    int height, width;
} SizeI;

typedef struct Viewport {
    PointI lowerLeft;
    SizeI size;
} Viewport;

typedef struct Game {
    long time;
    int speed;
    bool paused;
    bool exit;
    Viewport viewport;
    int windowId;
    SizeI windowSize;
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
    //printf("Key pressed: %d\n", key);
}

void idleCallback() {
    if (GAME.exit) {
        glutDestroyWindow(GAME.windowId);
        exit(0);
    }
}

void mouseMoveCallback(int x, int y) {
}

void setViewport(Viewport* v) {
    glViewport(v->lowerLeft.column, v->lowerLeft.row, v->size.width, v->size.height);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0, GAME.windowSize.width, 0, GAME.windowSize.height, -1, 1); // Set orthographic projection with viewport
    setViewport(&(GAME.viewport));
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glFlush();
    glutSwapBuffers();
}

void initGraphics(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(GAME.windowSize.width, GAME.windowSize.height);
    GAME.windowId = glutCreateWindow("Game");
    glutTimerFunc(GAME.speed, tick, 0);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboardCallack);
    glutIdleFunc(idleCallback);
    glutPassiveMotionFunc(mouseMoveCallback);
    GAME.viewport = (Viewport){(PointI){0, 0}, (SizeI){GAME.windowSize.height, GAME.windowSize.width}};
}

void run() {
    glutMainLoop();
}

void initWorld() {

}

int main(int argc, char** argv) {
    GAME = (Game) {};
    initWorld();
    initGraphics(argc, argv);
    run();
    return 0;
}
