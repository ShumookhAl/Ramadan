#include <GL\glew.h>
#include <GL\freeglut.h>
#include <windows.h>
#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <stdarg.h>
#include <mmsystem.h>
using namespace std;

GLint win_width = 950, win_hight = 950;
float transValueX;
float transValueY;
float transValueZ;
float womanWalk;
float manWalk;
float mouthEat;
float mouthTalk;
GLuint myTexture;
GLuint myTexture1;
char imagePath2[] = "/Users/lulu-/Downloads/Mosque.bmp";
char imagePath[] = "/Users/lulu-/Downloads/food (2).bmp";
float _angle = 40.0f;

GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
GLfloat light_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
GLfloat light_specular[] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat mat_specular[] = { 1, 1, 1, 1 };
GLfloat light_position[] = { -1.5, 1.0, -4.0, 1.0 };
GLfloat shininess[] = { 50 };

GLuint LoadTexture(const char* filename, int width, int height) {
    GLuint texture;
    unsigned char* data;
    FILE* file;

    fopen_s(&file, filename, "r+");
    data = (unsigned char*)malloc(width * height * 3);
    fread(data, width * height * 3, 1, file);
    fclose(file);

    for (int i = 0; i < width * height; ++i) {
        int index = i * 3;
        unsigned char B, R;
        B = data[index];
        R = data[index + 2];
        data[index] = R;
        data[index + 2] = B;
    }

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    free(data);

    return texture;
}

void init() {
    transValueX = 0.0;
    transValueY = 0.0;
    transValueZ = 2.0;
    myTexture = LoadTexture(imagePath, 904, 912);
    myTexture1 = LoadTexture(imagePath2, 904, 900);

    glMatrixMode(GL_PROJECTION);
    gluPerspective(65, (win_width / win_hight), 0.01, 50);

    glMatrixMode(GL_MODELVIEW);
    gluLookAt(1, 1, 1, 0, 0, 0, 0, 1, 0);

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
}

void reshapeFunc(GLint new_width, GLint new_hight) {
    glViewport(0, 0, new_width, new_hight);
    win_width = new_width;
    win_hight = new_hight;
}

void print_text(const char* text, int len, int x, int y) {
    glMatrixMode(GL_PROJECTION);
    double* matrix = new double[16];
    glGetDoublev(GL_PROJECTION_MATRIX, matrix);
    glLoadIdentity();
    glOrtho(0, 800, 0, 600, -5, 5);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glLoadIdentity();
    glRasterPos2i(x, y);
    for (int i = 0; i < len; i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (int)text[i]);
    }
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixd(matrix);
    glMatrixMode(GL_MODELVIEW);
}

void mouthFood() {

    glLineWidth(6);  //mouth-woman
    glBegin(GL_LINES);
    glColor3f(1, 0.5, 0.6);
    glVertex2f(-0.33, -0.05);
    glVertex2f(-0.27, -0.05);
    glEnd();
    glLineWidth(6);
    glBegin(GL_LINES);
    glColor3f(1, 0.5, 0.6);
    glVertex2f(-0.33, -0.06);
    glVertex2f(-0.27, -0.06);
    glEnd();

    glLineWidth(6);  //mouth-children2
    glBegin(GL_LINES);
    glColor3f(1, 0.5, 0.6);
    glVertex2f(-0.8, -0.18);
    glVertex2f(-0.74, -0.18);
    glEnd();
    glLineWidth(6);
    glBegin(GL_LINES);
    glColor3f(1, 0.5, 0.6);
    glVertex2f(-0.8, -0.19);
    glVertex2f(-0.74, -0.19);
    glColor4f(1, 1, 1, 1);
    glEnd();

    glLineWidth(6);  //mouth-children1
    glBegin(GL_LINES);
    glColor3f(1, 0.5, 0.6);
    glVertex2f(0.9, -0.18);
    glVertex2f(0.84, -0.18);
    glEnd();
    glLineWidth(6);
    glBegin(GL_LINES);
    glColor3f(1, 0.5, 0.6);
    glVertex2f(0.9, -0.19);
    glVertex2f(0.84, -0.19);
    glColor4f(1, 1, 1, 1);
    glEnd();

    glLineWidth(6);  //mouth-man
    glBegin(GL_LINES);
    glColor3f(1, 0.5, 0.6);
    glVertex2f(0.43, -0.05);
    glVertex2f(0.38, -0.05);
    glEnd();
    glLineWidth(6);
    glBegin(GL_LINES);
    glColor3f(1, 0.5, 0.6);
    glVertex2f(0.43, -0.06);
    glVertex2f(0.38, -0.06);
    glColor4f(1, 1, 1, 1);
    glEnd();
}

void fotoor() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(transValueX, transValueY, transValueZ, 0, 0, 0, 0, 1, 0);

    glBindTexture(GL_TEXTURE_2D, myTexture);
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    glNormal3d(0, 0, 1);
    glTexCoord2f(0, 0); glVertex3f(-1, -1, 0);
    glTexCoord2f(1, 0); glVertex3f(1, -1, 0);
    glTexCoord2f(1, 1); glVertex3f(1, 1, 0);
    glTexCoord2f(0, 1); glVertex3f(-1, 1, 0);
    glEnd();


    glEnable(GL_TEXTURE_2D);
    glColor3f(0.9, 0.8, 0.6);  //woman
    glPushMatrix();
    glTranslatef(-0.3, 0, 0);
    glutSolidSphere(0.12, 40, 10);
    //------------------------- eye
    glColor3f(1, 1, 1);
    glTranslatef(0.04, 0.002, 0);
    glutSolidSphere(0.02, 35, 5);

    glColor3f(1, 1, 1);
    glTranslatef(-0.08, -0.002, 0);
    glutSolidSphere(0.02, 35, 5);

    glColor3f(0, 0, 0);
    glTranslatef(0.07, 0.002, 0);
    glutSolidSphere(0.01, 25, 5);

    glColor3f(0, 0, 0);
    glTranslatef(-0.08, 0.002, 0);
    glutSolidSphere(0.01, 25, 5);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glBegin(GL_QUADS);  //clothes-woman
    glColor3f(1, 1, 0.47843137254902);
    glVertex2f(-0.38, -0.24);
    glVertex2f(-0.22, -0.24);
    glVertex2f(-0.22, -0.12);
    glVertex2f(-0.38, -0.12);
    glColor4f(1, 1, 1, 1);
    glEnd();

    glEnable(GL_TEXTURE_2D);
    glColor3f(0.9, 0.8, 0.6);  //man
    glPushMatrix();
    glTranslatef(0.4, 0, 0);
    glutSolidSphere(0.12, 40, 10);
    //------------- eye
    glColor3f(1, 1, 1);

    glTranslatef(-0.04, 0.002, 0);
    glutSolidSphere(0.02, 35, 5);

    glTranslatef(0.08, 0.001, 0);
    glutSolidSphere(0.02, 35, 5);

    glColor3f(0, 0, 0);
    glTranslatef(-0.08, 0.001, 0);
    glutSolidSphere(0.01, 25, 5);

    glTranslatef(0.08, 0.001, 0);
    glutSolidSphere(0.01, 25, 5);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glBegin(GL_QUADS);  //clothes-man
    glColor3f(0, 0.3, 0.6);
    glVertex2f(0.48, -0.23);
    glVertex2f(0.32, -0.23);
    glVertex2f(0.32, -0.12);
    glVertex2f(0.48, -0.12);
    glColor4f(1, 1, 1, 1);
    glEnd();

    glEnable(GL_TEXTURE_2D);
    glColor3f(0.9, 0.8, 0.6);  //children1
    glPushMatrix();
    glTranslatef(0.9, -0.12, 0);
    glutSolidSphere(0.12, 40, 10);
    glColor4f(1, 1, 1, 1);
    //------------------------------eye
    glColor3f(1, 1, 1);
    glTranslatef(0.04, 0.002, 0);
    glutSolidSphere(0.02, 35, 5);

    glColor3f(1, 1, 1);
    glTranslatef(-0.09, -0.002, 0);
    glutSolidSphere(0.02, 35, 5);


    glColor3f(0, 0, 0);
    glTranslatef(0.07, 0.001, 0);
    glutSolidSphere(0.01, 25, 5);

    glTranslatef(-0.08, 0.001, 0);
    glutSolidSphere(0.01, 25, 5);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glBegin(GL_QUADS);  //clothes-children1
    glColor3f(0.1, 0.8, 0.8);
    glVertex2f(0.98, -0.58);  //1
    glVertex2f(0.83, -0.38);  //2
    glVertex2f(0.83, -0.24);  //3
    glVertex2f(0.98, -0.24);  //4
    glColor4f(1, 1, 1, 1);
    glEnd();

    glEnable(GL_TEXTURE_2D);
    glColor3f(0.9, 0.8, 0.6);  //children2
    glPushMatrix();
    glTranslatef(-0.8, -0.12, 0);
    glutSolidSphere(0.12, 40, 10);
    glColor4f(1, 1, 1, 1);
    //-------------------------- eye
    glColor3f(1, 1, 1);
    glTranslatef(0.06, 0.002, 0);
    glutSolidSphere(0.02, 35, 5);

    glColor3f(1, 1, 1);
    glTranslatef(-0.07, -0.002, 0);
    glutSolidSphere(0.02, 35, 5);

    glColor3f(0, 0, 0);
    glTranslatef(0.07, 0.001, 0);
    glutSolidSphere(0.01, 25, 5);

    glTranslatef(-0.07, 0.001, 0);
    glutSolidSphere(0.01, 25, 5);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glBegin(GL_QUADS);  //clothes-children2
    glColor3f(1, 0.4, 0.4);
    glVertex2f(-0.87, -0.58);  //1
    glVertex2f(-0.74, -0.38);  //2
    glVertex2f(-0.74, -0.24);  //3
    glVertex2f(-0.87, -0.24);  //4
    glColor4f(1, 1, 1, 1);
    glEnd();

    glPushMatrix();
    glScalef(mouthEat, mouthEat, 1);
    mouthFood();
    glColor4f(1, 1, 1, 1);
    glPopMatrix();

    glutSwapBuffers();
    glFlush();

}

