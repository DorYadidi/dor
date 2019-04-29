package il.co.ilrd.compositetree;

import java.io.File;
import java.nio.file.NoSuchFileException;
import java.nio.file.NotDirectoryException;
import java.util.*;

public class Tree {

	private CompositeFolder root;

	public Tree(String path) throws NotDirectoryException, NoSuchFileException {
		if (new File(path).exists() == false) {
			throw new NoSuchFileException("File Not Exists");
		}
		if (new File(path).isDirectory() == false) {
			throw new NotDirectoryException("File Not Directory");
		}

		root = new CompositeFolder(path);
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

			for (File f1 : folder.listFiles()) {
				if (f1.isFile()) {
					list.add(new CompositeFile(f1.getAbsolutePath()));
				} else {
					list.add(new CompositeFolder(f1.getAbsolutePath()));
				}
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
		Tree tree = new Tree("/home/student/git/ds");
		tree.printTree();
	}
}
