public class TELLER_Departure extends Event {

	public String name = "teller_departure";
	public int time;
	
	public TELLER_Departure(int d){
		this.time = d;
		
	}
	
	public void process() {
		
		BankSim.clock = time;
		
		
		Statistics.total_Time = Statistics.total_Time + ( BankSim.clock - BankSim.TELLER.arrival_Time );
		BankSim.TELLER = null;
		
		if ( (BankSim.t_clientQueue).poll() != null ){
			BankSim.TELLER = (BankSim.t_clientQueue).poll();
		
			BankSim.eventPQ.add( new TELLER_Departure( BankSim.clock + RandBox.expo( BankSim.AVG_TIME_PER_TRNSACTION * BankSim.TELLER.transactions ) ) ); //scheduling new receptionnist departure
		
		}
		
		// statistics   CLOCK - client arrival time - give that to stats
		
	}
}
