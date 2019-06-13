public class OSDemo {

	public static void main(String[] args) {		// test class		
				
				OS os1 = new OS();
				
				os1.numberIO =OS.askIO();
				
				for (int i=0; i < os1.numberIO; i++)
					OS.iostructure.offer(new IO(i+1));		// i+1 to name the device properly
				
			    while(true){
			    	OS.processor.interruptHandler(OS.askInt());
			    }
	}

}
