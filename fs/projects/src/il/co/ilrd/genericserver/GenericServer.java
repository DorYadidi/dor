package il.co.ilrd.genericserver;

import java.io.Closeable;
import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.DatagramChannel;
import java.nio.channels.SelectableChannel;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.ServerSocketChannel;
import java.nio.channels.SocketChannel;
import java.util.Iterator;
import java.util.function.Consumer;

public class GenericServer implements Runnable, Closeable {
	private static final int BUFFER_SIZE = 8192;
	private int UDPport;
	private int TCPport;
	private Consumer<ByteBuffer> cosumer;
	private String hostname;
	private Selector selector;
	private ServerSocketChannel tcpChannel;
	private DatagramChannel udpChannel;

	public GenericServer(int port, String hostname, Consumer<ByteBuffer> cosumer) throws IOException {
		this.UDPport = port;
		this.TCPport = port;
		this.hostname = hostname;
		this.cosumer = cosumer;

		selector = Selector.open();
		tcpChannel = ServerSocketChannel.open();
		udpChannel = DatagramChannel.open();
	}

	@Override
	public void run() {
		try {
			tcpChannel.bind(new InetSocketAddress(hostname, TCPport));
			tcpChannel.configureBlocking(false);
			tcpChannel.register(selector, SelectionKey.OP_ACCEPT);

			udpChannel.socket().bind(new InetSocketAddress(hostname, UDPport));
			udpChannel.configureBlocking(false);
			udpChannel.register(selector, SelectionKey.OP_READ);

			Iterator<SelectionKey> keyRunner;
			SelectionKey key;

			while (selector.isOpen()) {
				if (selector.select(5000) == 0) {
					System.out.println("Server working!");
				}

				keyRunner = selector.selectedKeys().iterator();

				while (keyRunner.hasNext()) {
					key = keyRunner.next();
					keyRunner.remove();
					if (key.isAcceptable()) {
						register(key);
					} else if (key.isReadable()) {
						handleData(key);
					}
				}
			}
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	private void register(SelectionKey key) throws IOException {
		SocketChannel newClient = tcpChannel.accept();
		newClient.configureBlocking(false);
		newClient.register(selector, SelectionKey.OP_READ);
	}

	private void handleData(SelectionKey key) throws IOException {
		SelectableChannel client = key.channel();
		ByteBuffer buffer = ByteBuffer.allocate(BUFFER_SIZE);

		int numOfByte = 0;

		if (client instanceof SocketChannel) {
			while ((numOfByte = ((SocketChannel) client).read(buffer)) > 0) {
			}
			
			if (numOfByte == -1) {
				key.cancel();
				return;
			}
		} else if (client instanceof DatagramChannel) {
			((DatagramChannel) client).receive(buffer);
		}

		cosumer.accept(buffer);
	}

	@Override
	public void close() throws IOException {
		try {
			selector.close();
			tcpChannel.close();
			udpChannel.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	public int getUDPport() {
		return UDPport;
	}

	public void setUDPport(int uDPport) {
		UDPport = uDPport;
	}

	public int getTCPport() {
		return TCPport;
	}

	public void setTCPport(int tCPport) {
		TCPport = tCPport;
	}
}