package il.co.ilrd.enumWeekDay;

public class TestMain {

	public static void main(String[] args) {
		System.out.println("From Value 1 : " + EWeekDay.fromValue(1));
		System.out.println("From Value 2 : " + EWeekDay.fromValue(2));
		System.out.println("From Value 3 : " + EWeekDay.fromValue(3));
		System.out.println("From Value 4 : " + EWeekDay.fromValue(4));
		System.out.println("From Value 5 : " + EWeekDay.fromValue(5));
		System.out.println("From Value 6 : " + EWeekDay.fromValue(6));
		System.out.println("From Value 7 : " + EWeekDay.fromValue(7));
		System.out.println();
		EWeekDay.printAll();
	}
}
