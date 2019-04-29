package il.co.ilrd.chatserver;

import java.io.*;
import java.net.*;
import java.nio.*;
import java.nio.channels.*;
import java.util.Iterator;

public class ChatServerSelector implements Closeable {
	private static final int BUFFER_SIZE = 256;
	private Selector selector;
	private ServerSocketChannel serverSocket;
	private ByteBuffer buf;

	public ChatServerSelector(int port) throws IOException {
		buf = ByteBuffer.allocate(BUFFER_SIZE);
		selector = Selector.open();
		serverSocket = ServerSocketChannel.open();
		serverSocket.bind(new InetSocketAddress("localhost", port));
		serverSocket.configureBlocking(false);
		serverSocket.register(selector, SelectionKey.OP_ACCEPT);
	}

	public void run() throws IOException {
		Iterator<SelectionKey> keyRunner;
		SelectionKey key;

		while (selector.isOpen()) {
			selector.select(5000);
			keyRunner = selector.selectedKeys().iterator();

			while (keyRunner.hasNext()) {
				key = keyRunner.next();
				keyRunner.remove();
				if (key.isAcceptable()) {
					register(key);
				} else if (key.isReadable()) {
					handleMessage(key);
				}
			}
		}
	}

	private void register(SelectionKey key) throws IOException {
		System.out.println("Client Conected");
		SocketChannel newClient = serverSocket.accept();
		newClient.configureBlocking(false);
		newClient.register(selector, SelectionKey.OP_READ);

		buf = ByteBuffer.wrap("Welcome!".getBytes());
		newClient.write(buf);
		clearBuffer();
	}

	private void handleMessage(SelectionKey key) throws IOException {
		SocketChannel client = (SocketChannel) key.channel();
		int numOfByte;
		while ((numOfByte = client.read(buf)) > 0) {
		};
		if (numOfByte == -1) {
			key.cancel();
			System.out.println("disconected");
		} else {

			String str = new String(buf.array());
			if (key.attachment() == null) {
				key.attach(str);
			} else {
				System.out.println(str);
				broadcast(key);

			}

			clearBuffer();
		}
	}

	private void clearBuffer() {
		buf.clear();
		buf = ByteBuffer.wrap(new byte[BUFFER_SIZE]);
		buf.clear();
	}

	private void broadcast(SelectionKey key) throws IOException {
		for (SelectionKey temp_key : selector.keys()) {
			if (temp_key.isValid() && temp_key.channel() instanceof SocketChannel
					&& !temp_key.attachment().equals(key.attachment())) {
				SocketChannel channel = (SocketChannel) temp_key.channel();
				channel.write(buf);
				buf.rewind();
			}
		}
	}

	@Override
	public void close() throws IOException {
		selector.close();
		serverSocket.close();
	}

	public static void main(String[] args) throws IOException, InterruptedException {
		try (ChatServerSelector server = new ChatServerSelector(Integer.parseInt(args[0]))) {
			server.run();
		}
	}
}