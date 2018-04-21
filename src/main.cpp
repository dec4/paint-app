#include "ofMain.h"
#include "ofApp.h"
#include "toolgui.h"
#include "ofAppGLFWWindow.h"


// Reference: OpenFrameworks example events/multiWindowExample

int main( ) {

	/*
	// PROCESS NOTE: starting with tools as one windowed app
	// Can't run using tools without multi-window implementation, 
	// so copied everything to ofApp FOR NOW ONLY

	ofSetupOpenGL(1024, 768, OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());
	*/


// Reference: OpenFrameworks example events/multiWindowExample


	// MY NOTE: use makeShared (https://docs.microsoft.com/en-us/cpp/cpp/how-to-create-and-use-shared-ptr-instances)

	ofGLFWWindowSettings settings;

	settings.width = 600;
	settings.height = 600;
	settings.setPosition(ofVec2f(0,0));
	settings.resizable = true;
	shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);

	settings.width = 600;
	settings.height = 300;
	settings.setPosition(ofVec2f(700,0));
	settings.resizable = false;
	shared_ptr<ofAppBaseWindow> guiWindow = ofCreateWindow(settings);

	shared_ptr<ofApp> mainApp(new ofApp);
	shared_ptr<ToolGui> guiApp(new ToolGui);
	mainApp->gui = guiApp;

	ofRunApp(guiWindow, guiApp);
	ofRunApp(mainWindow, mainApp);
	ofRunMainLoop();

}