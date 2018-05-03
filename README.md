# CS 126 FinalProject <br />
For my final project, I have created a drawing application. This app allows you to adjust settings such as tool type, color, size, and more. There are two modes: timed and free. Free is a blank canvas on which you can draw anything you'd like. Timed will generate a random noun for you to draw, and will have a timer to track how long you take to draw the randomly generated word. In either mode, you will find a help button (?) in the upper right hand corner that will give more details on using the app. Note that saving an image will save the file to the directory bin/savedimages with a unique filename. <br />
## Installation and Deployment <br />
First, you will need to download [OpenFrameworks](http://openframeworks.cc/download/) <br />
Once you have that, download this repository and move it to the directory OF/apps/myApps/ <br />
Using the project generator, import this project folder and click update. <br />
Now you should be able to run the application from the command-line. <br />
```
$ cd {path to project}
$ make
$ makeRunRelease
```
## Screenshots <br />
#### Home Screen: <br />
![picture](bin/screenshots/ScreenshotHome.png) <br />
#### Free Draw: <br />
![picture](bin/screenshots/ScreenshotFree.png) <br />
#### Timed Draw: <br />
![picture](bin/screenshots/ScreenshotTimed.png) <br />
## Testing <br />
The large majority of this project relies heavily on OpenFrameworks methods (drawing to the screen, listening to mouse events, etc.). Due to this, I tested my program using manual testing. <br /> 
Some general things that were tested include:
* Drawing various lines with different settings changed in the tools window
* Ensuring that specific settings in the tool gui are locked when applicable (for example, you can't change the hue when pencil tool is selected)
* Test button functionalities (especially undo and redo, making sure the correct things are removed and placed)
* Checking that keyboard shortcuts work
* Proper switching between display modes depending on what button was pressed, if at all.
