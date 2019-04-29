package il.co.ilrd.shape;

public abstract class shape {

	protected String color;
	protected boolean filled;

	public shape() {
		color = "green";
		filled = true;
	}

	public shape(String colorUser, boolean filledUser) {
		color = colorUser;
		filled = filledUser;
	}

	public String getColor() {
		return color;
	}

	public void setColor(String color) {
		this.color = color;
	}

	public boolean isFilled() {
		return filled;
	}

	public void setFilled(boolean filled) {
		this.filled = filled;
	}

	@Override
	public String toString() {
		return "A Shape with color " + color + " and " + filled + " filled";
	}
}
