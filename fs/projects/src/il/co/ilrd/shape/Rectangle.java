package il.co.ilrd.shape;

public class Rectangle extends shape{
	
	protected double width;
	protected double lenght;
	
	public Rectangle() {
		super();
		width = 1.0;
		lenght = 1.0;
	}


	public Rectangle(double width, double lenght) {
		super();
		this.width = width;
		this.lenght = lenght;
	}
	
	public Rectangle(String colorUser, boolean filledUser, double width, double lenght) {
		super(colorUser, filledUser);
		this.width = width;
		this.lenght = lenght;
	}


	public double getWidth() {
		return width;
	}


	public void setWidth(double width) {
		this.width = width;
	}


	public double getLenght() {
		return lenght;
	}


	public void setLenght(double lenght) {
		this.lenght = lenght;
	}
	
	public double getArea() {

        return width * lenght;
	}
	
	public double getPerimeter() {
	
		return 2 * width + 2 * lenght;
	}
	
	
	@Override
	public String toString() {
		return ("A Rectangle with width=" + width + " ,lenght=" +lenght + " which is subclass of " + super.toString());
	}
	
	
}
