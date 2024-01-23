package a3group4;

import java.awt.Image;

import javax.swing.ImageIcon;
import javax.swing.JLabel;

/**
* @file SlPlayer.java
* @author Nick Prendergast
* @date 02 Dec 2014
* @see SLHuman.java
* @see SLBoard.java

* The class for the a player in the Snakes and Ladders game that gets the name and color.
*/
public abstract class SLPlayer{	
	protected String name;
	protected String color;
	protected int position;
	
	/**
	* This method retrieves the name of the player
	* @see SLBoard
	* @return the name of the player. Type:String
	*/	
	public String getName(){
		return name;
	}

	/**
	* This method retrieves the color
	* @see SLBoard
	* @return the color of the player. Type:String
	*/	
	public String getColor(){
		return color;
	}
	
	/**
	* This method returns the current players position on the board
	* @see SLBoard
	* @return the position of the player. Type:int
	*/	
	public int getPosition(){
		return position;
	}
	
	/**
	* This method returns JLabel with the Player Piece image
	* @see SLBoard
	* @return the image for the Player's Piece. Type:JLabel
	*/	
	public JLabel getPiece(){
		ImageIcon i = new ImageIcon(this.getClass().getResource("img/"+color+".png"));
		JLabel piece = new JLabel();
		piece.setIcon(i);
		return piece;
	}

	/**
	* This method sets the name of the player
	* @param n, string value that the name will be set to 
	* @see SLBoard
	*/
	public void setName(String n){
		name = n;
	}
	
	/**
	* This sets the color of the player
	* @param c, string value that the color will be set to 
	* @see SLBoard
	*/	
	public void setColor(String c){
		color = c;
	}	
	
	/**
	* This method sets the current players position on the board
	* @param position of the player's piece
	* @see SLBoard
	*/		
	public void setPosition(int position){
		this.position = position;
	}
	
}