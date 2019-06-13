
public abstract class Event implements Comparable<Event> {

	public int time;
	public String name;

	public Event(){}
	
	
	public void process() {
	}
	
	 public int compareTo(Event e) {
	        
		 if ( ( this.time - BankSim.clock ) == ( (e.time) - BankSim.clock ) )
	            return ( ( time - BankSim.clock ) - ( e.time - BankSim.clock ) );
	     return ( ( time - BankSim.clock ) - ( e.time - BankSim.clock ) );
	 }
	
//	public int compareTo(Event e) {
//        return this.time.compareTo(e.time);
//    }
}

