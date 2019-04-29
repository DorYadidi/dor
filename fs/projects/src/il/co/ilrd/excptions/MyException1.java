package il.co.ilrd.excptions;

public class MyException1 extends RuntimeException{
	public MyException1() {
        super();
    }
	
    public MyException1(String msg) {
        super(msg);
    }
}
