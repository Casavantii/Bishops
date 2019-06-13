public class RECEP_Departure extends Event {

	public String name = "recep_departure";
	public int time;
	
	public RECEP_Departure(int d){
		this.time = d;
		
	}
	

	public void process() {
		
		BankSim.clock = time;
		
		BankSim.CUSTOMER = BankSim.RECEPTIONIST;
		BankSim.RECEPTIONIST = null;
		
		if ( (BankSim.r_clientQueue).poll() != null ){
			BankSim.RECEPTIONIST = (BankSim.r_clientQueue).poll();
		
			BankSim.eventPQ.add( new RECEP_Departure( BankSim.clock + RandBox.expo( BankSim.AVG_TIME_PER_TRNSACTION * BankSim.RECEPTIONIST.transactions ) ) ); //scheduling new receptionnist departure
		
		}
		
		// statistics   CLOCK - client arrival time - give that to stats
		
	}
}
