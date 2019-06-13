import java.util.*;

public class OS {						// operating system simulation class 
										// catches exceptions
		static CPU processor;			// possessing a CPU, a bus for IOS, the first process, a counter for processes and a waiting queue accessible through system calls
		static LinkedList<IO> iostructure;
		PROCESS firstProcess; 
		static int numberProcesses=1;
		static LinkedList<PROCESS> waitingQ;
		int numberIO=0;
		
		public OS (){					// constructor initializing the process, CPU, waiting queue and io bus
			firstProcess = new PROCESS(OS.numberProcesses++);
			processor = new CPU(firstProcess);
			waitingQ = new LinkedList<PROCESS>();
			iostructure = new LinkedList<IO>();
		}

		static int askIO(){				// prompt for the os user
			int j = -1;
			System.out.println("\nHow many IO devices?");
			Scanner S=new Scanner(System.in);
				try{
				j =S.nextInt();
			}
			catch (Exception e){
				System.out.println("\nWrong Input, type in a NUMBER");
				askIO();
			}
				//S.close();
				return j;
		}

		
		static int askInt(){			// prompt for the os user
			int i = -1;
				System.out.println("\nWhich interrupt? 0, 15, 64, 65, 70, 71, 80, 81, 244 or 255?\n If 65, include pid right after the interrupt number.\n If 70 or 71, include the device number right after the interrupt number.");
				Scanner I=new Scanner(System.in);
				try{
				i =I.nextInt();
			}
			catch (Exception e){
				System.out.println("\nWrong Input, type in a number, maximum 5 digits");
				i=askInt();
			}
				//I.close();
				return i;
		}
    
//    InputStream is = null;			// could be able to enter a file with many interrupts 
//    int i;
//    char c;
//    
//    try{
//       // new input stream created
//       is = new FileInputStream("C://test.txt");
//       
//       System.out.println("Characters printed:");
//       
//       // reads till the end of the stream
//       while((i=is.read())!=-1)
//       {
//          // converts integer to character
//          c=(char)i;
//          
//          // prints character
//          System.out.print(c);
//       }
//    }catch(Exception e){
//       
//       // if any I/O error occurs
//       e.printStackTrace();
//    }finally{
//       
//       // releases system resources associated with this stream
//       if(is!=null) 
//      	 is.close();
//    }
// } 	
	}