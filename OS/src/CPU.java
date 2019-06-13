import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Iterator;
import java.util.LinkedList;


public class CPU {										// CPU simulator, catches exceptions and preemptive in a way that it checks before moving things
	static LinkedList<PROCESS> readyQ;  				// ready Queue
	static PROCESS runningProcess;						// CPU's processing unit
														// ideally i would consolidate repeating code into functions, especially make new process
	
	public CPU(PROCESS first) {							// constructor initializing queue and first process given by OS
		readyQ = new LinkedList<PROCESS>();
		runningProcess = first;
	}
	
	
	public void interruptHandler(int interrupt){		// takes the input, divides it in interrupt number and other number (dev# or pid) 
	    												// switch case for different interrupts
		int interruptCut = 0;
		int other = 0;
		
		if (interrupt == 0 || interrupt == 15 || interrupt == 64 || interrupt == 80 || interrupt == 81 ||interrupt == 244 ||interrupt == 255 ){
		interruptCut = interrupt;						// if input is standard input
		}
		
		else{											// probably not the best way to do this, but it works. eventually many repeating bits of code could be put into functions
			int num = interrupt;						// temporary variable to hold input
			String number = String.valueOf(num);		// transforming into a string to be able to seperate interrupt from other (DEV or PID)
			
			if (number.length() > 5){
				interruptCut = (Character.digit(2, 10));
			}
			
			if (number.length() == 5){					// using bases of 10, transforming single digit into its appropriate equivalent number
				interruptCut = (Character.digit(number.charAt(0), 10) * 10) + Character.digit(number.charAt(1), 10);
				other =(Character.digit(number.charAt(2), 10) * 100) + (Character.digit(number.charAt(3), 10) * 10) + Character.digit(number.charAt(4), 10);
			}
			
			if (number.length() == 4){
				interruptCut = (Character.digit(number.charAt(0), 10) * 10) + Character.digit(number.charAt(1), 10);
				other = (Character.digit(number.charAt(2), 10) * 10) + Character.digit(number.charAt(3), 10);
			}
			
			if (number.length() == 3){
				interruptCut = (Character.digit(number.charAt(0), 10) * 10) + Character.digit(number.charAt(1), 10);
				other = (Character.digit(number.charAt(2), 10) * 1);
			}
			
			if (number.length() == 2)	
				interruptCut = (Character.digit(number.charAt(0), 10) * 10) + Character.digit(number.charAt(1), 10);
		
			if (number.length() == 1)	
				interruptCut = (Character.digit(number.charAt(0), 10) * 1);		
		}
		System.out.println("Input = " + interrupt ); 		// testing
		System.out.println("Interrupt = " + interruptCut );
		System.out.println("Other = " + other );
		
		switch (interruptCut) {								// switch case that handles interrupts and passes DEV or PID to requiring functions
		    case 0:   shutdown();
		             break;
		             
		    case 15:  timer();
		             break;
		             
		    case 64:  waitsys();
		             break;
		             
		    case 65:  signal(other);
		             break;
		             
		    case 70:  IOreq(other); 
		             break;
		             
		    case 71:  IOcompl(other);
		             break;
		             
		    case 80:  create();
		             break;
		             
		    case 99:  createN(other);
		    		 break;
		             
		    case 81:  terminate();
		             break;
		             
		    case 244: gracefulShut();
		             break;
		             
		    case 255: display();
		             break;
		    
		    default: System.out.println("Please enter a new interrupt - invalid input");
		             break;
	    }
	}		
	
		private void shutdown() {							// error prone shut down
			System.out.println("Shutting down in a hurry");
			System.exit(-1);
		}
	
		public void timer() {								// turnaround at delta t
			PROCESS turnOut = CPU.runningProcess; 
			readyQ.offer(turnOut);
			PROCESS turnIn = readyQ.remove();
			turnIn.state = "ready";
			CPU.runningProcess = turnIn;
			
			System.out.println("Timer Interrupt");
			if (!readyQ.isEmpty())
				System.out.println("Process # " + readyQ.peekLast().PID + " from Ready Queue");
			else {
				System.out.println("Process # " + runningProcess.PID + " from Processor");
				System.out.println("No More Processes");// error handling
				CPU.runningProcess = new PROCESS(OS.numberProcesses);
				OS.numberProcesses++;
				System.out.println("Standard Process # " + runningProcess.PID + " added to Processor");
			}
		}
	
		private void waitsys() {						// wait system call
			CPU.runningProcess.state = "waiting";
			OS.waitingQ.add(CPU.runningProcess);
			
			if (!readyQ.isEmpty()){						
				CPU.runningProcess = readyQ.remove();	// take next ready process
				runningProcess.state = "ready";
			}
			else { 			
				System.out.println("No More Processes");// error handling
				CPU.runningProcess = new PROCESS(OS.numberProcesses);
				OS.numberProcesses++;
				System.out.println("Standard Process # " + runningProcess.PID + " added to Processor");
			}
			
			System.out.println("Wait System Call Interrupt");
			System.out.println("Process # " + OS.waitingQ.peekLast().PID + " put into OS Waiting Queue");
			System.out.println("Process # " + runningProcess.PID + " now into Processor");
		}
	
		private void signal(int PID){					// get process from os waiting queue
			PROCESS takeOut;
			PROCESS temp= new PROCESS(PID);				// temporary object to compare with the one in waiting queue
			if (OS.waitingQ.contains(temp)){ 
				takeOut = OS.waitingQ.remove(OS.waitingQ.indexOf(temp));
				takeOut.state = "ready";
				readyQ.add(takeOut);
				System.out.println("Process # " + readyQ.peekLast().PID + " added to Ready Queue");

			}
			else System.out.println("Process not present in Waiting Queue");
			System.out.println("Signal Interrupt");			
		}
        
