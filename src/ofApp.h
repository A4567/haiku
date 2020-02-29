#pragma once

#include "ofMain.h"
#include "ofxJSON.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		
		ofxJSONElement result;
    vector<string> alphabet,numbers;

    std::stringstream testing, haikuA,haikuB,haikuC;
    
    string url;
    
    string query,topics;
    
    int index, wc,sylA,sylB,sylC,letter;
    bool lineA,lineB,lineC, clear, feeder;
};
