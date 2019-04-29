package il.co.ilrd.complex;
import static org.junit.Assert.*;

import org.junit.jupiter.api.Test;

class TestComplex {

	@Test
	void test() {
		//Test Basic Methods
		Complex complexNum = Complex.createFromReal(11.5);
		assertTrue("OK", complexNum.isReal());
		assertFalse("OK", complexNum.isImaginary());
		assertTrue("OK", complexNum.getReal() == 11.5);
		assertTrue("OK", complexNum.getImaginary() == 0);
		complexNum.setImaginary(11.2);
		
		//Test equals
		Complex complexNum2 = Complex.createFromImaginary(5.1);
		complexNum2.setReal(3.2);
		assertFalse("OK", complexNum.equals(complexNum2));
		complexNum2.setReal(11.5);
		complexNum2.setImaginary(11.2);
		assertTrue("OK", complexNum.equals(complexNum2));
		complexNum2.setReal(3.2);
		complexNum2.setImaginary(5.3);

		//Test add
		Complex result = Complex.createFromReal(14.7);
		result.setImaginary(16.5);
		assertTrue("OK", result.equals(complexNum.add(complexNum2)));
		System.out.println("add: " + complexNum + " + " +complexNum2+ " = " + result);
		
		//Test sub
		complexNum.setReal(13.0);
		complexNum.setImaginary(4.5);		
		complexNum2.setReal(3.0);
		complexNum2.setImaginary(2.5);
		result.setReal(10.0);
		result.setImaginary(2.0);
		assertTrue("OK", result.equals(complexNum.subtract(complexNum2)));
		System.out.println("sabtract: " + complexNum + " - " +complexNum2+ " = " + result);
		
		//Test multiply
		result.setImaginary(46.0);
		result.setReal(27.75);
		assertTrue("OK", result.equals(complexNum.multiply(complexNum2)));
		System.out.println("multiply: " +complexNum + " * " +complexNum2+ " = " + result);
		
		//Test divide
		complexNum.setReal(12.0);
		complexNum.setImaginary(4.0);
		complexNum2.setReal(2.0);
		complexNum2.setImaginary(6.0);		
		result.setReal(1.2);
		result.setImaginary(-1.6);
		assertTrue("OK", result.equals(complexNum.divide(complexNum2)));
		System.out.println("divide: " + complexNum + " / " +complexNum2+ " = " + result);
		
		//Test parse	
		String stringComplex1 = "11.2 + 2.2i";
		Complex complexNum3 = Complex.parse(stringComplex1);
		result.setReal(11.2);
		result.setImaginary(2.2);
		assertTrue("OK", complexNum3.equals(result));
		System.out.println("\nString: "+ stringComplex1 + "--> Parser: " + complexNum3);
		
		String stringComplex2 = "11.2";
		Complex complexNum4 = Complex.parse(stringComplex2);
		result.setReal(11.2);
		result.setImaginary(0.0);
		assertTrue("OK", complexNum4.equals(result));
		System.out.println("String: "+ stringComplex2 + "--> Parser: " + complexNum4);
		
		String stringComplex3 = "11.2i";
		Complex complexNum5 = Complex.parse(stringComplex3);
		result.setReal(0.0);
		result.setImaginary(11.2);
		assertTrue("OK", complexNum5.equals(result));
		System.out.println("String: "+ stringComplex3 + "--> Parser: " + complexNum5);
		
		//Test hashCode
		assertFalse("OK", complexNum5.hashCode() == complexNum4.hashCode());
		complexNum5.setReal(12.0);
		complexNum5.setImaginary(11.2);
		complexNum4.setReal(12.0);
		complexNum4.setImaginary(11.2);
		assertTrue("OK", complexNum5.hashCode() == complexNum4.hashCode());

	}
}