		public void IOreq(int DEV){							//request IO : send running process into declared Device and bring next ready process in 
			IO temp= new IO(DEV);							// creating temporary IO to find appropriate IO in OS's device list
			if (OS.iostructure.contains(temp)){
				int index = OS.iostructure.indexOf(temp);
				if (!readyQ.isEmpty()){						
					CPU.runningProcess.state = "waiting";
					OS.iostructure.get(index).itsQ.offer(CPU.runningProcess);
					CPU.runningProcess = readyQ.remove();	// take next ready process
					runningProcess.state = "ready";
					System.out.println("Process # " + runningProcess.PID + " now into Processor");

				}
				else { 			
					CPU.runningProcess.state = "waiting";
					OS.iostructure.get(index).itsQ.offer(CPU.runningProcess);
					System.out.println("No More Processes");// error handling
					CPU.runningProcess = new PROCESS(OS.numberProcesses);
					OS.numberProcesses++;
					System.out.println("Standard Process # " + runningProcess.PID + " added to Processor");
				}
				System.out.println("Process # " + OS.iostructure.get(index).itsQ.peekLast().PID + " added in Device # " + OS.iostructure.get(index).num + " 's queue");
			}
			else {
				System.out.println("No such device");
			}
			System.out.println("IO Request Interrupt");
		}
        
		public void IOcompl(int DEV){			 			// upon IO process completion, send completed process back to ready queue
			IO temp= new IO(DEV);
			if (OS.iostructure.contains(temp)){				// making sure the device exists
				int index = OS.iostructure.indexOf(temp);
				OS.iostructure.get(index).IOprocess();		// rely on "io controller"
			}
			else {
				System.out.println("No such device");
			}
			System.out.println("IO Completed Interrupt");
		}

		private void create() {								// create a new process and increment os's count of processes
			readyQ.add(new PROCESS(OS.numberProcesses++));
			
			System.out.println("Create Process Interrupt");
			System.out.println("Process # " + readyQ.peekLast().PID + " added in Ready Queue");
		}
		
		private void createN(int n) {								// create a new process and increment os's count of processes
			for (int i=0; i < n; i++){
				readyQ.add(new PROCESS(OS.numberProcesses++));
			}
			
			System.out.println("Create Process Interrupt");
			System.out.println(n + " Processes added to Ready Queue\n" +"Up to Process # " + readyQ.peekLast().PID );
		}
		
		private void terminate() {							// terminate process and decrement os's count of processes
			CPU.runningProcess.terminateP();
			OS.numberProcesses--;
			if(!readyQ.isEmpty()){ 							// if the queue is empty, create another standard process for the cpu
				CPU.runningProcess = readyQ.remove();
				OS.numberProcesses--;
			}	
			else { 											// always making sure that the CPU has a running process
				System.out.println("No More Processes");
				CPU.runningProcess = new PROCESS(OS.numberProcesses);
				OS.numberProcesses++;
				System.out.println("Standard Process # " + runningProcess.PID + " added to Processor");
			}
			
			System.out.println("Terminate Process Interrupt");
		}
	
		private void gracefulShut() {						// turn off properly, by closing sequentially all processes in ready q and processor
			System.out.println("Process # " + runningProcess.PID + " was running prior to shutdown");
			CPU.runningProcess.terminateP();
			
			while (!readyQ.isEmpty()){ 
				CPU.runningProcess = readyQ.remove();
				CPU.runningProcess.terminateP();
			}	
			
			while (!OS.waitingQ.isEmpty()){
				OS.waitingQ.remove().terminateP();
			}
			
			for (IO ios : OS.iostructure){
				ios.itsQ.removeAll(ios.itsQ);
			}
			System.out.println("Terminated gracefully");
			System.exit(0);			
		}
	
		private void display() {							// display the content of the operating system and all its processes
			DateFormat df = new SimpleDateFormat("dd/MM/yy HH:mm:ss");
			Date dateobj = new Date();
			System.out.println("System status at " + df.format(dateobj));
			System.out.println("Process # " + runningProcess.PID + " running in Processor");
			this.ReadyQPrint();
			this.WaitingQPrint();
			this.IOSPrint();
			System.out.println("Displayed succesfully\n");	
		}
		
		void ReadyQPrint(){										// iterating printing functions
			Iterator<PROCESS> itRQ = readyQ.iterator();
			if (!itRQ.hasNext())
				System.out.println("No Process in Ready Queue");
			else {
				System.out.println("Processes in the Ready Queue");
				while (itRQ.hasNext()){
					PROCESS temp = itRQ.next();
					System.out.println("Process # " + temp.PID + " : " + temp.state );
				}
			}
		}
		
		void WaitingQPrint(){
			Iterator<PROCESS> itWait = OS.waitingQ.iterator();
			if (!itWait.hasNext())
				System.out.println("No Process in Waiting Queue");
			else {
				System.out.println("Processes in the Waiting Queue");
				while (itWait.hasNext()){
					PROCESS temp = itWait.next();
					System.out.println("Process # " + temp.PID + " : " + temp.state );
				}
			}	
		}

		void IOSPrint(){
			Iterator<IO> itIOS = OS.iostructure.iterator();
			if (!itIOS.hasNext())
				System.out.println("No IO Devices in OS");
			else {	
				System.out.println("IO Devices");
				while (itIOS.hasNext()){
					IO temp = itIOS.next();
					temp.IOPrint();
				}
			}
		}

}
