package il.co.ilrd.singleton;

public class Volotile {
    private volatile static Volotile singleton;
    private Volotile() {}
	public static Volotile getObject() {
		if (singleton == null)
		{
			synchronized (Volotile.class) {
				if (singleton == null) {
					singleton = new Volotile();					
				}
			}
		}
		
		return singleton;
	}
}
	
