import java.awt.*;
import java.awt.event.*;
import javax.swing.*;



/**
 * 
 * @author Steven Poulin
 * Better late than never
 * @Class Frame
 * @innerclasses : 	Steven14Frame
 * 					DrawPanel
 * 					MyMouseAdapter
 *
 */
	class Steven14Frame extends JFrame{
		private JButton show, draw;
		//private ButtonPanel bp;
		private DrawPanel dp;
		public static boolean active = false;
		public static int c = 0;
	
////////////////////////////////////////////////////////////////////////////////////
	
/**
 * 		
 * @class DrawPanel
 * contains a redrawing paintComponents
 */
	class DrawPanel extends JPanel{ // drawing pad
		

		//private int [][] clicks ;
		
		private Point[] points = new Point[100]; // an array of points
		
		public void paintComponent(Graphics g){

			super.paintComponent(g);
			
			for (int row = 0; row < c; row++){
				//for (int col = 0; col < dp.clicks[row].length; col++){
					if (points[row] != null){ // null protection
						g.setColor(Color.red);
						g.fillOval(points[row].x, points[row].y, 14, 14);
					}
			}
			
		}
	}
	


///////////////////////////////////////////////////////////////////////////

/**
 * Constructor
 * 
 */
	public Steven14Frame (String s){
		super (s);
		setSize(900,900);
		Container cp = getContentPane();
		
		cp.setBackground(Color.black);
		
		show = new JButton("Show"); // show repaints
		show.addActionListener(new ActionListener(){
								public void actionPerformed(ActionEvent ev){
									dp.repaint();
									System.out.println("Repaint");
										
								}	
							});
		
		draw = new JButton("Draw / Save"); // draw button and stop drawing, activates and desactivate
		draw.addActionListener(new ActionListener(){
								public void actionPerformed(ActionEvent ev){
									
									if (active == false){
										active = true;
										System.out.println("Active");
									}
									else {
										active = false;
										System.out.println("Not Active");
									}
								}
							});
		
		
		cp.add(show,  BorderLayout.EAST);
		cp.add(draw,  BorderLayout.WEST);
		
		dp = new DrawPanel();
		dp.addMouseListener(new MyMouseAdapter());
		dp.setBackground(Color.cyan);
		cp.add(dp,  BorderLayout.CENTER);
		
		setVisible(true);
	
	}
	
	
///////////////////////////////////////////////	
/**
 * 
 * @innerclass MyMouseAdapter
 *
 */
	class MyMouseAdapter extends MouseAdapter{	// using adapter pattern to avoid empty methods
		public void mouseClicked (MouseEvent ev){
			Point p = ev.getPoint();
			Object source = ev.getSource();
			if (source== dp && active==true){
				System.out.println("In Active : I've been clicked at: " + ev.getX() + " " + ev.getY());
				dp.points[c]= p;
				c++;
		
			}
			else 		
				System.out.println(" In NOT ACTIVE : I've been clicked at: " + ev.getX() + " " + ev.getY());
		}
	
	}
}

//////////////////////////////////
/**
 * 
 * @class Frame
 *
 */
public class Frame {
	public static void main(String[]arg){
		Steven14Frame s = new Steven14Frame("The LAB!");
	}
}
