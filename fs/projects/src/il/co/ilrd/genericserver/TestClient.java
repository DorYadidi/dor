package il.co.ilrd.genericserver;

import java.io.BufferedReader;
import java.io.Closeable;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SocketChannel;

public class TestClient implements Closeable {
	private static final int BUFFER_SIZE = 256;
	private BufferedReader inputClient = new BufferedReader(new InputStreamReader(System.in));
	private ByteBuffer buf = ByteBuffer.allocate(BUFFER_SIZE);
	private SocketChannel channel;
	private Thread listenThread = new Thread(new ListenMessage());

	public TestClient(int port, String clientID) throws IOException {
		channel = SocketChannel.open(new InetSocketAddress("localhost", port));
		buf = ByteBuffer.wrap(clientID.getBytes());
		channel.write(buf);
	}

	public void run() throws IOException {
		listenThread.start();
		String line;
		try {
			while (!((line = inputClient.readLine()).equals("exit"))) {
				resetBuffer();
				buf = ByteBuffer.wrap(line.getBytes());
				channel.write(buf);
			}
		} catch (IOException e) {
			e.printStackTrace();
		}

		System.out.println("Logout!");
	}

	private class ListenMessage implements Runnable {
		@Override
		public void run() {
			while (channel.isOpen()) {
				resetBuffer();
				try {
					channel.read(buf);
				} catch (IOException e) {
					e.printStackTrace();
				}

				System.out.println(new String(buf.array()));
			}
		}
	}

	private void resetBuffer() {
		buf.clear();
		buf = ByteBuffer.wrap(new byte[BUFFER_SIZE]);
		buf.clear();
	}

	@Override
	public void close() throws IOException {
		try {
			listenThread.join();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		inputClient.close();
		channel.close();
	}

	public static void main(String[] args) throws IOException, InterruptedException {

		try (TestClient client = new TestClient(13000, "asoso")) {
			client.run();
		}
	}
}
