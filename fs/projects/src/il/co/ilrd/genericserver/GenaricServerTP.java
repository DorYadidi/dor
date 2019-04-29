package il.co.ilrd.genericserver;

import java.io.IOException;
import java.nio.ByteBuffer;
import java.util.function.Consumer;

import il.co.ilrd.threadpool.ThreadPool;

public class GenaricServerTP {

	private class ConsumerTP implements Consumer<ByteBuffer> {
		private ThreadPool tp;

		public ConsumerTP(int numOfThread) {
			tp = new ThreadPool(numOfThread);
			tp.run();
		}

		@Override
		public void accept(ByteBuffer t) {
			Runnable task = new Runnable() {

				@Override
				public void run() {
					String print = new String(t.array());
					System.out.println(print);
				}
			};

			tp.execute(task);
		}
	}

	public static void main(String[] args) throws IOException {
		try {
			GenericServer server = new GenericServer(13000, "localhost", new GenaricServerTP().new ConsumerTP(8));
			Thread thread = new Thread(server);
			thread.start();

		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}
