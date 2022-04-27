/************************************************************
************************************************************/
#include "ofApp.h"

/************************************************************
************************************************************/

/******************************
******************************/
ofApp::ofApp(){
}
/******************************
******************************/
ofApp::~ofApp(){
	delete Gui_Global;
	
	if(fp_Log) fclose(fp_Log);
}

/******************************
******************************/
void ofApp::exit(){
	printf("\nGood-bye\n");
	fflush(stdout);
}

/******************************
******************************/
void ofApp::setup(){
	/********************
	********************/
	ofSetWindowTitle("study Coord");
	ofSetVerticalSync(true);
	ofSetFrameRate(30);
	ofSetWindowShape(WIDTH, HEIGHT);
	ofSetEscapeQuitsApp(false);
	
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	ofEnableAntiAliasing();
	
	/********************
	********************/
	setup_Gui();
	
	/********************
	********************/
	// ofDisableArbTex();
	img.load("img/jacket.png");
	// ofEnableArbTex();
	
	fbo.allocate(WIDTH, HEIGHT, GL_RGBA);
	ClearFbo(fbo);
	fbo_CopyOfImg.allocate(img.getWidth(), img.getHeight(), GL_RGBA);
	make_fbo_img();
	
	shader.load("sj_shader/sample.vert", "sj_shader/sample.frag");
	
	/********************
	********************/
	camera.setForceAspectRatio(true);
	set_CamParam();
	
	/********************
	********************/
	sphere.set(Gui_Global->Sphere_r, 16); // r, 面の細かさ
	sphere.setPosition(Gui_Global->SpherePos);
	
	box.set(Gui_Global->BoxSize); // size
	box.setPosition(Gui_Global->BoxPos);
}

/******************************
******************************/
void ofApp::make_fbo_img(){
	fbo_CopyOfImg.begin();
		ofBackground(0, 0, 0, 255);
		ofSetColor(255);
		img.draw(0, 0);
	fbo_CopyOfImg.end();
}

/******************************
******************************/
void ofApp::ClearFbo(ofFbo& fbo){
	fbo.begin();
		ofBackground(0, 0, 0, 255);
	fbo.end();
}

/******************************
******************************/
void ofApp::set_CamParam(){
	camera.setPosition(Gui_Global->Cam_Pos);
	camera.setNearClip(Gui_Global->Cam_NearClip);
	camera.setFarClip(Gui_Global->Cam_FarClip);
	
	if(camera.getOrtho() && !Gui_Global->Cam_Ortho)			camera.disableOrtho();
	else if(!camera.getOrtho() && Gui_Global->Cam_Ortho)	camera.enableOrtho();
	
	camera.lookAt(Gui_Global->Cam_LookAt, Gui_Global->Cam_Up);
	if( (camera.isVFlipped() && !Gui_Global->Cam_V_Flip) || (!camera.isVFlipped() && Gui_Global->Cam_V_Flip) ){
		camera.setVFlip(Gui_Global->Cam_V_Flip);
	}
	
	camera.setFov(Gui_Global->Cam_FOV);
	camera.setAspectRatio(Gui_Global->Cam_AspectRatio);
}

/******************************
******************************/
void ofApp::setup_Gui(){
	Gui_Global = new GUI_GLOBAL;
	Gui_Global->setup("param", "gui.xml", 10, 10);
}

/******************************
******************************/
void ofApp::update(){
	set_CamParam();
	
	sphere.set(Gui_Global->Sphere_r, 16); // r, 面の細かさ
	sphere.setPosition(Gui_Global->SpherePos);
	
	box.set(Gui_Global->BoxSize); // size
	box.setPosition(Gui_Global->BoxPos);
}

