#include "ofMain.h"
#include "ofApp.h"
#include "toolgui.h"
#include "ofAppGLFWWindow.h"


// Reference: OpenFrameworks example events/multiWindowExample

// USE STACK: UNDO AND REDO
// ONE FOR CURRENT AND ONE FOR UNDO (REDO COMES FROM LAST ADDED TO UNDO)

int main( ) {

// Reference: OpenFrameworks example events/multiWindowExample


	// MY NOTE: use makeShared (https://docs.microsoft.com/en-us/cpp/cpp/how-to-create-and-use-shared-ptr-instances)

	ofGLFWWindowSettings settings;

	settings.width = 600;
	settings.height = 600;
	settings.setPosition(ofVec2f(0,0));
	settings.resizable = true;
	shared_ptr<ofAppBaseWindow> main_window = ofCreateWindow(settings);

	settings.width = 600;
	settings.height = 300;
	settings.setPosition(ofVec2f(700,0));
	settings.resizable = false;
	shared_ptr<ofAppBaseWindow> tool_window = ofCreateWindow(settings);

	shared_ptr<ofApp> canvas(new ofApp);
	shared_ptr<ToolGui> tool_gui(new ToolGui);
	canvas->gui = tool_gui;

	ofRunApp(tool_window, tool_gui);
	ofRunApp(main_window, canvas);
	ofRunMainLoop();

}