package il.co.ilrd.concurrencyexercise;

public class CreateThread {

	class CreateThread1 extends Thread{
		@Override
		public void run() {
			for (int i = 0; i < 5; ++i)
			{
				System.out.println("CreateThread1 extends Thread");
				try {
					Thread.sleep(10);
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			}
		}
	}
	
	class CreateThread2 implements Runnable {
		@Override
		public void run() {
			for (int i = 0; i < 5; ++i)
			{
				System.out.println("CreateThread2 implements Runnable");
				try {
					Thread.sleep(10);
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			}
		}
	}
	
	public static void main(String[] args) {
		CreateThread1 thread1 = new CreateThread().new CreateThread1();
		Thread thread2 = new Thread(new CreateThread().new CreateThread2());
		thread1.start();
		thread2.start();
	}
}