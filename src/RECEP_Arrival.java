
public class RECEP_Arrival extends Event {

	public String name = "recep_arrival";
	public int time;
	
	public RECEP_Arrival(){
		this.time = (int) (BankSim.clock + RandBox.expo( BankSim.INTERARRIVAL_TIME ));
			 		
	}
	
	public void process() {
		
		BankSim.clock = time;
		
		Client c = new Client(BankSim.clock);
		
		if ( BankSim.RECEPTIONIST != null ){
			BankSim.r_clientQueue.add(c);
		}
		
		else {
			BankSim.RECEPTIONIST = c;
			
			BankSim.eventPQ.add( new RECEP_Departure( BankSim.clock + RandBox.expo( BankSim.AVG_TIME_PER_TRNSACTION * c.transactions ) ) ); //scheduling new receptionnist departure
				
		}
		
		BankSim.eventPQ.add( new RECEP_Arrival() ); // scheduling new arrival
		
	}
		
		
}

