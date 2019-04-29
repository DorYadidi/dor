package il.co.ilrd.java2c;

class Cat extends Animal{
	public Cat(){
		this("black");
		System.out.println("Cat Ctor");
		this.num_masters = 2;
	}
	
	static {
		System.out.println("Static block Cat");
	}
	
	public Cat(String colors){
		this.colors = colors;
		System.out.println("Cat Ctor with color: " + this.colors);
	}
	
	@Override
		protected void finalize() throws Throwable{
		System.out.println("finalize Cat with ID:" + this.ID);
		super.finalize();
	}
	
	@Override
	public String toString(){
		return "Cat with ID: " + ID; 
	}
	
	private String colors;
	private int num_masters = 5;
}
