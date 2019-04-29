package il.co.ilrd.excptions;

import javax.imageio.IIOException;

public class Main {

	static void func3() {
		throw new MyException1("Exception1");
	}
	
	static void func4() throws MyException2 {
		throw new MyException2("Exception2");
	}
	
	public static void main(String[] args) {
		/*try {
			Foo.func1();
		} catch (IIOException e) {
			e.printStackTrace();
		}
		Foo.func2();*/
		
		try {
			func3();			
		} catch (MyException1 e) {
			System.out.println("MyException1: " + e.getMessage());
		}
		
		try {
			func4();			
		} catch (MyException2 e1) {
			System.out.println("MyException2: " + e1.getMessage());
		}	
	
		byte[] a = new byte[100];
		a[101] = 2;
	}
}
