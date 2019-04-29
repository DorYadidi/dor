package il.co.ilrd.genericslinkedlist;

import static org.junit.jupiter.api.Assertions.*;

import java.util.ConcurrentModificationException;
import java.util.Iterator;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

class GenericLinkedListTest {

	GenericLinkedList<Double> sllDouble;
	GenericLinkedList<Integer> sllInteger1;
	GenericLinkedList<Integer> sllInteger2;

	@BeforeEach
	private void setUp() {
		sllDouble = new GenericLinkedList<Double>();
		sllInteger1 = new GenericLinkedList<Integer>();
		sllInteger2 = new GenericLinkedList<Integer>();
	}

	@Test
	void testBasic() {
		Double data1 = 1.1;
		Double data2 = 2.2;
		Double data3 = 3.3;
		Double data4 = 4.4;

		assertTrue(sllDouble.isEmpty());
		assertTrue(sllDouble.getSize() == 0);
		sllDouble.pushFront(data1);

		assertTrue(!sllDouble.isEmpty());
		assertEquals(1, sllDouble.getSize());

		sllDouble.pushFront(data2);
		sllDouble.pushFront(data3);
		sllDouble.pushFront(data4);

		assertTrue(sllDouble.getSize() == 4);
		assertTrue(sllDouble.popFront().equals(data4));
		assertEquals(3, sllDouble.getSize());

		sllDouble.popFront();
		sllDouble.popFront();
		sllDouble.popFront();

		assertTrue(sllDouble.isEmpty());

		sllDouble.pushFront(data1);
		sllDouble.pushFront(data2);
		sllDouble.pushFront(data3);
		sllDouble.pushFront(data4);

		assertEquals(4, sllDouble.getSize());
		Iterator<Double> iter = sllDouble.getBegin();
		assertTrue(data4.equals(iter.next()));

		iter = sllDouble.find(data2);
		assertTrue(data2.equals(iter.next()));

		iter = sllDouble.find(data1);
		assertTrue(data1.equals(iter.next()));

		try {
			sllDouble.pushFront(data1);
			iter.next();
		} catch (ConcurrentModificationException e) {
			assertTrue(true);
		}
	}

	@Test
	void testReverse() {
		Double data1 = 1.1;
		Double data2 = 2.2;
		Double data3 = 3.3;
		Double data4 = 4.4;
		sllDouble.pushFront(data1);
		sllDouble.pushFront(data2);
		sllDouble.pushFront(data3);
		sllDouble.pushFront(data4);

		GenericLinkedList<Double> sllDoubleReverse = GenericLinkedList.newReverse(sllDouble);
		Iterator<Double> iter = sllDoubleReverse.getBegin();
		assertTrue(data1.equals(iter.next()));
		assertTrue(data2.equals(iter.next()));
		assertTrue(data3.equals(iter.next()));
		assertTrue(data4.equals(iter.next()));
	}

	@Test
	void testMerge() {
		Integer data1 = 1;
		Integer data2 = 2;
		Integer data3 = 3;
		Integer data4 = 4;
		Integer data5 = 5;
		Integer data6 = 6;

		sllInteger1.pushFront(data1);
		sllInteger1.pushFront(data2);
		sllInteger1.pushFront(data3);
		sllInteger1.pushFront(data4);

		sllInteger2.pushFront(data5);
		sllInteger2.pushFront(data6);

		GenericLinkedList<Integer> sllIntegerMerge = GenericLinkedList.merge(sllInteger1, sllInteger2);
		Iterator<Integer> iter = sllIntegerMerge.getBegin();

		assertTrue(data4.equals(iter.next()));
		assertTrue(data3.equals(iter.next()));
		assertTrue(data2.equals(iter.next()));
		assertTrue(data1.equals(iter.next()));
		assertTrue(data6.equals(iter.next()));
		assertTrue(data5.equals(iter.next()));
	}

	@Test
	void testForEach() {
		Double data1 = 1.1;
		Double data2 = 2.2;
		Double data3 = 3.3;
		Double data4 = 4.4;

		sllDouble.pushFront(data1);
		sllDouble.pushFront(data2);
		sllDouble.pushFront(data3);
		sllDouble.pushFront(data4);

		Double[] array = new Double[] { data4, data3, data2, data1 };
		int i = 0;
		for (Double data : sllDouble) {
			array[i].equals(data);
			++i;
		}
	}
}
