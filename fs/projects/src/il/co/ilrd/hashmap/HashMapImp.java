package il.co.ilrd.hashmap;

import java.util.*;

public class HashMapImp<K, V> implements Map<K, V> {
	private List<List<Entry<K, V>>> table;
	private int size;
	private int modCount;
	private int capacity;
	private Collection<V> valueCollection;
	private Set<K> keySet;
	private Set<Entry<K, V>> entrySet;

	private static final int DEFAULT_CAPACITY = 16;
	private static final int NULL_BUCKET = 0;

	public HashMapImp() {
		this(DEFAULT_CAPACITY);
	}

	public HashMapImp(int capacity) {
		if (capacity <= 0) {
			throw new IllegalArgumentException("worng capacity");
		}

		this.capacity = capacity;
		table = new ArrayList<List<Entry<K, V>>>(capacity);
		for (int i = 0; i < capacity; ++i) {
			table.add(new LinkedList<Map.Entry<K, V>>());
		}
	}

	@Override
	public int size() {
		return size;
	}

	@Override
	public boolean isEmpty() {
		return size() == 0;
	}

	private int getIndexBucket(Object key) {
		if (key == null) {
			return NULL_BUCKET;
		}

		return key.hashCode() % capacity;
	}

	private Entry<K, V> getEntry(Object key) {
		List<Entry<K, V>> bucket;
		if (key == null) {
			bucket = table.get(NULL_BUCKET);
			for (Entry<K, V> e : bucket) {
				if (e.getKey() == null) {
					return e;
				}
			}
		} else {
			bucket = table.get(getIndexBucket(key));
			for (Entry<K, V> e : bucket) {
				if (e.getKey().equals(key)) {
					return e;
				}
			}
		}

		return null;
	}

	@Override
	public boolean containsKey(Object key) {
		return getEntry(key) != null;
	}

	@Override
	public boolean containsValue(Object value) {
		if (value == null) {
			for (V valueCheck : this.values()) {
				if (valueCheck == null) {
					return true;
				}
			}
		} else {
			for (V valueCheck : this.values()) {
				if (value.equals(valueCheck)) {
					return true;
				}
			}
		}

		return false;
	}

	@Override
	public V get(Object key) {
		Entry<K, V> element = getEntry(key);
		if (element != null) {
			return element.getValue();
		}

		return null;
	}

	@Override
	public V put(K key, V value) {
		Entry<K, V> removed = getEntry(key);
		if (removed != null) {
			return removed.setValue(value);
		}

		Entry<K, V> newData = Pair.of(key, value);
		table.get(getIndexBucket(key)).add(newData);
		++modCount;
		++size;
		return null;
	}

	@Override
	public V remove(Object key) {
		Entry<K, V> element = getEntry(key);
		if (element != null) {
			V result = element.getValue();
			table.get(getIndexBucket(key)).remove(element);
			--size;
			++modCount;
			return result;
		}

		return null;
	}

	@Override
	public void putAll(Map<? extends K, ? extends V> m) {
		if (m == null) {
			throw new NullPointerException("map == null");
		}

		for (Entry<? extends K, ? extends V> data : m.entrySet()) {
			this.put(data.getKey(), data.getValue());
		}
	}

	@Override
	public void clear() {
		for (List<Entry<K, V>> list : table) {
			list.clear();
		}
		size = 0;
		++modCount;
	}

	@Override
	public Set<K> keySet() {
		keySet = (keySet == null) ? new KeySet() : keySet;
		return keySet;
	}

	@Override
	public Collection<V> values() {
		valueCollection = (valueCollection == null) ? new ValuesCollection() : valueCollection;
		return valueCollection;
	}

	@Override
	public Set<Entry<K, V>> entrySet() {
		entrySet = (entrySet == null) ? new EntrySet() : entrySet;
		return entrySet;
	}

	private class EntrySet extends AbstractSet<Entry<K, V>> {
		@Override
		public Iterator<Entry<K, V>> iterator() {
			return new EntrySetIterator();
		}

		@Override
		public int size() {
			return HashMapImp.this.size();
		}

		private class EntrySetIterator implements Iterator<Entry<K, V>> {
			private Iterator<List<Entry<K, V>>> outerListRunner;
			private Iterator<Entry<K, V>> innerListRunner;

			private int expectedModCount;

			public EntrySetIterator() {
				this.expectedModCount = modCount;
				this.outerListRunner = table.iterator();
				this.innerListRunner = outerListRunner.next().iterator();
			}

			@Override
			public boolean hasNext() {
				while (innerListRunner.hasNext() == false) {
					if(outerListRunner.hasNext() == false) {
						return false;
					}
					innerListRunner = outerListRunner.next().iterator();
				}
				return true;
			}

			@Override
			public Entry<K, V> next() {
				if (expectedModCount != modCount) {
					throw new ConcurrentModificationException();
				}
				this.hasNext();	
				return innerListRunner.next();

			}
		}
	}

	private class ValuesCollection extends AbstractCollection<V> {
		@Override
		public Iterator<V> iterator() {
			return new ValuesCollectionIterator();
		}

		@Override
		public int size() {
			return HashMapImp.this.size();
		}

		private class ValuesCollectionIterator implements Iterator<V> {
			private Iterator<Entry<K, V>> Runner;

			public ValuesCollectionIterator() {
				this.Runner = entrySet().iterator();
			}

			@Override
			public boolean hasNext() {
				return Runner.hasNext();
			}

			@Override
			public V next() {
				return Runner.next().getValue();
			}
		}
	}

	private class KeySet extends AbstractSet<K> {
		@Override
		public Iterator<K> iterator() {
			return new KeySetIterator();
		}

		@Override
		public int size() {
			return HashMapImp.this.size();
		}

		private class KeySetIterator implements Iterator<K> {
			private Iterator<Entry<K, V>> Runner;

			public KeySetIterator() {
				this.Runner = entrySet().iterator();
			}

			@Override
			public boolean hasNext() {
				return Runner.hasNext();
			}

			@Override
			public K next() {
				return Runner.next().getKey();
			}
		}
	}
}