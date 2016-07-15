package a3group4;

import javax.swing.*;
import javax.swing.border.Border;
import javax.swing.border.LineBorder;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.geom.Line2D;
import java.util.ArrayList;
import java.util.List;

/**
* @file TTTBoard.java
* @author Kieran Hedditch
* @date 03 Dec 2014
* @see Board.java
* @see TTTSquare.java
* @see TTTPlayer.java
* @see TTTHuman.java
* @see a3group4.MainMenu.java
*
* The board where Tic Tac Toe is played. Contains all logic and visuals shown by the board
*/
public class TTTBoard extends Board {

	private TTTSquare[][] squares = new TTTSquare[8][8];
	private ArrayList<TTTPlayer> playerList;
    private final int WIN_NUMBER = 5;
    private final int JLABEL_WIDTH = 150;
    private final int JLABEL_HEIGHT = 50;
    private final int RESET_X = 550;
    private final int RESET_Y = 380;
    private final int BACK_X = 550;
    private final int BACK_Y = 450;
    private final int PLAYER_LABEL_X = 550;
    private final int PLAYER_LABEL_Y = 150;
    private final int TIME_LABEL_X = 550;
    private final int TIME_LABEL_Y = 0;
    private final int TIME_LABEL_WIDTH = 500;
    private final int TIME_LABEL_HEIGHT = 35;
    private final int FONT_SIZE = 20;
    private final int PADDING = 20;
    private final int EXTRA_H_PAD = 20;
    private final Color BACK = new Color(238, 238, 238, 255);
    private final Color FADED = new Color(0, 0, 0, 50);
    private final Color WINNER_PURPLE = new Color(0, 0, 0, 255);
    private final int MODEVEN = 2;
    private boolean gameWon = false;
    private JLabel player1;
    private JLabel player2;
    private Border selectedBorder = new LineBorder(Color.PINK, 3);
    private int totalMoves = 1;
    private ArrayList<TTTSquare> winningSquaresVert = new ArrayList<TTTSquare>();
    private ArrayList<TTTSquare> winningSquaresHoriz = new ArrayList<TTTSquare>();
    private ArrayList<TTTSquare> winningSquaresDiagPos = new ArrayList<TTTSquare>();
    private ArrayList<TTTSquare> winningSquaresDiagNeg = new ArrayList<TTTSquare>();
    private TTTSquare selSq;
    private int sqSize;

    /**
     * This is the constructor. It populates an arraylist with TTTSquare objects
     * Also sends important details to Board.java and sets up the event listener
     * for when players click the squares
     *
     * @param int width, Width of the desired board. dictates how many squares wide the game
     * @param int height, Height of the board. dictates how many squares long the board is
     * @param ArrayList<TTTPlayer>, PlayerList, contains the player objects
     * @see Board.java
     * @see MainMenu.java
     * @see TTTPlayer.java
     */
    public TTTBoard(int width, int height, ArrayList<TTTPlayer>playerList) {
		super(width, height);
		super.getContentPane().setBackground(BACK);

		int pos = 0;

        //Iterate through all possible squares in the board and create new objects for them
		for(int x = 0; x < width; x++) {
			for(int y = 0; y < height; y++) {
				squares[x][y] = new TTTSquare(pos);
                final TTTSquare square = getSquare(x, y);
                
                square.setFont(new Font(square.getFont().getName(),
                		Font.PLAIN,
                		FONT_SIZE));
                square.setFocusPainted(false);
                square.setBackground(BACK);
                square.setForeground(new Color(0, 0, 0, 0));
                if (x == 0 && y == 0) {
                	square.setBorder(BorderFactory.createMatteBorder(0, 0, 1, 1, Color.GRAY));
                }
                else if (x == 0 && y == height - 1) {
                	square.setBorder(BorderFactory.createMatteBorder(1, 0, 0, 1, Color.GRAY));
                }
                else if (x == width - 1 && y == 0) {
                	square.setBorder(BorderFactory.createMatteBorder(0, 1, 1, 0, Color.GRAY));
                }
                else if (x == width-1 && y == height-1) {
                	square.setBorder(BorderFactory.createMatteBorder(1, 1, 0, 0, Color.GRAY));
                }
                else if (y == 0) {
                	square.setBorder(BorderFactory.createMatteBorder(0, 1, 1, 1, Color.GRAY));
                }
                else if (y == height - 1) {
                	square.setBorder(BorderFactory.createMatteBorder(1, 1, 0, 1, Color.GRAY));
                }
                else if (x == 0) {
                	square.setBorder(BorderFactory.createMatteBorder(1, 0, 1, 1, Color.GRAY));
                }
                else if (x == width - 1) {
                	square.setBorder(BorderFactory.createMatteBorder(1, 1, 1, 0, Color.GRAY));
                }
                else {
                	square.setBorder(BorderFactory.createMatteBorder(1, 1, 1, 1, Color.GRAY));
                }
                pos++;
                squares[x][y].addActionListener(new ActionListener() {
                    public void actionPerformed(ActionEvent e) {
                        if (square.getActive()) {
                            click(square);
                            totalMoves++;
                        }
                    }
                });
			}
		}

		this.playerList = playerList;
        this.setUpGame();
	}
    
