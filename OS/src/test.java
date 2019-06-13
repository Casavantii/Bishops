import java.util.Scanner;

public class test {						// testing my interrupt divider

//	public static void main(String[] args) {
//		int i = 1;
//		while (i ==1){
//
//		interruptHandler();
//		}
//	}

	public static void interruptHandler(){	// takes the input, divides it in interrupt number and other number (dev# or pid) 
		// switch case for different interrupts
		int interrupt = askInt();
		int interruptCut = 0;
		int other = 0;
		
		if (interrupt == 0 || interrupt == 15 || interrupt == 64 || interrupt == 80 || interrupt == 81 ||interrupt == 244 ||interrupt == 255 ){
			interruptCut = interrupt;
			System.out.println(interruptCut);
		}
		
		else{
		//Integer integer = (Integer)interrupt;
		//String dealing = integer.toString();
		//int lenght = dealing.length();
		//String interStr = dealing.substring(0, 1);
		//interruptCut = Integer.parseInt(interStr);
		//lenght = lenght - 2;
		//String otherStr = dealing.substring(2, lenght);
		//other = Integer.parseInt(otherStr);
		//System.out.println(interruptCut + other);
		
			int num = interrupt;
				String number = String.valueOf(num);
//			try{
			if (number.length() == 5)	{
				interruptCut = (Character.digit(number.charAt(0), 10) * 10) + Character.digit(number.charAt(1), 10);

				other =(Character.digit(number.charAt(2), 10) * 100) + (Character.digit(number.charAt(3), 10) * 10) + Character.digit(number.charAt(4), 10);
			}
			if (number.length() == 4){
				interruptCut = (Character.digit(number.charAt(0), 10) * 10) + Character.digit(number.charAt(1), 10);

				other = (Character.digit(number.charAt(2), 10) * 10) + Character.digit(number.charAt(3), 10);
			}
			if (number.length() == 3){
				interruptCut = (Character.digit(number.charAt(0), 10) * 10) + Character.digit(number.charAt(1), 10);

				other = (Character.digit(number.charAt(2), 10) * 1);
			}
			if (number.length() == 2)	
				interruptCut = (Character.digit(number.charAt(0), 10) * 10) + Character.digit(number.charAt(1), 10);
			
			if (number.length() == 1)	
				interruptCut = (Character.digit(number.charAt(0), 10) * 1);
//			}
//			catch (Exception e){
//				interruptHandler();
//			}
//			finally {
			System.out.println("Input = " + interrupt + "\n");

			if (number.length()==1)System.out.println("First digit = " + Character.digit(number.charAt(0), 10) + "\n");
			if (number.length()==2)System.out.println("Second digit = " + Character.digit(number.charAt(1), 10) + "\n");
			if (number.length()==3)System.out.println("Third digit = " + Character.digit(number.charAt(2), 10) + "\n");
			if (number.length()==4)System.out.println("Fourth digit = " + Character.digit(number.charAt(3), 10) + "\n");
			if (number.length()==5)System.out.println("Fift digit = " + Character.digit(number.charAt(4), 10) + "\n");

			
			System.out.println("Interrupt = " + interruptCut + "\n");
			System.out.println("Other = " + other + "\n");

			}
		//}
		}
	
	static int askInt(){
		int i = -1;
			System.out.println("\nWhich interrupt? 0, 15, 64, 65, 70, 71, 80, 81, 244 or 255?\n If 65, include pid right after the interrupt number.\n If 70 or 71, include the device number right after the interrupt number.");
			Scanner I=new Scanner(System.in);
			try{
			i =I.nextInt();
		}
		catch (Exception e){
			System.out.println("\nWrong Input, type in a number, maximum 5 digits");
			askInt();
		}
			//I.close();
			return i;
	}
}