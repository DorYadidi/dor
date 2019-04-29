package il.co.ilrd.linkedlist;

public class TestLinkedList {
	public static void main(String[] args) {
		LinkedList sll = new LinkedList();
		Integer data1 = 1;
		Integer data2 = 2;
		Integer data3 = 3;
		Integer data4 = 4;

		if (sll.isEmpty()) {
			System.out.println("isEmpty 1 Work!");
		}

		sll.pushFront(data1);

		if (!sll.isEmpty()) {
			System.out.println("isEmpty 2 Work!");
		}

		if (sll.getSize() == 1) {
			System.out.println("GetSize 1 Work!");
		}
		
		sll.pushFront(data2);
		sll.pushFront(data3);
		sll.pushFront(data4);

		if (sll.getSize() == 4) {
			System.out.println("GetSize 2 Work!");
		}

		if (sll.popFront().equals(data4)) {
			System.out.println("popFront 1 Work!");
		}

		if (sll.getSize() == 3) {
			System.out.println("popFront 2 Work!");
		}

		sll.popFront();
		sll.popFront();
		sll.popFront();

		if (sll.isEmpty()) {
			System.out.println("isEmpty 3 Work!");
		}

		sll.pushFront(data1);
		sll.pushFront(data2);
		sll.pushFront(data3);
		sll.pushFront(data4);

		if (sll.getSize() == 4) {
			System.out.println("GetSize 2 Work!");
		}

		ListIterator iter = sll.getBegin();
		if (data4.equals(iter.next())) {
			System.out.println("getBegin 1 Work!");
		}

		iter = sll.find(data2);
		if (data2.equals(iter.next())) {
			System.out.println("find 1 Work!");
		}
		
		iter = sll.find(data1);
		if (data1.equals(iter.next())) {
			System.out.println("find 2 Work!");
		}
	}
}