void manMosque(void) {
    glColor3f(0.9, 0.8, 0.6);  //man
    glPushMatrix();
    glTranslatef(-1 + (manWalk * 0.32), -0.46, -0.6);
    glutSolidSphere(0.11, 29, 90);
    glPopMatrix();

    glColor3f(0.9, 0.8, 0.6);
    glLineWidth(5);
    glBegin(GL_LINES);
    glVertex2f(-0.80, -0.44);
    glVertex2f(-0.72, -0.44);
    glEnd();

    glLineWidth(20);
    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(-0.80, -0.48);
    glVertex2f(-0.90, -0.55);
    glVertex2f(-0.72, -0.48);
    glVertex2f(-0.61, -0.55);

    glLineWidth(15);
    glColor3f(0, 0, 0);
    glVertex2f(-0.81, -0.80);
    glVertex2f(-0.77, -0.80);
    glVertex2f(-0.75, -0.80);
    glVertex2f(-0.71, -0.80);

    glLineWidth(20);
    glColor3f(0.9, 0.8, 0.6);
    glVertex2f(-0.81, -0.78);
    glVertex2f(-0.77, -0.78);
    glVertex2f(-0.75, -0.78);
    glVertex2f(-0.71, -0.78);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex2f(-0.85, -0.45);
    glVertex2f(-0.67, -0.45);
    glVertex2f(-0.67, -0.77);
    glVertex2f(-0.85, -0.77);
    glEnd();
}
void Traawih(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(transValueX, transValueY, transValueZ, 0, 0, 0, 0, 1, 0);
    glBindTexture(GL_TEXTURE_2D, myTexture1);
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    glNormal3d(0, 0, 1);
    glTexCoord2f(0, 0); glVertex3f(-1, -1, 0);
    glTexCoord2f(1, 0); glVertex3f(1, -1, 0);
    glTexCoord2f(1, 1); glVertex3f(1, 1, 0);
    glTexCoord2f(0, 1); glVertex3f(-1, 1, 0);
    glEnd();

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(manWalk, 0, 0);

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glPushMatrix();
    glTranslatef(manWalk, 0, 0);
    manMosque();
    glColor4f(1, 1, 1, 1);
    glPopMatrix();

    glutSwapBuffers();
    glFlush();
}

void mouthAkhbar() {
    glPointSize(5);
    glBegin(GL_POINTS);
    glColor3f(0.8, 0, 0.2);
    glVertex2f(0.0, 0.47);
    glEnd();
}

