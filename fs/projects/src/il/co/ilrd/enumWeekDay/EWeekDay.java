package il.co.ilrd.enumWeekDay;

public enum EWeekDay {
	SUNDAY(7), MONDAY(1), TUESDAY(2), WEDNESDAY(3), THURSDAY(4), FRIDAY(5), SATURDAY(6);

	int value;

	EWeekDay(int value) {
		this.value = value;
	}

	int getValue() {
		return value;
	}

	public static EWeekDay fromValue(int value) {
		EWeekDay[] arr = EWeekDay.values();
		for (EWeekDay printer : arr) {
			if (printer.getValue() == value) {
				return printer;
			}
		}

		return null;
	}

	public static void printAll() {
		EWeekDay[] arr = EWeekDay.values();

		for (EWeekDay printer : arr) {
			System.out.println("Day :" + printer.name());
		}
	}
}
