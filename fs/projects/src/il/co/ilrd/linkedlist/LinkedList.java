package il.co.ilrd.linkedlist;

public class LinkedList {

	private Node head;

	public void pushFront(Object data) {
		head = new Node(data, head);
	}

	public Object popFront() {
		assert head != null : "Empty LinkList";
		Object result = head.data;
		head = head.next;

		return result;
	}

	public long getSize() {
		ListIteratorImplement iter = new ListIteratorImplement(head);
		long counter = 0;

		while (iter.hasNext())
		{
			++counter;
			iter.next();
		}
	
		return counter;
	}

	public boolean isEmpty() {
		return head == null;
	}

	public ListIterator find(Object data) {
		assert head != null : "Empty LinkList";
		ListIteratorImplement iter = new ListIteratorImplement(head);
		ListIteratorImplement ret = new ListIteratorImplement(head);

		
		while (iter.hasNext()) {
			if (data.equals(iter.next())) {
				return ret;
			}
			
			ret.next();
		}

		return null;
	}

	public ListIterator getBegin() {
		return new ListIteratorImplement(head);
	}

	private class Node {

		private Object data;
		private Node next;

		private Node(Object data, Node next) {
			this.data = data;
			this.next = next;
		}
	}

	public class ListIteratorImplement implements ListIterator {

		private Node current;
		
		public ListIteratorImplement(Node node)
		{
			current = node;
		}

		@Override
		public boolean hasNext() {
			return current != null;
		}

		@Override
		public Object next() {
			Object result = current.data;
			current = current.next;
			return result;
		}
	}
}
	