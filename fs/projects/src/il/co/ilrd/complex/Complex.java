package il.co.ilrd.complex;

import java.util.regex.*;
import java.util.regex.Matcher;

public class Complex implements Comparable<Complex> {
	private double real;
	private double imaginary;

	private Complex(double real, double imaginary) {
		this.real = real;
		this.imaginary = imaginary;
	}

	public static Complex createFromReal(double realUser) {
		return new Complex(realUser, 0);
	}

	public static Complex createFromImaginary(double imaginaryUser) {
		return new Complex(0, imaginaryUser);
	}

	public double getReal() {
		return real;
	}

	public void setReal(double real) {
		this.real = real;
	}

	public double getImaginary() {
		return imaginary;
	}

	public void setImaginary(double imaginary) {
		this.imaginary = imaginary;
	}

	public boolean isReal() {
		return imaginary == 0;
	}

	public boolean isImaginary() {
		return imaginary != 0;
	}

	public Complex add(Complex num1) {
		double newReal = real + num1.real;
		double newImaginary = imaginary + num1.imaginary;

		return new Complex(newReal, newImaginary);
	}

	public Complex subtract(Complex num1) {
		double newReal = real - num1.real;
		double newImaginary = imaginary - num1.imaginary;

		return new Complex(newReal, newImaginary);
	}

	public Complex multiply(Complex num1) {
		double newReal = real * num1.real - imaginary * num1.imaginary;
		double newImaginary = imaginary * num1.real + real * num1.imaginary;

		return new Complex(newReal, newImaginary);
	}

	public Complex divide(Complex num1) {
		double newRealUp = real * num1.real + imaginary * num1.imaginary;
		double newImaginaryUp = imaginary * num1.real - real * num1.imaginary;
		double newRealDown = num1.real * num1.real + num1.imaginary * num1.imaginary;

		return new Complex(newRealUp / newRealDown, newImaginaryUp / newRealDown);
	}

	@Override
	public int compareTo(Complex comp) {
		return (int) (real - comp.real);
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		long temp;
		temp = Double.doubleToLongBits(imaginary);
		result = prime * result + (int) (temp ^ (temp >>> 32));
		temp = Double.doubleToLongBits(real);
		result = prime * result + (int) (temp ^ (temp >>> 32));
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		Complex other = (Complex) obj;
		if (imaginary != other.imaginary)
			return false;
		if (real != other.real)
			return false;
		return true;
	}

	@Override
	public String toString() {
		if (imaginary > 0)
		{
			return "[" + real + " + " + imaginary + "i]";			
		}
		
		return "[" + real + " - " + (imaginary * -1) + "i]";
	}

	public static Complex parse(String str) {
		double parseImaginary = 0;
		double parseReal = 0;
		// remove Spaces
		String numberNoWhiteSpace = str.replaceAll("\\s", "");

		// Matches complex number with BOTH real AND imaginary parts.
		Pattern patternA = Pattern.compile("([-]?[0-9]+\\.?[0-9]?)" 
		                    + "([-|+]+[0-9]+\\.?[0-9]?)[i$]+");

		// Matches ONLY real number.
		Pattern patternB = Pattern.compile("([-]?[0-9]+\\.?[0-9]?)$");

		// Matches ONLY imaginary number.
		Pattern patternC = Pattern.compile("([-]?[0-9]+\\.?[0-9]?)[i$]");

		Matcher matcherA = patternA.matcher(numberNoWhiteSpace);
		Matcher matcherB = patternB.matcher(numberNoWhiteSpace);
		Matcher matcherC = patternC.matcher(numberNoWhiteSpace);

		if (matcherA.find()) {
			parseReal = Double.parseDouble(matcherA.group(1));
			parseImaginary = Double.parseDouble(matcherA.group(2));
		} else if (matcherB.find()) {
			parseReal = Double.parseDouble(matcherB.group(1));
			parseImaginary = 0;
		} else if (matcherC.find()) {
			parseReal = 0;
			parseImaginary = Double.parseDouble(matcherC.group(1));
		}

		return new Complex(parseReal, parseImaginary);
	}
}