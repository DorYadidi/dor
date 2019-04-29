package il.co.ilrd.crud;

import java.io.*;
import java.nio.file.Files;
import java.util.Objects;
import java.util.function.Consumer;
import il.co.ilrd.observer.Callback;

public class FileObserver {
	private File backup;
	private File monitorFile;
	private Callback<String> callback;
	private int numOfLines;

	public FileObserver(File monitor, File backup) throws IOException {
		Objects.requireNonNull(monitor);
		Objects.requireNonNull(backup);
		if (monitor.isDirectory() || backup.isDirectory()) {
			throw new IllegalArgumentException();
		}
		this.monitorFile = monitor;
		this.backup = backup;
		this.numOfLines = getNumOfLine(monitorFile);

		Consumer<String> update = new Consumer<String>() {
			@Override
			public void accept(String t) {
				int linesInFile = 0;
				try {
					linesInFile = getNumOfLine(monitorFile);
				} catch (IOException e1) {
					e1.printStackTrace();
				}

				while (numOfLines != linesInFile) {
					try (StringCrud crud = new StringCrud()) {
						crud.create(crud.read(numOfLines));
					} catch (Exception e) {
						e.printStackTrace();
					}
					++numOfLines;
				}
				return;
			}
		};

		Runnable terminate = new Runnable() {
			@Override
			public void run() {

			}
		};

		callback = new Callback<String>(update, terminate);
	}

	public void regMonitor(FileMonitor monitor) {
		Objects.requireNonNull(monitor);
		monitor.register(this.callback);
	}

	private int getNumOfLine(File file) throws IOException {
		return (int) Files.lines(file.toPath()).count();
	}

	private class StringCrud implements Crudable<Integer, String> {

		private BufferedReader monitorStream;
		private BufferedWriter backupStream;

		public StringCrud() throws IOException {
			monitorStream = new BufferedReader(new FileReader(monitorFile));
			backupStream = new BufferedWriter(new FileWriter(backup, true));
		}

		@Override
		public void close() throws Exception {
			monitorStream.close();
			backupStream.close();
		}

		@Override
		public Integer create(String data) {
			try {
				backupStream.write(data);
				backupStream.newLine();
				backupStream.flush();
			} catch (IOException e) {
				e.printStackTrace();
			}
			return null;
		}

		@Deprecated
		public void update(Integer id, String data) {
		}

		@Override
		public String read(Integer key) {
			try {
				for (int i = 0; i < key; ++i) {
					monitorStream.readLine();
				}
				return monitorStream.readLine();
			} catch (IOException e) {
				e.printStackTrace();
			}
			return null;
		}

		@Deprecated
		public void delete(Integer key) {
		}
	}
}