    /**
     * This getter method returns the name of a player based on their player number
     *
     * 
     * @param int playNum, an integer that tells the method which player name to retrieve
     * @return String, returns the name of the player requested 
     * @see TTTPlayer.java
     */
	public String getPlayer(int playNum) {
		return playerList.get(playNum).getName();
	}

    /**
     * This getter method returns the TTTSquare object at a certain x and y position
     *
     * 
     * @param int x, the x value fed into the arraylist
     * @param int y, the y value fed into the arraylist
     * @return TTTSquare, returns the TTTSquare object given the coords/place in the arraylist
     * @see TTTSquare.java
     */
    public TTTSquare getSquare(int x, int y) {
		return squares[x][y];
	}
    
    /**
     * This is the click method that executes when a square is clicked
     * This sets the type and text of the button
     * This method returns a TTTSquare object is sent to apply methods to it like setText etc
     *
     * @param TTTSquare square, the TTTSquare object which is also a JButton object
     * @see TTTSquare.java
     */
    void click(final TTTSquare square) {
        if (totalMoves % MODEVEN == 0) {
            square.setType('O');
            square.setText("O");
            square.setActive(false);

            player1.setBorder(selectedBorder);
            player2.setBorder(null);
        }
        else {
            square.setType('X');
            square.setText("X");
            square.setActive(false);

            player2.setBorder(selectedBorder);
            player1.setBorder(null);
        }
        
        square.fadeAlpha();
        update();
    }
    


