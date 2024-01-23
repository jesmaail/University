package a3group4;

import java.awt.Image;
/**
* @file Obstacle.java
* @author Joseph Esmaail
* @date 21 Nov 2014
* @see Snake.java
* @see Ladder.java
* @see SLBoard.java
*
* The Abstract superclass for Obstacles on a Snakes and Ladders Board
*/
public abstract class Obstacle {	
	protected int origin;
	protected int destination;
	
	/**
	* Retrieves the Origin point of an Obstacle object.
	* @see Snake.java
	* @see Ladder.java
	* @see SLBoard.java
	* @return the origin of the obstacle object. Type:int
	*/
	public int getOrigin(){		
		return origin;		
	}
	
	/**
	* Retrieves the Destination point of an Obstacle object.
	* @see Snake.java
	* @see Ladder.java
	* @see SLBoard.java
	* @return the destination of the obstacle object. Type:int
	*/
	public int getDestination(){		
		return destination;
	}
	
}
