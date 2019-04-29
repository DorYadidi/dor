package il.co.ilrd.chatserver;

import java.io.*;
import java.net.*;

public class ChatClientPing implements Closeable {

	private BufferedReader inputUser;
	private BufferedReader consoleReader;
	private PrintWriter output;
	private Socket chatSocket;
	private InetAddress IP;
	private int port;
	private String clientID;
	private boolean waitOnMessage = true;

	public ChatClientPing(InetAddress IP, int port, String clientID) {
		inputUser = new BufferedReader(new InputStreamReader(System.in));
		this.IP = IP;
		this.port = port;
		this.clientID = clientID;
	}

	public void run() throws IOException {
		chatSocket = new Socket(IP, port);
		output = new PrintWriter(chatSocket.getOutputStream(), true);
		consoleReader = new BufferedReader(new InputStreamReader(chatSocket.getInputStream()));

		String line;
		try {
			while (!((line = inputUser.readLine()).equals("logout"))) {
				output.println("> " + line);
				System.out.println(consoleReader.readLine());
			}
		} catch (IOException e) {
			e.printStackTrace();
		}

		waitOnMessage = false;
		System.out.println("ChatClient: GOODBYE!");
	}
	
	@Override
	public void close() throws IOException {
		inputUser.close();
		consoleReader.close();
		output.close();
		chatSocket.close();
	}

	public static void main(String[] args) throws IOException, InterruptedException {
		try (ChatClientPing cc = new ChatClientPing(InetAddress.getLocalHost(), Integer.parseInt(args[0]), args[1])) {
			cc.run();
		}
	}
}