	/**
	* This method gets called after each click in order to check if there is a winner
	*
	* @see TTTPlayer.java
	*/
	public void update() {
		
        if (verticalCheck()) {
            String name = "";
            char sType = winningSquaresVert.get(0).getType();
            for (int i = 0; i < playerList.size(); i++) {
                char pType = playerList.get(i).getType();
                if (sType == pType) {
                    name = playerList.get(i).getName();
                    if (i == 0) {
                        player1.setVisible(false);
                        player2.setText("<html>WINNER: " + name + "<br />AS TYPE: " + pType + "</html>");
                    }
                    else {
                        player2.setVisible(false);
                        player1.setText("<html>WINNER: " + name + "<br />AS TYPE: " + pType + "</html>");
                    }
                }
            }

            gameWon = true;
            
            for (int x = 0; x < super.width; x++) {
        		for (int y = 0; y< super.height; y++) {
        			TTTSquare tSquare = squares[x][y];
        			
    				tSquare.setForeground(FADED);
        		}
        	}
            for (int i = 0; i < winningSquaresVert.size(); i++) {
            	winningSquaresVert.get(i).setForeground(WINNER_PURPLE);            	
            }
            
            JOptionPane.showMessageDialog(null, "Congratulations " + name + "!\n You won vertically!" );
            new MainMenu().main(null);
            this.dispose();
        }
        else if (horizontalCheck()) {
            String name = "";
            char sType = winningSquaresHoriz.get(0).getType();
            for (int i =0; i < playerList.size(); i++) {
                char pType = playerList.get(i).getType();
                if (sType == pType) {
                    name = playerList.get(i).getName();
                    if (i == 0) {
                        player1.setVisible(false);
                        player2.setText("<html>WINNER: " + name + "<br />AS TYPE: " + pType + "</html>");
                    }
                    else {
                        player2.setVisible(false);
                        player1.setText("<html>WINNER: " + name + "<br />AS TYPE: " + pType + "</html>");
                    }
                }
            }

            gameWon = true;
            
            for (int x = 0; x < super.width; x++) {
        		for (int y = 0; y< super.height; y++) {
        			TTTSquare tSquare = squares[x][y];
        			
    				tSquare.setForeground(FADED);
        		}
        	}
            for (int i = 0; i < winningSquaresHoriz.size(); i++) {
            	winningSquaresHoriz.get(i).setForeground(WINNER_PURPLE);            	
            }
            
            JOptionPane.showMessageDialog(null, "Congratulations " + name + "!\n You won horizontally!" );
            new MainMenu().main(null);
            this.dispose();
        }
        else if (diagonalCheckPos()) {
            String name = "";
            char sType = winningSquaresDiagPos.get(0).getType();
            for (int i =0; i < playerList.size(); i++) {
                char pType = playerList.get(i).getType();
                if (sType == pType) {
                    name = playerList.get(i).getName();
                    if (i == 0) {
                        player1.setVisible(false);
                        player2.setText("<html>WINNER: " + name + "<br />AS TYPE: " + pType + "</html>");
                    }
                    else {
                        player2.setVisible(false);
                        player1.setText("<html>WINNER: " + name + "<br />AS TYPE: " + pType + "</html>");
                    }
                }
            }

            gameWon = true;
            
            for (int x = 0; x < super.width; x++) {
        		for (int y = 0; y< super.height; y++) {
        			TTTSquare tSquare = squares[x][y];
        			
    				tSquare.setForeground(FADED);
        		}
        	}
            for (int i = 0; i < winningSquaresDiagPos.size(); i++) {
            	winningSquaresDiagPos.get(i).setForeground(WINNER_PURPLE);            	
            }
            
            JOptionPane.showMessageDialog(null, "Congratulations " + name + "!\n You won diagonally!" );
            new MainMenu().main(null);
            this.dispose();
        }
        else if (diagonalCheckNeg()) {
            String name = "";
            char sType = winningSquaresDiagNeg.get(0).getType();
            for (int i =0; i < playerList.size(); i++) {
                char pType = playerList.get(i).getType();
                if (sType == pType) {
                    name = playerList.get(i).getName();
                    if (i == 0) {
                        player1.setVisible(false);
                        player2.setText("<html>WINNER: " + name + "<br />AS TYPE: " + pType + "</html>");
                    }
                    else {
                        player2.setVisible(false);
                        player1.setText("<html>WINNER: " + name + "<br />AS TYPE: " + pType + "</html>");
                    }
                }
            }

            gameWon = true;
            for (int x = 0; x < super.width; x++) {
        		for (int y = 0; y< super.height; y++) {
        			TTTSquare tSquare = squares[x][y];
        			
    				tSquare.setForeground(FADED);
        		}
        	}
            for (int i = 0; i < winningSquaresDiagNeg.size(); i++) {
            	winningSquaresDiagNeg.get(i).setForeground(WINNER_PURPLE);            	
            }
            JOptionPane.showMessageDialog(null, "Congratulations " + name + "!\n You won diagonally!" );
            new MainMenu().main(null);
            this.dispose();
        }
        else if (drawCheck()) {

            int crosses = 0;
            int naughts = 0;
            for (int x = 0; x < super.width; x++) {
                for (int y = 0; y < super.height; y++) {
                    if (!(getSquare(x,y).getActive()) && getSquare(x, y).getType() == 'X') {
                        crosses++;
                    }
                    else if (!(getSquare(x,y).getActive()) && getSquare(x, y).getType() == 'O') {
                        naughts++;
                    }
                }
            }

            JOptionPane.showMessageDialog(null, "It's a draw! All the squares are full.\n "
                    + "In the end there were " + crosses + " crosses, and " + naughts + " naughts!" );
            new MainMenu().main(null);
            this.dispose();
        }        
	}