/*void init1() {
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
    /////////////////////////////////////////
}*/
/*void light(void) {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    //light
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
    /////////////////////////////////////////
    glColor3f(0.5, 0.5, 0.8);
    glEnable(GL_DEPTH_TEST);
    glutSolidTorus(0.137, 0.42, 10, 10); //purple tara size
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    /////////////////////////////////////////
    glFlush();
}*/
void sala(void) {



    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //color of wall

    glColor3f(0.88627450980392, 0.7843137254902, 0.74901960784314);

    glRectf(-1.0f, 1.0f, 1.0f, 0.1f);

    glColor3f(0.76862745098039, 0.77647058823529, 0.8078431372549);

    glRectf(-1.0f, 0.1f, 1.0f, -1.0f);



    glLineWidth(1);
    glBegin(GL_LINES);
    glColor3f(0.0, 0.0, 0.0);
    glVertex2f(-1, 0.1);
    glVertex2f(1, 0.1);
    glEnd();







    //------------------------------------

    //furniture

    glColor3f(0.07843137254902, 0.36470588235294, 0.45882352941176);

    glRectf(-0.80f, -0.10f, 0.10f, -0.5f);

    glRectf(0.80f, -0.10f, 0.20f, -0.5f);

    glRectf(-0.83f, -0.20f, 0.13f, -0.5f);

    glRectf(0.83f, -0.20f, 0.17f, -0.5f);



    glLineWidth(2);

    glBegin(GL_LINES);

    glColor3f(0.0, 0.0, 0.0);

    glVertex2f(-0.80, -0.10);

    glVertex2f(0.10, -0.1);

    glVertex2f(-0.83, -0.50);

    glVertex2f(0.13, -0.50);

    glVertex2f(0.80, -0.10);

    glVertex2f(0.20, -0.1);

    glVertex2f(0.83, -0.50);

    glVertex2f(0.17, -0.50);

    glEnd();



    glLineWidth(3);

    glBegin(GL_LINES);

    glColor3f(0.0, 0.0, 0.0);

    glVertex2f(-0.83, -0.20);

    glVertex2f(0.13, -0.20);

    glVertex2f(0.83, -0.20);

    glVertex2f(0.17, -0.20);

    glVertex2f(-0.80, -0.50);

    glVertex2f(-0.80, -0.10);

    glVertex2f(0.20, -0.50);

    glVertex2f(0.20, -0.10);

    glVertex2f(0.10, -0.50);

    glVertex2f(0.10, -0.10);

    glVertex2f(0.80, -0.50);

    glVertex2f(0.80, -0.10);

    glEnd();



    glLineWidth(1);

    glBegin(GL_LINES);

    glVertex2f(0.83, -0.50);

    glVertex2f(0.83, -0.20);

    glVertex2f(0.13, -0.50);

    glVertex2f(0.13, -0.20);

    glVertex2f(0.17, -0.50);

    glVertex2f(0.17, -0.20);

    glVertex2f(-0.83, -0.50);

    glVertex2f(-0.83, -0.20);

    glVertex2f(-0.35, -0.1);

    glVertex2f(-0.35, -0.20);

    glVertex2f(0.5, -0.1);

    glVertex2f(0.5, -0.20);

    glEnd();







    //------------------------------------

    //table



    glBegin(GL_QUADS);

    glColor3f(0.7, 0.7, 0.7);

    glVertex2f(0.50, 0.3);

    glVertex2f(-0.5, 0.3);

    glVertex2f(-0.5, 0.1);

    glVertex2f(0.50, 0.1);

    glEnd();



    glLineWidth(1);

    glBegin(GL_LINES);

    glColor3f(0.0, 0.0, 0.0);

    glVertex2f(0.0, 0.2);

    glColor3f(0.0, 0.0, 0.0);

    glVertex2f(0.0, 0.1);



    glEnd();

    glLineWidth(1);

    glBegin(GL_LINES);

    glColor3f(0.0, 0.0, 0.0);

    glVertex2f(0.50, 0.2);

    glColor3f(0.0, 0.0, 0.0);

    glVertex2f(-0.5, 0.2);

    glEnd();

    //-----------------------------------------------

    //television

    glBegin(GL_QUADS);

    glColor3f(0.0, 0.0, 0.0);

    glVertex2f(0.3, 0.6);

    glVertex2f(-0.3, 0.6);

    glVertex2f(-0.3, 0.3);

    glVertex2f(0.3, 0.3);

    glEnd();

    //--------------------------- ÇáãÐíÚ
    glColor3f(0.9, 0.8, 0.6);
    glPushMatrix();
    glTranslatef(0, 0.5, 0);
    glutSolidSphere(0.06, 35, 10);

    glColor3f(1, 1, 1);
    glTranslatef(0.02, 0.009, 0);
    glutSolidSphere(0.01, 35, 5);

    glColor3f(1, 1, 1);
    glTranslatef(-0.05, -0.002, 0);
    glutSolidSphere(0.01, 35, 5);
    //---

    glColor3f(0, 0, 0);
    glTranslatef(0.05, 0, 0);
    glutSolidSphere(0.005, 25, 5);

    glTranslatef(-0.05, 0, 0);
    glutSolidSphere(0.005, 25, 5);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();


    glBegin(GL_QUADS);
    glColor3f(1, 1, 0.47843137254902);
    glVertex2f(0.05, 0.45);
    glVertex2f(-0.05, 0.45);
    glVertex2f(-0.05, 0.30);
    glVertex2f(0.05, 0.30);
    glColor4f(1, 1, 1, 1);
    glEnd();



    //----------------------------------------------

    //lamb

    glLineWidth(2);

    glBegin(GL_LINES);

    glColor3f(0.0, 0.0, 0.0);

    glVertex2f(-0.6, 0.1);

    glColor3f(0.0, 0.0, 0.0);

    glVertex2f(-0.6, 0.5);

    glEnd();

    glPointSize(10);

    glBegin(GL_POINTS);

    glColor3f(1.0, 1.0, 0.0);

    glVertex2f(-0.6, 0.5);

    glEnd();


    glBegin(GL_TRIANGLES);

    glColor3f(1, 1, 0);

    glVertex2f(-0.6, 0.5);

    glColor4f(0.91, 0.76, 0.65, 0.5);

    glVertex2f(-0.4, 0.2);

    glColor4f(1, 1, 1, 0);

    glVertex2f(-0.8, 0.2);

    glEnd();



    glBegin(GL_TRIANGLES);

    glColor3f(0.91, 0.76, 0.65);

    glVertex2f(-0.6, 0.6);

    glColor4f(0, 0.76, 0.65, 0.5);

    glVertex2f(-0.5, 0.4);

    glColor4f(1, 1, 1, 1);

    glVertex2f(-0.7, 0.4);

    glEnd();

    //--------------------------------------



    //Books



    glLineWidth(15);



    glBegin(GL_LINES);

    glColor3f(0.8, 0.7, 0.5);

    glVertex2f(-0.4, 0.1);

    glVertex2f(-0.4, 0.19);

    glColor3f(0.1, 0.6, 0.6);

    glVertex2f(-0.35, 0.1);

    glVertex2f(-0.35, 0.19);



    glColor3f(0.43137254901961, 0.71764705882353, 0.81176470588235);

    glVertex2f(-0.25, 0.1);

    glVertex2f(-0.31, 0.19);

    glEnd();



    glLineWidth(4);

    glBegin(GL_LINES);

    glColor3f(0, 0, 0);

    glVertex2f(-0.43, 0.13);

    glVertex2f(-0.38, 0.13);

    glVertex2f(-0.33, 0.13);

    glVertex2f(-0.39, 0.13);

    glVertex2f(-0.27, 0.16);

    glVertex2f(-0.31, 0.16);

    glEnd();



    glLineWidth(1);

    glBegin(GL_LINES);

    glColor3f(0, 0, 0);

    glVertex2f(-0.38, 0.10);

    glVertex2f(-0.38, 0.19);

    glVertex2f(-0.43, 0.10);

    glVertex2f(-0.43, 0.19);

    glVertex2f(-0.33, 0.10);

    glVertex2f(-0.33, 0.19);

    glVertex2f(-0.43, 0.19);

    glVertex2f(-0.33, 0.19);

    glVertex2f(-0.43, 0.10);

    glVertex2f(-0.33, 0.10);

    glVertex2f(-0.23, 0.1);

    glVertex2f(-0.29, 0.19);

    glVertex2f(-0.27, 0.1);

    glVertex2f(-0.33, 0.19);

    glVertex2f(-0.29, 0.19);

    glVertex2f(-0.33, 0.19);

    glVertex2f(-0.27, 0.1);

    glVertex2f(-0.23, 0.1);

    glEnd();



    //-----------------------------------------------



    //Box



    glBegin(GL_QUADS);

    glColor3f(0, 0.7, 0.7);

    glVertex2f(0.45, 0.17);

    glVertex2f(0.25, 0.17);

    glVertex2f(0.25, 0.1);

    glVertex2f(0.45, 0.1);

    glVertex2f(0.22, 0.17);

    glVertex2f(0.04, 0.17);

    glVertex2f(0.04, 0.1);

    glVertex2f(0.22, 0.1);

    glEnd();



    glLineWidth(9);

    glBegin(GL_LINES);

    glColor3f(0, 0.0, 0.0);

    glVertex2f(0.24, 0.18);

    glVertex2f(0.46, 0.18);

    glVertex2f(0.03, 0.18);

    glVertex2f(0.23, 0.18);

    glEnd();

    //-----------------------------------------------



    //people

    glColor3f(0.9, 0.8, 0.6);  //man

    glPushMatrix();

    glTranslatef(-0.3, 0, -0.5);

    glutSolidSphere(0.1, 40, 10);

    glPopMatrix();



    glColor3f(0, 0, 0);  //hair-man

    glPushMatrix();

    glTranslatef(-0.3, 0.02, -0.5);

    glutSolidSphere(0.1, 10, 100);

    glPopMatrix();



    glColor3f(0.9, 0.8, 0.6);  //woman

    glPushMatrix();

    glTranslatef(0.4, 0, -0.5);

    glutSolidSphere(0.1, 40, 10);

    glPopMatrix();



    glColor3f(0.5, 0.3, 0.1);  //hair

    glPushMatrix();

    glTranslatef(0.4, 0.02, -0.5);

    glutSolidSphere(0.1, 10, 100);

    glPopMatrix();



    glPointSize(10);  //ÈßáÉ

    glBegin(GL_POINTS);

    glColor3f(1.0, 1.0, 0.0);

    glVertex2f(0.4, -0.02);

    glEnd();

    glLineWidth(10);  //Ðíá ÇáÍÕÇä

    glBegin(GL_LINES);
    glColor3f(0.5, 0.3, 0.2);
    glVertex2f(0.4, -0.02);
    glVertex2f(0.4, -0.2);
    glEnd();

    glPushMatrix();
    glScalef(mouthTalk, mouthTalk, 1);
    mouthAkhbar();
    glColor4f(1, 1, 1, 1);
    glPopMatrix();

    //-----------------------------------------------
    glFlush();
    glutSwapBuffers();
}

