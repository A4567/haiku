#include "ofApp.h"
// using http://www.datamuse.com/api/
//--------------------------------------------------------------
void ofApp::setup(){
    sylA = 0;
    sylB = 0;
    sylC = 0;
    
    alphabet = {"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"};
    numbers = {"0","1","2","3","4","5","6","7","8","9"};
    
    testing << "book";
    
    topics = testing.str();
    
    url = "https://api.datamuse.com/words?topics="+testing.str()+"&max=20&md=sp";
    
    result.open(url);
    
//    cout << result << endl;
    
    index = ofRandom(20);
    
    query = result[index]["word"].asString();
    
    sylA += result[index]["numSyllables"].asInt();
    
    topics = query;
    
    haikuA << topics << " ";
    
    wc = 0;
    
    lineA = false;
    lineB = false;
    lineC = false;
    clear = false;
    feeder = false;
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    if(feeder){
        ofSetBackgroundColor(0);
        ofDrawBitmapString("Type in a new word to feed the machine", 10, 175);
        ofDrawBitmapString(testing.str(), 10, 200);
    }else{
        ofSetBackgroundColor(100, 100, 100);
    }
    ofDrawBitmapString(testing.str(), 10, 10);
    if(lineA){
        ofDrawBitmapString(haikuA.str(), 10, 50);
        ofDrawBitmapString(haikuB.str(), 10, 75);
        ofDrawBitmapString(haikuC.str(), 10, 100);
    }
    if(clear){
        wc = 0;
        sylA = 0;
        sylB = 0;
        sylC = 0;
        testing.str("");
        haikuA.str("");
        haikuB.str("");
        haikuC.str("");
        query = "";
        topics = "";
        ofClear(0);
        clear = !clear;
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    //allows re-entry of a feeder word
    if(key == OF_KEY_RETURN){
        if(feeder){
            topics = testing.str();
            
            url = "https://api.datamuse.com/words?topics="+testing.str()+"&max=20&md=sp";
            
            result.open(url);
            
            index = ofRandom(20);
            
            query = result[index]["word"].asString();
        }
        feeder = !feeder;
    }
    
    if(!feeder){
        // create a haiku
        if(key == 'h'){
            index = ofRandom(50);
            
            lineA = true;
            
            query = query.substr(0, query.find(" "));
            url = "https://api.datamuse.com/words?lc="+query+"&max=50&md=sp";
            result.open(url);
            
            ofxJSONElement prefix;
            prefix = result[index];
            
            if(!prefix){
                query = topics;
                query = query.substr(0, query.find(" "));
                url = "https://api.datamuse.com/words?rel_spc="+query+"&max=50&md=sp";
                result.open(url);
                prefix = result[index];
                
            }else if(prefix["word"] == "."){
                query = topics;
                query = query.substr(0, query.find(" "));
                url = "https://api.datamuse.com/words?rel_spc="+query+"&max=50&md=sp";
                result.open(url);
                prefix = result[index];
            }
            
            if(sylA + prefix["numSyllables"].asInt() <= 5){
                sylA += prefix["numSyllables"].asInt();
                haikuA << prefix["word"].asString() << " ";
                query = prefix["word"].asString();
            }else if((sylB + prefix["numSyllables"].asInt() <= 7)&&(sylA == 5)){
                sylB += prefix["numSyllables"].asInt();
                haikuB << prefix["word"].asString() << " ";
                query = prefix["word"].asString();
            }else if((sylC + result[index]["numSyllables"].asInt() <= 5)&&(sylA == 5)&&(sylB == 7)){
                sylC += prefix["numSyllables"].asInt();
                haikuC << prefix["word"].asString() << " ";
                query = prefix["word"].asString();
            }
            
        }
    }else{
        letter = key - 97;
        if((letter >= 0)&&(letter <= 26)){
            testing << alphabet[letter];
        }
    }
    
    if(key == OF_KEY_BACKSPACE){
        clear = true;
    }
}

