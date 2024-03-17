#define MAX_POINTS 4000
#define BRIGHTNESS 150
#define PI 3.14159
#define W_WIDTH 512
#define W_HEIGHT 512
#define SCALAR	1

#include "HeliosDac.h"
#include <GLFW/glfw3.h>
#include <GL/glut.h>
#include <math.h>


//make frames
HeliosPoint frame[MAX_POINTS];

int winW = W_WIDTH*SCALAR;
int winH = W_HEIGHT*SCALAR;
int idx = 0;
int r, g, b = 0;
int xoff, yoff = 0;
int xs, ys = 0;
int x, y = 0;
float angle = 0;

HeliosDac helios;
int numDevs = helios.OpenDevices();

void HeliosTranslate(int _xoff, int _yoff, int _zoff) {
	xoff = _xoff;
	yoff = _yoff;
	//glTranslatef(float(_xoff), float(_yoff), float(_zoff));
}

void HeliosScale(int _xs, int _ys, int _zs) {
	xs = _xs;
	ys = _ys;
	//glScalef(float(_xs), float(_ys), float(_zs));
}

void HeliosRotate( float _angle) {
	angle = _angle * PI / 180;
	glRotatef(angle, 0, 0, 1);
}

void SetHeliosColour(float _r, float _g, float _b) {
	r = int(_r * BRIGHTNESS);
	g = int(_g * BRIGHTNESS);
	b = int(_b * BRIGHTNESS);
	
	glColor3f(_r, _g, _b);
}

void WriteHeliosPoint(int _x, int _y) {
	
	x = (_x*xs + xoff*xs);
	y = (_y*ys + yoff*ys);
	
	frame[idx].x = x;
	frame[idx].y = y;			
	frame[idx].r = r;
	frame[idx].g = g;
	frame[idx].b = b;
	frame[idx].i = 0xff;
	
	glVertex2f(_x,_y);
	
	if (idx < MAX_POINTS) idx++;	
}

void WriteHeliosFrame() {
	for (int j = 0; j < numDevs; j++)
		{
		if (helios.GetStatus(j) == 1)
			helios.WriteFrame(j, 10*idx, HELIOS_FLAGS_DEFAULT, &frame[0], idx); //send the next frame	
		}	
	idx = 0;
}

void CloseHeliosDAC() {
	helios.CloseDevices();
}
