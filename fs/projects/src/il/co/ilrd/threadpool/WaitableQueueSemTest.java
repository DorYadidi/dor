package il.co.ilrd.threadpool;

import static org.junit.Assert.assertTrue;

import java.util.concurrent.TimeUnit;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

class WaitableQueueSemTest {
	private Integer counter;
	private WaitableQueueSem<Integer> queue;
	
	@BeforeEach
	private void setUp() {
		queue = new WaitableQueueSem<Integer>();
		counter = 0;
	}
	
	@Test
	void testBasic() throws InterruptedException {
		Runnable enqueueThread = new Runnable() {

			@Override
			public void run() {
				for(int i = 0; i< 10; ++i) {
					queue.enqueue(++counter);
				}
			}
		};
		
		Runnable denqueueThreadRunnable = new Runnable() {
			Integer tempCounter = 1;
			@Override
			public void run() {
				for(int i = 0; i< 10; ++i) {
					
						try {
							assertTrue(queue.dequeue() == tempCounter++);
						} catch (InterruptedException e) {
							e.printStackTrace();
						}
				}
			}
		};
		
		Thread producer = new Thread(enqueueThread);
		Thread consumer = new Thread(denqueueThreadRunnable);
		consumer.start();
		producer.start();
		producer.join();
		consumer.join();
	}
	
	@Test
	void testTimer() throws InterruptedException {
		Runnable enqueueThread = new Runnable() {

			@Override
			public void run() {
				for(int i = 0; i< 10; ++i) {
					try {
						Thread.sleep(10000);
					} catch (InterruptedException e) {
						e.printStackTrace();
					}
					queue.enqueue(++counter);
				}
			}
		};
		
		Runnable denqueueThreadRunnable = new Runnable() {
			@Override
			public void run() {
				for(int i = 0; i< 10; ++i) {
					
						try {
							assertTrue(queue.dequeue(1, TimeUnit.NANOSECONDS) == null);
						} catch (InterruptedException e) {
							e.printStackTrace();
						}
				}
			}
		};
		
		Thread producer = new Thread(enqueueThread);
		Thread consumer = new Thread(denqueueThreadRunnable);
		consumer.start();
		producer.start();
	}
	
	@Test
	void testRemove() throws InterruptedException {
		Runnable enqueueThread = new Runnable() {

			@Override
			public void run() {
				for(int i = 0; i< 10; ++i) {
					queue.enqueue(++counter);
				}
			}
		};
		
		Runnable denqueueThreadRunnable = new Runnable() {
			Integer tempCounter = 1;
			@Override
			public void run() {
				for(int i = 0; i< 10; ++i) {
					
						try {
							Thread.sleep(100);
							assertTrue((queue.remove(tempCounter++)));
						} catch (InterruptedException e) {
							e.printStackTrace();
						}
				}
			}
		};
		
		Thread producer = new Thread(enqueueThread);
		Thread consumer = new Thread(denqueueThreadRunnable);
		consumer.start();
		producer.start();
		producer.join();
		consumer.join();
	}
}
