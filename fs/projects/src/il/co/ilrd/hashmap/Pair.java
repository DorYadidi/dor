package il.co.ilrd.hashmap;

import java.util.*;

public class Pair<K, V> implements Map.Entry<K, V> {

	private K key;
	private V value;

	private Pair(K key, V value) {
		this.key = key;
		this.value = value;
	}

	public static <K, V> Pair<K, V> of(K key, V value) {
		return new Pair<K, V>(key, value);
	}

	public K setKey(K key) {
		K result = this.key;
		this.key = key;
		return result;
	}

	@Override
	public String toString() {
		return "Pair [key=" + key + ", value=" + value + "]";
	}

	@Override
	public K getKey() {
		return key;
	}

	@Override
	public V getValue() {
		return value;
	}

	@Override
	public V setValue(V value) {
		V result = this.value;
		this.value = value;
		return result;
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result + ((key == null) ? 0 : key.hashCode());
		result = prime * result + ((value == null) ? 0 : value.hashCode());
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (!(this instanceof Pair))
			return false;
		Pair<?, ?> other = (Pair<?, ?>) obj;
		if (key == null) {
			if (other.key != null)
				return false;
		} else if (!key.equals(other.key))
			return false;
		if (value == null) {
			if (other.value != null)
				return false;
		} else if (!value.equals(other.value))
			return false;
		return true;
	}

	public static <V, K> Pair<V, K> swap(Pair<K, V> pair) {
		if (pair == null) {
			throw new NullPointerException("invalid argument");
		}

		return new Pair<V, K>(pair.getValue(), pair.getKey());
	}

	public static <T extends Comparable<? super T>> Pair<T, T> minMax(T[] array) {
		if (array == null) {
			throw new NullPointerException("Array == null");
		}

		Comparator<T> comp = new Comparator<T>() {
			@Override
			public int compare(T o1, T o2) {
				return o1.compareTo(o2);
			}
		};

		return minMax(array, comp);
	}

	public static <T> Pair<T, T> minMax(T[] array, Comparator<? super T> comp) {
		if (array == null) {
			throw new NullPointerException("Array == null");
		}
		if (comp == null) {
			throw new NullPointerException("Comparator == null");
		}
		for (T runner : array) {
			if (runner == null) {
				throw new IllegalStateException("Null element in array");
			}
		}

		T min;
		T max;
		if (array.length == 1) {
			return new Pair<T, T>(array[0], array[0]);
		}

		if (comp.compare(array[0], array[1]) > 0) {
			min = array[1];
			max = array[0];
		} else {
			min = array[0];
			max = array[1];
		}

		for (int i = 2; i <= array.length - 2; i = i + 2) {
			if (comp.compare(array[i], array[i + 1]) > 0) {
				if (comp.compare(array[i], max) > 0) {
					max = array[i];
				}
				if (comp.compare(min, array[i + 1]) > 0) {
					min = array[i + 1];
				}
			} else {
				if (comp.compare(array[i + 1], max) > 0) {
					max = array[i];
				}
				if (comp.compare(min, array[i]) > 0) {
					min = array[i + 1];
				}
			}
		}

		if (array.length % 2 == 1) {
			if (comp.compare(array[array.length - 1], max) > 0) {
				max = array[array.length - 1];
			}
			if (comp.compare(min, array[array.length - 1]) > 0) {
				min = array[array.length - 1];
			}
		}

		return new Pair<T, T>(min, max);
	}
}
