package il.co.ilrd.observer;

import java.io.File;
import java.nio.file.NoSuchFileException;
import java.nio.file.NotDirectoryException;
import java.util.*;
import java.util.function.Consumer;

import il.co.ilrd.genericsfactory.Factory;

public class TreeTest {
	private CompositeFolder root;
	private Dispatcher<Integer> dispatcher = new Dispatcher<>();
	private Factory<Boolean, Component, File> factory = new Factory<Boolean, Component, File>();
	
	{
		factory.add(true, (File f) -> {return new CompositeFolder(f.getAbsolutePath());});
		factory.add(false, (File f) -> {return new CompositeFile(f.getAbsolutePath());});
	}
	
	public void CreateTree(String path) throws NotDirectoryException, NoSuchFileException {
		if (new File(path).exists() == false) {
			throw new NoSuchFileException("File Not Exists");
		}
		if (new File(path).isDirectory() == false) {
			throw new NotDirectoryException("File Not Directory");
		}
		
		root = new CompositeFolder(path);
	}
	
	public void register(Callback<Integer> observer) {
		dispatcher.register(observer);
	}

	public void updateAll() {
		dispatcher.notifyObservers(1);
	}

	public void terminate() {
		dispatcher.terminate();
	}

	public void printTree() {
		root.print(0);
	}

	private abstract class Component {
		private String name;

		public String getName() {
			return name;
		}

		public void setName(String name) {
			this.name = name;
		}

		abstract void print(int depth);
	}

	private class CompositeFile extends Component {

		public CompositeFile(String path) {
			setName(new File(path).getName());
		}

		@Override
		void print(int depth) {
			for (int i = 0; i <= depth; ++i) {
				System.out.print("  ");
			}

			System.out.print("╠" + getName() + "\n");
		}
	}

	private class CompositeFolder extends Component {

		private List<Component> list = new ArrayList<Component>();

		public CompositeFolder(String path) {
			File folder = new File(path);
			setName(folder.getName());
			updateAll();

			for (File f1 : folder.listFiles()) {
				list.add(factory.create(f1.isDirectory(), f1));
			}
		}

		@Override
		void print(int depth) {
			for (int i = 0; i < depth; ++i) {
				System.out.print(" ");
			}

			if (depth >= 1) {
				System.out.print("  ");
			}

			System.out.println("\u001B[36m" + getName() + "\u001b[0m");

			for (Component runer : list) {
				runer.print(depth + 1);
			}
		}
	}

	public static void main(String[] args) throws NotDirectoryException, NoSuchFileException {
		TreeTest tree = new TreeTest();
		tree.register(new Count().getCallback());
		tree.register(new Observer2().getCallback());
		tree.CreateTree("/home/student/git/ds");
		tree.printTree();
		System.out.println();
		tree.terminate();
	}
}

class Count {
	private Callback<Integer> callback;
	private int counterDirec;
	
	public Count() {
		Consumer<Integer> update = (Integer num) -> {
			++counterDirec;
		};

		Runnable terminate = () -> {
			System.out.println("Count: " + counterDirec);
		};

		callback = new Callback<Integer>(update, terminate);
	}

	public Callback<Integer> getCallback() {
		return callback;
	}
}

class Observer2 {
	private Callback<Integer> callback;
	
	public Observer2() {
		Consumer<Integer> update = (Integer num) -> {
		};

		Runnable terminate = () -> {
			System.out.println("Kill Observer2");
		};

		callback = new Callback<Integer>(update, terminate);
	}

	public Callback<Integer> getCallback() {
		return callback;
	}
}
