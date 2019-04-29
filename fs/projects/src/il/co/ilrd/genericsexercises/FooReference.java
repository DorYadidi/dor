package il.co.ilrd.genericsexercises;


public class FooReference<T> {
	   private T dataType;

	public T getDataType() {
		return dataType;
	}

	public void setDataType(T dataType) {
		this.dataType = dataType;
	}
	
	public static void main(String[] args) {

		FooReference<Integer> intFoo = new FooReference<Integer>();
		FooReference<String> stingFoo = new FooReference<String>();
		FooReference<Double> doubleFoo = new FooReference<Double>();
		
		intFoo.setDataType(3);
		System.out.println("FooReference<Integer> ==>: " + intFoo.getClass());
		
		stingFoo.setDataType("Dor");
		System.out.println("FooReference<String> ==>: " + stingFoo.getClass());
		
		doubleFoo.setDataType(3.5);
		System.out.println("FooReference<Double> ==>: " + doubleFoo.getClass());
	}
}
