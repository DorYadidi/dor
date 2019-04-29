package il.co.ilrd.genericslinkedlist;

import java.util.ConcurrentModificationException;
import java.util.Iterator;

public class GenericLinkedList<T> implements Iterable<T> {
	private Node head;
	private int modCount;

	@Override
	public Iterator<T> iterator() {
		return new ListIterator(head);
	}

	public void pushFront(T data) {
		++modCount;
		head = new Node(data, head);
	}

	public T popFront() {
		assert head != null : "Empty LinkList";
		++modCount;
		T result = head.data;
		head = head.next;

		return result;
	}

	public long getSize() {
		long counter = 0;
		for (@SuppressWarnings("unused")
		T data : this) {
			++counter;
		}

		return counter;
	}

	public boolean isEmpty() {
		return head == null;
	}

	public Iterator<T> find(T toFind) {
		assert head != null : "Empty LinkList";
		ListIterator ret = new ListIterator(head);

		for (T data : this) {
			if (toFind.equals(data)) {
				return ret;
			}

			ret.next();
		}

		return null;
	}

	public Iterator<T> getBegin() {
		return new ListIterator(head);
	}

	public static <E> GenericLinkedList<E> newReverse(GenericLinkedList<E> list) {
		assert list.isEmpty() != true : "Empty LinkList";
		GenericLinkedList<E> result = new GenericLinkedList<E>();
		for (E runner : list) {
			result.pushFront(runner);
		}

		return result;
	}

	public static <E> GenericLinkedList<E> merge(GenericLinkedList<E> list1, GenericLinkedList<E> list2) {
		GenericLinkedList<E> result = new GenericLinkedList<E>();

		for (E runner1 : list1) {
			result.pushFront(runner1);
		}

		for (E runner2 : list2) {
			result.pushFront(runner2);
		}

		return newReverse(result);
	}

	private class Node {
		private T data;
		private Node next;

		private Node(T data, Node next) {
			this.data = data;
			this.next = next;
		}
	}

	private class ListIterator implements Iterator<T> {
		private int modCountIterator;
		private Node node;

		public ListIterator(Node node) {
			this.node = node;
			this.modCountIterator = modCount;
		}

		@Override
		public boolean hasNext() {
			return node != null;
		}

		@Override
		public T next() throws ConcurrentModificationException {

			if (modCountIterator != modCount) {
				throw new ConcurrentModificationException();
			}
			if (!hasNext()) {
				throw new NullPointerException("hasNext() == flase");
			}

			T result = node.data;
			node = node.next;

			return result;
		}
	}
}
