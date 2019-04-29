package il.co.ilrd.singleton;

public class SyncroMethod {
    private static SyncroMethod singleton;
    private SyncroMethod() {}
	public synchronized static SyncroMethod getObject() {
		if (singleton == null)
		{
			singleton = new SyncroMethod();
		}
		
		return singleton;
	}
}
