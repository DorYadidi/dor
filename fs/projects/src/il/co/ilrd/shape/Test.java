package il.co.ilrd.shape;

public class Test {
	
	public static void main(String[] args) throws ClassNotFoundException {
		
		Integer i = new Integer(5); 
		boolean b = Square.fun(i, "java.lang.Integer"); 
		System.out.println(b);
		shape s1 = new Circle("RED",false, 5.5);
		System.out.println("--------------------");
		System.out.println(s1);
		System.out.println("color:" + s1.getColor());
		System.out.println("filled:" + s1.isFilled());
		System.out.println("--------------------");
			
		Circle c1 = (Circle)s1;
		System.out.println("perimiter:" + c1.getPerimeter());
		System.out.println("area:" + c1.getArea());
		System.out.println("radius:" + c1.getRadius());
		System.out.println("--------------------");
			
	/*	shape s2 = new shape();
		System.out.println("color:" + s2.getColor());
		System.out.println("--------------------");*/
			
		shape s3 = new Rectangle("RED",false,1.0,2.0);
		Rectangle r1 =(Rectangle)s3;
		System.out.println(r1);
		System.out.println("area:" + r1.getArea());
		System.out.println("color:" + r1.getColor());
		System.out.println("length:" + r1.getLenght());
		System.out.println("--------------------");
			
		Rectangle r2 = (Rectangle)new Square(6.6);
		System.out.println(r2);
		System.out.println("area:" + r2.getArea());
		System.out.println("color:" + r2.getColor());
		System.out.println("length:" + r2.getLenght());
		System.out.println("--------------------");
			
		Square sq1 = (Square)r2;
		System.out.println(sq1);
		System.out.println("area:" + sq1.getArea());
		System.out.println("color:" + sq1.getColor());
		System.out.println("side:" + sq1.getSide());
		System.out.println("length:" + sq1.getLenght());
	}
}
