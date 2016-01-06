package org.rafal.comport;

import gnu.io.CommPortIdentifier;
import gnu.io.SerialPort;
import gnu.io.SerialPortEvent;
import gnu.io.SerialPortEventListener;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.EventQueue;
import java.awt.geom.Rectangle2D;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.util.Arrays;
import java.util.Enumeration;


public class ComPortReadWrite implements SerialPortEventListener {
SerialPort serialPort;
    /** The port we're normally going to use. */
private static final String PORT_NAMES[] = {                  "/dev/tty.usbserial-A9007UX1", // Mac OS X
        "/dev/ttyUSB0", // Linux
        "COM3", // Windows
};
private BufferedReader input;
private OutputStream output;
private static final int TIME_OUT = 2000;
private static final int DATA_RATE = 9600;
private static GraphWindow frame;
private static LineGraphDrawable graph;
private static Number[] data = new Number[1000]; //{150,1,1,1,1,1,1,1,1,1,1,50};
private static int count = 0;
private static int treshold = 802;

public void initialize() {
    CommPortIdentifier portId = null;
    Enumeration portEnum = CommPortIdentifier.getPortIdentifiers();

    //First, Find an instance of serial port as set in PORT_NAMES.
    while (portEnum.hasMoreElements()) {
        CommPortIdentifier currPortId = (CommPortIdentifier) portEnum.nextElement();
        for (String portName : PORT_NAMES) {
            if (currPortId.getName().equals(portName)) {
                portId = currPortId;
                break;
            }
        }
    }
    if (portId == null) {
        System.out.println("Could not find COM port.");
        return;
    }

    try {
        serialPort = (SerialPort) portId.open(this.getClass().getName(),
                TIME_OUT);
        serialPort.setSerialPortParams(DATA_RATE,
                SerialPort.DATABITS_8,
                SerialPort.STOPBITS_1,
                SerialPort.PARITY_NONE);

        // open the streams
        input = new BufferedReader(new InputStreamReader(serialPort.getInputStream()));
        output = serialPort.getOutputStream();

        serialPort.addEventListener(this);
        serialPort.notifyOnDataAvailable(true);
    } catch (Exception e) {
        System.err.println(e.toString());
    }
}


public synchronized void close() {
    if (serialPort != null) {
        serialPort.removeEventListener();
        serialPort.close();
    }
}



public synchronized void serialEvent(SerialPortEvent oEvent) {
    if (oEvent.getEventType() == SerialPortEvent.DATA_AVAILABLE) {
        try {
            String inputLine=null;
            if (input.ready()) {
            	
            	count++;
                inputLine = input.readLine();
                System.out.println(inputLine);
                if(count > 998){
                	count = 0;
                	data = new Number[1000];
                    Arrays.fill(data, treshold-30);
                    data[0] = treshold+30;
                    data[999] = treshold-30;
                	return;	
                }
                int datain = Integer.parseInt(inputLine);
                data[count] = datain; 
                graph.setData(data);
                if(datain > treshold+2 || datain < treshold-2){
                	graph.setColor(Color.red);
                }else{
                	graph.setColor(Color.green);
                }
                graph.draw(frame.getDrawGraphics(), frame.getDrawArea());
//                frame.setValue(inputLine);
                
               
            }
//            frame.setValue(inputLine);
//            count++;
//            
//           
//            System.out.println("   COUNT: "+ (count >  101));
//            if(count >  101){
//            	
//            	count = 0;
//            	graph.setData(data);
//            }
//            data[count] = Integer.parseInt(inputLine);

        } catch (Exception e) {
            System.err.println(e.toString());
        }
    }
    // Ignore all the other eventTypes, but you should consider the other ones.
}

public static void main(String[] args) throws Exception {
	ComPortReadWrite main = new ComPortReadWrite();
    main.initialize();
    Thread t=new Thread() {
        public void run() {
            //the following line will keep this app alive for 1000    seconds,
            //waiting for events to occur and responding to them    (printing incoming messages to console).
            try {Thread.sleep(1000000);} catch (InterruptedException    ie) {}
        }
    };
    t.start();
   
    EventQueue.invokeLater(new Runnable() {
		public void run() {
			try {
				frame = new GraphWindow();
				frame.setVisible(true);
				
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
	});
    System.out.println("Started");
    
    Thread.sleep(1000);
    graph = new LineGraphDrawable();
//    graph.setData(data);
//    graph.draw(frame.getDrawGraphics(), frame.getDrawArea());
//    frame.startDrawingThread();
    Thread.sleep(500);
    new Thread(){
    	public void run() {
    		while(true){
    			graph.draw(frame.getDrawGraphics(), frame.getDrawArea());
    		frame.repaint();
    		try {
				Thread.sleep(200);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
    		}
    	};
    }.start();
    Arrays.fill(data, treshold-30);
    data[0] = treshold+30;
    data[999] = treshold-30;
}
}