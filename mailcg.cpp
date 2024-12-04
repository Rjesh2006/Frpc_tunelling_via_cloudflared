#include <iostream>
#include <graphics.h>
#include <cmath>
#include <algorithm>
using namespace std;

struct Point {
    int x, y;
};

// 1. Bresenham's Line Drawing Algorithm
void bresenhamLine(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1), dy = abs(y2 - y1);
    int p = 2 * dy - dx;
    int twoDy = 2 * dy, twoDyDx = 2 * (dy - dx);

    if (x1 > x2) swap(x1, x2);
    if (y1 > y2) swap(y1, y2);

    putpixel(x1, y1, WHITE);
    while (x1 < x2) {
        x1++;
        if (p < 0) {
            p += twoDy;
        } else {
            y1++;
            p += twoDyDx;
        }
        putpixel(x1, y1, WHITE);
    }
}

// 2. Midpoint Circle Drawing Algorithm
void midpointCircle(int cx, int cy, int r) {
    int x = 0, y = r;
    int p = 1 - r;
    putpixel(cx + x, cy + y, WHITE);
    putpixel(cx - x, cy + y, WHITE);
    putpixel(cx + x, cy - y, WHITE);
    putpixel(cx - x, cy - y, WHITE);
    putpixel(cx + y, cy + x, WHITE);
    putpixel(cx - y, cy + x, WHITE);
    putpixel(cx + y, cy - x, WHITE);
    putpixel(cx - y, cy - x, WHITE);

    while (x < y) {
        x++;
        if (p < 0) {
            p += 2 * x + 1;
        } else {
            y--;
            p += 2 * (x - y) + 1;
        }
        putpixel(cx + x, cy + y, WHITE);
        putpixel(cx - x, cy + y, WHITE);
        putpixel(cx + x, cy - y, WHITE);
        putpixel(cx - x, cy - y, WHITE);
        putpixel(cx + y, cy + x, WHITE);
        putpixel(cx - y, cy + x, WHITE);
        putpixel(cx + y, cy - x, WHITE);
        putpixel(cx - y, cy - x, WHITE);
    }
}

// 3. Cohen-Sutherland Line Clipping Algorithm
void cohenSutherlandClip(int x1, int y1, int x2, int y2, int xmin, int ymin, int xmax, int ymax) {
    int code1 = 0, code2 = 0, code;
    const int LEFT = 1, RIGHT = 2, BOTTOM = 4, TOP = 8;

    // Compute region codes
    if (x1 < xmin) code1 |= LEFT;
    if (x1 > xmax) code1 |= RIGHT;
    if (y1 < ymin) code1 |= BOTTOM;
    if (y1 > ymax) code1 |= TOP;

    if (x2 < xmin) code2 |= LEFT;
    if (x2 > xmax) code2 |= RIGHT;
    if (y2 < ymin) code2 |= BOTTOM;
    if (y2 > ymax) code2 |= TOP;

    while (true) {
        if (!(code1 | code2)) {
            // Accept the line
            line(x1, y1, x2, y2);
            break;
        } else if (code1 & code2) {
            // Reject the line
            break;
        } else {
            int x, y;
            code = code1 ? code1 : code2;

            if (code & TOP) {
                x = x1 + (x2 - x1) * (ymax - y1) / (y2 - y1);
                y = ymax;
            } else if (code & BOTTOM) {
                x = x1 + (x2 - x1) * (ymin - y1) / (y2 - y1);
                y = ymin;
            } else if (code & RIGHT) {
                y = y1 + (y2 - y1) * (xmax - x1) / (x2 - x1);
                x = xmax;
            } else if (code & LEFT) {
                y = y1 + (y2 - y1) * (xmin - x1) / (x2 - x1);
                x = xmin;
            }

            if (code == code1) {
                x1 = x;
                y1 = y;
                code1 = 0;
            } else {
                x2 = x;
                y2 = y;
                code2 = 0;
            }
        }
    }
}

