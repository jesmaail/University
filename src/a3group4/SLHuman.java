package a3group4;

/**
* @file SLHuman.java
* @author Nick Prendergast
* @date 03 Dec 2014
* @see SLBoard.java
* @see SLPlayer.java
* 
* this class holds the name and the color of the player.
*/
public class SLHuman extends SLPlayer{
	
	/**
	* The method used is to the name and color
	* @param name, the string value that the name will be set to
	* @param color, the string value that the color will be set to
	* @see SLBoard
	* @see SLPlayer
	*/
	SLHuman(String name, String color){
		this.name = name;
		this.color = color;
		position = 1;
	}

}
