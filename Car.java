import java.util.concurrent.ThreadLocalRandom;
/**
 * 
 * @author Steven Poulin
 * a simulation of a one-lane circulation event
 * @class Car
 * threads sharing the bridge
 */
public class Car{

	public static int onTheBridge = 0;
	public static boolean bLocked = false; // the locks
	public static boolean lioLocked = false;
	public static int countingBishCars = 0; // to make sure all cars have crossed, or not
	public static int countingLionCars = 0;
	public static int testSize = 5; // to test for larger amounts, just change this

	public static void main(String [] args){

		BishBound bish = new BishBound();
		LionBound lion = new LionBound();

		for (int i = 1; i <= testSize; i++){ // runs for the amount of the testSize (presently 5)

			new Thread(bish, "Bishop's Bound "+i).start(); //concurrently starting the threads
			new Thread(lion, "Lion's Bound: "+i).start();
		}
		
	}
}
/**
 * 
 * @class BishBound
 * a thread simulating - arriving at a bridge, waiting, going at a random speed
 */
class BishBound extends Thread{

	public void run(){

		while (Car.lioLocked == true){

			System.out.println(Thread.currentThread().getName() + " waiting");
			try{
				sleep(ThreadLocalRandom.current().nextInt(0, 200)); // waiting (found this piece of code online
			} catch (InterruptedException ex) {}
		}

		Car.onTheBridge++;
		Car.lioLocked = false; /*making it so if there is a car on the bridge,
							   the same type can go.. too bad for the others*/
		Car.bLocked = true;

		System.out.println(Thread.currentThread().getName() + " entering");

		try{
			sleep(ThreadLocalRandom.current().nextInt(0, 200));} 
		catch (InterruptedException ex) {}

		Car.onTheBridge--;
		System.out.println (Thread.currentThread().getName() + " CROSSED");
		Car.countingBishCars++;
		if (Car.onTheBridge <= 0){
			Car.bLocked = false; // unlocking the bridge
			Car.lioLocked = false;
		}
		if(Car.countingBishCars == Car.testSize)
			System.out.println("All Bishop's Bound cars have crossed");
		else System.out.println("Not all Bishop's Bound cars have crossed");
	}
}
/**
 * 
 * @class LionBound
 * a thread simulating - arriving at a bridge, waiting, going at a random speed
 */
class LionBound extends Thread{

	public void run(){

		while (Car.bLocked == true){

			System.out.println(Thread.currentThread().getName() + " waiting");

			try{
				sleep(ThreadLocalRandom.current().nextInt(0, 200));
			} catch (InterruptedException ex) {}
		}

		Car.lioLocked = true; 
		Car.onTheBridge++;
		System.out.println(Thread.currentThread().getName() + " entering");
		Car.lioLocked = true;
		Car.bLocked = false; // making it so if there is a car on the bridge, the same type can go.. too bad for the others

		try{
			sleep(ThreadLocalRandom.current().nextInt(0, 200));
		} catch (InterruptedException ex) {}

		Car.onTheBridge--;
		System.out.println (Thread.currentThread().getName() + " CROSSED");
		Car.countingLionCars++;
		if (Car.onTheBridge <= 0){
			Car.lioLocked = false;
			Car.bLocked = false;
		}
		if(Car.countingLionCars == Car.testSize)
			System.out.println("All Lion's Bound cars have crossed");
		else System.out.println("Not all Lion's Bound cars have crossed");
	}
} 