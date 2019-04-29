package il.co.ilrd.threadpool;

import static org.junit.jupiter.api.Assertions.*;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.Callable;
import java.util.concurrent.CancellationException;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.Future;
import java.util.concurrent.RejectedExecutionException;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.TimeoutException;

import org.junit.jupiter.api.Test;

import il.co.ilrd.threadpool.ThreadPool.Priority;

class ThreadPoolTest {

	class WorkerThread implements Callable<Integer> {

		private Integer command;

		public WorkerThread(Integer command)  {
			this.command = command;
		}

		@Override
		public Integer call() {
			return command;
		}
	}
	
	class WorkerPause implements Runnable{
		@Override
		public void run() {
			try {
				Thread.sleep(10);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
	}
	
	@Test
	void testBasic() throws InterruptedException, ExecutionException {
		ThreadPool executor = new ThreadPool(3);

		Callable<Integer> worker1 = new WorkerThread(1);
		Future<Integer> task1 = executor.submit(worker1, Priority.MAX_PRIORITY);
		
		Callable<Integer> worker2 = new WorkerThread(2);
		Future<Integer> task2 = executor.submit(worker2, Priority.MAX_PRIORITY);
		
		Callable<Integer> worker3 = new WorkerThread(3);
		Future<Integer> task3 = executor.submit(worker3);
		
		Runnable worker4 = new Runnable() {
			
			@Override
			public void run() {
			 System.out.println("Never Print");
			}
		};
		
		Future<Integer> task4 = executor.submit(worker4, Priority.MIN_PRIORITY);
		task4.cancel(false);
		
		Callable<Integer> worker5 = new WorkerThread(5);
		Future<Integer> task5 = executor.submit(worker5, Priority.MIN_PRIORITY);
		assertTrue(task5.isDone() == false);
		
		executor.run();
		assertTrue(task5.isCancelled() == false);
		assertTrue(task1.get() == 1);
		assertTrue(task1.isDone());
		assertTrue(task2.get() == 2);
		assertTrue(task3.get() == 3);
		assertTrue(task5.get() == 5);
		assertTrue(task4.isCancelled());
		try {
			task4.get();			
		} catch (CancellationException e) {
			assertTrue(true);
		}

		executor.shutDown();
	}

	@Test
	void testMultiThread() throws InterruptedException, ExecutionException, TimeoutException {
		ThreadPool executor = new ThreadPool(3);
		List<Future<Integer>> futures = new ArrayList<>();
		executor.run();
		
		for (int i = 0; i < 100; ++i) {
			futures.add(executor.submit(new WorkerThread(i)));
		}
		
		for (int i = 0; i < 100; ++i) {
			assertTrue(futures.get(i).get() == i);
		}
		
		executor.pause();

		for (int i = 0; i < 50; ++i) {
			futures.add(executor.submit(new WorkerPause(), Priority.MAX_PRIORITY));
		}
		
		Future<Integer> temp = executor.submit(new WorkerThread(1), Priority.MIN_PRIORITY);
		
		Thread.sleep(100);
		executor.resume();
		try {
			executor.resume();			
		} catch (IllegalStateException e) {
			assertTrue(true);
		}

		try {
			temp.get(100, TimeUnit.MICROSECONDS);			
		} catch (TimeoutException e) {
			assertTrue(true);
		}
		
		assertTrue(temp.get() == 1);
		executor.shutDown();
	}
	
	@Test
	void testPauseShutdown() throws InterruptedException, ExecutionException {
		ThreadPool executor = new ThreadPool(3);
		List<Future<Integer>> futures = new ArrayList<>();
	
		for (int i = 0; i < 100; ++i) {
			futures.add(executor.submit(new WorkerThread(i)));
		}
		
		executor.run();
		executor.pause();
		executor.shutDown();
		
		for (int i = 0; i < 100; ++i) {
			assertTrue(futures.get(i).get() == i);
		}
	}
	
	@Test
	void testException() throws InterruptedException, ExecutionException {
		ThreadPool executor = new ThreadPool(3);
		List<Future<Integer>> futures = new ArrayList<>();
	
		for (int i = 0; i < 100; ++i) {
			futures.add(executor.submit(new WorkerThread(i)));
		}
		
		executor.shutDown();
		try {
			executor.submit(new WorkerThread(1), Priority.MIN_PRIORITY);			
		} catch (RejectedExecutionException e) {
			assertTrue(true);
		}
		executor.run();
		
		for (int i = 0; i < 100; ++i) {
			assertTrue(futures.get(i).get() == i);
		}
		
		Thread.sleep(1000);
		Future<Integer> temp = executor.submit(new WorkerThread(1), Priority.MIN_PRIORITY);

		try {
			temp.get(100, TimeUnit.MICROSECONDS);			
		} catch (TimeoutException e) {
			assertTrue(true);
		}

		Thread.sleep(1000);
		executor.setNumThreads(1);
		assertTrue(temp.get() == 1);
		
		try {
			executor.setNumThreads(-6);			
		} catch(IllegalArgumentException e) {
			assertTrue(true);
		}
	}
	
}