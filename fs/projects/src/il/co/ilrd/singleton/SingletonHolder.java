package il.co.ilrd.singleton;

public class SingletonHolder {
	
	private SingletonHolder() {}
	  private static class InnerSingleton {
	       public static SingletonHolder singleton = new SingletonHolder();
	    }
	 
	    public static SingletonHolder getInstance() {
	        return InnerSingleton.singleton;
	    }
}
