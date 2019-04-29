package il.co.ilrd.concurrencyexercise;

import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.locks.ReentrantLock;

public class CostOfLocking {
	private static final int MAX_COUNTER = 10000000;
	
	static class SynchronizedMethod implements Runnable{
		private volatile int counter = 1;
		
		private synchronized void incrementCounter() {
		      //System.out.println("name=" + Thread.currentThread().getName() + ", Counter = " + counter);
			if (counter < MAX_COUNTER)	{
				++counter;				
			}      
		}

		@Override
		public void run() {
			long startTime = System.currentTimeMillis();
			while (counter < MAX_COUNTER) {
				this.incrementCounter();
			}
			long estimatedTime = System.currentTimeMillis() - startTime;
			System.out.println("SynchronizedMethod Counter = "+ counter +", Time : "+ estimatedTime + "ms");
		}
	}
	
	
	static class SynchronizedBlock implements Runnable{
		private volatile int counter = 1;

		private void incrementCounter() {
		      //System.out.println("name=" + Thread.currentThread().getName() + ", Counter = " + counter);
		      ++counter;
		}

		@Override
		public void run() {
			long startTime = System.currentTimeMillis();
			while (counter < MAX_COUNTER) {
				synchronized (this) {
					if (counter < MAX_COUNTER) {
						this.incrementCounter();											
					}
				}
			}
			
			long estimatedTime = System.currentTimeMillis() - startTime;
			System.out.println("SynchronizedBlock Counter = "+ counter +", Time : "+ estimatedTime + "ms");
		}
	}
	
	static class Atomics implements Runnable{
		private AtomicInteger counter = new AtomicInteger(1);

		@Override
		public void run() {
			long startTime = System.currentTimeMillis();
			int tempCounter = counter.get();
			while (tempCounter < MAX_COUNTER) {
		      //System.out.println("name=" + Thread.currentThread().getName() + ", Counter = " + counter);
				int newValue = tempCounter + 1;
				counter.compareAndSet(tempCounter, newValue);
				tempCounter = counter.get();
			}
			
			long estimatedTime = System.currentTimeMillis() - startTime;
			System.out.println("Atomics Counter = "+ counter +", Time : "+ estimatedTime + "ms");
		}	
	}
	
	static class Reentrantlock implements Runnable{
		private int counter = 1;
		static ReentrantLock counterLock = new ReentrantLock(true);
		 
		private void incrementCounter() {
			counterLock.lock();
			if (counter < MAX_COUNTER)	{
				try {
					//System.out.println("name=" + Thread.currentThread().getName() + ", Counter = " + counter);
					++counter;
				} finally {
					counterLock.unlock();
				}				
			}
		}
		
		@Override
		public void run() {
			long startTime = System.currentTimeMillis();
			while (counter < MAX_COUNTER) {
				this.incrementCounter();
			}
			
			long estimatedTime = System.currentTimeMillis() - startTime;
			System.out.println("ReentrantLock Counter = "+ counter +", Time : "+ estimatedTime + "ms");
			}
	}
	
	public static void main(String[] args) throws Exception {
		//Synchronized Method
		SynchronizedMethod syncMethod = new SynchronizedMethod();
		Thread threadSynchronizedMethod1 = new Thread(syncMethod, "thread1");
		Thread threadSynchronizedMethod2 = new Thread(syncMethod, "thread2");
		threadSynchronizedMethod2.start();
		threadSynchronizedMethod1.start();
		threadSynchronizedMethod1.join();
		threadSynchronizedMethod1.join();
		
		//Synchronized Block
		SynchronizedBlock syncBlock = new SynchronizedBlock();
		Thread threadSynchronizedBlock1 = new Thread(syncBlock, "thread1");
		Thread threadSynchronizedBlock2 = new Thread(syncBlock, "thread2");
		threadSynchronizedBlock1.start();
		threadSynchronizedBlock2.start();
		threadSynchronizedBlock1.join();
		threadSynchronizedBlock2.join();
		
		//Atomics
		Atomics atomic = new Atomics();
		Thread threadAtomics1 = new Thread(atomic, "thread1");
		Thread threadAtomics2 = new Thread(atomic, "thread2");
		threadAtomics1.start();
		threadAtomics2.start();
		threadAtomics1.join();
		threadAtomics2.join();
		
		Thread.sleep(1000);
		
		//Reentrant Lock
		Reentrantlock reenlock = new Reentrantlock();
		Thread Reentrantlock1 = new Thread(reenlock, "thread1");
		Thread Reentrantlock2 = new Thread(reenlock, "thread2");
		Reentrantlock1.start();
		Reentrantlock2.start();
		Reentrantlock1.join();
		Reentrantlock2.join();
	}
}
