#include "HeliosDacFunctions.h"
#include <unistd.h>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <SFML/Audio.hpp>
//g++ -pthread -o audio2laser main.cpp HeliosDac.cpp -lglfw -lGLU -lGL -lXrandr -lXxf86vm -lXi -lXinerama -lX11 -lrt -ldl -std=c++17 -lusb-1.0 -lsfml-audio -lsfml-system

											// TODO:
unsigned int SAMPLE_RATE = 44100; 			// cin -> sample rate, buffer size
constexpr int FRAMES_PER_BUFFER = 512;		// live settings -> r, g, b, xoff, yoff, size
constexpr int NUM_CHANNELS = 2;				// move l/r to change setting, u/d to change value

using namespace std;
using namespace sf;

int main(void)
{
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
	
	setreuid(geteuid(), getuid());
	
	SoundBufferRecorder recorder;
	recorder.setChannelCount(NUM_CHANNELS);
	
	//-------------------------------------------------
	/* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {	
		const int dT = 1000 * FRAMES_PER_BUFFER * NUM_CHANNELS / SAMPLE_RATE;
		recorder.start();
		sleep(milliseconds(dT));
		recorder.stop();
		
		const SoundBuffer& buffer = recorder.getBuffer();
    	const Int16* samples = buffer.getSamples();
	
		//-------------Frame Info---------------
		glClear(GL_COLOR_BUFFER_BIT);
		glPointSize(2.0f);		
		SetHeliosColour(0,1,0);
		glPushMatrix();
		HeliosTranslate(-winW, -winH, 0); 
		glTranslatef(winW/2, winH/2, 0); 
		HeliosScale(12,-12,0);
		glScalef(3,-3,0);
		glBegin(GL_LINE_STRIP);
		for (size_t i = 0; i < FRAMES_PER_BUFFER*NUM_CHANNELS; i+=NUM_CHANNELS) {
			WriteHeliosPoint(samples[i]>>8, samples[i+1]>>8);  
   		}	
		glEnd();
		glPopMatrix();
		
		//---Cleanup---
		glfwSwapBuffers(window);
		glfwPollEvents();
		WriteHeliosFrame();
		
	}
	CloseHeliosDAC() ;
    glfwTerminate();
    return 0;
}

