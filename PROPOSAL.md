# Project Proposal <br />
### Overview <br />
My idea for the final project is to create a drawing application (similar to MS Paint). The user would be able to draw something onto a canvas using their mouse. Some main features that I would like to include are saving and loading image files, options for different brush types (pencil, marker, eraser, etc.), and sliders for settings such as opacity, size, and color.  <br />
### Resources <br />
**Links to portions of the OpenFrameworks documentation that I suspect will be useful for this project:** <br />
For the GUI: <br />
http://openframeworks.cc/documentation/ofxGui/ <br />
The graphics module (in particular, ofImage) can be used for image modifications: <br />
http://openframeworks.cc/documentation/graphics/ofImage/ <br />
Parts of the events module could also be used to get data such as mouse movement for drawing: <br />
http://openframeworks.cc/documentation/events/ <br />
I also found files posted to GitHub for a workshop on drawing using OpenFrameworks: <br />
https://github.com/ofZach/drawing-examples <br />
### Extending This Project (not included)<br />
The reason I wanted to create a drawing application is that it is part of a bigger project idea I had earlier this semester. Originally, I wanted to be able to use some automatic image captioning system that could generate a caption for a random image to be used as a prompt for the user to draw. Using object recognition, there would potentionally be blank boxes on the canvas to give an idea of where main objects of the image are located. At the end, the original image that the caption came from would be revealed and the user would be able to compare their result with the original. I found some tools that may be able to help me accomplish this (mainly some of Google's resources in TensorFlow), however I'm not sure whether I could accomplish all of this, which is why this information is here in an extended portion of my proposal. Below, I've listed links for Google's open source models that implement what I'm interested in. <br />
<br />
Google Show and Tell (Image Captioning): <br />
https://research.googleblog.com/2016/09/show-and-tell-image-captioning-open.html <br />
Google Object Detection: <br />
https://research.googleblog.com/2017/06/supercharge-your-computer-vision-models.html <br />
