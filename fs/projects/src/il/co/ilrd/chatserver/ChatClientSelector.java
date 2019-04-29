package il.co.ilrd.chatserver;

import java.io.*;
import java.net.*;
import java.nio.*;
import java.nio.channels.SocketChannel;

public class ChatClientSelector implements Closeable {
	private static final int BUFFER_SIZE = 256;
	private BufferedReader inputClient = new BufferedReader(new InputStreamReader(System.in));
	private ByteBuffer buf = ByteBuffer.allocate(BUFFER_SIZE);
	private SocketChannel channel;
	private Thread listenThread = new Thread(new ListenMessage());
	private String clientName;

	public ChatClientSelector(int port, String clientID) throws IOException {
		channel = SocketChannel.open(new InetSocketAddress("10.1.0.126", port));
		buf = ByteBuffer.wrap(clientID.getBytes());
		channel.write(buf);
		this.clientName = clientID;
	}

	public void run() throws IOException {
		listenThread.start();
		String line;
		try {
			while (!((line = inputClient.readLine()).equals("exit"))) {
				line = clientName + ": " + line;
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
					int numOfByte;
					while ((numOfByte = channel.read(buf)) > 0) {
					}
					;
					if (numOfByte == -1) {
						System.out.println("disconected");
					} else {
						System.out.println(new String(buf.array()));
					}
				} catch (IOException e) {
					e.printStackTrace();
				}

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

		try (ChatClientSelector client = new ChatClientSelector(Integer.parseInt(args[0]), "ss")) {
			client.run();
		}
	}
}
