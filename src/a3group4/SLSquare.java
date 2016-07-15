package a3group4;

import java.awt.Color;
import java.awt.Rectangle;

import javax.swing.BorderFactory;
import javax.swing.JLabel;
import javax.swing.SwingConstants;
import javax.swing.border.Border;

/**
* @file SLSquare.java
* @author Laila Al harbi
* @date 30 Nov 2014
* @see SLBoard.java
*
*this class is used to set up the squares in the board  
*/
public class SLSquare extends JLabel{	
	private int position;
	private boolean obstacle = false;
	//Is this square the head of a snake or bottom of a ladder?
	private boolean obstStart;
	private int obstacleDestination;
	
	/**
	* a method to get the position outside of the class    
	* @see SLBoard.java
	* @return position of the square. Type: int
	*/
	public int getPosition(){
		return position;
	}
	
	/**
	* a method to add an obstacle to a square by flagging a boolean true and 
	* holding the obstacles destination and origin  
	* @param destination, where the Obstacle leads to.
	* @param start, whether the square is the start of an obstacle as opposed to the end.
	* @see SLBoard.java
	* @see Snake.java
	* @see Ladder.java
	*/
	public void addObstacle(int destination, boolean start){
		obstacle = true;
		obstStart = start;
		obstacleDestination = destination;
	}
	
	/**
	* a method to get whether a square is the start of an Obstacle.    
	* @see SLBoard.java
	* @see Snake.java
	* @see Ladder.java
	* @return whether the square is the start point of an obstacle. Type:boolean
	*/
	public boolean isObstacleStart(){
		return obstStart;
	}
	
	/**
	* a method to get the destination of the Obstacle held in the square(if any).    
	* @param n/a
	* @see SLBoard.java
	* @see Snake.java
	* @see Ladder.java
	* @return destination of the Obstacle starting at this square, Type: int
	*/
	public int getObstDestination(){
		return obstacleDestination;
	}
	
	/**
	* constructor to set the position and styling of a Snakes and Ladder Square . 
	* @param position, the position of the Square on the Board
	* @param bounds, the bounds of the Square on the Board
	* @param border, the style and colour of the border for the Square to use
	* @param color, the colour for the squares background
	* @see SLBoard.java
	*/
	public SLSquare(int position, Rectangle bounds, Border border, Color color){
		this.position = position;
		setOpaque(true);
		setBackground(color);
		setBounds(bounds);
		setText(Integer.toString(position));
		setHorizontalAlignment(SwingConstants.CENTER);
		setBorder(border);
	}
	
	/**
	* Determines whether the square contains an obstacle
	* @see SLBoard.java
	* @return whether the square holds an Obstacle
	*/
	public Boolean hasObstacle(){	
		return obstacle;
	}

}