    /**
     * This method is the win checker. It will check all squares and work out if
     * the next square vertically if they are the same type. If so then that object
     * is added to a list and the length of the unbroken line increments
     *
     * @see TTTSquare.java
     * @return boolean, returns either true or false if there is a winning line vertically
     */
	boolean verticalCheck () {
        //Vertical check
        winningSquaresVert.clear();
        for (int x = 0; x < super.width; x++) {
            int lineLength = 1;
            for (int y = 0; y < super.height; y++) {
                TTTSquare square = getSquare(x, y);
                char type = square.getType();

                if (!(square.getActive())) {
                    winningSquaresVert.add(square);
                    if (y == super.height - 1) {
                		if (lineLength >= WIN_NUMBER) {
                			break;
                		}
                		else {
                			winningSquaresVert.clear();
                			lineLength = 1;
                			break;
                		}
                	}
                    else if (lineLength >= WIN_NUMBER) {
                    	if (square.getType() != winningSquaresVert.get(0).getType()) {
                    		break;
                    	}
                    }
                    else if (this.getSquare(x, y + 1).getType() == type) {
                        lineLength++; //If two adjacent squares are the same then inc
                    } 
                    else if (this.getSquare(x, y + 1).getType() != type && lineLength < WIN_NUMBER) {
                        lineLength = 1;
                        winningSquaresVert.clear();
                    }
                }
            }
            if (lineLength >= WIN_NUMBER) {
                if (winningSquaresVert.get(winningSquaresVert.size()-1).getType() != winningSquaresVert.get(0).getType()) {
                	winningSquaresVert.remove(winningSquaresVert.size()-1);
                }
                return true;
            }
        }
        return false;
    }

    /**
     * This method is the win checker. It will check all squares and work out if
     * the next square horizontally if they are the same type. If so then that object
     * is added to a list and the length of the unbroken line increments
     *
     * @see TTTSquare.java
     * @return boolean, returns either true or false if there is a winning line horizontally
     */
	boolean horizontalCheck () {
        //Vertical check
        winningSquaresHoriz.clear();
        for (int y = 0; y < super.height; y++) {
            int lineLength = 1;
            for (int x = 0; x < super.width; x++) {
                TTTSquare square = getSquare(x, y);
                char type = square.getType();

                if (!(square.getActive())) {
                    winningSquaresHoriz.add(square);
                    if (x == super.height-1) {
                    	if (lineLength >= WIN_NUMBER) {
                			break;
                		}
                		else {
                			winningSquaresHoriz.clear();
                			lineLength = 1;
                			break;
                		}
                    } 
                    else if (lineLength >= WIN_NUMBER) {
                    	if (square.getType() != winningSquaresHoriz.get(0).getType()) {
                    		break;
                    	}
                    }
                    else if (this.getSquare(x + 1, y).getType() == type) {
                        lineLength++;
                    } 
                    else if (this.getSquare(x + 1, y).getType() != type && lineLength < WIN_NUMBER) {
                        lineLength = 1;
                        winningSquaresHoriz.clear();
                    }
                }
            }
            if (lineLength >= WIN_NUMBER) {
                if (winningSquaresHoriz.get(winningSquaresHoriz.size()-1).getType() != winningSquaresHoriz.get(0).getType()) {
                	winningSquaresHoriz.remove(winningSquaresHoriz.size()-1);
                }
                return true;
            }
        }
        return false;
    }

