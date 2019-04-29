package il.co.ilrd.concurrencyexercise;

import java.util.LinkedList;

public class MultiProducerMultiCounsumer {
	private LinkedList<Integer> list = new LinkedList<>();
	private static final int capacity = 4;
	private int value = 0;

	class Producer implements Runnable {
		@Override
		public void run() {
			
			while (true) {
				synchronized (this) {
					while (list.size() == capacity) {
						try {
							wait();
						} catch (InterruptedException e) {
							e.printStackTrace();
						}
					}

					System.out.println("\u001b[35mProducer produced-" + value+"\u001b[0m");
					list.add(value++);
					notify();
					
					try {
						Thread.sleep(1000);
					} catch (InterruptedException e) {
						e.printStackTrace();
					}
				}
			}
		}
	}

	class Consumer implements Runnable {
		@Override
		public void run() {
			while (true) {
				synchronized (this) {
					while (list.isEmpty()) {
						try {
							wait();
						} catch (InterruptedException e) {
							e.printStackTrace();
						}

					}

					int val = list.removeFirst();

					System.out.println("\u001B[32mConsumer consumed-" + val + "\u001b[0m");
					notify();
					try {
						Thread.sleep(1000);
					} catch (InterruptedException e) {
						e.printStackTrace();
					}
				}
			}
		}
	}

	public static void main(String[] args) {
		MultiProducerMultiCounsumer e = new MultiProducerMultiCounsumer();
		Thread producer1 = new Thread(e.new Producer());
		Thread consumer1 = new Thread(e.new Consumer());
		Thread producer2 = new Thread(e.new Producer());
		Thread consumer2 = new Thread(e.new Consumer());
		producer1.start();
		producer2.start();
		consumer1.start();
		consumer2.start();
	}
}