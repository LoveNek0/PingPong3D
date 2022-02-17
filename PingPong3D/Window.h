#pragma once
#include <iostream>
#include <chrono>
#include <GL/openglut.h>
#include <vector>
#include "Input.h"
#include "Vector2D.h"
#include "Scene.h"
#include "Time.h"
#include "Log.h"
using namespace std::chrono;
using namespace std;

class Window {
private:
	string title;
    int width = 800;
    int height = 600;

    Vector2D* mousePosition = new Vector2D(-1, -1);
    Vector2D* mouseOffset = new Vector2D();
    bool* mouseButtons = new bool[3];
    vector<unsigned char>* keyboardButtons;
    vector<int>* keyboardSpecButtons;
    unsigned char lastPressed = '\0';

    Input* input;

    Scene* currentScene = NULL;

    static Window* currentInstance;
    

    void Display() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (currentScene != NULL) {
            // 3D Models
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            glPushMatrix();

            glEnable(GL_LIGHTING);
            glEnable(GL_DEPTH_TEST);

            glScalef(zoom, zoom, zoom);

            glTranslatef(currentScene->transform.position.x, currentScene->transform.position.z, currentScene->transform.position.y);

            glRotatef(-45, 0, 0, 1);
            glRotatef(-currentScene->transform.rotation.GetX(), 1.0, 0.0, 0.0);
            glRotatef(currentScene->transform.rotation.GetZ(), 0.0, 0.0, 1.0);

            for (GameObject* object : currentScene->GetObjects()) {
                glTranslatef(object->transform.position.x, object->transform.position.y, object->transform.position.z);

                glRotatef(object->transform.rotation.GetX(), 1.0, 0.0, 0.0);
                glRotatef(object->transform.rotation.GetY(), 0.0, 1.0, 0.0);
                glRotatef(object->transform.rotation.GetZ(), 0.0, 0.0, 1.0);

                for (Polygon3D polygon : object->GetPolygones()) {
                    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                    glBegin(GL_POLYGON);
                    glColor3f(polygon.color.GetRedFloat(), polygon.color.GetGreenFloat(), polygon.color.GetBlueFloat());
                    for (Vector3D point : polygon.GetPoints())
                        glVertex3f(point.x, point.z, point.y);
                    glEnd();

                    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                    glBegin(GL_POLYGON);
                    glColor3f(0, 0, 0);
                    for (Vector3D point : polygon.GetPoints())
                        glVertex3f(point.x, point.z, point.y);
                    glEnd();
                }

                glTranslatef(-object->transform.position.x, -object->transform.position.y, -object->transform.position.z);

            }
           
            glDisable(GL_DEPTH_TEST);
            glDisable(GL_LIGHTING);
            glPopMatrix();
            // 3D Models end


            // Text
            glMatrixMode(GL_PROJECTION);
            glPushMatrix();
            glLoadIdentity();
            glOrtho(0, glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_HEIGHT), -1, 1);

            glMatrixMode(GL_MODELVIEW);
            glPushMatrix();
            glLoadIdentity();

