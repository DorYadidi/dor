package il.co.ilrd.crud;

import java.io.File;
import java.io.IOException;
import java.nio.file.*;
import java.util.Objects;

import il.co.ilrd.observer.Callback;
import il.co.ilrd.observer.Dispatcher;

public class FileMonitor {
	private Dispatcher<String> dispatcher;
	private File monitorFile;
	private long timeStamp;
	private WatchService watchService;
	private volatile boolean run;

	public FileMonitor(File monitor) throws IOException {
		Objects.requireNonNull(monitor);
		if (monitor.isDirectory()) {
			throw new IllegalArgumentException();
		}
		this.monitorFile = monitor;
		this.run = true;
		this.timeStamp = monitor.lastModified();
		watchService = FileSystems.getDefault().newWatchService();
		dispatcher = new Dispatcher<String>();
	}

	public void register(Callback<String> callback) {
		dispatcher.register(callback);
	}

	public void startMonitor() {
		Thread watcher = new Thread(() -> {
			try {
				monitorFile.toPath().getParent().register(watchService, StandardWatchEventKinds.ENTRY_MODIFY);
				while (run) {
					WatchKey key = watchService.take();
					for (WatchEvent<?> event : key.pollEvents()) {
						if (event.kind() == StandardWatchEventKinds.ENTRY_MODIFY) {
							long timeStamp = this.monitorFile.lastModified();
							if (this.timeStamp != timeStamp) {
								this.timeStamp = timeStamp;
								dispatcher.notifyObservers(null);
							}
						}
					}
					if (!key.reset()) {
						break;
					}
				}
			} catch (ClosedWatchServiceException e) {
				return;
			} catch (InterruptedException | IOException ex) {
				ex.printStackTrace();
			}
		});

		watcher.start();
	}

	public void stopMonitor() throws IOException {
		run = false;
		watchService.close();
	}
}
