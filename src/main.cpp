#include "ofMain.h"
#include "ofApp.h"
#include "toolgui.h"
#include "ofAppGLFWWindow.h"


// Reference: OpenFrameworks example events/multiWindowExample


int main( ) {

	// MY NOTE: use makeShared? (https://docs.microsoft.com/en-us/cpp/cpp/how-to-create-and-use-shared-ptr-instances)

	ofGLFWWindowSettings settings;

	// Settings for first window: canvas
	settings.width = 800;
	settings.height = 600;
	settings.setPosition(ofVec2f(0,0));
	settings.resizable = true;
	shared_ptr<ofAppBaseWindow> main_window = ofCreateWindow(settings);

	// Settings for second window: tools
	settings.width = 220;
	settings.height = 350;
	settings.setPosition(ofVec2f(900,0));
	settings.resizable = false;
	shared_ptr<ofAppBaseWindow> tool_window = ofCreateWindow(settings);

	// Create app objects and pointers
	shared_ptr<ofApp> canvas_gui(new ofApp);
	shared_ptr<ToolGui> tool_gui(new ToolGui);
	canvas_gui->tools = tool_gui;
	tool_gui->canvas = canvas_gui;

	// Run app to corresponding window
	ofRunApp(tool_window, tool_gui);
	ofRunApp(main_window, canvas_gui);
	ofRunMainLoop();

}



/* NOTES

	OBJECT OBJECT INSTEAD OF JUST LINE; DO MANY THINGS
	~/OF/OF/examples/graphics/polygonExample
	(probably won't figure this out)
		-abstract class of 

	ADD HELP ICON TOP RIGHT

	CHANGE PREVIEW TO BAR INSTEAD OF TINY 
		-color preview (square)
		-radius preview (tiny dot)

	ADD ALLOW MOUSE EXIT

	get rid of thickness if can't fix segfault


*/