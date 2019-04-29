package il.co.ilrd.threadpool;

import java.util.*;
import java.util.Objects;
import java.util.concurrent.*;

public class ThreadPool implements Executor {
	private WaitableQueueSem<Task<?>> wq = new WaitableQueueSem<>();;
	private List<Thread> threadList = new LinkedList<Thread>();
	private Semaphore semPause = new Semaphore(0);
	private volatile boolean shutdownFlag;
	private volatile boolean isPause;
	private static final int PAUSE_PRIOTITY = Priority.MAX_PRIORITY.ordinal() - 1;
	private static final int SHUTDOWN_PRIOTITY = Priority.MIN_PRIORITY.ordinal() + 1;
	private static final int SHUTDOWNOW_PRIOTITY = Priority.MAX_PRIORITY.ordinal() - 1;

	public enum Priority {
		MAX_PRIORITY, NORM_PRIORITY, MIN_PRIORITY
	};

	public enum Status {
		WAIT, RUN, DONE, CANCELLED
	};

	public <T> ThreadPool(int numThread) {
		if (numThread <= 0) {
			throw new IllegalArgumentException("nThreads Can not be <= 0");
		}
		for (int i = 0; i < numThread; ++i) {
			threadList.add(new ThreadRefernce());
		}
	}

	public void run() {
		shutdownFlag = false;
		for (int i = 0; i < threadList.size(); ++i) {
			/*
			 * Could not be loop with iterator --> setNumThread before run FAIL (FAIL-FAST)
			 */
			if (!threadList.get(i).isAlive()) {
				threadList.get(i).start();
			}
		}
	}

	public <T> Future<T> submit(Runnable runnable, Priority priority) throws RejectedExecutionException {
		Objects.requireNonNull(runnable);
		return submit(Executors.callable(runnable, null), priority.ordinal());
	}

	public <T> Future<T> submit(Runnable runnable, Priority priority, T result) throws RejectedExecutionException {
		Objects.requireNonNull(runnable);
		return submit(Executors.callable(runnable, result), priority.ordinal());
	}

	public <T> Future<T> submit(Callable<T> callable) throws RejectedExecutionException {
		return submit(callable, Priority.NORM_PRIORITY.ordinal());
	}

	public <T> Future<T> submit(Callable<T> callable, Priority priority) throws RejectedExecutionException {
		Objects.requireNonNull(callable);
		Objects.requireNonNull(priority);

		return submit(callable, priority.ordinal());
	}

	@Override
	public void execute(Runnable command) throws RejectedExecutionException {
		Objects.requireNonNull(command);
		submit(Executors.callable(command, null), Priority.NORM_PRIORITY.ordinal());
	}

	private <T> Future<T> submit(Callable<T> callable, int priorityValue) throws RejectedExecutionException {
		if (shutdownFlag) {
			throw new RejectedExecutionException();
		}

		Task<T> task = new Task<>(callable, priorityValue);
		wq.enqueue(task);
		return task.getFuture();
	}

	private class PauseTask implements Runnable {
		public void run() {
			try {
				semPause.acquire();
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
	}

	public void pause() {
		if (isPause) {
			throw new IllegalStateException();
		}

		for (int i = 0; i < threadList.size(); i++) {
			submit(Executors.callable(new PauseTask(), null), PAUSE_PRIOTITY);
		}

		isPause = true;
	}

	public void resume() {
		if (isPause == false) {
			throw new IllegalStateException();
		}

		semPause.release(threadList.size());
		isPause = false;
	}

	private class KillThread implements Runnable {
		@Override
		public void run() {
			((ThreadRefernce) Thread.currentThread()).shutdownThread();
			threadList.remove(Thread.currentThread());
		}
	}

	public <T> void setNumThreads(int numThread) {
		if (numThread <= 0) {
			throw new IllegalArgumentException();
		}

		if (numThread >= threadList.size()) {
			for (int i = numThread - threadList.size(); i > 0; --i) {
				ThreadRefernce newThread = new ThreadRefernce();
				threadList.add(newThread);
				if (isPause) {
					submit(Executors.callable(new PauseTask(), null), PAUSE_PRIOTITY);

				}

				newThread.start();
			}
		} else {
			for (int i = threadList.size() - numThread; i > 0; --i) {
				submit(Executors.callable(new KillThread(), null), SHUTDOWNOW_PRIOTITY);
			}
		}
	}

	public void shutDown() {
		if (shutdownFlag) {
			throw new IllegalStateException();
		}

		if (isPause) {
			resume();
		}

		for (int i = 0; i < threadList.size(); ++i) {
			submit(Executors.callable(new KillThread(), null), SHUTDOWN_PRIOTITY);
		}
		shutdownFlag = true;
	}

	public void shutDownNow() {
		if (isPause) {
			resume();
		}
		for (int i = 0; i < threadList.size(); ++i) {
			submit(Executors.callable(new KillThread(), null), SHUTDOWNOW_PRIOTITY);
		}
	}

	private class Task<T> implements Comparable<Task<T>>, Runnable {
		private Callable<T> callable;
		private int priorityValue;
		private TaskFuture future = new TaskFuture();
		private Semaphore semGetResult = new Semaphore(0);

		public Task(Callable<T> callable, int priorityValue) {
			this.callable = callable;
			this.priorityValue = priorityValue;
			future.setStatus(Status.WAIT);
		}

		@Override
		public int compareTo(Task<T> o) {
			return getPriorityValue() - o.getPriorityValue();
		}

		@Override
		public void run() {
			future.setStatus(Status.RUN);
			try {
				future.setResult(callable.call());
				future.setStatus(Status.DONE);
			} catch (Exception e) {
				future.setStatus(Status.CANCELLED);
			} finally {
				semGetResult.release();
			}
		}

		private TaskFuture getFuture() {
			return future;
		}

		private int getPriorityValue() {
			return priorityValue;
		}

		private class TaskFuture implements Future<T> {
			private T result;
			private volatile Status status;

			@Override
			public boolean cancel(boolean mayInterruptIfRunning) {
				boolean isRemoved = false;
				try {
					isRemoved = wq.remove(Task.this);
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
				if (isRemoved) {
					setStatus(Status.CANCELLED);
					semGetResult.release();
				}

				return isRemoved;
			}

			@Override
			public boolean isCancelled() {
				return status == Status.CANCELLED;
			}

			@Override
			public boolean isDone() {
				return status == Status.DONE;
			}

			@Override
			public T get() throws InterruptedException, ExecutionException {
				semGetResult.acquire();
				semGetResult.release();

				if (isCancelled()) {
					throw new CancellationException("Task alrady cancelled");
				}

				return result;
			}

			@Override
			public T get(long timeout, TimeUnit unit)
					throws InterruptedException, ExecutionException, TimeoutException {
				Objects.requireNonNull(unit);

				if (semGetResult.tryAcquire(timeout, unit) == false) {
					throw new TimeoutException("Timeout");
				}

				if (isCancelled()) {
					throw new CancellationException("Task alrady cancelled");
				}

				semGetResult.release();
				return result;
			}

			private void setResult(T newResult) {
				result = newResult;
			}

			private void setStatus(Status status) {
				this.status = status;
			}
		}
	}

	private class ThreadRefernce extends Thread {
		private boolean isOff = false;

		public void shutdownThread() {
			isOff = true;
		}

		@Override
		public void run() {
			while (!isOff) {
				try {
					wq.dequeue().run();
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			}
		}
	}
}