package il.co.ilrd.threadpool;

import java.util.Comparator;
import java.util.Objects;
import java.util.PriorityQueue;
import java.util.concurrent.Semaphore;
import java.util.concurrent.TimeUnit;

public class WaitableQueueSem<T> {
	private PriorityQueue<T> queueList;
	private final Semaphore semaphore = new Semaphore(0);
	private Object monitor = new Object();

	public WaitableQueueSem() {
		queueList = new PriorityQueue<>();
	}

	public WaitableQueueSem(Comparator<? super T> comp) {
		queueList = new PriorityQueue<>(comp);
	}

	public void enqueue(T item) throws NullPointerException {
		Objects.requireNonNull(item, "item can not be null");

		synchronized (monitor) {
			queueList.add(item);
		}

		semaphore.release();
	}

	public T dequeue() throws InterruptedException {
		semaphore.acquire();
		synchronized (monitor) {
			return queueList.poll();
		}
	}

	public T dequeue(int timeOut, TimeUnit timeUnit) throws InterruptedException {
		Objects.requireNonNull(timeUnit);
		T result = null;

		if (semaphore.tryAcquire(timeOut, timeUnit)) {
			synchronized (monitor) {
				result = queueList.poll();
			}
		}
		return result;
	}

	public boolean remove(T object) throws InterruptedException {
		Objects.requireNonNull(object, "object can not be null");

		if (semaphore.tryAcquire()) {
			synchronized (monitor) {
				if (queueList.remove(object)) {
					return true;
				} else {
					semaphore.release();
				}
			}
		}
		return false;
	}
}
