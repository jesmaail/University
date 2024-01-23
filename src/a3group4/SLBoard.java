package a3group4;

//change this to java.util.*; later maybe
import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Rectangle;
import java.awt.Stroke;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.geom.Ellipse2D;
import java.awt.geom.Line2D;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;

import javax.swing.BorderFactory;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JLayeredPane;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.SwingConstants;
import javax.swing.Timer;
import javax.swing.border.Border;

/**
 * @file SLBoard.java
 * @author Connor Macaskill
 * @date 5 Dec 2014)
 * @see Board.java
 * @see Snake.java
 * @see Ladder.java
 * @see MainMenu.java
 * @see SLPlayer
 * @see SLHuman
 * @see SLSquare
 * 
 *      Board upon which Snakes and Ladders will be played, handles both game
 *      logic and game display.
 */
public class SLBoard extends Board {
	private ArrayList<Snake> snakeList = new ArrayList<Snake>();
	private ArrayList<Ladder> ladderList = new ArrayList<Ladder>();
	private ArrayList<SLSquare> squares = new ArrayList<SLSquare>();
	private ArrayList<SLPlayer> playerList;
	private ArrayList<JLabel> pieces = new ArrayList<JLabel>();
	private ArrayList<JLabel> info = new ArrayList<JLabel>();
	private int width;
	private int height;
	private int snakeCount;
	private int ladderCount;
	private final int DIE_MAX = 6;
	private final int BOARD_SIZE;
	private final int SQSIZE = 70;
	private final int W_PADDING = 300;
	private final int PADDING = 20;
	private final int EVEN = 2;
	private final int LBL_X = 750;
	private int lblY = 200;
	private final int LBL_W = 200;
	private final int LBL_H = 25;
	private JButton roll = new JButton("Roll!");
	private JLayeredPane panel;
	private JLabel rolled = new JLabel();
	private int turn = 0;

	private final int THICKSNAKE = 6;
	private final int THICKLADDER = 8;
	private final int SNAKEBUFFER = 20;
	private final int SNAKEHEAD = 16;
	private final int SECOND = 1000;
	private final Color BEIGE = new Color(245, 245, 220, 255);
	private final Color PURPLE = new Color(128, 0, 128, 255);
	private final Color BROWN = new Color(105, 27, 13, 255);
	
	private final int LBLX = 750;
	private final int LBLTY = 50;
	private final int LBLRY = 20;
	private final int LBLW = 200;
	private final int LBLTH = 25;
	private final int LBLRH = 100;
	private final int RLY = 150;
	private final int BY = 600;
	private final int RY = 450;
	
	//Animation related
	private int MOVEINTERVAL = 300;
	private int squaresLeft;
	private JLabel movingPiece;
	private int movingOrigin;
	private int curMove;
	private String curColor;
	private boolean moving = false;
	

	/**
	 * Calls methods to set up both the game and board. Initialises variables,
	 * calls the constructor of Board, its superclass.
	 * 
	 * @param width, Width of the board in squares.
	 * @param height, Height of the board in squares.
	 * @param players, ArrayList of SLPlayer, the players that are going to play the game.
	 * @param snakes, Number of snakes to place on the board.
	 * @param ladders, Number of ladders to place on the board.
	 * @see Board.java
	 * @see Snake.java
	 * @see Ladder.java
	 * @see MainMenu.java
	 * @see SLPlayer
	 * @see SLHuman
	 * @see SLSquare
	 */
	public SLBoard(int width, int height, ArrayList<SLPlayer> players,
			int snakes, int ladders) {
		super(width, height);
		this.width = width;
		this.height = height;
		snakeCount = snakes;
		ladderCount = ladders;
		panel = new JLayeredPane();
		Dimension size = new Dimension(width + W_PADDING, height + PADDING
				+ PADDING);
		panel.setPreferredSize(size);
		panel.setSize(size);
		panel.setVisible(true);
		panel.setMinimumSize(size);
		add(panel);
		playerList = players;
		BOARD_SIZE = width * height;
		setUpGame();
		setUpFrame(width * SQSIZE, height * SQSIZE);
		setUpSnake(snakes);
		setUpLadder(ladders);
	}

