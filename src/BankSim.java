import java.util.ArrayDeque;
import java.util.Deque;
import java.util.PriorityQueue;

public class BankSim {
	
	public static int clock = 0;
	
	public static PriorityQueue<Event> eventPQ;
	public static Deque<Client> r_clientQueue; // receptionist queue
	public static Deque<Client> t_clientQueue; // teller queue
	
	public static Client RECEPTIONIST = null;
	public static Client TELLER = null;
	public static Client CUSTOMER = null; // passing the customer from recep to tell
	
	public static double INTERARRIVAL_TIME = 0;
	public static double AVG_TIME_PER_TRNSACTION = 0;
	
	public BankSim( double i, double a ){
		
		eventPQ = new PriorityQueue<Event>(10000, new comparableEvent()); // instanciating priority q
		r_clientQueue = new ArrayDeque<Client>(); // instanciating receptioisst q
		t_clientQueue = new ArrayDeque<Client>(); // instanciating teller q
		INTERARRIVAL_TIME = i;
		AVG_TIME_PER_TRNSACTION = a;
	}
	
	public void run ( int simulation_time ){
		
		//BankSim here = new BankSim (120.0, 60);
		
		eventPQ.add( new RECEP_Arrival() ); // scheduling new arrival
		
		while ( clock < simulation_time ){
			(eventPQ.poll()).process();
		}
		
		Statistics.average(); //calculates the average and prints in one method

	}
	
	public static void main(String[] args){
		
		BankSim s = new BankSim (120.0, 60.0);
		s.run( 5 * 8 * 60 * 60 );
	}
}
	

