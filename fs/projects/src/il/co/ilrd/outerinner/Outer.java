package il.co.ilrd.outerinner;


public class Outer {
	private int x = 5;
	private static int y = 3;
	
	class Inner {
		
		public void printX() {
			System.out.println("Print Outer Variable from Inner:" + x);
		}
	}
	
	static class InnerStatic {
		
		public static void printYStatic() {
			System.out.println("Print Outer Static Variable from InnerStatic in Static Method: " + y);
		}
		
		public void printY() {
			System.out.println("Print Outer Static Variable from InnerStatic in Non Static Method: " + y);
		}
	}

	public static void main(String[] args) {
		Outer.Inner inner = new Outer() .new Inner();
		inner.printX();
		
		Outer.InnerStatic.printYStatic();
		
		InnerStatic innerStatic = new InnerStatic();
		innerStatic.printY();
		}
}