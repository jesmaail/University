package a3group4;

import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.ArrayList;

import javax.swing.*;

/**
* @file MainMenu.java
* @author Joseph Esmaail
* @date 29 Nov 2014
* @see SLHuman.java
* @see TTTHuman.java
* @see SLBoards.java
* @see TTTBoards.java
*
* Main Menu is where the games will start, it will allocate players to a game and hold the Boards to play the game.
*/
public class MainMenu{	
	private final int SL_BOARD_SIZE = 10;
	private final int TTT_BOARD_SIZE = 8;
	private final int SL_MIN_PLAYERS = 2;
	private final int SL_MAX_PLAYERS = 4;
	private final int TTT_MIN_PLAYERS = 2;
	private final int TTT_MAX_PLAYERS = 2;
	private int height = 305;
	private int width = 600;
	private Dimension menuDim = new Dimension(width, height);
	private int slMenuHeight = 400;	
	private int tttMenuHeight = 200;
	private int slBtnX = 25;	
	private int menuBtnY = 25;	
	private int menuBtnH = 250;
	private int menuBtnW = 250;
	private int tttBtnX = slBtnX + menuBtnW + 50;		
	private int spacerX = 20;
	private int spacerY = 20;
	private int lblY = 15;
	private final int YPOS_INITIAL = 45;
	private int yPos = YPOS_INITIAL;	
	private int txtX = 25;
	private int txtHeight = 25;
	private int txtWidth = 100;	
	private int radBtnX = txtX + txtWidth + spacerX;
	private int radBtnH = txtHeight;
	private int radBtnW = radBtnH;	
	private int cmbX = radBtnX + radBtnW + spacerY;
	private int cmbHeight = txtHeight;
	private int cmbWidth = 90;
	private int lblComX = radBtnX + 4;
	private int lblColX = cmbX + 18;	
	private int playerSelBtnW = 100;
	private int playerSelBtnH = 50;	
	private int slSubmitX = cmbX - 10;
	private final int MAX_OBST = 30;
	private final String NOT_AVAIL ="Not Available";
	private final String AI_VER = "AI functionality is not available in this version.";
	private final String DUP_ERR = "Duplicate issue";
	private final String DUP_XO = "Two Players cannot play with the same symbol (X or O)!";
	private final String DUP_COL = "Multiple Players cannot use the same colour!";
	private final String PLAY_ERR = "Add more players";
	private final String PLAY_COUNT = "Not enough players to start Game.";
	private final String OBST_ERR = "Error with Obstacles";
	private final String OBST_COUNT = "Please enter amount of obstacles to start Game.";
	private final String OBST_MAX = "Please enter less obstacles!";
	private String[] colourList = {"Black", "Blue", "Red", "Yellow"};
	private String[] xoList = {"X", "O"};
	private ArrayList<JTextField> txtNames = new ArrayList<JTextField>();
	private ArrayList<JRadioButton> isCom = new ArrayList<JRadioButton>();
	private ArrayList<JComboBox<String>> colours = new ArrayList<JComboBox<String>>();	
	private ArrayList<JComboBox<String>> xos = new ArrayList<JComboBox<String>>();
	private JButton ttt = new JButton();
	private JButton sl = new JButton();
	private JButton back = new JButton("Back");
	private JButton slSubmit = new JButton("Submit");
	private JButton tttSubmit = new JButton("Submit");
	private JLabel lblName = new JLabel();
	private JLabel lblCom = new JLabel();
	private JLabel lblColour = new JLabel();
	private JLabel lblXO = new JLabel();
	private JLabel lblSnakes = new JLabel();
	private JLabel lblLadders = new JLabel();
	private JTextField txtSnakes = new JTextField();
	private JTextField txtLadders = new JTextField();
	
