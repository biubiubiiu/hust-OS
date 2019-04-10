#include <conio.h>
#include <math.h>
#include <windows.h>
#include "graphics.h"

#define PI 3.1415926535

const int radius = 200;
const int height = 2 * radius;
const int width = 1.5 * height;
const int pixels = 720;

int rec[pixels][2];
int cir[pixels][2];

void initCoord() {
    int circle_center_x = 20 + radius;
    int circle_center_y = 720 / 2;  // 720: window height
    for (int i = 0; i < pixels; ++i) {
        cir[i][0] =
            circle_center_x + radius * sin((360.0 * i / pixels) * (PI / 180));
        cir[i][1] =
            circle_center_y - radius * cos((360.0 * i / pixels) * (PI / 180));
    }

    int rec_lefttop_x = 1080 - width - 20;  // 1080: window width
    int rec_lefttop_y = circle_center_y - radius;
    int x_pixels = round(pixels * 0.5 * width / (width + height));
    int y_pixels = pixels / 2 - x_pixels;
    double x_step = width * 1.0 / x_pixels;
    double y_step = height * 1.0 / y_pixels;
    for (int i = 0; i < x_pixels; ++i) {
        rec[i][0] = rec_lefttop_x + round(i * x_step);
        rec[i][1] = rec_lefttop_y;
        rec[pixels - y_pixels - i][0] = rec_lefttop_x + round(i * x_step);
        rec[pixels - y_pixels - i][1] = rec_lefttop_y + height;
    }

    for (int i = 0; i < y_pixels; ++i) {
        rec[x_pixels + i][0] = rec_lefttop_x + width;
        rec[x_pixels + i][1] = rec_lefttop_y + round(i * y_step);
        rec[pixels - 1 - i][0] = rec_lefttop_x;
        rec[pixels - 1 - i][1] = rec_lefttop_y + round(i * y_step);
    }
}

DWORD WINAPI drawRect(LPVOID lpParam) {
    static int i = 0;
    while (i < 720) {
        putpixel(rec[i][0], rec[i][1], RED);
        ++i;
        Sleep(20);
    }
    return 0;
}

DWORD WINAPI drawCircle(LPVOID lpParam) {
    static int j = 0;
    while (j < 720) {
        putpixel(cir[j][0], cir[j][1], RED);
        ++j;
        Sleep(20);
    }
    return 0;
}

int main() {
    initgraph(1080, pixels);
    setbkcolor(WHITE);
    cleardevice();

    initCoord();

    HANDLE hThread[2];
    hThread[0] = CreateThread(NULL, 0, drawCircle, NULL, 0, NULL);
    hThread[1] = CreateThread(NULL, 0, drawRect, NULL, 0, NULL);
    WaitForMultipleObjects(2, hThread, TRUE, INFINITE);

    _getch();
    closegraph();
}
