#include "DrawingFunctions.h"
#include <unistd.h>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <SFML/Audio.hpp>
// g++ -pthread -o audio2laser main.cpp HeliosDac.cpp -lglfw -lGLU -lGL -lXrandr -lXxf86vm -lXi -lXinerama -lX11 -lrt -ldl -std=c++17 -lusb-1.0 -lsfml-audio -lsfml-system
// chmod u+s ./audio2laser
// sudo -E ./audio2laser

unsigned int SAMPLE_RATE = 44100;
int FRAMES_PER_BUFFER = 1024;
constexpr int NUM_CHANNELS = 2;
int MAX_SETTING = 5;

using namespace std;
using namespace sf;

int main(void)
{
	cout << "Enter sample rate:" << endl;
	cin >> SAMPLE_RATE;
	cout << "Enter buffer size:" << endl;
	cin >> FRAMES_PER_BUFFER;
	
    /* Initialize the library */
	GLFWwindow* window;
    if (!glfwInit()) return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(winW, winH, "Audio2HeliosDAC", NULL, NULL);
    if (!window)    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);	
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glViewport(0, 0, winW, winH); 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, winW, winH, 0, -10, 10);

	//Back to the modelview so we can draw stuff 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
	
	setreuid(geteuid(), getuid());
	
	SoundBufferRecorder recorder;
	recorder.setChannelCount(NUM_CHANNELS);
	int state;
	int setting = 0;
	//-------------------------------------------------
	/* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {	
		//-------------Input Controller-----------
		state = glfwGetKey(window, GLFW_KEY_UP);
		if (state == GLFW_PRESS){ 
			setting--;
			if (setting < 0) setting = MAX_SETTING;
		}
		state = glfwGetKey(window, GLFW_KEY_DOWN);
		if (state == GLFW_PRESS){ 
			setting++;
			if (setting > MAX_SETTING) setting = 0;
		}
		state = glfwGetKey(window, GLFW_KEY_LEFT);
		if (state == GLFW_PRESS){ 
			if (setting == 0) r--;
			else if (setting == 1) g--;
			else if (setting == 2) b--;
			else if (setting == 3) xoff--;
			else if (setting == 4) yoff--;
			else if (setting == 5) {
				scale--;
				if (scale < 1) { scale = 12; }
			}
		}
		state = glfwGetKey(window, GLFW_KEY_RIGHT);
		if (state == GLFW_PRESS){ 
			if (setting == 0) r++;
			else if (setting == 1) g++;
			else if (setting == 2) b++;
			else if (setting == 3) xoff++;
			else if (setting == 4) yoff++;
			else if (setting == 5) {
				scale++;
				if (scale > 12) { scale = 1; }
			}
		}
		
		//-------------Get Audio Stream--------------------
		const int dT = 1000 * FRAMES_PER_BUFFER * NUM_CHANNELS / SAMPLE_RATE;
		recorder.start();
		sleep(milliseconds(dT));
		recorder.stop();
		
		const SoundBuffer& buffer = recorder.getBuffer();
    	const Int16* samples = buffer.getSamples();
	
		//-------------Frame Info---------------
		glClear(GL_COLOR_BUFFER_BIT);
		glPointSize(2.0f);		
		SetHeliosColour(r,g,b);
		glPushMatrix();
		HeliosTranslate(xoff, yoff, 0); 
		glTranslatef(winW/2, winH/2, 0); 
		HeliosScale(scale,-scale,0);
		glScalef(2,-2,0);
		glBegin(GL_LINE_STRIP);
		for (size_t i = 0; i < FRAMES_PER_BUFFER*NUM_CHANNELS; i+=NUM_CHANNELS) {
			WriteHeliosPoint(samples[i]>>8, samples[i+1]>>8);  
   		}	
		glEnd();
		glPopMatrix();
		
		if (setting == 0) { 
			glColor3f(1,1,1); 
		} else { glColor3f(0.5f,0.5f,0.5f); }
		drawText(20,10,'R');
		drawValue(60,10,r);
		
		if (setting == 1) { 
			glColor3f(1,1,1); 
		} else { glColor3f(0.5f,0.5f,0.5f); }
		drawText(20,30,'G');
		drawValue(60,30,g);
		
		if (setting == 2) { 
			glColor3f(1,1,1); 
		} else { glColor3f(0.5f,0.5f,0.5f); }
		drawText(20,50,'B');
		drawValue(60,50,b);
		
		if (setting == 3) { 
			glColor3f(1,1,1); 
		} else { glColor3f(0.5f,0.5f,0.5f); }
		drawText(20,70,'X');
		drawValue(60,70,xoff);
		
		if (setting == 4) { 
			glColor3f(1,1,1); 
		} else { glColor3f(0.5f,0.5f,0.5f); }
		drawText(20,90,'Y');
		drawValue(60,90,yoff);
		
		if (setting == 5) { 
			glColor3f(1,1,1); 
		} else { glColor3f(0.5f,0.5f,0.5f); }
		drawText(20,110,'S');
		drawValue(60,110,scale);
		
		//---Cleanup---
		glfwSwapBuffers(window);
		glfwPollEvents();
		WriteHeliosFrame();
		
	}
	CloseHeliosDAC() ;
    glfwTerminate();
    return 0;
}

