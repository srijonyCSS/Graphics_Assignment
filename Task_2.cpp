#include <GL/glut.h>
#include <cmath>

int windowWidth = 800, windowHeight = 600;


void drawCircle(int xc, int yc, int r, float red, float green, float blue, int thickness) {
    glColor3f(red, green, blue);

    for (int t = 0; t < thickness; t++) {
        int x = 0;
        int y = r + t;
        int d = 1 - y;

        glBegin(GL_POINTS);
        while (x <= y) {

            glVertex2i(xc + x, yc + y);
            glVertex2i(xc - x, yc + y);
            glVertex2i(xc + x, yc - y);
            glVertex2i(xc - x, yc - y);
            glVertex2i(xc + y, yc + x);
            glVertex2i(xc - y, yc + x);
            glVertex2i(xc + y, yc - x);
            glVertex2i(xc - y, yc - x);

            if (d < 0)
                d += 2 * x + 3;
            else {
                d += 2 * (x - y) + 5;
                y--;
            }
            x++;
        }
        glEnd();
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    int xc = 0, yc = 0;
    int numCircles = 10;
    int radiusStep = 20;
    int thicknessStep = 2;


    for (int i = 0; i < numCircles; i++) {
        float red = (float)i / numCircles;
        float green = 1.0f - (float)i / numCircles;
        float blue = 0.5f + 0.5f * sin(i);

        drawCircle(xc, yc, 30 + i * radiusStep, red, green, blue, 1 + i * thicknessStep);
    }

    glFlush();
}


void init() {
    glClearColor(0, 0, 0, 0);
    gluOrtho2D(-400, 400, -300, 300);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Concentric Circles with Color Gradient");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
