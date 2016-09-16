#include <GL/glew.h>
#include <GL/freeglut.h>

#include <iostream>
#include <cstdlib>

#include "GameEngine.h"

static const int WIDTH = 400;
static const int HEIGHT = 600;
static const int FPS = 30;
static const float deltaT = FPS / 1000.f;

static arkanoid::GameEngine *gameEngine = nullptr;

static void glutIdleCallback() {
	static int previousClock = glutGet(GLUT_ELAPSED_TIME);
	static int currentClock = glutGet(GLUT_ELAPSED_TIME);
	static float t;

	currentClock = glutGet(GLUT_ELAPSED_TIME);
	t = currentClock - previousClock;
	if (t < deltaT) { return; }
	else { previousClock = currentClock; }

	gameEngine->animate();

	glutPostRedisplay();
}

static void glutDrawCallback(void) {
	gameEngine->paintScene();
	glutSwapBuffers();
}

static void glutReshapeCallback(int width, int height) {
	gameEngine->onResize(width, height);
	glutPostRedisplay();
}

static void keyDownCallback(const unsigned char key, const int, const int) {
	// escape key
	if (key == 27) {
		glutLeaveMainLoop();
	}
	else {
		gameEngine->onKeyDown(key);
	}
	glutPostRedisplay();
}

static void keyUpCallback(const unsigned char key, const int, const int) {
	gameEngine->onKeyUp(key);
	glutPostRedisplay();
}

static void specialKeyDownCallback(int key, const int, const int) {
	gameEngine->onKeyDown(key);
	glutPostRedisplay();
}

static void specialKeyUpCallback(int key, const int, const int) {
	gameEngine->onKeyUp(key);
	glutPostRedisplay();
}

int  main(int argc, char *argv[]) {

	glutInit(&argc, argv);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_MULTISAMPLE);
	if ((glutCreateWindow("Arkanoid")) == GL_FALSE) {
		std::cerr << "GLUT : Unable to create an OpenGL window" << std::endl;
		exit(EXIT_FAILURE);
	}

	glewInit();

	gameEngine = new arkanoid::GameEngine();
	gameEngine->onResize(WIDTH, HEIGHT);

	glutDisplayFunc(glutDrawCallback);
	glutIdleFunc(glutIdleCallback);
	glutReshapeFunc(glutReshapeCallback);

	glutKeyboardFunc(keyDownCallback);
	glutKeyboardUpFunc(keyUpCallback);
	glutSpecialFunc(specialKeyDownCallback);
	glutSpecialUpFunc(specialKeyUpCallback);

	glutMainLoop();

	delete gameEngine;

	return 0;
}
