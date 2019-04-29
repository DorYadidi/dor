package il.co.ilrd.calculaor;

import org.junit.jupiter.api.Test;

class CalculatorTest {

	@Test
	void test() {
		Calculator calculator = new Calculator();
		System.out.println(calculator.opearate("addition", 2, 3));
		System.out.println(calculator.opearate("subtraction", 2, 3));
		System.out.println(calculator.opearate("multiplication", 2, 3));
		System.out.println(calculator.opearate("division", 10, 5));
	}
}
