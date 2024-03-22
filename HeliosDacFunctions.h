#define MAX_POINTS 4000
#define BRIGHTNESS 150
#define PI 3.14159

#include "HeliosDac.h"
#include <GLFW/glfw3.h>
#include <GL/glut.h>
#include <math.h>


//make frames
HeliosPoint frame[MAX_POINTS];

int idx = 0;
unsigned char r = 0; 
unsigned char g = 255;
unsigned char b = 0; 
unsigned char xoff = 128;
unsigned char yoff = 128;
int xs, ys = 0;
int x, y = 0;
float angle = 0;
int scale = 5;

HeliosDac helios;
int numDevs = helios.OpenDevices();

void HeliosTranslate(int _xoff, int _yoff, int _zoff) {
	xoff = _xoff;
	yoff = _yoff;
}

void HeliosScale(int _xs, int _ys, int _zs) {
	xs = _xs;
	ys = _ys;
}

void HeliosRotate( float _angle) {
	angle = _angle * PI / 180;
	glRotatef(angle, 0, 0, 1);
}

void SetHeliosColour(unsigned char _r, unsigned char _g, unsigned char _b) {
	r = _r;
	g = _g;
	b = _b;
	
	glColor3f(float(_r)/255, float(_g)/255, float(_b)/255);
}

void WriteHeliosPoint(int _x, int _y) {
	
	x = (_x*xs + xoff*16);
	y = (_y*ys + yoff*16);
	
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
			helios.WriteFrame(j, 30*idx, HELIOS_FLAGS_DEFAULT, &frame[0], idx); //send the next frame	
		}	
	idx = 0;
}

void CloseHeliosDAC() {
	helios.CloseDevices();
}
