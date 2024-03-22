# Audio2HeliosDAC
Script for reading audio data (l/r) as an xy plot. Mainly built for use with OsciStudio on Linux systems to connect to Helios DAC. 

To compile the C++ source you will need the openGL graphics library, the SFML audio library and I suggest using g++ to compile. You can use this command line to compile if you have g++:


g++ -pthread -o audio2laser main.cpp HeliosDac.cpp -lglfw -lGLU -lGL -lXrandr -lXxf86vm -lXi -lXinerama -lX11 -lrt -ldl -std=c++17 -lusb-1.0 -lsfml-audio -lsfml-system  

...if there are no errors then you can use this to run the app (after starting the ROM):

chmod u+s ./audio2laser (this will allow the program to modify root access for connecting to audio)  
sudo -E ./audio2laser   (this will run the app, the -E flag is necessary


(if there are errors then it is likely you are missing one of the libraries in the compile line, these can be searched easily enough online)