void womanKitchen() {
    //woman
    glColor3f(1, 1, 0.47843137254902);
    glBegin(GL_QUADS);
    glVertex2f(0.37, -0.12);
    glVertex2f(0.19, -0.12);
    glVertex2f(0.19, -0.35);
    glVertex2f(0.37, -0.35);

    glVertex2f(0.37, -0.35);
    glVertex2f(0.19, -0.35);
    glVertex2f(0.14, -0.70);
    glVertex2f(0.44, -0.70);


    glColor3f(0.9, 0.8, 0.6);
    glVertex2f(0.23, 0);
    glVertex2f(0.33, 0);
    glVertex2f(0.33, -0.12);
    glVertex2f(0.23, -0.12);
    glEnd();


    glColor3f(0.9, 0.8, 0.6);
    glLineWidth(15);
    glBegin(GL_LINES);
    glVertex2f(0.24, -0.70);
    glVertex2f(0.24, -0.90);
    glVertex2f(0.35, -0.70);
    glVertex2f(0.35, -0.90);
    glVertex2f(0.13, -0.21);
    glVertex2f(0.17, -0.21);
    glVertex2f(0.39, -0.21);
    glVertex2f(0.43, -0.21);
    glLineWidth(20);
    glColor3f(1, 1, 0.47843137254902);
    glVertex2f(0.15, -0.20);
    glVertex2f(0.20, -0.12);
    glVertex2f(0.41, -0.20);
    glVertex2f(0.36, -0.12);

    glLineWidth(15);
    glColor3f(0, 0, 0);
    glVertex2f(0.21, -0.90);
    glVertex2f(0.27, -0.90);
    glVertex2f(0.32, -0.90);
    glVertex2f(0.38, -0.90);
    glEnd();

    glColor3f(0.9, 0.8, 0.6); //head
    glPushMatrix();
    glTranslatef(0.28, 0.01, -0.5);
    glutSolidSphere(0.1, 40, 10);
    glPopMatrix();
    glColor3f(0.5, 0.3, 0.1);  //hair
    glPushMatrix();
    glTranslatef(0.28, 0.03, -0.5);
    glutSolidSphere(0.1, 10, 100);
    glPopMatrix();
    glPointSize(10);  //ÈßáÉ

    glBegin(GL_POINTS);
    glColor3f(1.0, 1.0, 0.0);
    glVertex2f(0.28, -0.02);
    glEnd();
    glLineWidth(10);  //Ðíá ÇáÍÕÇä
    glBegin(GL_LINES);
    glColor3f(0.5, 0.3, 0.2);
    glVertex2f(0.28, -0.02);
    glVertex2f(0.28, -0.2);
    glEnd();
    //ãÑíáÉ
    glLineWidth(6);
    glColor3f(0.49411764705882, 0.84313725490196, 0.74901960784314);
    glBegin(GL_LINES);
    glVertex2f(0.19, -0.33);
    glVertex2f(0.37, -0.33);
    glVertex2f(0.33, -0.38);
    glVertex2f(0.29, -0.33);
    glVertex2f(0.25, -0.38);
    glVertex2f(0.29, -0.33);
    glVertex2f(0.19, -0.30);
    glVertex2f(0.14, -0.70);
    glVertex2f(0.37, -0.30);
    glVertex2f(0.45, -0.70);
    glEnd();

    /*glutSwapBuffers();
    glFlush();*/
}




