package a3group4;

/**
* @file TTTHuman.java
* @author Priya Patel
* @date 25 Nov 2014
* @see TTTBoard.java 
* @see TTTPlayer.java
*
* This class holds the name and the type of the player aswell as the constructor of the TTTHuman class
*/
public class TTTHuman extends TTTPlayer {

	/**
	* The method that is used are the set names and set type.
	* @param name, the string for the name to be set to
	* @param type, the char for the type to be set
	* @see TTTBoard
	* @see TTTPlayer
	*/	
	public TTTHuman(String name, char type){
		this.setName(name);
		this.setType(type);
	}
}
