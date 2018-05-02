# Development <br />
### Week 1 <br />
Starting off by implementing the settings window and drawing canvas independently; will integrate brush settings once working. <br />
* Implemented brush color settings (hsba)
* Implemented toggles for brush type as radio buttons
  * Problems with keeping the user from unchecking a tool (one should always be active) [resolved]
* Implementing drawing on canvas
  * ofLine not drawing a line as expected [resolved]
    * needed to specify width, color, and fill (false)
### Week 2 <br />
* Integrating tools and canvas
  * Using ofPath means changing anything in tools will change ALL lines [resolved]
    * fix: created custom object to hold all data of each line
* Issue with max radius size (not very big) [UNRESOLVED]
  * fix? https://forum.openframeworks.cc/t/ofsetlinewidth-maximum-value/3751/2
* Created vector and stack to hold AppLine objects (no longer using ofPath)
* Implemented undo and redo buttons
  * logic issue: when drawing new lines, you can't redo old lines that have been written over [resolved]
    * old lines stay in stack; how to distinguish undo lines between valid and invalid? 
      * clear undo stack (now named redo_lines for clarity) whenever new line is drawn
* Implemented clear (note: cannot be undone)
* Implemented save
  * Tried using system dialogue box, but wasn't working properly (ubuntu/linux problem?)
  * Issue: first implementation would save screenshot of tool gui, not canvas
    * ~~Fixed, but with less than ideal implementation~~
    * Now useing ofFbo
* Added keyboard shortcuts; functions can be called from either canvas or toolgui
* Note: not using custom hsbaColor object anymore (wanted to use ofParameter with it, but couldn't figure out how ofParameter creates sliders just with ofColor object, therefore couldn't figure out how to duplicate using custom object)
### Week 3 <br />
* Using drawing tool object where each tool type has its own class with the default initializations
* Added help button to display information about how to use the app
* Added toggle to determine whether or not the canvas is bounded
* Added ability to change background color
* Modified slightly to draw depending on display enum
  * Added timed mode that allows the user to draw on canvas the same way, but prints a bar at the bottom containing a noun to draw and the time it's taking for them to draw
