package il.co.ilrd.excptions;

import javax.imageio.IIOException;

public class MyException2 extends IIOException{

	public MyException2(String message) {
		super(message);
	}
}