    /**
     * This method is the win checker. It will check all squares and work out if
     * the next square diagonally if they are the same type. If so then that object
     * is added to a list and the length of the unbroken line increments.
     * A diagonal line can go two ways and this method check the next square down
     * and right. There is a separate method the check the other way.
     *
     * @see TTTSquare.java
     * @return boolean, returns either true or false if there is a winning line diagonally positive (increasing in both x and y)
     */
    boolean diagonalCheckPos() {
        //Diagonal check
        winningSquaresDiagPos.clear();
        int lineLength = 1;
        for (int x = 0; x < super.width; x++) {
            for (int y = 0; y < super.height; y++) {
                
            	TTTSquare square = getSquare(x, y);
                char type = square.getType();

                if (!(square.getActive())) {  
                	if (x == super.width-1 || y == super.height-1) {
                    	if (lineLength >= WIN_NUMBER) {
                    		winningSquaresDiagPos.add(square);
                    		if (square.getType() != winningSquaresDiagPos.get(0).getType()) {
                        		return true;
                        	}
                        	else if (winningSquaresDiagPos.get(winningSquaresDiagPos.size()-1).getType() != winningSquaresDiagPos.get(0).getType()) {
                            	winningSquaresDiagPos.remove(winningSquaresDiagPos.size()-1);
                            }
                		}
                		else {
                			winningSquaresDiagPos.clear();
                			lineLength = 1;
                			break;
                		}
                    } 
                    else if (lineLength >= WIN_NUMBER) {
                    	if (square.getType() == winningSquaresDiagPos.get(0).getType()) {
                    		winningSquaresDiagPos.add(square);
                    		return true;
                    	}
                    	else if (winningSquaresDiagPos.get(winningSquaresDiagPos.size()-1).getType() != winningSquaresDiagPos.get(0).getType()) {
                        	winningSquaresDiagPos.remove(winningSquaresDiagPos.size()-1);
                        }
                    	lineLength++;
                    }
                    else if (this.getSquare(x + 1, y + 1).getType() == type) {
                        lineLength++;
                        winningSquaresDiagPos.add(square);
                        x++;
                    } 
                    else if (this.getSquare(x + 1, y + 1).getType() != type && lineLength < WIN_NUMBER) {
                        lineLength = 1;
                        winningSquaresDiagPos.clear();
                    }
                }
            }
        }
        return false;
    }

    /**
     * This method is the win checker. It will check all squares and work out if
     * the next square diagonally if they are the same type. If so then that object
     * is added to a list and the length of the unbroken line increments.
     * A diagonal line can go two ways and this method check the next square down
     * and right. There is a separate method the check the other way.
     *
     * @see TTTSquare.java
     * @return boolean, returns either true or false if there is a winning line diagonally negative increasing in y but decreasing in x
     */
    boolean diagonalCheckNeg () {

    	winningSquaresDiagNeg.clear();
        int lineLength = 1;
        for (int x = super.width - 1; x > 0; x--) {
            for (int y = 0; y < super.height; y++) {
                
            	TTTSquare square = getSquare(x, y);
                char type = square.getType();

                if (!(square.getActive())) {  
                	if (x == 0 || y == super.height-1) {
                    	if (lineLength >= WIN_NUMBER) {
                    		winningSquaresDiagNeg.add(square);
                    		if (square.getType() != winningSquaresDiagNeg.get(0).getType()) {
                        		return true;
                        	}
                        	else if (winningSquaresDiagNeg.get(winningSquaresDiagNeg.size()-1).getType() != winningSquaresDiagNeg.get(0).getType()) {
                            	winningSquaresDiagNeg.remove(winningSquaresDiagNeg.size()-1);
                            }
                		}
                		else {
                			winningSquaresDiagNeg.clear();
                			lineLength = 1;
                			break;
                		}
                    } 
                    else if (lineLength >= WIN_NUMBER) {
                    	if (square.getType() == winningSquaresDiagNeg.get(0).getType()) {
                    		winningSquaresDiagNeg.add(square);
                    		return true;
                    	}
                    	else if (winningSquaresDiagNeg.get(winningSquaresDiagNeg.size()-1).getType() != winningSquaresDiagNeg.get(0).getType()) {
                        	winningSquaresDiagNeg.remove(winningSquaresDiagNeg.size()-1);
                        }
                    	lineLength++;
                    }
                    else if (this.getSquare(x - 1, y + 1).getType() == type) {
                        lineLength++;
                        winningSquaresDiagNeg.add(square);
                        x--;
                    } 
                    else if (this.getSquare(x - 1, y + 1).getType() != type && lineLength < WIN_NUMBER) {
                        lineLength = 1;
                        winningSquaresDiagNeg.clear();
                    }
                }
            }
        }
        return false;
    }

    /**
     * This method checks to see if it is a draw by summing the total number of selected
     * squares and comparing the the maximum there could be
     * ie filling the entire board
     *
     * @see TTTSquare.java
     * @return boolean, returns true if all squares have an X or O in them and false otherwise
     */
    boolean drawCheck() {
        //Check if draw
        //ie game is over when all squares full and no other win condition
        int c = 0; //This counts all the active squares
        for (int x = 0; x < super.width; x++) {
            for (int y = 0; y < super.height; y++) {
                TTTSquare square = getSquare(x, y);
                if (!(square.getActive())) {
                    c++;
                }

            }
        }
        if (c == super.width * super.height) {
            return true;
        }
        return false;
    }

