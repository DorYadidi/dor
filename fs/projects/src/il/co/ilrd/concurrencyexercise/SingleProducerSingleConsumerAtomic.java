package il.co.ilrd.concurrencyexercise;

import java.util.concurrent.atomic.AtomicBoolean;

public class SingleProducerSingleConsumerAtomic {
	private AtomicBoolean flag = new AtomicBoolean(false);
	
	class Producer implements Runnable{
		@Override
		public void run() {
			while (true) {
				if (flag.get() == false) {
					System.out.println("\u001b[35mPing!\u001b[0m");
					flag.getAndSet(true);
				}
			}
		}
	}
	
	class Consumer implements Runnable{
		@Override
		public void run() {
			while (true) {
				if (flag.get() == true) {
					System.out.println("\u001B[32mPong!\u001b[0m");
					flag.getAndSet(false);
				}
			}
		}
	}
	
	public static void main(String[] args) {
		SingleProducerSingleConsumerAtomic e = new SingleProducerSingleConsumerAtomic();
		Thread producer = new Thread(e.new Producer());
		Thread consumer = new Thread(e.new Consumer());
		producer.start();
		consumer.start();
	}
}
