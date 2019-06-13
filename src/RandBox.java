import java.util.Random;

public class RandBox extends Random {

	/**
	 * 
	 */
	private static final long serialVersionUID = -5451245332783176374L;

	static Random rnd = new Random();

	public int random;
	
	public RandBox(int i){
		
		random = rnd.nextInt(i);
	}
	
	static int expo(double mean){
		double x = Math.random();
		x = -mean * Math.log(x);
		return (int) x;
	}
}

