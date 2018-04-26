# Development <br />
### Week 1 <br />
Starting off by implementing the settings window and drawing canvas independently; will integrate brush settings once working. <br />
* Implemented brush color settings (hsba)
* Implemented toggles for brush type as radio buttons
  * Problems with keeping the user from unchecking a tool (one should always be active) [UNRESOLVED]
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
  * logic issue: when drawing new lines, you can't redo old lines that have been written over [UNRESOLVED]
    * old lines stay in stack; how to distinguish undo lines between valid and invalid? 
