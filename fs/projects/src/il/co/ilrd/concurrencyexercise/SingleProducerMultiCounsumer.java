package il.co.ilrd.concurrencyexercise;

import java.util.concurrent.Semaphore;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;


public class SingleProducerMultiCounsumer {
	private Integer globalData = 0;
	private static final int CONSUMER_NUMBER = 10;
	private int currentCounter = 0;
	private Lock lock = new ReentrantLock();
	private Condition cond = lock.newCondition();
	private Semaphore semaphore = new Semaphore(1);
	
	class Producer implements Runnable {
		@Override
		public void run() {
			while (true) {		
				try {
					semaphore.acquire();
				} catch (InterruptedException e) {
					e.printStackTrace();
				}

				lock.lock();
				++globalData;
				currentCounter = CONSUMER_NUMBER;
				cond.signalAll();
				lock.unlock();
			}
		}
	}

	class Consumer implements Runnable {
		@Override
		public void run() {
			while (true) {
				lock.lock();
				
				while (currentCounter == 0) {
					try {
						cond.await();
					} catch (InterruptedException e) {
						e.printStackTrace();
					}
				}
			
				System.out.println(Thread.currentThread().getName() + ", Global Data = "+ globalData);
				--currentCounter;
				
				if (currentCounter == 0) {
					System.out.println();
					semaphore.release();
				}
				
				try {
					cond.await();
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
				lock.unlock();
			}
		}
	}
	
	public static void main(String[] args) {
		SingleProducerMultiCounsumer e = new SingleProducerMultiCounsumer();
		Thread producer1 = new Thread(e.new Producer());
		Thread[] consumer = new Thread[10]; 
		
		for (int i = 0; i < 10; ++i) {
			consumer[i] = new Thread(e.new Consumer());
			consumer[i].start();
		}

		producer1.start();

	}
}
	