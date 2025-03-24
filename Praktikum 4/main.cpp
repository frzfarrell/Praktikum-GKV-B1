#include <GL/glut.h>
#include <cmath>

float angle = 0.0f, deltaAngle = 0.0f;
float x = 0.0f, y = 2.0f, z = 10.0f;
float lx = 0.0f, lz = -1.0f;
int deltaMove = 0;

void initLighting() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat light_pos[] = {1.0, 1.0, 1.0, 0.0};
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
}

void drawCube(float x, float y, float z, float sizeX, float sizeY, float sizeZ, float r, float g, float b) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(sizeX, sizeY, sizeZ);
    glColor3f(r, g, b);
    glutSolidCube(1.0);
    glPopMatrix();
}

void drawWheel(float x, float y, float z) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glColor3f(0.1, 0.1, 0.1);
    glutSolidTorus(0.2, 0.5, 10, 20);
    glPopMatrix();
}

void drawSedan() {
    // Bodi bawah (lebih panjang dan ramping untuk sedan)
    drawCube(0, 0, 0, 7.0, 1.2, 3.0, 0.8, 0.0, 0.0); // Merah gelap
    
    // Kabin
    drawCube(0, 1.5, 0, 4.5, 1.5, 2.5, 0.0, 0.0, 0.8); // Biru gelap
    
    // Kap mesin lebih landai
    drawCube(2.5, 0.8, 0, 2.5, 0.7, 2.5, 0.8, 0.0, 0.0); // Merah gelap
    
    // Bagasi lebih pendek
    drawCube(-2.8, 0.8, 0, 1.8, 0.7, 2.5, 0.8, 0.0, 0.0); // Merah gelap
    
    // Roda lebih proporsional
    drawWheel(-2.8, -0.75, 1.5);
    drawWheel(2.8, -0.75, 1.5);
    drawWheel(-2.8, -0.75, -1.5);
    drawWheel(2.8, -0.75, -1.5);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(x, y, z, x + lx, y, z + lz, 0.0, 1.0, 0.0);
    
    drawSedan();
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)w / (float)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void moveCamera(int dir) {
    x += dir * lx * 0.2;
    z += dir * lz * 0.2;
}

void rotateCamera(float ang) {
    angle += ang;
    lx = sin(angle);
    lz = -cos(angle);
}

void pressKey(int key, int xx, int yy) {
    switch (key) {
        case GLUT_KEY_UP: moveCamera(1); break;
        case GLUT_KEY_DOWN: moveCamera(-1); break;
        case GLUT_KEY_LEFT: rotateCamera(-0.05); break;
        case GLUT_KEY_RIGHT: rotateCamera(0.05); break;
    }
    glutPostRedisplay();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("3D Mobil Sedan");
    initLighting();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(pressKey);
    glutMainLoop();
    return 0;
}

