package il.co.ilrd.hashmap;

import static org.junit.jupiter.api.Assertions.*;

import java.util.Comparator;
import org.junit.jupiter.api.Test;

class PairTest {
	@Test
	void testBasic() {
		Pair<Integer, Double> pair = Pair.of(new Integer(3), new Double(3.5));
		assertTrue(pair.getKey() == 3);
		assertTrue(pair.getValue() == 3.5);
		pair.setKey(new Integer(2));
		assertTrue(pair.getKey() == 2);
		
		Pair<Integer, Double> pair2 = Pair.of(new Integer(2), new Double(3.5));
		assertTrue(pair.hashCode() == pair.hashCode());
		assertTrue(pair.equals(pair2));
		pair.setKey(new Integer(1));
		assertTrue(!pair.equals(pair2));
		
		Pair<Double, Integer> swapPair = Pair.swap(pair2);
		assertTrue(swapPair.getKey() == pair2.getValue());
		assertTrue(swapPair.getValue() == pair2.getKey());
	}

	@Test
	void testMinMax() {
		Integer[] array = new Integer[5];
		array[0] = new Integer(2);
		array[1] = new Integer(22);
		array[2] = new Integer(12);
		array[3] = new Integer(-5);
		array[4] = new Integer(15);
		Pair<Integer, Integer> minMax = Pair.minMax(array);
		assertTrue(minMax.getKey() == -5);
		assertTrue(minMax.getValue() == 22);
		
		Comparator<Integer> comp = new Comparator<Integer>() {
			@Override
			public int compare(Integer o1, Integer o2) {
				if (o1 > o2) {
					return 1;
				} else if (o1 < o2) {
					return -1;
				}
				return 0;
			}
		};
		
		Pair<Integer, Integer> minMax2 = Pair.minMax(array, comp);
		assertTrue(minMax2.getKey() == -5);
		assertTrue(minMax2.getValue() == 22);
		
		Integer[] array2 = new Integer[1];
		array2[0] = new Integer(2);
		Pair<Integer, Integer> minMax3 = Pair.minMax(array2);
		assertTrue(minMax3.getKey() == 2);
		assertTrue(minMax3.getValue() == 2);
		
		Integer[] array3 = new Integer[4];
		array3[0] = new Integer(2);
		array3[1] = new Integer(22);
		array3[2] = null;
		array3[3] = new Integer(-5);
		try
		{
			@SuppressWarnings("unused")
			Pair<Integer, Integer> minMax4 = Pair.minMax(array3);
		}
		catch (IllegalStateException e) {
			assertTrue(true);
		}
		
		
	}
}
