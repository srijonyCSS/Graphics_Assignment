#include <GL/glut.h>
#include <iostream>
#include <cmath>
using namespace std;

int x1_, y1_, x2_, y2_;
int thickness = 1;
bool thickMode = false;
void drawPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}


// (a) Standard Bresenham Line 

void bresenhamLine(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (true) {
        drawPixel(x1, y1);
        if (x1 == x2 && y1 == y2)
            break;

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}


// (b) Thick Line 

void thickBresenhamLine(int x1, int y1, int x2, int y2, int width) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    float length = sqrt(dx * dx + dy * dy);
    float perpX = -dy / length;
    float perpY = dx / length;

    for (int i = -width / 2; i <= width / 2; i++) {
        int offsetX1 = round(x1 + i * perpX);
        int offsetY1 = round(y1 + i * perpY);
        int offsetX2 = round(x2 + i * perpX);
        int offsetY2 = round(y2 + i * perpY);
        bresenhamLine(offsetX1, offsetY1, offsetX2, offsetY2);
    }
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0); // white color

    if (thickMode)
        thickBresenhamLine(x1_, y1_, x2_, y2_, thickness);
    else
        bresenhamLine(x1_, y1_, x2_, y2_);

    glFlush();
}


void init() {
    glClearColor(0, 0, 0, 0); // black color
    gluOrtho2D(0, 640, 0, 480);
}


int main(int argc, char** argv) {
    cout << "Enter x1 y1: ";
    cin >> x1_ >> y1_;
    cout << "Enter x2 y2: ";
    cin >> x2_ >> y2_;
    cout << "Do you want a thick line? (1=yes, 0=no): ";
    cin >> thickMode;
    if (thickMode) {
        cout << "Enter line thickness: ";
        cin >> thickness;
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Bresenham Line Drawing (OpenGL)");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

