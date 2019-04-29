package il.co.ilrd.gatewayserver;

import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.nio.ByteBuffer;
import java.util.function.Consumer;
import java.util.function.Function;

import il.co.ilrd.genericserver.GenericServer;
import il.co.ilrd.genericsfactory.Factory;
import il.co.ilrd.threadpool.ThreadPool;

public class GatewayServer<K, D> implements Runnable {
	private GenericServer server;
	private ThreadPool tp;
	private Factory<K, Runnable, D> factory;

	public GatewayServer(int port, String hostname, int num_threads) throws IOException {
		tp = new ThreadPool(num_threads);
		factory = new Factory<>();
		server = new GenericServer(port, hostname, new Callback());
		
	}

	@Override
	public void run() {
		tp.run();
		server.run();
	}

	public void stop() throws IOException {
		server.close();
		tp.shutDownNow();
	}

	public Function<D, Runnable> addCommand(K key, Function<D, Runnable> function) {
		return factory.add(key, function);
	}

	private class Callback implements Consumer<ByteBuffer> {
		@Override
		public void accept(ByteBuffer t) {
			Runnable task = new Runnable() {

				@Override
				public void run() {
					try {
						ByteArrayInputStream in = new ByteArrayInputStream(t.array());
						ObjectInputStream ois = new ObjectInputStream(in);
						@SuppressWarnings("unchecked")
						Packet<K, D> packet = (Packet<K, D>) ois.readObject();

						factory.create(packet.getKey(), packet.getData()).run();

					} catch (IOException | ClassNotFoundException e) {
						e.printStackTrace();
					} catch (ClassCastException e) {
						System.err.println("Class cast Exception");
						return;
					} catch (Exception e) {
						e.printStackTrace();
					}
				}
			};

			tp.execute(task);
		}
	}
	
	public static void main(String[] args) throws IOException {
		GatewayServer<Integer, String> server = new GatewayServer<Integer, String>(13000, "10.1.0.142", 3);
		server.addCommand(1, (data)-> {
			Runnable runnable = new Runnable() {
				
				@Override
				public void run() {
					System.out.println("RC: " + data);					
				}
			};
			return runnable;
		});
		
		server.addCommand(2, (data)-> {
		Runnable runnable = new Runnable() {
				
				@Override
				public void run() {
					System.out.println("RP: " + data);					
				}
			};
			return runnable;
		});
		
		server.addCommand(3, (data)-> {
		Runnable runnable = new Runnable() {
				
				@Override
				public void run() {
					System.out.println("RIOT: " + data);					
				}
			};
			return runnable;
		});
		
		server.addCommand(4, (data)-> {
		Runnable runnable = new Runnable() {
				
				@Override
				public void run() {
					System.out.println("UIOT: " + data);					
				}
			};
			return runnable;
		});
		
		server.addCommand(5, (data)-> {
		Runnable runnable = new Runnable() {
				
				@Override
				public void run() {
					try {
						server.stop();
					} catch (IOException e) {
						e.printStackTrace();
					}
					System.out.println("Logout");					
				}
			};
			return runnable;
		});
		
		server.run();
	}
}