package il.co.ilrd.execurorframework;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class MultipleTasksExecutorExample {
	 
	class CountDownClock extends Thread {
	    private String clockName;
	 
	    public CountDownClock(String clockName) {
	        this.clockName = clockName;
	    }
	 
	    public void run() {
	        String threadName = Thread.currentThread().getName();
	 
	        for (int i = 5; i >= 0; i--) {
	 
	            System.out.printf("%s -> %s: %d\n", threadName, clockName, i);
	 
	            try {
	                Thread.sleep(1000);
	            } catch (InterruptedException ex) {
	                ex.printStackTrace();
	            }
	        }
	    }
	}
	
	
    public static void main(String[] args) {
    	//newCachedThreadPool
    	//ExecutorService pool = Executors.newCachedThreadPool();
    	
    	//newFixedThreadPool
        ExecutorService pool = Executors.newFixedThreadPool(2);
    	
    	//newSingleThreadExecutor
    	//ExecutorService pool = Executors.newSingleThreadExecutor();
    	
    	//newScheduledThreadPool
    	//ExecutorService pool = Executors.newScheduledThreadPool(2);

    	
    	
        MultipleTasksExecutorExample e = new MultipleTasksExecutorExample();
        pool.execute(e.new CountDownClock("A"));
        pool.execute(e.new CountDownClock("B"));
        pool.execute(e.new CountDownClock("C"));
        pool.execute(e.new CountDownClock("D"));
 
        pool.shutdown();
 
    }
}