	/**
	 * Sets up the frame upon which the game will be drawn. Sets up all labels
	 * to display information.
	 * 
	 * @param width, Width of the board in squares.
	 * @param height, Height of the board in squares.
	 * @see SLBoard()
	 */
	private void setUpFrame(int width, int height) {
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setTitle("Snakes And Ladders!");
		this.setVisible(true);
		Dimension size = new Dimension(width + W_PADDING, height + PADDING
				+ PADDING);
		this.getContentPane().setPreferredSize(size);
		// this.getContentPane().setSize(width + W_PADDING, height + PADDING);
		this.getContentPane().setLayout(null);
		this.pack();
		this.setLocationRelativeTo(null);

		for (int i = 0; i < playerList.size(); i++) {
			JLabel l = new JLabel(playerList.get(i).getName() + " : 1");
			l.setBackground(Color.LIGHT_GRAY);
			l.setOpaque(true);
			String col = playerList.get(i).getColor();
			if (col.equals("Red")) {
				l.setForeground(Color.RED);
			} else if (col.equals("Blue")) {
				l.setForeground(Color.BLUE);
			} else if (col.equals("Yellow")) {
				l.setForeground(Color.YELLOW);
			}
			l.setBounds(LBL_X, lblY, LBL_W, LBL_H);
			info.add(l);
			lblY += LBL_H;
			this.add(info.get(i));
			if (i == 0) {
				l.setBorder(BorderFactory.createLineBorder(Color.BLACK, 1));
			}
		}

		lblTime.setBounds(LBLX, LBLRY, LBLW, LBLTH);
		this.add(lblTime);
		roll.setBounds(LBLX, LBLTY, LBLW, LBLRH);
		roll.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				if(moving == false)
				{
					update();
					repaint();
				}
			}
		});
		this.add(roll);
		rolled.setBounds(LBLX, RLY, LBLW, LBLTH);
		rolled.setHorizontalAlignment(SwingConstants.CENTER);
		this.add(rolled);

		JButton back = new JButton();
		back.setVisible(true);
		back.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				backBtn();
			}
		});
		back.setBounds(LBLX, BY, LBLW, LBLRH);
		back.setText("Back");
		this.add(back);

		JButton reset = new JButton();
		reset.setVisible(true);
		reset.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				reset();
			}
		});
		reset.setBounds(LBLX, RY, LBLW, LBLRH);
		reset.setText("Reset Game");
		this.add(reset);
	}


	/**
	 * Sets up the frame upon which the game will be drawn. Sets up all labels
	 * to display information.
	 * 
	 * @param width, Width of the board in squares.
	 * @param height, Height of the board in squares.
	 * @see SLBoard()
	 */
	public void setUpGame() {
		int pos = 0;
		Border border = BorderFactory.createLineBorder(Color.BLACK, 1);
		int maxHeight = SQSIZE * (height - 1);
		int maxWidth = SQSIZE * (width - 1);
		boolean right = true;

		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				pos += 1;
				SLSquare square;
				Rectangle bounds;

				if (right == true) {
					bounds = new Rectangle(PADDING + y * SQSIZE, PADDING 
							+ maxHeight - x * SQSIZE, SQSIZE, SQSIZE);
				} else {
					bounds = new Rectangle(PADDING + maxWidth - y * SQSIZE,
							PADDING + maxHeight - x * SQSIZE, SQSIZE, SQSIZE);
				}

				// Alternate color, if pos mod 2 is 0 then the pos is even.
				if (pos % EVEN == 0) {
					square = new SLSquare(pos, bounds, border, Color.LIGHT_GRAY);
				} else {
					square = new SLSquare(pos, bounds, border, BEIGE);
				}

				squares.add(square);
				this.getLayeredPane().add(square);
				this.getLayeredPane().setLayer(square, 0);

			}

			if (right == true) {
				right = false;
			} else {
				right = true;
			}
		}

		playerList = orderPlayers(playerList);
		drawPlayers();
	}
	
	/**
	 * Plays the game, rolling the die for and moving the current player.
	 * 
	 * @see setUpFrame()
	 */
	public void update() {
		int rollVal = rollDie();
		int currentSq = playerList.get(turn).getPosition();
		int destination = currentSq + rollVal;
		info.get(turn).setBorder(null);
		if (destination >= 100) {
			destination = 100;
		}
		
		curColor = playerList.get(turn).getColor();
		
		rolled.setText("Rolled: " + rollVal);		
		moveTo(pieces.get(turn), playerList.get(turn).getPosition(), destination);		

		if(squares.get(destination -1).hasObstacle())
		{
			destination = squares.get(destination - 1).getObstDestination();
		}
		info.get(turn).setText(
				playerList.get(turn).getName() + " : " + destination);
		
		playerList.get(turn).setPosition(destination);

		
		if (destination == 100) {
			gameWon(playerList.get(turn));
		}
		if (turn + 1 < playerList.size()) {
			turn++;
		} else {
			turn = 0;
		}
		info.get(turn)
				.setBorder(BorderFactory.createLineBorder(Color.BLACK, 1));
	}

	/**
	 * Closes the game and returns to the main menu.
	 * 
	 * @see MainMenu.java
	 */
	public void backBtn() {
		this.dispose();
		MainMenu.main(null);
	}

	/**
	 * Sets up the snakes, initialising them and adding them to the global list.
	 * 
	 * @param snakes, The number of snakes to add to the board.
	 * @see SLBoard()
	 */
	private void setUpSnake(int snakes) {
		for (int i = 0; i < snakes; i++) {
			Snake snake = new Snake(BOARD_SIZE, width, height);
			snakeList.add(snake);

			SLSquare destSquare = getSquare(snake.getDestination());
			SLSquare originSquare = getSquare(snake.getOrigin());

			if (originSquare.hasObstacle()) {
				i -= 1;
			} else if (destSquare.hasObstacle()) {
				i -= 1;
			} else {
				destSquare.addObstacle(snake.getDestination(), false);
				originSquare.addObstacle(snake.getDestination(), true);
			}
		}
	}

	/**
	 * Sets up the ladders, initialising them and adding them to the global
	 * list.
	 * 
	 * @param ladders, The number of ladders to add to the board.
	 * @see SLBoard()
	 */
	private void setUpLadder(int ladders) {
		for (int i = 0; i < ladders; i++) {
			Ladder ladder = new Ladder(BOARD_SIZE, width, height);
			ladderList.add(ladder);

			SLSquare destSquare = getSquare(ladder.getDestination());
			SLSquare originSquare = getSquare(ladder.getOrigin());

			if (originSquare.hasObstacle()) {
				i -= 1;
			} else if (destSquare.hasObstacle()) {
				i -= 1;
			} else {
				destSquare.addObstacle(ladder.getDestination(), false);
				originSquare.addObstacle(ladder.getDestination(), true);
			}
		}
	}

	/**
	 * Draws pieces to the board for each player.
	 * 
	 * @see setUpGame()
	 */
	private void drawPlayers() {
		for (int i = 0; i < playerList.size(); i++) {
			pieces.add(playerList.get(i).getPiece());
			this.getLayeredPane().add(pieces.get(i));
			this.getLayeredPane().setLayer(pieces.get(i), 1);
			curColor = playerList.get(i).getColor();
			drawToSquare(pieces.get(i), 1);
			drawToSquare(pieces.get(i), 1);
		}
	}

	
	/**
	 * Draws the specified player piece to the specified square.
	 * 
	 * @param piece, The piece to be drawn to the square.
	 * @param position, The position of the square to be drawn to.
	 * @see update()
	 * @see drawPlayers()
	 */
	private void drawToSquare(JLabel piece, int position) 
	{	
		Rectangle bounds = piecePosition(squares.get(position-1).getBounds(), curColor);
		piece.setBounds(bounds);
	}
	
	/**
	 * Offsets the pieces to position them evenly around the square.
	 * 
	 * @param destination, the position that the piece is being drawn at.
	 * @param colour, The color of the piece to be offset.
	 * @return Returns the offset position to draw the piece at.
	 * @see drawToSquare()
	 */
	private Rectangle piecePosition(Rectangle destination, String colour){
		double x = destination.getX();
		double y = destination.getY();
		double w = destination.getWidth();
		double h = destination.getHeight();
		int newX = (int) x;
		int newY = (int) y;
		int newW = (int) w;
		int newH = (int) h;
		
		if(colour == "Blue"){
			newX += 35;
			newY -= 17;
		}else if(colour == "Red"){
			newY += 17;
		}else if(colour == "Yellow"){
			newX += 35;
			newY += 17;
		}else{
			newY -= 17;
		}
		
		Rectangle r = new Rectangle();
		r.setBounds(newX, newY, newW, newH);
		return r;
	}
	
	/**
	 * Moves a piece from its origin to the position specified.
	 * 
	 * @param piece, The piece to be moved.
	 * @param origin, Position the piece is moving from.
	 * @param position, Position the piece is moving to.
	 * @see update()
	 * @see move
	 */
	private void moveTo(JLabel piece, int origin, int position)
	{
		movingPiece = piece;
		movingOrigin = origin;
		curMove = 1;
		squaresLeft = position-origin;
		moving = true;
		roll.setText("Moving Piece....");
		roll.setEnabled(false);
		new Timer(300, move).start();
	}
	
	/**
	 * Declares a new Graphics2D to allow drawing of shapes.
	 * Used to draw both snakes and ladders.
	 * @param g, Graphics device to do the drawing.
	 * @see panel
	 */
	public void paint(Graphics g) {
		super.paint(g);
		Graphics2D g2 = (Graphics2D) g;
		drawSnakes(g2);
		drawLadders(g2);
	}

	/**
	 * Draws shapes to represent snakes on the board.
	 * @param g, Graphics2D device to do the drawing.
	 * @see paint()
	 */
	private void drawSnakes(Graphics2D g) {
		g.setStroke(new BasicStroke(THICKSNAKE));
		g.setColor(PURPLE);

		for (int i = 0; i < snakeList.size(); i++) {
			Snake s = snakeList.get(i);
			Rectangle rectOrig = squares.get(s.getOrigin() - 1).getBounds();
			Rectangle rectDest = squares.get(s.getDestination() - 1)
					.getBounds();

			float startX = (float) rectOrig.getCenterX();
			float startY = (float) rectOrig.getCenterY() + SNAKEBUFFER;
			float endX = (float) rectDest.getCenterX();
			float endY = (float) rectDest.getCenterY();

			float headX = startX - (SNAKEHEAD / EVEN);
			float headY = startY - (SNAKEHEAD / EVEN);
			Ellipse2D.Double circle;
			circle = new Ellipse2D.Double(headX, headY, SNAKEHEAD, SNAKEHEAD);
			Line2D line = new Line2D.Float(startX, startY, endX, endY);
			g.draw(line);
			g.fill(circle);
		}
	}

	/**
	 * Draws shapes to represent ladders on the board.
	 * @param g, Graphics2D device to do the drawing.
	 * @see paint()
	 */
	private void drawLadders(Graphics2D g) {
		Stroke dashed = new BasicStroke(THICKLADDER, BasicStroke.CAP_BUTT,
				BasicStroke.JOIN_BEVEL, 0, new float[] { EVEN }, 0);
		g.setStroke(dashed);
		g.setColor(BROWN);

		for (int i = 0; i < ladderList.size(); i++) {
			Ladder l = ladderList.get(i);
			Rectangle rectOrig = squares.get(l.getOrigin() - 1).getBounds();
			Rectangle rectDest = squares.get(l.getDestination() - 1)
					.getBounds();

			float startX = (float) rectOrig.getCenterX();
			float startY = (float) rectOrig.getCenterY();
			float endX = (float) rectDest.getCenterX();
			float endY = (float) rectDest.getCenterY() + SNAKEBUFFER;

			Line2D line = new Line2D.Float(startX, startY, endX, endY);
			g.draw(line);
		}
	}

	/**
	 * Rolls the die for each player, and orders them accordingly. 
	 * Repeats rolls for players who get the same result until all are ordered.
	 * @param players, ArrayList of players to be sorted.
	 * @see setUpGame()
	 * @return ArrayList<SLPlayer>, Returns a sorted list of players.
	 */
	private ArrayList<SLPlayer> orderPlayers(ArrayList<SLPlayer> players) {
		ArrayList<Integer> rollList = new ArrayList<Integer>();
		ArrayList<SLPlayer> sortedPlayers = new ArrayList<SLPlayer>();
		int lowest = DIE_MAX;
		int lowIndex = 0;

		for (int i = 0; i < playerList.size(); i++) {
			rollList.add(rollDie());
		}

		while (rollList.size() > 0) {

			for (int i = 0; i < rollList.size(); i++) {
				if (rollList.get(i) <= lowest) {
					lowest = rollList.get(i);
					lowIndex = i;
				}
			}

			sortedPlayers.add(players.get(lowIndex));
			rollList.remove(lowIndex);
			players.remove(lowIndex);
			lowest = DIE_MAX; // Change to constant called DIEMAX perhaps, use
								// for other things.
			lowIndex = 0;
		}

		return sortedPlayers;
	}

	/**
	 * Returns the name of the player who's number matches the parameter.
	 * @param playNum, Number of the player to get the name of.
	 * @return String, Returns the name of the relevant player.
	 */
	public String getPlayer(int playNum) {
		return playerList.get(playNum).getName();
	}

	/**
	 * Returns the square at the position provided.
	 * @param pos, Position of the square needed..
	 * @return SLSquare, Returns the square at the position provided.
	 * @see setUpSnake()
	 * @see setUpLadder()
	 */
	private SLSquare getSquare(int pos) {
		return squares.get(pos - 1);
	}

	/**
	 * Returns the a random die roll, represented by a random number generator.
	 * @return int, Returns the result of the die roll.
	 * @see setUpPlayers()
	 * @see update()
	 */
	private int rollDie() {
		Random rand = new Random();
		return rand.nextInt(DIE_MAX) + 1;
	}

	/**
	 * Declares that the player provided has won, ends the game.
	 * @param winner, The player who has won.
	 * @see update()
	 */
	public void gameWon(SLPlayer winner) {
		String name = winner.getName();
		new Timer(MOVEINTERVAL, flash).start();
		JOptionPane.showMessageDialog(null, "Congratulations " + name
				+ "!\n You won!");
		new MainMenu().main(null);
		this.dispose();

	}

	/**
	 * Resets the game, 
	 * @see setUpFrame()
	 */
	public void reset() {
		for(int i=0; i<playerList.size(); i++){
			playerList.get(i).setPosition(1);
		}
		SLBoard s = new SLBoard(width, height, playerList, 
				snakeCount, ladderCount);
		this.dispose();
	}
	
	ActionListener flash = new ActionListener()
	{		
		public void actionPerformed(ActionEvent evt)
		{	
			for(int i = 0; i < squares.size(); i++)
			{
				SLSquare square = squares.get(i);
				
				if(square.getBackground() == Color.LIGHT_GRAY)
				{
					square.setBackground(BEIGE);
					repaint();
				}
				else if(square.getBackground() == BEIGE)
				{
					square.setBackground(Color.LIGHT_GRAY);
					repaint();
				}
			}			
		}
	};
	
	ActionListener move = new ActionListener()
	{		
		public void actionPerformed(ActionEvent evt)
		{			
			drawToSquare(movingPiece, movingOrigin+curMove);

			if(curMove >= squaresLeft)
			{
				roll.setText("Roll");
				roll.setEnabled(true);
				moving = false;
				((Timer)evt.getSource()).stop();
				
				boolean obstacle = getSquare(movingOrigin+curMove).isObstacleStart();
				
				if(obstacle == true)
				{
					drawToSquare(movingPiece, getSquare(movingOrigin+curMove).getObstDestination());
					//We have finished moving.
					curMove = squaresLeft;
				}
			}
			
			repaint();
			curMove += 1;
		}
	};
}