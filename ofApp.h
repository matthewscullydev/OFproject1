#pragma once
// rotation apply the mouse movement to the object using a roation matrx
//
// dragging object, stays relative to point in the triangle you clicked, so all
// directions of the triangle move by the point you selected
//
// ctrl key + mouse apply motion of mouse vector to rotate matrix// think of
// position of mouse as one point and position of mouse after movement as a
// vector connecting these points
//
// 1/ofFramerate --       you dont want to divide by zero though (issue with
// floating point division) cant divide by 0, game starts and framerate is 0 so
// you have to check for that in your code
//
// origin + delta to get position mousedrag call to get current and prev
// positions. put x and y in vec 3 //same way as converting vec3 to vec4
//
// develop with aspect ratio in mind

#include "fwd.hpp"
#include "ofGraphics.h"
#include "ofMain.h"
#include "ofxGui.h"
class Shape {
   public:
    float scaleval = 1.0;
    glm::vec3 pos;
    float rotation = 0;  // degrees
    ofColor tricolor = ofColor::blue;
    vector<glm::vec3> verts;

    Shape() {}
    virtual void draw() {}
    virtual bool inside(glm::vec3 p) { return true; }

    glm::mat4 getMatrix() {
        glm::mat4 scale = glm::scale(glm::mat4(1.0), glm::vec3(scaleval));
        glm::mat4 trans = glm::translate(glm::mat4(1.0), glm::vec3(pos));
        glm::mat4 rot = glm::rotate(glm::mat4(1.0), glm::radians(rotation),
                                    glm::vec3(0, 0, 1));
        return (trans * rot * scale);
    }

    };

class TriangleShape : public Shape {
   public:
    float speed;

    TriangleShape() {}
    TriangleShape(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3) {
        verts.push_back(p1);
        verts.push_back(p2);
        verts.push_back(p3);
    }
    void draw();
    void agentDraw();
    bool inside(glm::vec3 p) {
        glm::vec4 vec(p, 1);
        glm::mat4 inversepoints = inverse(getMatrix());
        glm::vec4 z = inversepoints * vec;
        glm::vec3 finalpoint = glm::vec3(z);

        if (inside(finalpoint, verts[0], verts[1], verts[2])) {
            return true;
        }

        return false;
    }

    bool inside(glm::vec3 p, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3) {
        glm::vec3 v1 = glm::normalize(p1 - p);
        glm::vec3 v2 = glm::normalize(p2 - p);
        glm::vec3 v3 = glm::normalize(p3 - p);
        float a1 = glm::orientedAngle(v1, v2, glm::vec3(0, 0, 1));
        float a2 = glm::orientedAngle(v2, v3, glm::vec3(0, 0, 1));
        float a3 = glm::orientedAngle(v3, v1, glm::vec3(0, 0, 1));
        if (a1 < 0 && a2 < 0 && a3 < 0)
            return true;
        else
            return false;
    }
    //------
};

class Player : public TriangleShape {
   public:

    bool headshow;
    bool showsprite = true;

    //constructor for player which inherits triangle shape constructor

    Player() {}
    Player(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3)
        : TriangleShape(p1, p2, p3) {}

    //methods for player are beneath here

    glm::vec3 heading() {
        float num = ofDegToRad(rotation - 90);
        glm::vec3 directionvec = glm::vec3(cos(num), sin(num), 0);
        glm::vec3 normalizedvec = glm::normalize(directionvec);
        return normalizedvec;
    };

    void draw();
};

class Agent: public TriangleShape {
   public:

    bool headshow;
    bool showsprite = true;
    ofColor agentColor = ofColor::darkRed; 
    //constructor for player which inherits triangle shape constructor

    Agent() {}
    Agent(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3)
        : TriangleShape(p1, p2, p3) {}

    //methods for player are beneath here
    
    void followPlayer(Player p){
        if(this->pos.x != p.pos.x){
            this->pos.x += 3;    
        }     
    };

    glm::vec3 heading() {
        float num = ofDegToRad(rotation - 90);
        glm::vec3 directionvec = glm::vec3(cos(num), sin(num), 0);
        glm::vec3 normalizedvec = glm::normalize(directionvec);
        return normalizedvec;
    };

    void draw();
};
class ofApp : public ofBaseApp {
   public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

    Player tri;
    glm::vec3 normalizedplayervec;
    glm::vec3 beginMousePos;
    glm::vec3 mousePos;
    glm::vec3 displacement;
    glm::vec3 endMousePos;
    glm::vec3 origPos;
    bool drag = false;
    bool buttonflag = false;
    bool ctrlflag = false;
    bool insidetri = false;
    float speed;

    int nAgents;
    int nEnergy;
    
    map<int, bool> keymap;
    ofxPanel gui;
    ofxToggle toggle;
    ofxButton button;
    ofxButton button2;
    ofxVec3Slider vec3Slider;
};