void kitchen(void) {


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glColor3f(0.8, 0.9, 1);

    glBegin(GL_QUADS);

    glVertex2f(0.50, -1);

    glVertex2f(0.95, -1);

    glVertex2f(0.95, 0.80);

    glVertex2f(0.50, 0.80);

    //--------------------------------------------





    //----------------------------------------------

    glColor3f(0.8, 0.9, 1); //ÇáÏÑÌ ÇáÇæá

    glVertex2f(0.50, -0.51);

    glVertex2f(0.95, -0.51);

    glVertex2f(0.95, -0.29);

    glVertex2f(0.50, -0.29);

    //----------------------------------------------





    glColor3f(0.8, 0.9, 1); //ÇáÏÑÌ ÇáËÇäí 

    glVertex2f(0.50, -0.71);

    glVertex2f(0.95, -0.71);

    glVertex2f(0.95, -0.51);

    glVertex2f(0.50, -0.51);

    //----------------------------------------------





    glColor3f(0.8, 0.9, 1); //ÇáÏÑÌ ÇáËÇáË 

    glVertex2f(0.50, -0.92);

    glVertex2f(0.95, -0.92);

    glVertex2f(0.95, -0.72);

    glVertex2f(0.50, -0.72);

    //---------------------------------------------





    glColor3f(0.6, 0.6, 0.6);//ÇáÊÍÏíÏ

    glVertex2f(0.73, 0.10);





    glVertex2f(0.74, 0.10);//ÇáÏæáÇÈ ÇáãÞÓæã

    glVertex2f(0.74, 0.80);

    glVertex2f(0.73, 0.80);

    glVertex2f(0.50, -1);

    glVertex2f(0.51, -1);

    glVertex2f(0.51, 0.80);

    glVertex2f(0.50, 0.80);

    glVertex2f(0.96, -1);

    glVertex2f(0.95, -1);

    glVertex2f(0.95, 0.80);

    glVertex2f(0.96, 0.80);
    glVertex2f(0.50, 0.80);
    glVertex2f(0.96, 0.80);
    glVertex2f(0.96, 0.81);
    glVertex2f(0.50, 0.81);
    glVertex2f(0.50, -0.71);
    glVertex2f(0.95, -0.71);
    glVertex2f(0.95, -0.72);
    glVertex2f(0.50, -0.72);
    glVertex2f(0.50, -0.92);
    glVertex2f(0.95, -0.92);
    glVertex2f(0.95, -0.91);
    glVertex2f(0.50, -0.91);
    glVertex2f(0.50, -0.52);
    glVertex2f(0.95, -0.52);
    glVertex2f(0.95, -0.51);
    glVertex2f(0.50, -0.51);
    glVertex2f(0.50, -0.51);
    glVertex2f(0.95, -0.51);
    glVertex2f(0.95, -0.51);
    glVertex2f(0.50, -0.51);
    glVertex2f(0.50, -0.28);
    glVertex2f(0.95, -0.28);
    glVertex2f(0.95, -0.29);
    glVertex2f(0.50, -0.29);
    glVertex2f(0.51, -0.25);
    glVertex2f(0.95, -0.25);
    glVertex2f(0.95, -0.28);
    glVertex2f(0.51, -0.28);
    glVertex2f(0.51, 0.13);
    glVertex2f(0.95, 0.13);
    glVertex2f(0.95, 0.10);
    glVertex2f(0.51, 0.10);

    //---------------------------------ÇáãÓßÇÊ
    glColor3f(0.6, 0.6, 0.6);
    glVertex2f(0.66, -0.40);
    glVertex2f(0.80, -0.40);
    glVertex2f(0.80, -0.39);
    glVertex2f(0.66, -0.39);

    //
    glVertex2f(0.66, -0.61);
    glVertex2f(0.80, -0.61);
    glVertex2f(0.80, -0.60);
    glVertex2f(0.66, -0.60);

    //
    glVertex2f(0.66, -0.81);
    glVertex2f(0.80, -0.81);
    glVertex2f(0.80, -0.80);
    glVertex2f(0.66, -0.80);
    glVertex2f(0.68, 0.40);
    glVertex2f(0.70, 0.40);
    glVertex2f(0.70, 0.60);
    glVertex2f(0.68, 0.60);
    glVertex2f(0.79, 0.40);
    glVertex2f(0.77, 0.40);
    glVertex2f(0.77, 0.60);
    glVertex2f(0.79, 0.60);

    //ÇáÝÑä
    glColor4f(0.0, 0.0, 0.0, 0.5);
    glVertex2f(0.92, -0.18);
    glVertex2f(0.93, -0.18);
    glVertex2f(0.93, 0.05);
    glVertex2f(0.92, 0.05);
    glVertex2f(0.57, -0.15);
    glVertex2f(0.87, -0.15);
    glVertex2f(0.87, 0.0);
    glVertex2f(0.57, 0.0);

    //
    glColor3f(0, 0, 0);//ÊÍÏíÏ ãÑÈÚ ÇáÝÑä ÈÇáÇÓæÏ , ÇÐÇ ÞãÊ ÈÓæíå
    glVertex2f(0.58, -0.15);
    glVertex2f(0.88, -0.15);
    glVertex2f(0.88, -0.15);
    glVertex2f(0.58, -0.15);
    glEnd();

    //ËáÇÌÉ
    glColor3f(0.7, 0.7, 0.7);
    glBegin(GL_QUADS);
    glVertex2f(-0.4, -1);
    glVertex2f(-1, -1);
    glVertex2f(-1, 0.8);
    glVertex2f(-0.4, 0.8);
    glEnd();
    glLineWidth(1);
    glBegin(GL_LINES);
    glColor3f(0, 0, 0);
    glVertex2f(-0.4, 0.3);
    glColor3f(0, 0, 0);
    glVertex2f(-1, 0.3);
    glEnd();
    glLineWidth(5);
    glBegin(GL_LINES);
    glColor3f(0.4, 0.4, 0.4);
    glVertex2f(-0.45, 0.7);
    glColor3f(0.4, 0.4, 0.4);
    glVertex2f(-0.45, 0.4);
    glEnd();
    glLineWidth(5);
    glBegin(GL_LINES);
    glColor3f(0.4, 0.4, 0.4);
    glVertex2f(-0.45, -0.5);
    glColor3f(0.4, 0.4, 0.4);
    glVertex2f(-0.45, 0.2);
    glEnd();
    glLineWidth(1);
    glBegin(GL_LINES);
    glColor3f(0, 0, 0);
    glVertex2f(-0.4, 0.8);
    glColor3f(0, 0, 0);
    glVertex2f(-0.4, -1);
    glEnd();

    glLineWidth(1);
    glBegin(GL_LINES);
    glColor3f(0, 0, 0);
    glVertex2f(-0.4, 0.8);
    glColor3f(0, 0, 0);
    glVertex2f(-1, 0.8);
    glEnd();

    glColor3f(0.8, 0.9, 1);  //ÇáãÛÓáÉ
    glBegin(GL_QUADS);
    glVertex2f(-0.4, -1);
    glVertex2f(0, -1);
    glVertex2f(0, -0.2);
    glVertex2f(-0.4, -0.2);
    glEnd();

    glLineWidth(5);
    glBegin(GL_LINES);
    glColor3f(0.4, 0.4, 0.4);
    glVertex2f(-0.05, -0.4);
    glColor3f(0.4, 0.4, 0.4);
    glVertex2f(-0.05, -0.7);
    glEnd();
    glLineWidth(1);
    glBegin(GL_LINES);
    glColor3f(0.4, 0.4, 0.4);
    glVertex2f(0, -0.2);
    glColor3f(0.4, 0.4, 0.4);
    glVertex2f(-0.4, -0.2);
    glEnd();

    glColor3f(1, 1, 1);  //ÇáãÛÓáÉ
    glBegin(GL_QUADS);
    glVertex2f(-0.4, -0.22);
    glVertex2f(0, -0.22);
    glVertex2f(0, -0.2);
    glVertex2f(-0.4, -0.2);
    glEnd();
    glLineWidth(1);
    glBegin(GL_LINES);
    glColor3f(0.4, 0.4, 0.4);
    glVertex2f(0, -0.22);
    glColor3f(0.4, 0.4, 0.4);
    glVertex2f(-0.4, -0.22);
    glEnd();

    glPointSize(8);
    glBegin(GL_POINTS);
    glColor3f(0.6, 0.6, 0.6);
    glVertex2f(-0.25, -0.19);
    glEnd();

    glPointSize(8);
    glBegin(GL_POINTS);
    glColor3f(0.6, 0.6, 0.6);
    glVertex2f(-0.35, -0.19);
    glEnd();

    glLineWidth(8);
    glBegin(GL_LINES);
    glColor3f(0.6, 0.6, 0.6);
    glVertex2f(-0.30, -0.2);
    glColor3f(0.6, 0.6, 0.6);
    glVertex2f(-0.30, -0.1);
    glEnd();

    glLineWidth(8);
    glBegin(GL_LINES);
    glColor3f(0.6, 0.6, 0.6);
    glVertex2f(-0.31, -0.1);
    glColor3f(0.6, 0.6, 0.6);
    glVertex2f(-0.20, -0.1);
    glEnd();

    glLineWidth(1);
    glBegin(GL_LINES);
    glColor3f(0, 0, 0);
    glVertex2f(0, -0.2);
    glColor3f(0, 0, 0);
    glVertex2f(0, -1);
    glEnd();

    //ÇáÝÑä
    glColor3f(0.7, 0.7, 0.7);
    glBegin(GL_QUADS);
    glVertex2f(0, -1);
    glVertex2f(0.5, -1);
    glVertex2f(0.5, -0.1);
    glVertex2f(0, -0.1);
    glEnd();

    glLineWidth(5);
    glBegin(GL_LINES);
    glColor3f(0.4, 0.4, 0.4);
    glVertex2f(0.09, -0.35);
    glVertex2f(0.43, -0.35);
    glEnd();

    glLineWidth(20);
    glBegin(GL_LINES);
    glColor3f(0, 0, 0);
    glVertex2f(0, -0.26);
    glVertex2f(0.51, -0.26);
    glEnd();

    glColor4f(0, 0, 0, 0.1);
    glBegin(GL_QUADS);
    glVertex2f(0.33, -0.20);
    glVertex2f(0.19, -0.20);
    glVertex2f(0.19, -0.13);
    glVertex2f(0.33, -0.13);
    glEnd();

    glColor4f(0, 0, 0, 0.4);
    glPushMatrix();
    glTranslatef(0.05, -0.16, -0.55);
    glutSolidSphere(0.03, 29, 100);
    glPopMatrix();
    glColor4f(0, 0, 0, 0.4);
    glPushMatrix();
    glTranslatef(0.13, -0.16, -0.55);
    glutSolidSphere(0.03, 29, 100);
    glPopMatrix();
    glColor4f(0, 0, 0, 0.4);
    glPushMatrix();
    glTranslatef(0.37, -0.16, -0.55);
    glutSolidSphere(0.03, 29, 100);
    glPopMatrix();
    glColor4f(0, 0, 0, 0.4);
    glPushMatrix();
    glTranslatef(0.45, -0.16, -0.55);
    glutSolidSphere(0.03, 29, 100);
    glPopMatrix();

    //ÊÍÏíÏ ÇáÝÑä
    glLineWidth(1);
    glBegin(GL_LINES);
    glColor3f(0, 0, 0);
    glVertex2f(0, -1);
    glVertex2f(0.5, -1);
    glVertex2f(0, -0.1);
    glVertex2f(0.5, -0.1);
    glVertex2f(0, -0.1);
    glVertex2f(0, -1);
    glVertex2f(0.51, -0.1);
    glVertex2f(0.51, -1);
    glVertex2f(0.43, -0.5);
    glVertex2f(0.11, -0.5);
    glVertex2f(0.43, -0.7);
    glVertex2f(0.11, -0.7);
    glVertex2f(0.43, -0.5);
    glVertex2f(0.43, -0.7);
    glVertex2f(0.11, -0.5);
    glVertex2f(0.11, -0.7);
    glVertex2f(0.33, -0.20);
    glVertex2f(0.19, -0.20);
    glVertex2f(0.33, -0.13);
    glVertex2f(0.19, -0.13);
    glVertex2f(0.33, -0.20);
    glVertex2f(0.33, -0.13);
    glVertex2f(0.19, -0.20);
    glVertex2f(0.19, -0.13);
    glEnd();

    glColor4f(0.0, 0.0, 0.0, 0.5);
    glBegin(GL_QUADS);
    glVertex2f(0.11, -0.5);
    glVertex2f(0.43, -0.5);
    glVertex2f(0.43, -0.7);
    glVertex2f(0.11, -0.7);
    glEnd();

    //ÇáÃÑÝÝ
    glLineWidth(1);
    glBegin(GL_LINES);
    glVertex2f(0.03, 0.30);
    glVertex2f(0.47, 0.30);
    glVertex2f(0.03, 0.40);
    glVertex2f(0.47, 0.40);
    glVertex2f(0.03, 0.40);
    glVertex2f(0.03, 0.30);
    glVertex2f(0.47, 0.40);
    glVertex2f(0.47, 0.30);

    glEnd();

    glColor3f(0.6, 0.6, 0.6);
    glLineWidth(8);
    glBegin(GL_LINES);
    glVertex2f(0.10, 0.35);
    glVertex2f(0.10, 0.20);
    glVertex2f(0.25, 0.35);
    glVertex2f(0.25, 0.20);
    glVertex2f(0.40, 0.35);
    glVertex2f(0.40, 0.20);
    glEnd();
    glPushMatrix();
    glTranslatef(0.10, 0.20, -0.55);
    glutSolidSphere(0.06, 29, 100);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.25, 0.20, -0.55);
    glutSolidSphere(0.06, 29, 100);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.40, 0.20, -0.55);
    glutSolidSphere(0.06, 29, 100);
    glPopMatrix();

    //ãäÔÝÉ
    glColor3f(0.96470588235294, 0.65490196078431, 0.68627450980392);
    glBegin(GL_QUADS);
    glVertex2f(0.12, -0.33);
    glVertex2f(0.27, -0.33);
    glVertex2f(0.27, -0.6);
    glVertex2f(0.12, -0.6);
    //the window
    glColor3f(0.8, 0.9, 1);
    glVertex2f(-0.03, -0.05);
    glVertex2f(-0.33, -0.05);
    glVertex2f(-0.33, 0.35);
    glVertex2f(-0.03, 0.35);
    glEnd();
    glColor3f(0, 0, 0);
    glLineWidth(1);
    glBegin(GL_LINES);
    glVertex2f(-0.03, 0.35);
    glVertex2f(-0.33, 0.35);
    glVertex2f(-0.03, -0.05);
    glVertex2f(-0.33, -0.05);
    glVertex2f(-0.03, 0.35);
    glVertex2f(-0.03, -0.05);
    glVertex2f(-0.33, 0.35);
    glVertex2f(-0.33, -0.05);
    glEnd();
    glColor3f(0.96470588235294, 0.65490196078431, 0.68627450980392);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.38, 0.37);
    glVertex2f(-0.15, 0.37);
    glVertex2f(-0.38, 0.05);
    glVertex2f(0.02, 0.37);
    glVertex2f(-0.20, 0.37);
    glVertex2f(0.02, 0.05);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(-0.38, -0.03);
    glVertex2f(-0.35, -0.03);
    glVertex2f(-0.35, 0.12);
    glVertex2f(-0.38, 0.12);

    glVertex2f(0.02, -0.03);
    glVertex2f(-0.01, -0.03);
    glVertex2f(-0.01, 0.12);
    glVertex2f(0.02, 0.12);
    glEnd();
    glColor3f(0, 0, 0);
    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex2f(-0.01, 0.10);
    glVertex2f(0.02, 0.10);
    glVertex2f(-0.38, 0.10);
    glVertex2f(-0.35, 0.10);
    glEnd();
    glLineWidth(1);
    glBegin(GL_LINES);
    glVertex2f(-0.38, 0.37);
    glVertex2f(0.02, 0.37);
    glVertex2f(-0.38, 0.37);
    glVertex2f(-0.38, -0.03);
    glVertex2f(-0.38, -0.03);
    glVertex2f(-0.35, -0.03);
    glVertex2f(-0.01, -0.03);
    glVertex2f(0.02, -0.03);
    glVertex2f(0.02, -0.03);
    glVertex2f(0.02, 0.37);
    glVertex2f(-0.01, -0.03);
    glVertex2f(-0.01, 0.10);
    glVertex2f(-0.35, 0.10);
    glVertex2f(-0.35, -0.03);
    glVertex2f(-0.35, 0.10);
    glVertex2f(-0.17, 0.34);
    glVertex2f(-0.01, 0.10);
    glVertex2f(-0.17, 0.34);
    glEnd();

    glColor3f(0.76862745098039, 0.77647058823529, 0.8078431372549);
    glRectf(-1.0f, -0.87f, 1.0f, -1.0f);
    glLineWidth(1);
    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
    glVertex2f(-1, -0.87);
    glVertex2f(1, -0.87);
    glEnd();

    glPushMatrix();
    glTranslatef(womanWalk, 0, 0);
    womanKitchen();
    glPopMatrix();

    glutSwapBuffers();
    glFlush();
}

