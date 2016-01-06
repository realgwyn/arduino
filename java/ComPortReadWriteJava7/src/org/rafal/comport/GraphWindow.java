package org.rafal.comport;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.EventQueue;
import java.awt.Graphics2D;
import java.awt.Rectangle;
import java.awt.geom.Rectangle2D;

import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import java.awt.Font;
import javax.swing.border.CompoundBorder;
import javax.swing.border.BevelBorder;

public class GraphWindow extends JFrame {

	private JPanel contentPane;
	JLabel lblNewLabel;
	String value;
	int time;
	JPanel panel;

	/**
	 * Create the frame.
	 */
	public GraphWindow() {
		setBackground(Color.BLACK);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 1120, 622);
		contentPane = new JPanel();
		contentPane.setBackground(Color.BLACK);
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		contentPane.setLayout(new BorderLayout(0, 0));
		setContentPane(contentPane);
		
		lblNewLabel = new JLabel("[aaaa]");
		lblNewLabel.setBackground(Color.BLACK);
		lblNewLabel.setFont(new Font("Consolas", Font.PLAIN, 14));
		lblNewLabel.setForeground(Color.GREEN);
		contentPane.add(lblNewLabel, BorderLayout.NORTH);
		
		panel = new JPanel();
		panel.setBorder(new BevelBorder(BevelBorder.LOWERED, new Color(255, 255, 255), null, null, Color.WHITE));
		panel.setBackground(Color.black);
		panel.setForeground(Color.BLACK);
		contentPane.add(panel, BorderLayout.CENTER);
		
	}
	
	public void startDrawingThread(){
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					while(true){
						System.out.println("drawing " + value);
						lblNewLabel.setText(value);
						revalidate();
						repaint();
						try {
							Thread.sleep(100);
						} catch (InterruptedException e) {
							// TODO Auto-generated catch block
							e.printStackTrace();
						}
					}
					
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}
	
	public void setValue(String s){
		value = s;
		lblNewLabel.setText(value);
		repaint();
	}
	
	public Graphics2D getDrawGraphics(){
		return (Graphics2D) panel.getGraphics();
	}
	
	public Rectangle2D getDrawArea(){
		Rectangle2D rec = new Rectangle();
		rec.setRect(0, 0, 800, 500);
		return rec;
	}

}
