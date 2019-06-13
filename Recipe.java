/**
 * @author Steven Poulin 
 * using SemaphorePrecedence program given in Moodle
 */
import java.util.*;

 class Semaphore
{
  private int count;
  private int waiting;

  public Semaphore(int count)
  {
    this.count = count;
    waiting = 0;
  }

  public synchronized void down()
  {
    if (count == 0) {
      try {
        waiting++;
        wait();
      }
      catch (InterruptedException e) {
        System.out.println("Semaphore : Error.");
      }
    }
    else {
      count--;
    }
  }

  public synchronized void down(String s)
  {
    if (count == 0) {
      try {
        waiting++;
        System.out.println("Down going to sleep " + s);
        wait();
      }
      catch (InterruptedException e) {
        System.out.println("Semaphore : Error.");
      }
    }
    else
    {
      System.out.println("Down decrementing " + s);
      count--;
    }
  }

  public synchronized void up()
  {
    if (waiting > 0)
    {
      waiting --;
      notify();
    }
    else
    {
      count++;
    }
  }

  public synchronized void up(String s)
  {
    if (waiting > 0)
    {
      System.out.println("Up waking thread " + s);
      waiting --;
      notify();
    }
    else
    {
      System.out.println("Up incrementing " + s);
      count++;
    }
  }
}
 class Task implements Runnable{
  Thread t ;
  String name;

  Semaphore [ ] uppers;
  Semaphore [ ] downers;

  public Task( String name, Semaphore [ ] downers, Semaphore[ ] uppers) {
   this.uppers  = uppers;
   this.downers = downers;
   this.name = name;
   t = new Thread(this);
   t.start();
  }
   public void run() {
     for ( int i = 0; i < downers.length ; i++)
        downers[ i ].down();
     try{
    	 System.out.println( name + " STARTED");
     Thread.sleep( (int) (Math.random()*200));
     } catch( Exception ex ){ }
     System.out.println( name + " ENDED");
     for ( int i = 0; i < uppers.length ; i++)
        uppers[ i ].up();

   }

 }

public class Recipe{

 static Semaphore [ ] theSemas = new Semaphore[ 11 ];

 public static void main(String [ ] args) throws Exception{

 try{
 for (int k = 0; k < theSemas.length ; k++)
     theSemas[k] = new Semaphore(0);

 System.out.println("RUNNING...");
 Semaphore [ ] P0_D = { };
 Semaphore [ ] P0_U = {theSemas[0] };


 Semaphore [ ] P1_D = { };
 Semaphore [ ] P1_U = {theSemas[1]};

 Semaphore [ ] P2_D = {};
 Semaphore [ ] P2_U = {theSemas[2] };

 Semaphore [ ] P3_D = {theSemas[0], theSemas[1]};
 Semaphore [ ] P3_U = { theSemas[3]};

 Semaphore [ ] P4_D = {};
 Semaphore [ ] P4_U = { theSemas[4]};

 Semaphore [ ] P5_D = {theSemas[2],theSemas[3] };
 Semaphore [ ] P5_U = { theSemas[5]};

 Semaphore [ ] P6_D = {theSemas[4],theSemas[5]  };
 Semaphore [ ] P6_U = { theSemas[6]};

 Semaphore [ ] P7_D = { };
 Semaphore [ ] P7_U = { theSemas[7]};

 Semaphore [ ] P8_D = {theSemas[6],theSemas[7] };
 Semaphore [ ] P8_U = {theSemas[8]};
 
 Semaphore [ ] P9_D = {theSemas[8] };
 Semaphore [ ] P9_U = {theSemas[9]};
 
 Semaphore [ ] P10_D = {theSemas[9] };
 Semaphore [ ] P10_U = {theSemas[10]};

 Task P0 = new Task("Task 1: Cut onions ",P0_D, P0_U);
 Task P1 = new Task("Task 2: Mince meat ",P1_D, P1_U);
 Task P2 = new Task("Task 3: Slice aubergines ",P2_D, P2_U);
 Task P3 = new Task("Task 4: Make sauce ",P3_D, P3_U);
 Task P4 = new Task("Task 5: Make bechamel ",P4_D, P4_U);
 Task P5 = new Task("Task 6: Layout the layers ",P5_D, P5_U);
 Task P6 = new Task("Task 7: Put bechamel and cheese ",P6_D, P6_U);
 Task P7 = new Task("Task 8: Turn on oven ",P7_D, P7_U);
 Task P8 = new Task("Task 9: Cook ",P8_D, P8_U);
 Task P9 = new Task("Turn OFF oven just before Serving",P9_D, P9_U);

 Task P10 = new Task("Serve",P10_D, P10_U);

 } catch (Exception ex) {  ex.printStackTrace();  System.in.read();}

  System.in.read();
 }






}