void home(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);
    glColor3f(0.1, 0.1, 0.2);
    glVertex2f(-600, -600);
    glVertex2f(-600, 600);
    glVertex2f(600, 600);
    glVertex2f(600, -600);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.7, 0.6, 0.4);
    glVertex2f(-0.6, 0.6);
    glVertex2f(0.6, 0.6);
    glVertex2f(0.0, 0.8);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(0.6, 0.6);
    glVertex2f(-0.6, 0.6);
    glVertex2f(-0.6, -0.8);
    glVertex2f(0.6, -0.8);
    glEnd();


    glBegin(GL_QUADS);
    glColor3f(0.7, 0.9, 0.9);
    glVertex2f(0.5, 0.4);
    glVertex2f(0.2, 0.4);
    glVertex2f(0.2, 0.2);
    glVertex2f(0.5, 0.2);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(-0.5, 0.4);
    glVertex2f(-0.2, 0.4);
    glVertex2f(-0.2, 0.2);
    glVertex2f(-0.5, 0.2);
    glEnd();


    glBegin(GL_QUADS);
    glVertex2f(0.5, 0.0);
    glVertex2f(0.2, 0.0);
    glVertex2f(0.2, -0.2);
    glVertex2f(0.5, -0.2);
    glEnd();


    glBegin(GL_QUADS);
    glVertex2f(-0.5, 0.0);
    glVertex2f(-0.2, 0.0);
    glVertex2f(-0.2, -0.2);
    glVertex2f(-0.5, -0.2);
    glEnd();



    glBegin(GL_QUADS);
    glVertex2f(0.2, -0.4);
    glVertex2f(-0.1, -0.4);
    glVertex2f(-0.1, -0.99);
    glVertex2f(0.2, -0.99);
    glEnd();



    glBegin(GL_QUADS);
    glColor3f(0.5, 0.5, 0.5);
    glVertex2f(1, -0.7);
    glVertex2f(-1, -0.7);
    glVertex2f(-1, -0.99);
    glVertex2f(1, -0.99);
    glEnd();


    glLineWidth(4);
    glLineStipple(2, 0x00FF);
    glEnable(GL_LINE_STIPPLE);
    glBegin(GL_LINES);
    glColor3f(0, 0, 0);
    glVertex2f(1, -0.85);
    glVertex2f(-1, -0.85);
    glEnd();
    glDisable(GL_LINE_STIPPLE);

    glLineWidth(40);
    glBegin(GL_LINES);// ÊÍÏíÏ ÇáÈíÊ
    glColor3f(0.7, 0.5, 0.2);
    glVertex2f(-0.6, 0.6);
    glVertex2f(0, 0.8);
    glVertex2f(0.6, 0.6);
    glVertex2f(0, 0.8);
    glVertex2f(0.6, -0.7);
    glVertex2f(0.6, 0.6);
    glVertex2f(-0.6, -0.7);
    glVertex2f(-0.6, 0.6);
    glEnd();


    glLineWidth(2);
    glBegin(GL_LINES);// ÇáÊÍÏíÏ ÇáÏÇÎáí 
    glVertex2f(0.5, 0.4);
    glVertex2f(0.2, 0.4);
    glVertex2f(0.5, 0.4);
    glVertex2f(0.5, 0.2);
    glVertex2f(0.5, 0.2);
    glVertex2f(0.2, 0.2);
    glVertex2f(0.2, 0.2);
    glVertex2f(0.2, 0.4);//1
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(0.49, 0.39);
    glVertex2f(0.21, 0.21);

    glColor3f(0.7, 0.5, 0.2);
    glVertex2f(-0.5, 0.4);
    glVertex2f(-0.2, 0.4);
    glVertex2f(-0.5, 0.4);
    glVertex2f(-0.5, 0.2);
    glVertex2f(-0.5, 0.2);
    glVertex2f(-0.2, 0.2);
    glVertex2f(-0.2, 0.2);
    glVertex2f(-0.2, 0.4);//2
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(-0.21, 0.39);
    glVertex2f(-0.49, 0.21);

    glColor3f(0.7, 0.5, 0.2);
    glVertex2f(0.5, 0.0);
    glVertex2f(0.2, 0.0);
    glVertex2f(0.5, 0.0);
    glVertex2f(0.5, -0.2);
    glVertex2f(0.5, -0.2);
    glVertex2f(0.2, -0.2);
    glVertex2f(0.2, -0.2);
    glVertex2f(0.2, 0.0);//3
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(0.49, -0.006);
    glVertex2f(0.21, -0.19);

    glColor3f(0.7, 0.5, 0.2);
    glVertex2f(-0.5, 0.0);
    glVertex2f(-0.2, 0.0);
    glVertex2f(-0.5, 0.0);
    glVertex2f(-0.5, -0.2);
    glVertex2f(-0.5, -0.2);
    glVertex2f(-0.2, -0.2);
    glVertex2f(-0.2, -0.2);
    glVertex2f(-0.2, 0.0);//4
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(-0.21, -0.006);
    glVertex2f(-0.49, -0.19);

    glColor3f(0.7, 0.5, 0.2);
    glVertex2f(0.2, -0.4);
    glVertex2f(0.2, -0.7);
    glVertex2f(-0.1, -0.7);
    glVertex2f(-0.1, -0.4);
    glVertex2f(-0.1, -0.4);
    glVertex2f(0.2, -0.4);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(0.05, -0.41);
    glVertex2f(0.05, -0.7);
    glEnd();

    glutSwapBuffers();
    glFlush();


}

