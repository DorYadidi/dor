package il.co.ilrd.collectionsframework;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Set;

public class Exercises {

	public static void Ex1() {
		int[] array = new int[] {10, 2, 11, 5, 6};
		System.out.println(Arrays.toString(array));
		List<Integer> list = new ArrayList<>();
	    for (int value : array) {
	        list.add(value);
	    }
	    
	    Collections.sort(list);
		System.out.println(list.toString());
	}
	
	public static void Ex2() {
		Map<String, Integer> weekday = new HashMap<String, Integer>();
		weekday.put("Sunday", 1);
		weekday.put("Monday", 2);
		weekday.put("Tuesday", 3);
		weekday.put("Wednesday", 4);
		weekday.put("Thursday", 5);
		weekday.put("Friday", 6);
		weekday.put("Saturday", 7);
		
        Set<Map.Entry<String, Integer>> set = weekday.entrySet();
        for (Map.Entry<String, Integer> runner : set) {
        	System.out.println(runner);
        }
        
        Collection<Integer> valus = weekday.values();
        for (Integer runner : valus) {
        	System.out.println(runner);
        }
	}
	
	private static class DateObject {
		private String code;
		private int value1;
		private int value2;
		
		public DateObject(String code, int value1, int value2) {
			this.code = code;
			this.value1 = value1;
			this.value2 = value2;
		}

		public String getCode() {
			return code;
		}

		public int getValue1() {
			return value1;
		}

		public int getValue2() {
			return value2;
		}
	}
	
	public static void Ex3() {
		DateObject[] array = new DateObject[4];
		array[0] = new DateObject("a", 1, 2);
		array[1] = new DateObject("b", 3, 1);
		array[2] = new DateObject("a", 9, 12);
		array[3] = new DateObject("b", 10, 47);
		
		Map<String, Integer> map = new HashMap<String, Integer>();
		for (DateObject data : array) {
			Integer sum = map.put(data.getCode(), data.getValue1() + data.getValue2());
			if (sum != null) {
				map.replace(data.getCode(), map.get(data.getCode()) + sum);
			}
		}
		
		System.out.println(map.toString());
	}

	public static void main(String[] args) {
		Ex1();
		Ex2();
		Ex3();
	}
}
