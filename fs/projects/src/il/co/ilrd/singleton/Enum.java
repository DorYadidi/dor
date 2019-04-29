package il.co.ilrd.singleton;

public enum Enum {
	 RED(1), GREEN(2), YELLOW(3);
	 
    private int nCode ;
 
    private Enum(int userVal) {
 
        nCode = userVal;
    }

	public int getnCode() {
		return nCode;
	}
}