void fanos() {

    glColor3f(1, 1, 0);
    glBegin(GL_TRIANGLES);
    glVertex2f(0.2, 0.0);
    glVertex2f(0.1, -0.3);
    glVertex2f(0.0, -0.2);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.2, 0.0);
    glVertex2f(-0.1, -0.3);
    glVertex2f(0.0, -0.2);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(1, 0, 0);
    glVertex2f(0.2, 0.0);
    glVertex2f(-0.2, 0.0);
    glVertex2f(0.0, -0.2);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(1, 0, 0);
    glVertex2f(0.1, -0.3);
    glVertex2f(0.0, -0.2);
    glVertex2f(-0.1, -0.3);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 1, 0);
    glVertex2f(0.25, 0.0);
    glVertex2f(-0.25, 0.0);
    glVertex2f(-0.25, 0.06);
    glVertex2f(0.25, 0.06);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(1, 0, 0);
    glVertex2f(0.0, 0.2);
    glVertex2f(0.2, 0.06);
    glVertex2f(-0.2, 0.06);
    glEnd();

    glColor3f(1, 1, 0);
    glPushMatrix();
    glTranslatef(0.0, 0.2, 0.01);
    glutSolidSphere(0.05, 9, 100);
    glPopMatrix();

    glBegin(GL_QUADS);
    glColor3f(1, 1, 0);
    glVertex2f(0.13, -0.29);
    glVertex2f(-0.13, -0.29);
    glVertex2f(-0.13, -0.33);
    glVertex2f(0.13, -0.33);
    glEnd();

    std::string text;
    text = "Hello ramadan";
    glColor3f(1.0, 1.0, 1.0);
    print_text(text.data(), text.size(), 490, 260);

}

