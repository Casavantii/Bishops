import java.util.*;

public class IO {								// class IO having a number and a queue

	int num;
	LinkedList<PROCESS> itsQ;					
	
	public IO(int dev){							// constructor giving the device a number and initializing its queue
		num = dev;
		itsQ = new LinkedList<PROCESS>();	
	}
	
	void IOprocess(){							// IO processing function removes from device queue, set to ready and place into CPU's ready queue

		if (!this.itsQ.isEmpty()){
			PROCESS now = this.itsQ.removeFirst();
			now.state = "ready";
			System.out.print("IO device # " + this.num + " processed Process # " + now.PID + "\n");
	        CPU.readyQ.offer(now);
	        System.out.print("Process # " + CPU.readyQ.peekLast().PID + " back in Ready Queue\n");
		}
		else 
			System.out.println("IO Queue empty");
	}
	
	void IOPrint(){								// IO being able to print its content or lack thereof
		Iterator<PROCESS> itIO = itsQ.iterator();
		if (!itIO.hasNext())
			System.out.println("No Processes in Device #  " + this.num + "'s Queue" );
		else {
			System.out.println("Processes in the Device # " + this.num + "'s Queue" );
			while (itIO.hasNext()){
				PROCESS temp = itIO.next();
				System.out.println("Process # " + temp.PID + " : " + temp.state);
			}
		}
	}

	public boolean equals(Object o) {					// overrriding equals and hashcode to be able to find IO in the OS's list of IOs
	    // self check
	    if (this == o)
	        return true;
	    // null check
	    if (o == null)
	        return false;
	    // type check and cast
	    if (getClass() != o.getClass())
	        return false;
	    IO device = (IO) o;
	    // field comparison
	    return Objects.equals(this.num, device.num);
	}
	
	public int hashCode() {
	    return Objects.hash(num);
	}
	
	}
