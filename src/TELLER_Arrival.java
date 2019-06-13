

public class TELLER_Arrival extends Event {

	public String name = "teller_arrival";
	public int time;
	
	public TELLER_Arrival(){
		this.time = BankSim.clock + RandBox.expo( BankSim.INTERARRIVAL_TIME );
			 		
	}
	
	public void process() {
		
		BankSim.clock = time;
	
		if ( BankSim.TELLER != null ){
			BankSim.t_clientQueue.add(BankSim.CUSTOMER);

		}
		
		else {
			BankSim.TELLER = BankSim.CUSTOMER;
			
			BankSim.eventPQ.add( new TELLER_Departure( BankSim.clock + RandBox.expo( BankSim.AVG_TIME_PER_TRNSACTION * (BankSim.TELLER).transactions ) ) ); //scheduling new receptionnist departure
				
		}
		
		BankSim.CUSTOMER = null;
		
		BankSim.eventPQ.add( new TELLER_Arrival() ); // scheduling new arrival
		
	}
		
		
}

