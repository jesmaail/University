package a3group4;

/**
* @file TTTPlayer.java
* @author Priya Patel
* @date 25 Nov 2014
* @see TTTHuman.java 
* @see TTTBoard.java
*
* This class gets the name of the player and the icon type
*/
public abstract class TTTPlayer {
	private String name;
	private char type;
	
	/**
	* This method gets the player name.
	* @see TTTBoard
	* @return String containing the player name 
	*/
	public String getName(){
		return name;
	}
	
	/**
	* This method gets the player type.
	* @see TTTBoard
	* @return Character that determines whether a player is X or O.
	*/
	public char getType(){
		return type;
	}
	
	/**
	* This method sets the player name.
	* @see TTTBoard
	* @param s, the string for the name to be set to
	*/
	public void setName(String s) {
        name = s;
    }
	
	/**
	* This method sets the player type.
	* @see TTTBoard
	* @param character to set the players type (X or O).
	*/
	public void setType(char type) {
        this.type = type;
    }
}