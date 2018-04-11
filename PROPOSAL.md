# Project Proposal
### Overview
My idea for the final project is to create a drawing application (similar to MS Paint). The user would be able to draw something onto a canvas using their mouse. Some main features that I would like to include are saving and loading image files, options for different brush types (pencil, marker, eraser, etc.), and sliders for settings such as opacity, size, and color. 
### Resources
**Links to portions of the OpenFrameworks documentation that I suspect will be useful for this project:**
The graphics module (in particular, ofImage) can be used for image modifications:
http://openframeworks.cc/documentation/graphics/ofImage/
To get data regarding mouse movement for drawing, I'll use parts of the events module:
http://openframeworks.cc/documentation/events/
I also found files posted to GitHub for a workshop on drawing using OpenFrameworks:
https://github.com/ofZach/drawing-examples
### Extending This Project
The reason I wanted to create a drawing application is because it is part of a bigger project idea I had earlier this semester. Originally, I wanted to be able to use some automatic image captioning system that could generate a caption for a random image to be used as a prompt for the user to draw. Using object recognition, there would potentionally be blank boxes on the canvas to give an idea of where main objects of the image are located. At the end, the original image that the caption came from would be revealed and the user would be able to compare their result with the original. I found some tools that may be able to help me accomplish this (mainly some of Google's resources in TensorFlow), however I'm not sure whether I could accomplish all of this, which is why this information is here in an extended portion of my proposal. Below, I've listed links for Google's open source models that implement what I'm interested in.
Google Show and Tell (Image Captioning):
https://research.googleblog.com/2016/09/show-and-tell-image-captioning-open.html
Google Object Detection:
https://research.googleblog.com/2017/06/supercharge-your-computer-vision-models.html