// 4. Sutherland-Hodgman Polygon Clipping Algorithm
void clipPolygon(Point in[], int &inCount, int xMin, int yMin, int xMax, int yMax) {
    Point out[20];
    int outCount = 0;

    for (int i = 0; i < inCount; i++) {
        int k = (i + 1) % inCount;
        Point p1 = in[i], p2 = in[k];

        if (p1.x >= xMin && p1.x <= xMax && p1.y >= yMin && p1.y <= yMax) {
            out[outCount++] = p1;
        }
    }
    inCount = outCount;
    for (int i = 0; i < inCount; i++) in[i] = out[i];
}

void drawPolygon(Point p[], int n) {
    for (int i = 0; i < n; i++) {
        int next = (i + 1) % n;
        line(p[i].x, p[i].y, p[next].x, p[next].y);
    }
}

// 5. Scanline Polygon Fill Algorithm
void scanlineFill(int poly[][2], int n) {
    int ymin = poly[0][1], ymax = poly[0][1];
    for (int i = 1; i < n; i++) {
        if (poly[i][1] < ymin) ymin = poly[i][1];
        if (poly[i][1] > ymax) ymax = poly[i][1];
    }

    for (int y = ymin; y <= ymax; y++) {
        int intersections[20], k = 0;
        for (int i = 0; i < n; i++) {
            int x1 = poly[i][0], y1 = poly[i][1];
            int x2 = poly[(i + 1) % n][0], y2 = poly[(i + 1) % n][1];

            if (y1 < y2) {
                swap(x1, x2);
                swap(y1, y2);
            }

            if (y > y1 && y <= y2 || y <= y1 && y > y2) {
                int x = x1 + (y - y1) * (x2 - x1) / (y2 - y1);
                intersections[k++] = x;
            }
        }
        sort(intersections, intersections + k);
        for (int i = 0; i < k; i += 2) {
            line(intersections[i], y, intersections[i + 1], y);
        }
    }
}

// 6. 2D Transformations Using Homogeneous Coordinates
void apply2DTransform(int &x, int &y, int tx, int ty, float angle) {
    int tempX = x * cos(angle) - y * sin(angle) + tx;
    int tempY = x * sin(angle) + y * cos(angle) + ty;
    x = tempX;
    y = tempY;
}

// 7. 3D Transformations and Projection
void draw3D(int x, int y, int z, int projection) {
    int projectedX = x / (1 + z / projection);
    int projectedY = y / (1 + z / projection);
    putpixel(projectedX, projectedY, WHITE);
}

// 8. Bezier Curve
void bezier(int x[], int y[]) {
    for (float t = 0.0; t <= 1.0; t += 0.001) {
        float px = pow(1 - t, 3) * x[0] + 3 * t * pow(1 - t, 2) * x[1] +
                   3 * pow(t, 2) * (1 - t) * x[2] + pow(t, 3) * x[3];
        float py = pow(1 - t, 3) * y[0] + 3 * t * pow(1 - t, 2) * y[1] +
                   3 * pow(t, 2) * (1 - t) * y[2] + pow(t, 3) * y[3];
        putpixel(px, py, WHITE);
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);

    // Test Bresenham's Line Drawing
    bresenhamLine(100, 100, 200, 200);

    // Test Midpoint Circle Drawing
    midpointCircle(300, 300, 50);

    // Test Cohen-Sutherland Line Clipping
    cohenSutherlandClip(100, 100, 250, 250, 50, 50, 400, 400);

    // Test Sutherland-Hodgman Polygon Clipping
    Point polygon[] = {{100, 100}, {200, 100}, {200, 200}, {100, 200}};
    int n = 4;
    clipPolygon(polygon, n, 50, 50, 300, 300);
    drawPolygon(polygon, n);

    // Test Scanline Polygon Fill
    int poly[5][2] = {{100, 100}, {150, 150}, {200, 100}, {200, 50}, {100, 50}};
    scanlineFill(poly, 5);

    // Test 2D Transformations
    int x = 100, y = 100;
    apply2DTransform(x, y, 50, 50, 45);

    // Test 3D Transformations and Projection
    draw3D(100, 100, 50, 300);

    // Test Bezier Curve
    int bx[] = {100, 150, 200, 250};
    int by[] = {200, 50, 100, 150};
    bezier(bx, by);

    getch();
    closegraph();
    return 0;
}