/******************************
******************************/
void ofApp::draw(){
	/********************
	********************/
	printf("(%5d, %5d)\r", mouseX, mouseY);
	fflush(stdout);
	
	/********************
	********************/
	img.setAnchorPercent(Gui_Global->img_Anchor->x, Gui_Global->img_Anchor->y);
	fbo_CopyOfImg.setAnchorPercent(Gui_Global->img_Anchor->x, Gui_Global->img_Anchor->y);
	
	/********************
	********************/
	if(Gui_Global->SW_fbo)		fbo.begin();
	if(Gui_Global->SW_camera)	camera.begin();
	if(Gui_Global->SW_shader)	shader.begin();
	
	if(Gui_Global->SW_Matrix){
		ofPushMatrix();
		if(!Gui_Global->SW_camera)	ofTranslate(ofGetWidth(), 0);
		ofScale(-1, 1, 1);
	}
	
		ofBackground(0, 0, 0, 255);
		ofSetColor(255);
		
		if(Gui_Global->SW_shader){
			shader.setUniform1i("check_id", check_id);
			shader.setUniform2f("u_resolution", ofGetWidth(), ofGetHeight());
			shader.setUniform2f("u_mouse", mouseX, mouseY);
		}
		
		if(Gui_Global->b_draw_sphere){
			sphere.drawWireframe();
		}else if(Gui_Global->b_draw_box){
			ofPushMatrix();
				ofRotate(Gui_Global->Box_Rotate_deg, Gui_Global->Box_Mat_Rotate_Axis->x, Gui_Global->Box_Mat_Rotate_Axis->y, Gui_Global->Box_Mat_Rotate_Axis->z);
				ofTranslate(Gui_Global->Box_Mat_Translate->x, Gui_Global->Box_Mat_Translate->y, Gui_Global->Box_Mat_Translate->z);
				ofScale(Gui_Global->Box_Mat_Scale->x, Gui_Global->Box_Mat_Scale->y, Gui_Global->Box_Mat_Scale->z);
				
				box.drawWireframe();
			ofPopMatrix();
		}else{
			if(Gui_Global->SW_UseFbo_CopyOfImg)	fbo_CopyOfImg.draw(Gui_Global->img_DrawPos->x, Gui_Global->img_DrawPos->y, ofGetWidth(), ofGetHeight());
			else								img.draw(Gui_Global->img_DrawPos->x, Gui_Global->img_DrawPos->y, Gui_Global->img_DrawPos->z, ofGetWidth(), ofGetHeight());
		}
		
		
	if(Gui_Global->SW_Matrix)	ofPopMatrix();
	
	if(Gui_Global->SW_shader)	shader.end();
	if(Gui_Global->SW_camera)	camera.end();
	if(Gui_Global->SW_fbo)		fbo.end();
	
	/********************
	********************/
	if(Gui_Global->SW_fbo)		fbo.draw(0, 0, ofGetWidth(), ofGetHeight());
	
	/********************
	********************/
	if(Gui_Global->b_Disp){
		Gui_Global->gui.draw();
	}
}

/******************************
******************************/
void ofApp::keyPressed(int key){
	switch(key){
		case '0':
		case '1':
			check_id = key - '0';
			break;
			
		case 'd':
			Gui_Global->b_Disp = !Gui_Global->b_Disp;
			break;
	}
}

/******************************
******************************/
void ofApp::keyReleased(int key){

}

/******************************
******************************/
void ofApp::mouseMoved(int x, int y ){

}

/******************************
******************************/
void ofApp::mouseDragged(int x, int y, int button){

}

/******************************
******************************/
void ofApp::mousePressed(int x, int y, int button){

}

/******************************
******************************/
void ofApp::mouseReleased(int x, int y, int button){

}

/******************************
******************************/
void ofApp::mouseEntered(int x, int y){

}

/******************************
******************************/
void ofApp::mouseExited(int x, int y){

}

/******************************
******************************/
void ofApp::windowResized(int w, int h){

}

/******************************
******************************/
void ofApp::gotMessage(ofMessage msg){

}

/******************************
******************************/
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
