package il.co.ilrd.crud;

import java.io.File;
import java.io.IOException;
import java.nio.file.Paths;

public class TestCRUD {
	
	public static void main(String[] args) throws IOException, InterruptedException {
		String directory = Paths.get("").toAbsolutePath().toString() + "/src/il/co/ilrd/crud/";
		File observedFile = new File(directory + "observed");
		File backupFile = new File(directory + "backup");
		observedFile.createNewFile();
		backupFile.createNewFile();

		FileMonitor monitor = new FileMonitor(observedFile);
		FileObserver observer = new FileObserver(observedFile, backupFile);
		observer.regMonitor(monitor);
		monitor.startMonitor();
		Thread.sleep(300000);
		monitor.stopMonitor();
	}
}
