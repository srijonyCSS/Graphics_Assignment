#include <GL/glut.h>
#include <iostream>
#include <vector>
using namespace std;

// Clipping window boundaries
float xmin, ymin, xmax, ymax;

// Line structure
struct Line {
    float x1, y1, x2, y2;
};

// Vector to store user input lines
vector<Line> lines;

// Liang–Barsky Line Clipping Function
bool liangBarskyClip(float x1, float y1, float x2, float y2,
                     float &cx1, float &cy1, float &cx2, float &cy2)
{
    float dx = x2 - x1;
    float dy = y2 - y1;

    float p[4] = {-dx, dx, -dy, dy};
    float q[4] = {x1 - xmin, xmax - x1, y1 - ymin, ymax - y1};

    float u1 = 0.0f, u2 = 1.0f;

    for (int i = 0; i < 4; i++) {
        if (p[i] == 0) {
            if (q[i] < 0) return false; // Line parallel and outside
        } else {
            float t = -q[i] / p[i];
            if (p[i] < 0)
                u1 = max(u1, t);
            else
                u2 = min(u2, t);
        }
    }

    if (u1 > u2) return false;

    cx1 = x1 + u1 * dx;
    cy1 = y1 + u1 * dy;
    cx2 = x1 + u2 * dx;
    cy2 = y1 + u2 * dy;

    return true;
}

// Draw the clipping window
void drawClippingWindow() {
    glColor3f(1, 1, 1); // White
    glBegin(GL_LINE_LOOP);
        glVertex2f(xmin, ymin);
        glVertex2f(xmax, ymin);
        glVertex2f(xmax, ymax);
        glVertex2f(xmin, ymax);
    glEnd();
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(2.0);

    drawClippingWindow();

    for (auto &line : lines) {
        float x1 = line.x1, y1 = line.y1;
        float x2 = line.x2, y2 = line.y2;

        // Draw original line in RED
        glColor3f(1, 0, 0);
        glBegin(GL_LINES);
            glVertex2f(x1, y1);
            glVertex2f(x2, y2);
        glEnd();

        // Clip and draw in GREEN
        float cx1, cy1, cx2, cy2;
        if (liangBarskyClip(x1, y1, x2, y2, cx1, cy1, cx2, cy2)) {
            glColor3f(0, 1, 0);
            glBegin(GL_LINES);
                glVertex2f(cx1, cy1);
                glVertex2f(cx2, cy2);
            glEnd();
        }
    }

    glFlush();
}

// OpenGL Initialization
void init() {
    glClearColor(0, 0, 0, 0);
    gluOrtho2D(-300, 300, -300, 300);
}

// Main function
int main(int argc, char **argv) {
    cout << "Enter clipping window coordinates:" << endl;
    cout << "xmin ymin xmax ymax: ";
    cin >> xmin >> ymin >> xmax >> ymax;

    int n;
    cout << "Enter number of lines: ";
    cin >> n;

    cout << "Enter line coordinates (x1 y1 x2 y2):" << endl;
    for (int i = 0; i < n; i++) {
        Line temp;
        cout << "Line " << i + 1 << ": ";
        cin >> temp.x1 >> temp.y1 >> temp.x2 >> temp.y2;
        lines.push_back(temp);
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Liang–Barsky Line Clipping (User Input)");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
