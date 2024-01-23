package a3group4;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.text.DateFormat;
import java.text.SimpleDateFormat;

import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.Timer;

/**
* @file Board.java
* @author Connor John Macaskill
* @date 03 Dec 2014
* @see SLBoard.java
* @see TTTBoard.java
*
* Super class for SLBoard and TTTBoard. Implements variables and methods common to both boards.
* Extends the JFrame class, adding functionality to it.
*/
public abstract class Board extends JFrame
{
	protected int width;
	protected int height;
	protected long startTime;
	protected long timeElapsed;
	protected long hour = 3600000;
	protected JLabel lblTime = new JLabel("Time Elapsed : 00:00:00");
	DateFormat time = new SimpleDateFormat("HH:mm:ss");	
	
	/**
	* Called by subclasses, sets the width and height of the board and starts the board timer.
	* @param width, Width of the board in squares.
	* @param height, Height of the board in squares.
	* @see SLBoard.java
	* @see TTTBoard.java
	*/
	public Board(int width, int height)
	{
		this.width = width;
		this.height = height;
		startTime = System.currentTimeMillis() + hour;
		Timer t = new Timer(1000, new ActionListener(){
			public void actionPerformed(ActionEvent e)
			{
				timeElapsed = System.currentTimeMillis() - startTime;
				lblTime.setText("Time Elapsed : " + time.format(timeElapsed));
			}
		});
		t.start();
	}
	
	public abstract void update();
	public abstract void setUpGame();
	public abstract String getPlayer(int playNum);
}
