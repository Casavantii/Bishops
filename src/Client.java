import java.util.Random;

public class Client {

	static Random rnd = new Random();
	
	public int arrival_Time;
	public int transactions;
	
	public Client(int clock){
		arrival_Time = clock;
		transactions = rnd.nextInt(100);
	}

}	
