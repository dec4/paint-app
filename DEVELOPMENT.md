# Development <br />
### Week 1 <br />
Starting off by implementing the settings window and drawing canvas independently; will integrate brush settings once working. <br />
* Implemented brush color settings (hsba)
* Implemented toggles for brush type as radio buttons
  * Problems with keeping the user from unchecking a tool (one should always be active) UNRESOLVED
* Implementing drawing on canvas
  * ofLine not drawing a line as expected RESOLVED
    * needed to specify width, color, and fill (false)
* Integrating tools and canvas
  * Using ofPath means changing anything in tools will change ALL lines UNRESOLVED
  * Creatiing custom object to hold all data of each line
