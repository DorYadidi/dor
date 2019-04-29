package il.co.ilrd.excptions;

import javax.imageio.IIOException;

public class Foo {

	public static void func1() throws IIOException{
		
	}
	
	public static void func2(){
		String ab = null;
		ab.charAt(0);
	}
}
