package il.co.ilrd.shape;

public class Circle extends shape{

	protected double radius;

	
	public Circle() {
		super();
		radius = 1.0;
	}

	public Circle(double radius) {
		super();
		this.radius = radius;
	}

	public Circle(String colorUser, boolean filledUser, double radius) {
		super(colorUser, filledUser);
		this.radius = radius;
	}

	public double getRadius() {
		return radius;
	}

	public void setRadius(double radius) {
		this.radius = radius;
	}

	public double getArea() {

        return radius * radius * Math.PI;
	}
	
	public double getPerimeter() {
	
		return 2 * radius * Math.PI;
	}
	
	@Override
	public String toString() {
		return ("A Circle with radius=" + radius + " which is subclass of " + super.toString());
	}
}