            for (TextField* text : currentScene->GetTexts()) {
                glColor3f(text->color.GetRedFloat(), text->color.GetGreenFloat(), text->color.GetBlueFloat());
                glRasterPos2i(text->position.x, this->height - 18 - text->position.y);
                int j = 0;
                for (unsigned int i = 0; i < text->text.length(); i++)
                    if (text->text[i] == '\n')
                        glRasterPos2i(text->position.x, (this->height - 18 - text->position.y) + (++j * (-18)));
                    else
                        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text->text[i]);
            }

            glMatrixMode(GL_MODELVIEW);
            glPopMatrix();
            glMatrixMode(GL_PROJECTION);
            glPopMatrix();
            // Text end
        }

        glFlush();
        glutSwapBuffers();
    }

    static void _Display() {
        currentInstance->Display();
    }
    static void _Reshape(int w, int h) {
        currentInstance->SetSize(w, h);
    }
    static void _OnKeyDown(unsigned char key, int x, int y) {
        if (!currentInstance->input->keyboard->GetKey(key)) {
            currentInstance->keyboardButtons->push_back(tolower(key));
            currentInstance->lastPressed = key;
        }
    }
    static void _OnKeyUp(unsigned char key, int x, int y) {
        if (currentInstance->input->keyboard->GetKey(key)) {
            currentInstance->keyboardButtons->erase(std::remove(currentInstance->keyboardButtons->begin(), currentInstance->keyboardButtons->end(), key), currentInstance->keyboardButtons->end());
            currentInstance->lastPressed = '\0';
        }
    }
    static void _OnSpecialKeyDown(int key, int x, int y) {
        if (!currentInstance->input->keyboard->GetSpecialKey(key))
            currentInstance->keyboardSpecButtons->push_back(key);
    }
    static void _OnSpecialKeyUp(int key, int x, int y) {
        if (currentInstance->input->keyboard->GetSpecialKey(key))
            currentInstance->keyboardSpecButtons->erase(std::remove(currentInstance->keyboardSpecButtons->begin(), currentInstance->keyboardSpecButtons->end(), key), currentInstance->keyboardSpecButtons->end());
    }
    static void _OnMouseMove(int x, int y) {
        if (currentInstance->mousePosition->x == -1 || currentInstance->mousePosition->y == -1) {
            currentInstance->mousePosition->x = x;
            currentInstance->mousePosition->y = y;
        }
        currentInstance->mouseOffset->x += x - currentInstance->mousePosition->x;
        currentInstance->mouseOffset->y += y - currentInstance->mousePosition->y;
        currentInstance->mousePosition->x = x;
        currentInstance->mousePosition->y = y;
    }
    static void _OnMouseClick(int button, int state, int x, int y) {
        _OnMouseMove(x, y);
        if (button <= 2 && button >= 0)
            currentInstance->mouseButtons[button] = ((state == 0) ? (true) : (false));
    }
    static void _OnTimer(int p) {
        Time::Update();
        if (currentInstance->currentScene != NULL) {
            for (GameObject* object : currentInstance->currentScene->GetObjects())
                for (ObjectScript* script : object->GetScripts())
                    if(script->active)
                        script->OnUpdate();
        }

        currentInstance->mouseOffset->x = 0;
        currentInstance->mouseOffset->y = 0;

        glutPostRedisplay();
        glutTimerFunc(16, Window::_OnTimer, 0);
    }

public:
    float zoom = 1.0f;

    Window(string title) {
        this->title = title;
        Mouse* m_ = new Mouse(mousePosition, mouseOffset, mouseButtons);
        Keyboard* k_ = new Keyboard(keyboardButtons, keyboardSpecButtons, &lastPressed);
        input = new Input(m_, k_);

        int argc = 0;
        char* argv[] = { NULL };
        glutInit(&argc, argv);

        glutInitWindowSize(this->width, this->height);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
        glutCreateWindow(this->title.c_str());
        SetSize(width, height);

        // Light
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glEnable(GL_COLOR_MATERIAL);
        glShadeModel(GL_SMOOTH);

        // Smooth
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);
        glEnable(GL_POINT_SMOOTH);
        glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
        glEnable(GL_LINE_SMOOTH);
        glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
        glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    }

    string GetTitle() {
        return this->title;
    }
    Vector2D GetSize() {
        return Vector2D(width, height);
    }
    Scene* GetScene() {
        return currentScene;
    }

    void SetTitle(string value) {
        glutSetWindowTitle(value.c_str());
    }
    void SetSize(int width, int height) {
        if (width < 0)
            width = 0;
        if (height < 0)
            height = 0;

        this->width = width;
        this->height = height;

        glutReshapeWindow(width, height);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glViewport(0, 0, width, height);
        GLfloat fAspect = (GLfloat)width / (GLfloat)height;
        gluPerspective(60.0f, fAspect, 1.0, 1000.0);
        gluLookAt(100.0f, 100.0f, 100.0f, .0f, .0f, .0f, .0f, .0f, 1.0f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        gluPerspective(60.0, (float)width / (float)height, 1.0, 100.0);
    }
    void SetScene(Scene* scene) {
        this->currentScene = scene;
        Scene::Init(scene, this);
    }

    Input* GetInput() {
        return input;
    }

    void Run() {
        currentInstance = this;

        glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);

        glutKeyboardFunc(Window::_OnKeyDown);
        glutKeyboardUpFunc(Window::_OnKeyUp);

        glutSpecialFunc(Window::_OnSpecialKeyDown);
        glutSpecialUpFunc(Window::_OnSpecialKeyUp);

        glutPassiveMotionFunc(Window::_OnMouseMove);
        glutMotionFunc(Window::_OnMouseMove);
        glutMouseFunc(Window::_OnMouseClick);

        glutReshapeFunc(Window::_Reshape);

        glutDisplayFunc(Window::_Display);

        glutTimerFunc(0, Window::_OnTimer, 0);

        SetSize(width, height);
        glutMainLoop();
    }
};

Window* Window::currentInstance = NULL;