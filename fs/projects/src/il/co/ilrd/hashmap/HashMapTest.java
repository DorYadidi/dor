package il.co.ilrd.hashmap;

import static org.junit.jupiter.api.Assertions.*;

import java.util.Iterator;
import java.util.Map.Entry;
import java.util.Set;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

class HashMapTest {
	
	HashMapImp<Integer, String> hash_map;
	
	@BeforeEach
	void setAll() {
		hash_map = new HashMapImp<Integer, String>(100);
	}

	@Test
	void testBasic() { 
		assertTrue(hash_map.isEmpty());
		assertTrue(hash_map.size() == 0);
        hash_map.put(1, "a"); 
        assertTrue(!hash_map.isEmpty());
		assertTrue(hash_map.size() == 1);
		assertTrue(!hash_map.containsKey(2));
		assertTrue(hash_map.containsKey(1));
		hash_map.put(2, "b"); 
		hash_map.put(3, "c"); 
		hash_map.put(4, "d");
		hash_map.put(5, "e");
		
		assertTrue(hash_map.size() == 5);
		assertTrue(hash_map.containsValue("c"));
		assertTrue(hash_map.put(4, "f") == "d");
		assertTrue(hash_map.size() == 5);
		assertTrue(!hash_map.containsValue("d"));
		assertTrue(hash_map.containsValue("f"));
		
		assertTrue(hash_map.get(2) == "b");
		assertTrue(hash_map.get(5) == "e");
		
		assertTrue(hash_map.remove(10) == null);
		
		assertTrue(hash_map.size() == 5);
		
		assertTrue(hash_map.remove(2) == "b");
		assertTrue(hash_map.size() == 4);
		
		assertTrue(hash_map.remove(3) == "c");
		assertTrue(hash_map.size() == 3);
		
		assertTrue(hash_map.remove(5) == "e");
		assertTrue(hash_map.size() == 2);
		
		assertTrue(hash_map.remove(1) == "a");
		assertTrue(hash_map.size() == 1);
		
		assertTrue(hash_map.remove(4) == "f");
		assertTrue(hash_map.size() == 0);
		
		 hash_map.clear();
	     assertTrue(hash_map.size() == 0);
	     
        hash_map.put(1, "a"); 
        hash_map.clear();
        assertTrue(hash_map.size() == 0);
        hash_map.put(1, "a"); 
        assertTrue(hash_map.size() == 1);
	}
	
	@Test
	void testPutNull() {
		hash_map.put(1, "a");
		hash_map.put(null, "b");
        assertTrue(hash_map.size() == 2);
		assertTrue(hash_map.containsValue("b"));
		assertTrue(hash_map.containsKey(null));
		assertTrue(hash_map.put(null, "c") == "b");
        assertTrue(hash_map.size() == 2);
        
        hash_map.put(2, null); 
		hash_map.put(3, null); 
		hash_map.put(4, null);
        assertTrue(hash_map.size() == 5);
        assertTrue(hash_map.containsValue(null));
        assertTrue(hash_map.remove(2) == null);
        assertTrue(hash_map.remove(3) == null);
        assertTrue(hash_map.remove(4) == null);
        assertTrue(hash_map.size() == 2);
        hash_map.clear();
        assertTrue(hash_map.size() == 0);
		hash_map.put(null, null);
        assertTrue(hash_map.size() == 1);
		assertTrue(hash_map.containsKey(null));
        assertTrue(hash_map.containsValue(null));
        hash_map.clear();
	}
	
	
	@Test
	void testEmptyLists() {
		int count = 0;
        hash_map.put(1, "a"); 
		hash_map.put(2, "b"); 
		hash_map.put(5, "c"); 
		hash_map.put(6, "d");
		hash_map.put(99, "e");
		assertTrue(hash_map.size() == 5);
		Set<Entry<Integer, String>> setList = hash_map.entrySet();
		Iterator<Entry<Integer, String>> iterator = setList.iterator();
		while (iterator.hasNext()) {
			count += iterator.next().getKey();
		}
		
		assertTrue(count == 113);	
	}
	
	@Test
	void test() {
		HashMapImp<Integer, String> hash_map = new HashMapImp<Integer, String>(100);
		hash_map.put(1, "a");
		hash_map.put(2, "b"); 
		hash_map.put(3, "c"); 
		hash_map.put(4, "d");
		hash_map.put(5, "e");
		System.out.println(hash_map.entrySet());
		System.out.println(hash_map.keySet());
		System.out.println(hash_map.values());
	}
}