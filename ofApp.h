/************************************************************
************************************************************/
#pragma once

/************************************************************
************************************************************/
#include "ofMain.h"
#include "sj_common.h"

/************************************************************
************************************************************/
class ofApp : public ofBaseApp{
private:
	/****************************************
	****************************************/
	enum{
		WIDTH	= 1200,
		HEIGHT	= 1200,
	};
	
	/****************************************
	****************************************/
	int check_id = 0;
	
	ofImage img;
	ofFbo fbo;
	ofFbo fbo_CopyOfImg;
	ofShader shader;
	ofCamera camera;
	
	ofSpherePrimitive sphere;
	ofBoxPrimitive box;
	
	/****************************************
	****************************************/
	void setup_Gui();
	void ClearFbo(ofFbo& fbo);
	void make_fbo_img();
	void set_CamParam();
	
public:
	/****************************************
	****************************************/
	ofApp();
	~ofApp();
	void exit();
	
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	
};
