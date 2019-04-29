package il.co.ilrd.observer;

import java.util.function.Consumer;

public class Subject {
	private Dispatcher<String> dispatcher;
	private String name;

	public Subject() {
		name = "Mariv";
		this.dispatcher = new Dispatcher<>();
	}

	public void register(Callback<String> observer) {
		dispatcher.register(observer);
	}

	public void run() {
		dispatcher.notifyObservers(name);
	}

	public void terminate() {
		dispatcher.terminate();
	}
}

class ObserverDor {
	private Callback<String> callBack;
	private String name;

	public ObserverDor() {
		this.name = "Dor";
		Consumer<String> update = (String nameSub) -> {
			System.out.println("Dor Read " + nameSub);
		};

		Runnable terminate = () -> {
			System.out.println("Dor Stop Read ");
		};

		callBack = new Callback<String>(update, terminate);
	}

	public Callback<String> getCallBack() {
		return callBack;
	}

	public String getName() {
		return name;
	}
}

class ObserverTomer {
	private Callback<String> callBack;
	private String name;

	public ObserverTomer() {
		this.name = "Tomer";
		Consumer<String> update = (String nameSub) -> {
			System.out.println("Tomer Read " + nameSub);
		};

		Runnable terminate = () -> {
			System.out.println("Tomer Stop Read ");
		};

		callBack = new Callback<String>(update, terminate);
	}

	public Callback<String> getCallBack() {
		return callBack;
	}

	public String getName() {
		return name;
	}
}

class ObserverChen {
	private Callback<String> callBack;
	private String name;

	public ObserverChen() {
		this.name = "Chen";
		Consumer<String> update = (String nameSub) -> {
			System.out.println("Chen Read " + nameSub);
		};

		Runnable terminate = () -> {
			System.out.println("Chen Stop Read ");
		};

		callBack = new Callback<String>(update, terminate);
	}

	public Callback<String> getCallBack() {
		return callBack;
	}

	public String getName() {
		return name;
	}
}