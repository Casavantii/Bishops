
public class Statistics {

	public static double total_Time = 0;
	public static int counter = 0;
	
	public Statistics(){};
	
	public static void average(){
		
		double average = total_Time / counter;
		
		System.out.println( "The average waiting time for this week has been : " + average);
	}
	
	
}