	/**
	* Creates the frame for menu and sets it's initial layout.
	*/
	public MainMenu(){		
		final JFrame MENU = new JFrame();
		MENU.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		MENU.setTitle("G4GM: Group 4 Game Menu");
		MENU.setVisible(true);
		//MENU.setResizable(false);
		MENU.setPreferredSize(menuDim);
		MENU.setSize(menuDim);
		MENU.setLocationRelativeTo(null);//find solution using setMinimumSize
		MENU.getContentPane().setLayout(null);
		sl.setBounds(slBtnX, menuBtnY, menuBtnW, menuBtnH);
		sl.setText("Play Snakes & Ladders");
		sl.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				playerSelect(MENU, true);
			}
		});
		sl.setVisible(true);		
		MENU.add(sl);
		
		ttt.setBounds(tttBtnX, menuBtnY, menuBtnW, menuBtnH);
		ttt.setText("Play Dan's Crazy Tic Tac Toe");
		ttt.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				playerSelect(MENU, false);
			}
		});
		ttt.setVisible(true);
		MENU.add(ttt);
	}

	/**
	* Creates a MainMenu object to start the Program.
	*/
	public static void main(String[] args){
		new MainMenu();
	}
	
	/**
	* Readies the frame for users to select Players for the game.
	* @param frame, JFrame object to perform changes to.
	* @param sl, boolean value to determine if the game selected is or isn't 'Snakes & Ladders'.
	* @see slPlayerSelect()
	* @see tttPlayerSelect()
	*/
	private void playerSelect(JFrame frame, boolean sl){
		frame.getContentPane().removeAll();
		//frame.pack();
		if(sl){
			slPlayerSelect(frame);
			frame.setTitle("SL Player Select");
			menuDim = new Dimension(height, slMenuHeight);
			frame.setSize(menuDim);
			frame.setPreferredSize(menuDim);
		}else{
			tttPlayerSelect(frame);
			frame.setTitle("TTT Player Select");
			menuDim = new Dimension(height, tttMenuHeight);
			frame.setSize(menuDim);
			frame.setPreferredSize(menuDim);
			frame.setMinimumSize(menuDim);
		}		
		frame.setLocationRelativeTo(null);
	}
	
	/**
	* Populates the frame with objects for the user to be able to select players for a Snakes & Ladders game.
	* @param FRAME, JFrame object to perform changes to.
	* @see popJObjectArrays()
	* @see playerSelectLabels()
	* @see playerSelectButtons()
	* @see startSL()
	*/
	private void slPlayerSelect(final JFrame FRAME){
		popJObjectArrays(SL_MAX_PLAYERS);		
		playerSelectLabels(FRAME, true);
		
		for(int i=0; i<SL_MAX_PLAYERS; i++){
			txtNames.get(i).setBounds(txtX, yPos, txtWidth,txtHeight);
			txtNames.get(i).setVisible(true);
			FRAME.add(txtNames.get(i));
			
			isCom.get(i).setBounds(radBtnX, yPos, radBtnW, radBtnH);
			isCom.get(i).setVisible(true);			
			FRAME.add(isCom.get(i));			
			
			colours.get(i).setBounds(cmbX, yPos, cmbWidth, cmbHeight);
			colours.get(i).setVisible(true);
			FRAME.add(colours.get(i));
			
			yPos += txtHeight + spacerY;
		}
		lblSnakes.setText("Snakes:");
		lblSnakes.setBounds(txtX, yPos, txtWidth, txtHeight);
		FRAME.add(lblSnakes);		
		txtSnakes.setBounds(radBtnX, yPos, txtWidth, txtHeight);
		FRAME.add(txtSnakes);
		yPos += txtHeight + spacerY;
		lblLadders.setText("Ladders:");
		lblLadders.setBounds(txtX, yPos, txtWidth, txtHeight);
		FRAME.add(lblLadders);
		txtLadders.setBounds(radBtnX, yPos, txtWidth, txtHeight);
		FRAME.add(txtLadders);
		yPos += txtHeight + spacerY;
		playerSelectButtons(FRAME, true);
		slSubmit.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e){
				startSL(FRAME);
			}
		});
		yPos = YPOS_INITIAL;
	}
	
	/**
	* Populates the frame with objects for the user to be able to select players for a Tic tac toe game.
	* @param FRAME, JFrame object to perform changes to.
	* @see popJObjectArrays()
	* @see playerSelectLabels()
	* @see playerSelectButtons()
	* @see startTTT()
	*/
	private void tttPlayerSelect(final JFrame FRAME){
		popJObjectArrays(TTT_MAX_PLAYERS);		
		playerSelectLabels(FRAME, false);
		
		for(int i=0; i<TTT_MAX_PLAYERS; i++){
			txtNames.get(i).setBounds(txtX, yPos, txtWidth,txtHeight);
			txtNames.get(i).setVisible(true);
			FRAME.add(txtNames.get(i));
			
			isCom.get(i).setBounds(radBtnX, yPos, radBtnW, radBtnH);
			isCom.get(i).setVisible(true);			
			FRAME.add(isCom.get(i));			
			
			xos.get(i).setBounds(cmbX, yPos, cmbWidth, cmbHeight);
			xos.get(i).setVisible(true);
			FRAME.add(xos.get(i));
			
			yPos += txtHeight + spacerY;
		}
		playerSelectButtons(FRAME, false);
		tttSubmit.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e){
				startTTT(FRAME);
			}
		});
		yPos = YPOS_INITIAL;
	}
	
	/**
	* Populates arrays with their respective objects and makes sure colours/xo are unique values.
	* @param num, the amount of each objects to create
	* @see SLPlayerSelect()
	* @see TTTPlayerSelect()
	*/
	private void popJObjectArrays(int num){
		for(int i=0; i<num; i++){
			txtNames.add(new JTextField());
			isCom.add(new JRadioButton());
			colours.add(new JComboBox<String>(colourList));
			xos.add(new JComboBox<String>(xoList));		
		}
		if(num <4){
			for(int i=0; i<num; i++){
				xos.get(i).setSelectedIndex(i);
			}
		}else{
			for(int i=0; i<num; i++){
				colours.get(i).setSelectedIndex(i);
			}
		}
	}
	
	/**
	* Populates frame with appropriate labels for Player Select.
	* @param frame, JFrame object to perform changes to.
	* @param sl, boolean value to determine if the game selected is or isn't 'Snakes & Ladders'.
	* 
	*/
	private void playerSelectLabels(JFrame frame, boolean sl){
		lblName.setBounds(txtX, lblY, txtWidth, txtHeight);
		lblName.setText("Player Name");
		lblName.setVisible(true);
		frame.add(lblName);
		lblCom.setBounds(lblComX, lblY, radBtnW, radBtnH);
		lblCom.setText("AI");
		lblCom.setVisible(true);
		frame.add(lblCom);
		if(sl){
			lblColour.setBounds(lblColX, lblY, cmbWidth, cmbHeight);
			lblColour.setText("Colour");
			lblColour.setVisible(true);
			frame.add(lblColour);
		}else{
			lblXO.setBounds(lblColX, lblY, cmbWidth, cmbHeight);
			lblXO.setText("X or O");
			lblXO.setVisible(true);
			frame.add(lblXO);
		}
	}
	
	/**
	* Populates frame with appropriate buttons for Player Select.
	* @param FRAME, JFrame object to perform changes to.
	* @param sl, boolean value to determine if the game selected is or isn't 'Snakes & Ladders'.
	*/
	private void playerSelectButtons(final JFrame FRAME, boolean sl){
			back.setBounds(txtX, yPos, playerSelBtnW, playerSelBtnH);
			back.setVisible(true);
			back.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e){
					resetToMenu(FRAME);
				}
			});
			FRAME.add(back);
			
			if(sl){
				slSubmit.setBounds(slSubmitX, yPos, playerSelBtnW, playerSelBtnH);
				slSubmit.setVisible(true);
				FRAME.add(slSubmit);
			}else{
				tttSubmit.setBounds(slSubmitX, yPos, playerSelBtnW, playerSelBtnH);
				tttSubmit.setVisible(true);
				FRAME.add(tttSubmit);
			}
	}
	
	/**
	* Checks whether the player selections are valid and starts the Snakes and Ladders Game.
	* @see SLBoard.java
	* @param frame, JFrame object to hide when starting game.
	*/
	private void startSL(JFrame frame){
		ArrayList<SLPlayer> players = new ArrayList<SLPlayer>();
		ArrayList<String> selectedColours = new ArrayList<String>();
		int snakeNum = 0;
		int ladderNum = 0;
		
		String currentName, colour;
		boolean ai;
		boolean noErrors = true; 
		
		try{
			snakeNum = Integer.parseInt(txtSnakes.getText());
			ladderNum = Integer.parseInt(txtLadders.getText());
		}catch(Exception e){
			JOptionPane.showMessageDialog(null, OBST_COUNT, OBST_ERR, JOptionPane.INFORMATION_MESSAGE);
			noErrors = false;
		}
		if(snakeNum + ladderNum >= MAX_OBST){
			JOptionPane.showMessageDialog(null, OBST_MAX, OBST_ERR, JOptionPane.INFORMATION_MESSAGE);
			noErrors = false;
		}
		
		for(int i=0; i<txtNames.size(); i++){
			currentName = txtNames.get(i).getText();
			ai = isCom.get(i).isSelected();
			colour = colours.get(i).getSelectedItem().toString();
			
			if(!currentName.isEmpty()){
				selectedColours.add(colour);
				if(ai){
					JOptionPane.showMessageDialog(null, AI_VER, NOT_AVAIL, JOptionPane.INFORMATION_MESSAGE);
					noErrors = false;
					break;
				}else if(checkDuplicates(selectedColours)){
					JOptionPane.showMessageDialog(null, DUP_COL, DUP_ERR, JOptionPane.INFORMATION_MESSAGE);
					selectedColours.clear();
					noErrors = false;
					break;
				}else{
					players.add(new SLHuman(currentName, colour));
				}
			}					
		}
		
		if(noErrors){
			if(players.size()< SL_MIN_PLAYERS){
				JOptionPane.showMessageDialog(null, PLAY_COUNT, PLAY_ERR, JOptionPane.INFORMATION_MESSAGE);
				players.clear();
			}else{
				SLBoard game = new SLBoard(SL_BOARD_SIZE,SL_BOARD_SIZE, players, snakeNum, ladderNum);
				game.setVisible(true);
				frame.setVisible(false);
			}
		}
	}
	
	/**
	* Checks whether the player selections are valid and starts the Tic Tac Toe Game.
	* @see TTTBoard.java
	* @param frame, JFrame object to hide when starting game.
	*/
	private void startTTT(JFrame frame){
		ArrayList<TTTPlayer> players = new ArrayList<TTTPlayer>();
		ArrayList<String> selectedXO = new ArrayList<String>();
		String currentName;
		boolean ai;
		char xo;
		boolean noErrors = true;
		
		for(int i=0; i<txtNames.size(); i++){
			currentName = txtNames.get(i).getText();
			ai = isCom.get(i).isSelected();
			xo = xos.get(i).getSelectedItem().toString().charAt(0);
					
			if(!currentName.isEmpty()){
				selectedXO.add(xos.get(i).getSelectedItem().toString());
				
				if(ai){
					JOptionPane.showMessageDialog(null, AI_VER, NOT_AVAIL, JOptionPane.INFORMATION_MESSAGE);
					noErrors = false;
					break;
				}else if(checkDuplicates(selectedXO)){
					JOptionPane.showMessageDialog(null, DUP_XO, DUP_ERR, JOptionPane.INFORMATION_MESSAGE);
					noErrors = false;
					selectedXO.clear();
					break;
				}else{
					players.add(new TTTHuman(currentName, xo));
				}
			}			
		}
		if(noErrors){
			if(players.size() < TTT_MIN_PLAYERS){
				System.out.println(players.size());
				JOptionPane.showMessageDialog(null, PLAY_COUNT, PLAY_ERR, JOptionPane.INFORMATION_MESSAGE);
				players.clear();
			}else{
				TTTBoard game = new TTTBoard(TTT_BOARD_SIZE, TTT_BOARD_SIZE, players);
				game.setVisible(true);
				frame.setVisible(false);
			}
		}
	}
	
	/**
	* Checks whether the player selections are valid and starts the Snakes and Ladders Game.
	* @return boolean, based on if there a duplicates for either X/O symbols or colours.
	*/
	private boolean checkDuplicates(ArrayList<String> list){
		for(int i=0; i<list.size(); i++){
			
			for(int j=i+1; j<list.size(); j++){
				
				if(list.get(i) == list.get(j)){
					return true;
				}
			}
		}
		return false;		
	}
	
	/**
	* Resets the frame.
	* @param frame, JFrame object to perform changes to.
	*/
	public void resetToMenu(JFrame frame){
		txtNames.clear();
		colours.clear();
		isCom.clear();
		frame.getContentPane().removeAll();
		frame.getContentPane().revalidate();
		frame.getContentPane().repaint();		
		frame.setTitle("G4GM: Group 4 Game Menu");
		frame.setSize(width, height);
		frame.setLocationRelativeTo(null);		
		sl.setBounds(slBtnX, menuBtnY, menuBtnW, menuBtnH);
		sl.setText("Play Snakes & Ladders");
		sl.setVisible(true);		
		frame.add(sl);		
		ttt.setBounds(tttBtnX, menuBtnY, menuBtnW, menuBtnH);
		ttt.setText("Play Dan's Crazy Tic Tac Toe");
		ttt.setVisible(true);
		frame.add(ttt);
	}
	
}