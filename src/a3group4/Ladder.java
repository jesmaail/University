package a3group4;

import java.awt.Image;
import java.util.Random;

import javax.swing.ImageIcon;

/**
* @file Ladder.java
* @author Matthew Barrett
* @date 02 Dec 2014
* @see Obstacle.java
* @see SLBoard.java
*
*Ladder, moves player from one to square to a higher square.
*/
public class Ladder extends Obstacle{	
	private final int LOWER_BOUND = 2;
	private final int UPPER_BOUND;
	private final int MIN_DESTINATION;
	private final int MAX_DESTINATION;
	private final int END_SQUARE;
	private final int EVEN = 2;
	
	/**
	* Sets an end destination for the Ladder object.
	* Stops ladder going beyond board limits.
	* @see SLBoard.java
	* @return the highest non-final square if above 99. Type:int
	*/
	private int setDestination(){		
			int tempDest;
			
			do{
				Random rng = new Random(System.currentTimeMillis());
				int randMax = rng.nextInt(MAX_DESTINATION - MIN_DESTINATION);
				randMax += MIN_DESTINATION;
				tempDest = randMax + origin;
			}while(tempDest > END_SQUARE);
			
			return tempDest;
	}
	
	/**
	* Constructs the ladder object, setting its origin and destination.
	* @param maxSquare - Maximum number of squares in the board.
	* @param width - Width of the board in squares.
	* @param height - Height of the board in squares.
	* @see SLBoard.java
	*/
	public Ladder(int maxSquare, int width, int height){
			END_SQUARE = maxSquare;
			UPPER_BOUND = maxSquare-width;
			MIN_DESTINATION = width;
			MAX_DESTINATION = height*(width/EVEN);
			origin = new Random().nextInt(UPPER_BOUND) + LOWER_BOUND;
			destination = setDestination();		
	}
}
