#include <GL/glut.h>
#include <cmath>

void drawCircle(float cx, float cy, float r, int num_segments) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < num_segments; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

void drawSun() {
    glColor3f(1.0, 1.0, 0.0);
    drawCircle(-0.8, 0.6, 0.15, 30);
    
    glColor3f(1.0, 0.8, 0.0);
    glBegin(GL_LINES);
    for (int i = 0; i < 12; i++) {
        float angle = i * 30.0f * 3.1415926f / 180.0f;
        float x1 = -0.8 + 0.17 * cosf(angle);
        float y1 = 0.6 + 0.17 * sinf(angle);
        float x2 = -0.8 + 0.25 * cosf(angle);
        float y2 = 0.6 + 0.25 * sinf(angle);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
    }
    glEnd();
}

void drawCloud(float cx, float cy) {
    glColor3f(0.9, 0.9, 0.9);
    drawCircle(cx, cy, 0.1, 20);
    drawCircle(cx + 0.1, cy + 0.05, 0.12, 20);
    drawCircle(cx + 0.2, cy, 0.1, 20);
}

void drawCar() {
    glPushMatrix();
    
    // Badan mobil sedan
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex2f(-0.6, -0.2);
    glVertex2f(0.6, -0.2);
    glVertex2f(0.6, 0.1);
    glVertex2f(-0.6, 0.1);
    glEnd();

    // Atap mobil sedan
    glColor3f(0.0, 0.5, 1.0);
    glBegin(GL_POLYGON);
    glVertex2f(-0.4, 0.1);
    glVertex2f(0.4, 0.1);
    glVertex2f(0.3, 0.3);
    glVertex2f(-0.3, 0.3);
    glEnd();

    // Roda kanan
    glColor3f(0.0, 0.0, 0.0);
    drawCircle(0.35, -0.25, 0.1, 20);

    // Roda kiri
    drawCircle(-0.35, -0.25, 0.1, 20);
    
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    
    // Menggambar langit
    glColor3f(0.5, 0.8, 1.0);
    glBegin(GL_POLYGON);
    glVertex2f(-1, 1);
    glVertex2f(1, 1);
    glVertex2f(1, 0);
    glVertex2f(-1, 0);
    glEnd();
    
    // Menggambar rumput
    glColor3f(0.0, 0.6, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(-1, 0);
    glVertex2f(1, 0);
    glVertex2f(1, -1);
    glVertex2f(-1, -1);
    glEnd();
    
    // Menggambar matahari
    drawSun();
    
    // Menggambar awan
    drawCloud(-0.5, 0.7);
    drawCloud(0.2, 0.8);
    
    // Menggambar mobil sedan
    glTranslatef(0.0, -0.2, 0.0);
    glRotatef(5, 0.0, 0.0, 1.0);
    drawCar();

    glutSwapBuffers();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Mobil Sedan 2D dengan OpenGL");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
