package a3group4;


import java.awt.Color;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.Timer;

/**
* @file TTTSquare.java
* @author Laila Alharbi
* @date 3 Nov 2014
* @see TTTBoard.java 
*
* This class is used to set up the square on the tic-tac-toe Board,and check the status of the square (empty,X,O).
*/
public class TTTSquare extends JButton{
	private int position;
	private char type;	
	private boolean active = true;
	private final int SQ_SIZE = 60;
	
	
    private final int FADE_TIME = 10;
    private final int MAX_ALPHA = 255;
    private final int ALPHA_INC = 5;
    private int alpha;

	/**
	* A method to get the position outside of the class.
	* @param n/a
	* @see TTTBoard.java
	* @return position of the square
	*/
	public int getPosition(){
		return position;
	}
	
	/**
	* A method to get the size of the square.   
	* @param n/a
	* @see TTTBoard.java
	* @return size of the square
	*/
	public int getSquareSize(){
		return SQ_SIZE;
	}
	
	/**
	* Getter  method to access the type outside of the class.
	* @return type 
	*/
	public char getType(){
		return type;
	}
	/**
	* Getter  method to access active outside of the class.
	* @return type 
	*/
	public boolean getActive(){
		return active;
	}

	/**
	* Setter  method to set up the type.  
	* @param char type
	*
	*/
	public void setType(char type){
		this.type = type;	
	}

    /**
    * Setter method to set the active status of a square.
    * @param boolean active
    *
    */
    public void setActive(boolean active) {
        this.active = active;
    }
    
    /**
     * Starts the square fading in.
     * @see fade
     */
    public void fadeAlpha()
    {
        Timer t = new Timer(FADE_TIME, fade);
        t.start();
    }
    
    
    ActionListener fade = new ActionListener() {		
		public void actionPerformed(ActionEvent evt) {	
			setForeground(new Color(0, 0, 0, alpha));
			if (alpha < MAX_ALPHA) {
				alpha += ALPHA_INC;
			}
			else {
				((Timer)evt.getSource()).stop();
				alpha = 0;
			}
			System.out.println(alpha);
		}
	};

	/**
	* the constructor is to initialize active 
	* @param booleanactive
	* @see TTTBoard.java
	*
	*/
	public TTTSquare(int position){
		this.position = position;
	}
	

}