void hilal(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBegin(GL_POLYGON);
    glColor3f(0.1, 0.1, 0.2);
    glVertex2f(-600, -600);
    glVertex2f(-600, 600);
    glVertex2f(600, 600);
    glVertex2f(600, -600);
    glEnd();
    glDisable(GL_LIGHTING);

    glPointSize(2.0f);
    glBegin(GL_POINTS);
    glColor3f(1, 1, 1);
    glVertex2f(0, 8);
    glVertex2f(-0.9, 0.9);
    glVertex2f(-0.9, -0.3);
    glVertex2f(-0.8, 0.6);
    glVertex2f(-0.7, -0.6);
    glVertex2f(-0.7, -0.7);
    glVertex2f(-0.5, 0.6);
    glVertex2f(-0.4, 0.6);
    glVertex2f(-0.2, 0.4);
    glVertex2f(-0.1, -0.6);
    glVertex2f(0.8, 0);
    glVertex2f(0.8, -0.8);
    glVertex2f(0.6, 0.6);
    glVertex2f(0.4, -0.5);
    glVertex2f(0.2, 0.3);
    glVertex2f(0.1, -0.6);
    glVertex2f(0.0, 0.8);
    glEnd();

    /////////////////////////////////////////

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    //light
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

    glPushMatrix();
    glTranslatef(-0.3, 0, -0.5);
    glutSolidSphere(0.5, 40, 10);        //hilal
    glPopMatrix();
    glDisable(GL_LIGHTING);

    glColor3f(0.1, 0.1, 0.2);
    glPushMatrix();
    glTranslatef(0, 0, -0.5);
    glutSolidSphere(0.5, 40, 5);        //sky
    glPopMatrix();


    glLineWidth(4);
    glBegin(GL_LINES);
    glColor3f(0, 0, 0);
    glVertex2f(0.0, 0.28);
    glVertex2f(-0.2, 0.43);
    glEnd();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glRotatef(_angle, 0, 1, 0);
    glRotatef(0, 0, 1, 0);
    fanos();
    glPopMatrix();

    glutSwapBuffers();
    glFlush();
}

void emam(void) {
    //head
    glColor3f(0.9, 0.8, 0.6);
    glPushMatrix();
    glTranslatef(0.1, -0.15, -0.6);
    glutSolidSphere(0.1, 29, 90);
    glPopMatrix();


    glBegin(GL_QUADS);
    //neck
    glVertex2f(0.05, -0.23);
    glVertex2f(0.15, -0.23);
    glVertex2f(0.15, -0.30);
    glVertex2f(0.05, -0.30);
    //feet
    glVertex2f(0.06, -0.73);
    glVertex2f(0.09, -0.73);
    glVertex2f(0.09, -0.76);
    glVertex2f(0.06, -0.76);

    glVertex2f(0.12, -0.73);
    glVertex2f(0.15, -0.73);
    glVertex2f(0.15, -0.76);
    glVertex2f(0.12, -0.76);
    //body
    glColor3f(1, 1, 1);
    glVertex2f(0.0, -0.26);
    glVertex2f(0.2, -0.26);
    glVertex2f(0.2, -0.73);
    glVertex2f(0.0, -0.73);
    //hand
    glVertex2f(0.2, -0.26);
    glVertex2f(0.22, -0.26);
    glVertex2f(0.22, -0.43);
    glVertex2f(0.2, -0.43);

    glVertex2f(-0.02, -0.26);
    glVertex2f(0.1, -0.26);
    glVertex2f(0.1, -0.43);
    glVertex2f(-0.02, -0.43);
    glEnd();

    glLineWidth(1);
    glBegin(GL_LINES);
    glColor3f(0, 0, 0);
    glVertex2f(-0.02, -0.26);
    glVertex2f(-0.02, -0.43);
    glVertex2f(-0.02, -0.43);
    glVertex2f(0.0, -0.43);
    glVertex2f(0.0, -0.43);
    glVertex2f(0.1, -0.41);
    glVertex2f(0.0, -0.3);
    glVertex2f(0.0, -0.40);
    glVertex2f(0.0, -0.40);
    glVertex2f(0.1, -0.38);
    glVertex2f(0.1, -0.38);
    glVertex2f(0.1, -0.41);
    //
    glVertex2f(0.2, -0.3);
    glVertex2f(0.2, -0.4);
    glVertex2f(0.22, -0.26);
    glVertex2f(0.22, -0.43);
    glVertex2f(0.2, -0.43);
    glVertex2f(0.22, -0.43);
    glVertex2f(0.2, -0.43);
    glVertex2f(0.11, -0.41);
    glVertex2f(0.2, -0.4);
    glVertex2f(0.11, -0.38);
    //
    glVertex2f(0.05, -0.26);
    glVertex2f(-0.02, -0.26);
    glVertex2f(0.15, -0.26);
    glVertex2f(0.22, -0.26);
    glVertex2f(0.2, -0.43);
    glVertex2f(0.2, -0.73);
    glVertex2f(0.0, -0.43);
    glVertex2f(0.0, -0.73);
    glVertex2f(0.0, -0.73);
    glVertex2f(0.2, -0.73);
    glEnd();

    glColor3f(0.9, 0.8, 0.6);
    glLineWidth(12);
    glBegin(GL_LINES);
    glVertex2f(0.11, -0.41);
    glVertex2f(0.11, -0.371);
    glEnd();
}

void pray(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(0.49019607843137, 0.050980392156863, 0.094117647058824);
    glRectf(-0.99f, 0.10f, 0.99f, -0.99f);
    glColor3f(0.92549019607843, 0.97647058823529, 0.72156862745098);
    glRectf(-0.99f, 0.10f, 0.99f, 0.99f);


    glPushMatrix();
    glTranslatef(0.1, 0.1, 0);
    emam();
    glTranslatef(0.25, 0, 0);
    emam();
    glTranslatef(0.25, 0, 0);
    emam();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-0.15, 0.1, 0);
    emam();
    glTranslatef(-0.25, 0, 0);
    emam();
    glTranslatef(-0.25, 0, 0);
    emam();
    glTranslatef(-0.25, 0, 0);
    emam();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0, 0, 0);
    emam();
    glPopMatrix();

    glutSwapBuffers();
    glFlush();
}

void update(int value) {
    _angle += 2;
    if (_angle > 360) {
        _angle -= 360;
    }
    glutPostRedisplay();
    glutTimerFunc(25, update, 0);
}

static void key(unsigned char keyPressed, int x, int y) {
    switch (keyPressed) {
    case 'w': womanWalk = womanWalk + 0.1;
        break;
    case 'W': womanWalk = womanWalk - 0.1;
        break;
    case 'm': manWalk = manWalk + 0.1;
        break;
    case 'e': mouthEat = mouthEat / 1.06;
        break;
    case 'E': mouthEat = 1;
        break;
    case '0': PlaySound(NULL, 0, 0); glutDisplayFunc(home); PlaySound(TEXT("ramadan-voice.wav"), NULL, SND_ASYNC);  glutMainLoop();
        break;
    case '2': glutDisplayFunc(sala); glutMainLoop();
        break;
    case '3': PlaySound(NULL, 0, 0); glutDisplayFunc(kitchen); PlaySound(TEXT("hello-ramadan.wav"), NULL, SND_ASYNC | SND_LOOP); glutMainLoop();
        break;
    case '4': init();  glutDisplayFunc(fotoor); glutMainLoop();
        break;
    case '5':  glutDisplayFunc(Traawih); glutMainLoop();
        break;
    case '6': glutDisplayFunc(pray); glutMainLoop();
        break;
    }
    glutPostRedisplay();
}

static void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_UP) {
            mouthTalk = mouthTalk / 1.01;
        }
    }
    if (button == GLUT_RIGHT_BUTTON) {
        if (state == GLUT_UP) {
            mouthTalk = 1;
        }
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitWindowSize(915, 915);
    glutInitWindowPosition(100, 100);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Ramadan");

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_BLEND);
    glClearColor(1, 1, 1, 1);
    womanWalk = 0;
    manWalk = 0;
    mouthEat = 1;
    mouthTalk = 1;

    glutDisplayFunc(hilal); PlaySound(TEXT("hello-ramadan.wav"), NULL, SND_ASYNC);
    glutMouseFunc(mouse);
    glutKeyboardFunc(key);
    glutTimerFunc(25, update, 0);

    glutMainLoop();
    return 0;
}