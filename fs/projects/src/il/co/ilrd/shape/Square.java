package il.co.ilrd.shape;


public class Square extends Rectangle
{
	public static boolean fun(Object obj, String c) 
	        throws ClassNotFoundException 
	{ 
	return Class.forName(c).isInstance(obj); 
	} 
	protected double side;

	public Square() {
		super();
		side = 1.0;	
	}

	public Square(double side) {
		super(side, side);
		this.side = side;
	}

	public Square(String colorUser, boolean filledUser, double side) {
		super(colorUser, filledUser, side, side);
		this.side = side;
	}

	public double getSide() {
		return side;
	}

	public void setSide(double side) {
		this.side = side;
	}
	
	@Override
	public String toString() {
		return ("A Sqare with side=" + side + " which is subclass of " + super.toString());
	}
}
