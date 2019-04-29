package il.co.ilrd.threadpool;

import java.util.Comparator;
import java.util.Objects;
import java.util.PriorityQueue;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class WaitableQueueCV<T> {
	private PriorityQueue<T> queueList;
	private final Lock lock = new ReentrantLock();
	private final Condition cond = lock.newCondition();

	public WaitableQueueCV() {
		queueList = new PriorityQueue<>();
	}

	public WaitableQueueCV(Comparator<? super T> comp) {
		queueList = new PriorityQueue<>(comp);
	}

	public void enqueue(T item) throws NullPointerException {
		Objects.requireNonNull(item, "item can not be null");
		
		lock.lock();
		try {
			queueList.add(item);
			cond.signal();			
		} finally {
			lock.unlock();			
		}
	}

	public T dequeue() throws InterruptedException {
		lock.lock();
		try {
			while (queueList.isEmpty() == true) {
				cond.await();
			}

			return queueList.poll();
		} finally {
			lock.unlock();
		}
	}

	public T dequeue(int timeOut, TimeUnit timeUnit) throws InterruptedException {
		Objects.requireNonNull(timeUnit);
		lock.lock();
		try {
			while (queueList.isEmpty() == true) {
				if (cond.await(timeOut, timeUnit) == false) {
					return null;
				}
			}
			return queueList.poll();
		} finally {
			lock.unlock();
		}
	}

	public boolean remove(T object) throws InterruptedException {
		Objects.requireNonNull(object, "object can not be null");

		lock.lock();
		try {
			return queueList.remove(object);
			
		} finally {
			lock.unlock();
		}
	}
}
