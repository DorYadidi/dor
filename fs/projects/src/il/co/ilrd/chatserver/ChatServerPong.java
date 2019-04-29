package il.co.ilrd.chatserver;

import java.io.*;
import java.net.*;

public class ChatServerPong implements Closeable {
	private BufferedReader input;
	private PrintWriter output;
	private ServerSocket serverSocket;
	private Socket clientSocket;
	private int port;

	public ChatServerPong(int port) throws IOException {
		this.port = port;
	}

	public void run() throws IOException {
		serverSocket = new ServerSocket(port);
		clientSocket = serverSocket.accept();
		output = new PrintWriter(clientSocket.getOutputStream(), true);
		input = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));

		while (!((input.readLine()).equals("close server"))) {
			output.println("pong");
		}
		output.println("ChatServer: GOODBYE!");
	}

	@Override
	public void close() throws IOException {
		input.close();
		output.close();
		serverSocket.close();
		clientSocket.close();
	}

	public static void main(String[] args) throws IOException, InterruptedException {
		try (ChatServerPong cc = new ChatServerPong(Integer.parseInt(args[0]))) {
			cc.run();
		}
	}
}