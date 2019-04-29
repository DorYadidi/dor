package il.co.ilrd.calculaor;

import java.util.HashMap;

public class Calculator {
	private HashMap<String, Operator> mapOperator = new HashMap<>();
	
	public Calculator() {
		
		Operator add = (int a, int b) -> {
			return a+b;
		};
		mapOperator.put("addition", add);
		
		Operator sub = new Operator() {
			
			@Override
			public int operate(int a, int b) {
				return a - b;
			}
		};
		mapOperator.put("subtraction", sub);
		
		mapOperator.put("multiplication", new InnerClassMultiply());
		
		class LocalClassDivision implements Operator{

			@Override
			public int operate(int a, int b) {
				return a / b;
			}
		}
		
		mapOperator.put("division", new LocalClassDivision());

		
	}
	
	private class InnerClassMultiply implements Operator{

		@Override
		public int operate(int a, int b) {
			return a * b;
		}
	}

	interface Operator {
		int operate(int a, int b);
	}
	
	public void addOperator(String key, Operator o) {
		mapOperator.put(key, o);
	}
	
	public int opearate(String key, int a, int b) {
		return mapOperator.get(key).operate(a, b);
	}
}
