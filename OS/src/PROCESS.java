import java.util.Objects;

public class PROCESS{
	int PID;
	String state;
	
	public PROCESS(int pid){				// constructing a process by giving it the os's numberofProcesses number
		this.PID = pid;						// and setting state to ready
		this.state = "ready";
	}
	
	public void terminateP(){				// terminating Process
		System.out.println("Process # " + this.PID + " terminating ....");
		this.PID = 0;
		this.state = null;
		System.out.println("... done.");


	}
	
	public int getPID(){					// returns process.pid
		return this.PID;
	}
	
	public boolean equals(Object o) {		//overriding equals to find process in the queue
	    // self check
	    if (this == o)
	        return true;
	    // null check
	    if (o == null)
	        return false;
	    // type check and cast
	    if (getClass() != o.getClass())
	        return false;
	    PROCESS proc = (PROCESS) o;
	    // field comparison
	    return Objects.equals(this.PID, proc.PID);
	}
	
	public int hashCode() {
	    return Objects.hash(PID);
	}
}

