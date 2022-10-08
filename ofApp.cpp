#include "ofApp.h"

//#include "fwd.hpp"
#include "ofEvents.h"

void Player::draw() {
    ofSetColor(tricolor);
    ofFill();
    TriangleShape::draw();
    ofSetColor(ofColor::green);
    if (headshow) {
        ofDrawLine(pos, pos + heading() * scaleval * 75);
    }
    if (showsprite) {
    };
}

void TriangleShape::agentDraw(){
    
}

void Agent::draw() {
    ofSetColor(agentColor);
    ofFill();
    TriangleShape::draw();
    ofSetColor(ofColor::green);
    if (headshow) {
        ofDrawLine(pos, pos + heading() * scaleval * 75);
    }
    if (showsprite) {
    };

}
void TriangleShape::draw() {
    ofSetColor(tricolor);
    ofFill();

    ofPushMatrix();
    ofMultMatrix(getMatrix());
    ofDrawTriangle(verts[0], verts[1], verts[2]);
    ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::setup() {
    gui.setup();

    gui.add(button2.setup("show sprite"));
    gui.add(toggle.setup("show heading vector", false));

    //initializing values for (speed,scale)
    //
    gui.add(vec3Slider.setup("x is speed y is scale", ofVec3f(10, 1, 0),
                             ofVec3f(0, 1, 0), ofVec3f(20, 3, 0)));

    //creating vectors that compose triangle in middle of screen
    //
    tri = Player(glm::vec3(-25, 25, 0), glm::vec3(25, 25, 0),
                 glm::vec3(0, -25, 0));
    
    //placing player on grid in middle - 100 on x and y
    tri.pos = glm::vec3(ofGetWindowWidth() / 2.0,
                        ofGetWindowHeight() / 2.0 + 200, 0);
}

//--------------------------------------------------------------
void ofApp::update() {

    if (keymap[OF_KEY_RIGHT]) {
        tri.rotation += 6;
    }
    if (keymap[OF_KEY_LEFT]) {
        tri.rotation -= 6;
    }  
    if (keymap[OF_KEY_UP]) {
        glm::vec3 speedvec = glm::vec3(tri.speed, tri.speed, 0);
        glm::vec3 finalvec = speedvec * tri.heading();
        tri.pos += finalvec;
    }
    if (keymap[OF_KEY_DOWN]) {
        glm::vec3 speedvec = glm::vec3(-tri.speed, -tri.speed, 0);
        glm::vec3 finalvec = speedvec * tri.heading();
        tri.pos += finalvec;
    }

    if (toggle) {
        tri.headshow = true;
    } else {
        tri.headshow = false;
    }

    // agentFollow(Player p);

}
//--------------------------------------------------------------
void ofApp::draw() {
    tri.draw();

    tri.speed = vec3Slider->x;
    tri.scaleval = vec3Slider->y;
    
    

    //collision checking

    if(tri.pos.x > ofGetWindowWidth()){
        tri.pos.x = ofGetWindowWidth();
    }
    if(tri.pos.x < 0) {
        tri.pos.x = 0;
    }
 
    if(tri.pos.y > ofGetWindowHeight()){
        tri.pos.y = ofGetWindowHeight();
    }
    if(tri.pos.y < 0){
        tri.pos.y = 0;
    }


    gui.draw();
}
void ofApp::keyPressed(int key) { keymap[key] = true; }

void ofApp::keyReleased(int key) {
    keymap[key] = false;

    if (keymap[OF_KEY_RIGHT]) {
    }
    if (keymap[OF_KEY_LEFT]) {
    }
    if (keymap[' ']) {
    }
}
//--------------------------------------------------------------
/*void ofapp::keypressed(int key) {
    if (key == of_key_control) {
        ctrlflag = true;
    }
}
*/
//--------------------------------------------------------------
// void ofapp::keyreleased(int key) {
//  if (key == of_key_control) {
//    ctrlflag = false;
//}
//}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
    if (tri.inside(glm::vec3(x, y, 0)) && !drag) {
        tri.tricolor = ofColor::beige;
    } else {
        tri.tricolor = ofColor::blue;
    }
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
    mousePos = glm::vec3(x, y, 0);
    if (insidetri) {
        drag = true;
        displacement = mousePos - beginMousePos;
        cout << displacement << endl;
        tri.pos = tri.pos + displacement;
        beginMousePos = mousePos;
    }
    drag = false;
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
    buttonflag = true;
    beginMousePos = glm::vec3(x, y, 0);
    cout << beginMousePos << endl;
    if (tri.inside(glm::vec3(x, y, 0))) {
        insidetri = true;
        tri.tricolor = ofColor::yellow;
        cout << "INSIDE" << endl;
    }
    if (!tri.inside(glm::vec3(x, y, 0))) {
        insidetri = false;
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
    cout << mousePos << endl;
    endMousePos = mousePos - beginMousePos;
    ctrlflag = false;
    buttonflag = false;
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {}