    /**
     * This method sets up the frame and board.
     * It sets the size and dimensions of the frame.
     * It also adds the buttons to reset and go back.
     * Also the labels to show the players
     *
     * @see TTTBoard.java
     */
	public void setUpGame() {

		sqSize = getSquare(0, 0).getSquareSize();
		
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setTitle("Dan's Crazy Tic Tac Toe!");
        this.setVisible(true);
        Dimension d = new Dimension(super.width * sqSize + JLABEL_WIDTH + JLABEL_WIDTH,
        		super.height * sqSize + PADDING + EXTRA_H_PAD);
        this.getContentPane().setPreferredSize(d);
        this.getContentPane().setLayout(null);
        this.setLocationRelativeTo(null);
        
        JButton reset = new JButton();
        reset.setVisible(true);
        reset.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                	reset();
                }
            });
        reset.setBounds(RESET_X, RESET_Y, JLABEL_WIDTH, JLABEL_HEIGHT);
        reset.setText("Reset Game");
        this.add(reset);

        JButton back = new JButton();
        back.setVisible(true);
        back.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                backBtn();
            }
        });
        back.setBounds(BACK_X, BACK_Y, JLABEL_WIDTH, JLABEL_HEIGHT);
        back.setText("Back");
        this.add(back);


        for (int x = 0; x < super.width; x++) {
            for (int y = 0; y < super.height; y++) {
                TTTSquare square = getSquare(x, y);
                square.setLocation(x*sqSize+PADDING, y*sqSize+PADDING);
                square.setSize(sqSize, sqSize);
                square.setVisible(true);
                this.add(square);
                this.add(square);
            }
        }

        for (int i = 0; i < playerList.size(); i++) {
            if (i == 0) {
                player1 = new JLabel("<html>Player: " + playerList.get(i).getName() + "<br />Type: " + playerList.get(i).getType() + "</html>");
                player1.setVisible(true);
                player1.setBounds(PLAYER_LABEL_X,
                		PLAYER_LABEL_Y,
                		JLABEL_WIDTH, JLABEL_HEIGHT);
                this.add(player1);
            }
            else if (i == 1) {
                player2 = new JLabel("<html>Player: " + playerList.get(i).getName() + "<br />Type: " + playerList.get(i).getType() + "</html>");
                player2.setVisible(true);
                player2.setBounds(PLAYER_LABEL_X,
                		PLAYER_LABEL_Y+JLABEL_HEIGHT+PADDING,
                		JLABEL_WIDTH, JLABEL_HEIGHT);
                this.add(player2);
            }
        }
        if (playerList.get(0).getType() == 'X') {
            player1.setBorder(selectedBorder);
            player2.setBorder(null);
        }
        else {
            player2.setBorder(selectedBorder);
            player1.setBorder(null);
        }

        player1.setHorizontalAlignment(SwingConstants.CENTER);
        player2.setHorizontalAlignment(SwingConstants.CENTER);
        
        lblTime.setBounds(TIME_LABEL_X, TIME_LABEL_Y, TIME_LABEL_WIDTH, TIME_LABEL_HEIGHT);
		this.add(lblTime);
        
        this.pack();
	}

    /**
     * This method is the code that resets the board as if a completely new game
     * was started. It clears the squares and resets the borders on the labels.
     * This calls the setupGame method again and resets the total moves
     *
     * @see TTTSquare.java
     */
	public void reset() {
		TTTBoard t = new TTTBoard(super.width, super.height, playerList);
		this.dispose();
    }

    /**
     * This method is the button to go back to the main menu and exit the game
     *
     * @see MainMenu.java
     */
    public void backBtn() {
        this.dispose();
        MainMenu.main(null);
    }

    /**
     * This method will return a boolean true or false depending on if the game has
     * been won
     *
     * @return boolean, returns true if the game has been won and false otherwise
     */
	public boolean gameWon() {
		if (gameWon) {
            return true;
        }
        return false;
	}
}