package a3group4;

import java.awt.Image;
import java.util.Random;

import javax.swing.ImageIcon;
/**
* @file Snake.java
* @author Joseph Esmaail
* @date 21 Nov 2014
* @see Obstacle.java
* @see SLBoard.java
*
* Used to determine where a Snake is on a board, and where it will take a player.
*/
public class Snake extends Obstacle{
	
	private final int LOWER_BOUND;
	private final int UPPER_BOUND;
	private final int MIN_DESTINATION;
	private final int MAX_DESTINATION;
	private static final int START_SQUARE = 1;
	
	/**
	* Determines the destination of a Snake object making sure it does not go beyond board limits.
	* @see SLBoard.java
	* @return the destination of the object. Type:int
	*/
	private int setDestination(){
		int tempDest;
		
		do{
	
			Random rng = new Random(System.currentTimeMillis());
			int randMax = rng.nextInt(MAX_DESTINATION - MIN_DESTINATION);
			randMax += MIN_DESTINATION;
			tempDest = origin - randMax;
		}while(tempDest < START_SQUARE);
		
		return tempDest;
	}
	
	/**
	* Constructs the snake object, setting its origin and destination.
	* @param maxSquare - Maximum number of squares in the board.
	* @param width - Width of the board in squares.
	* @param height - Height of the board in squares.
	* @see SLBoard.java
	*/
	public Snake(int maxSquare, int width, int height){
		UPPER_BOUND = maxSquare-1;
		LOWER_BOUND = width+1;
		MIN_DESTINATION = width;
		//Snakes cannot go down more than half the board.
		MAX_DESTINATION = height*(width/2);
		//get origin, between below bottom row and top row.
		origin = new Random().nextInt(UPPER_BOUND - LOWER_BOUND) + LOWER_BOUND;
		destination = setDestination();		
	}
	
}