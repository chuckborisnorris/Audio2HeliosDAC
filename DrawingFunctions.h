#define W_WIDTH 512
#define W_HEIGHT 512
#define SCALAR 1
#define TEXTSCALAR 2
#define SHIPSCALAR 2

#include <cstring>
#include <iostream>
#include <string>
#include <bits/stdc++.h> 
#include "HeliosDacFunctions.h"

int winW = W_WIDTH*SCALAR;
int winH = W_HEIGHT*SCALAR;

void drawText(int _x, int _y, char letter)
{
	int x = _x*SCALAR;
	int y = _y*SCALAR;

	glPushMatrix();	
    glTranslatef(x-6, y, 0); 
	glScalef(TEXTSCALAR,-TEXTSCALAR,0);
	
    glBegin(GL_LINE_STRIP);
    switch ( letter ) {
		case 'R': 
		glVertex2f(-2, -4);   
		glVertex2f(-2, 4); 
		glVertex2f(2, 4); 
		glVertex2f(2, 0); 
		glVertex2f(-2, 0);  
		glVertex2f(2, -4);	
		break;
		
		case 'G': 
		glVertex2f(2, 4);   
		glVertex2f(-2, 4); 
		glVertex2f(-2, -4);  
		glVertex2f(2, -4);
		glVertex2f(2, 0);
		glVertex2f(0, 0);
		break;
		
		case 'B': 
		glVertex2f(-2, 0);   
		glVertex2f(2, 0); 
		glVertex2f(2, -4);   
		glVertex2f(-2, -4); 
		glVertex2f(-2, 4); 
		glVertex2f(1, 4); 
		glVertex2f(1, 0); 
		break;
		
		case 'X': 
		glVertex2f(-2, -4);   
		glVertex2f(2, 4);
		glEnd();
		glBegin(GL_LINE_STRIP);
		glVertex2f(-2, 4); 
		glVertex2f(2, -4);  		
		break;
		
		case 'Y': 
		glVertex2f(-2, 4);   
		glVertex2f(0,0); 
		glVertex2f(2, 4); 
		glVertex2f(0, 0); 
		glVertex2f(0,-4); 
		break;
		
		case 'S': 
		glVertex2f(-2, -4);   
		glVertex2f(2, -4); 
		glVertex2f(2, 0); 
		glVertex2f(-2, 0); 
		glVertex2f(-2, 4);  
		glVertex2f(2, 4);	
		break;

		default: 	
		break;
	}
	glEnd();
	glBegin(GL_POINTS);
	glVertex2f(4, 2); 
	glVertex2f(4, -2); 
	glEnd();
	glPopMatrix();
	
}

void drawValue(int _x, int _y, unsigned char val)
{
int x = _x*SCALAR;
int y = _y*SCALAR;

std::string tmp = std::to_string(val);
reverse(tmp.begin(),tmp.end());
char const *c = tmp.c_str();
	
for (int i = tmp.length(); i > -1; i--) {
	glPushMatrix();
	
    glTranslatef(float(x-6*i*TEXTSCALAR), y, 0); 
	glScalef(TEXTSCALAR,-TEXTSCALAR,0);
	
    glBegin(GL_LINE_STRIP);
    switch ( c[i] ) {
		case '5': 
		glVertex2f(-2, -4);   
		glVertex2f(2, -4); 
		glVertex2f(2, 0); 
		glVertex2f(-2, 0); 
		glVertex2f(-2, 4);  
		glVertex2f(2, 4);	
		break;
		
		case '0': 
		glVertex2f(-2, -4);   
		glVertex2f(-2, 4); 
		glVertex2f(2, 4);  
		glVertex2f(2, -4);
		glVertex2f(-2, -4);
		break;
		
		case '1': 
		glVertex2f(0, -4);   
		glVertex2f(0, 4); 
		break;
		
		case '2': 
		glVertex2f(2, -4);   
		glVertex2f(-2, -4); 
		glVertex2f(-2, 0); 
		glVertex2f(2, 0); 
		glVertex2f(2, 4);  
		glVertex2f(-2, 4); 		
		break;
		
		case '3': 
		glVertex2f(-2, -4);   
		glVertex2f(2, -4); 
		glVertex2f(2, 0); 
		glVertex2f(-2, 0); 
		glVertex2f(2, 0); 
		glVertex2f(2, 4);  
		glVertex2f(-2, 4); 	
		break;
		
		case '4': 
		glVertex2f(2, -4);   
		glVertex2f(2, 4); 
		glVertex2f(2, 0); 
		glVertex2f(-2, 0); 
		glVertex2f(-2, 4); 	
		break;
		
		case '6': 
		glVertex2f(2, 4); 
		glVertex2f(-2, 4);   
		glVertex2f(-2, -4); 
		glVertex2f(2, -4); 
		glVertex2f(2, 0); 
		glVertex2f(-2, 0);		
		break;
		
		case '7': 
		glVertex2f(2, -4);   
		glVertex2f(2, 4); 
		glVertex2f(-2, 4); 
		break;
		
		case '8': 
		glVertex2f(-2, -4);   
		glVertex2f(-2, 4); 
		glVertex2f(2, 4);  
		glVertex2f(2, -4);  
		glVertex2f(-2, -4);  
		glVertex2f(-2, 0);  
		glVertex2f(2, 0);  
		break;
		
		case '9': 
		glVertex2f(2, -4);   
		glVertex2f(2, 4); 
		glVertex2f(-2, 4); 
		glVertex2f(-2, 0); 
		glVertex2f(2, 0); 
		break;
		
		default: 	
		break;
	}
	glEnd();
	glPopMatrix();
	
}
}
