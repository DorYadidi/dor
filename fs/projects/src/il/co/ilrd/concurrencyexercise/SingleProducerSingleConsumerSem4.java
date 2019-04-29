package il.co.ilrd.concurrencyexercise;

import java.util.concurrent.Semaphore;

public class SingleProducerSingleConsumerSem4 {
	private Semaphore semProducer = new Semaphore(1);
	private Semaphore semConsumer = new Semaphore(0);

	class Producer implements Runnable {
		
		@Override
		public void run() {
			while (true) {
				try {
					semProducer.acquire();
				} catch (InterruptedException e) {
					e.printStackTrace();
				} 
				
				System.out.println("\u001b[35mPing!\u001b[0m");
				semConsumer.release();
				}
			}
		}
	
	class Consumer implements Runnable{
		@Override
		public void run() {
			while (true) {
				try {
					semConsumer.acquire();
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
				System.out.println("\u001B[32mPong!\u001b[0m");
				semProducer.release();
				}
			}
	}
	
	public static void main(String[] args) {
		SingleProducerSingleConsumerSem4 e = new SingleProducerSingleConsumerSem4();
		Thread producer = new Thread(e.new Producer());
		Thread consumer = new Thread(e.new Consumer());
		producer.start();
		consumer.start();
	}
}