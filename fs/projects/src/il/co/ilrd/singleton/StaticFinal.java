package il.co.ilrd.singleton;

public class StaticFinal {
	private static final StaticFinal singleton = new StaticFinal();
    private StaticFinal() {}

	public static StaticFinal getObject() {
		return singleton;
	}
}