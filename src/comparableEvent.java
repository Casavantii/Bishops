import java.util.Comparator;

public class comparableEvent implements Comparator<Event>{
	
	public int compare(Event e1, Event e2){
		return Integer.compare(e1.time, e2.time);
	}

}
