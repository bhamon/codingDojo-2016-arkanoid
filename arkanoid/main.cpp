#include <GL/freeglut.h>

#include <iostream>
#include <cstdlib>

#include "GameEngine.h"

static const int WIDTH = 800;
static const int HEIGHT = 600;

static arkanoid::GameEngine *gameEngine = nullptr;

static void glutIdleCallback() {
	glutPostRedisplay();
}

static void glutDrawCallback(void) {
	gameEngine->animate();
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
		std::cerr << "Unable to create an OpenGl GLUT window" << std::endl;
		exit(EXIT_FAILURE);
	}

	gameEngine = new arkanoid::GameEngine();
	gameEngine->onResize(WIDTH, HEIGHT);

	glutDisplayFunc(glutDrawCallback);
	glutIdleFunc(glutIdleCallback);
	glutKeyboardFunc(keyDownCallback);
	glutKeyboardUpFunc(keyUpCallback);
	glutSpecialFunc(specialKeyDownCallback);
	glutSpecialUpFunc(specialKeyUpCallback);

	glutMainLoop();

	delete gameEngine;

	return 0;
}
