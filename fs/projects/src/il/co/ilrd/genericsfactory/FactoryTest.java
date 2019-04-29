package il.co.ilrd.genericsfactory;

import static org.junit.jupiter.api.Assertions.*;

import java.util.function.Function;

import org.junit.jupiter.api.Test;

class FactoryTest {
	
	private static Foo applyFoo3(String s) {
		return (s == null) ? new Foo3() : new Foo3(s);
	}
	
	@Test
	void test1() {
		Factory<Integer, Foo, String> factory = new Factory<>();
		String data = "data";
		
		//Lambada
		factory.add(1, (String s) -> (s == null) ? new Foo() : new Foo(s));
		
		//Anonymous class
		Function<String, Foo> funcAnonymus = new Function<String, Foo>() {
			@Override
			public Foo apply(String s) {
				return (s == null) ? new Foo2() : new Foo2(s);
			}
		};
		factory.add(2, funcAnonymus);
		
		//static method Reference
		factory.add(3, FactoryTest::applyFoo3);
		
		//Method Reference
		factory.add(4, new MethodReference()::applyFoo4);
		
		assertEquals("foo: no data", factory.create(1).run());
		assertEquals("foo2: no data", factory.create(2).run());
		assertEquals("foo3: no data", factory.create(3).run());
		assertEquals("foo4: no data", factory.create(4).run());
		
		assertEquals(data, factory.create(1, data).run());
		assertEquals(data, factory.create(2, data).run());
		assertEquals(data, factory.create(3, data).run());
		assertEquals(data, factory.create(4, data).run());		
	}
	
	@Test
	void test2() {
		//Method Reference Non Static
		Factory<Integer, Integer, Data> factory = new Factory<>();
		factory.add(1, Data::applyData);
	}
}

class MethodReference {
	public Foo applyFoo4(String s) {
		return (s == null) ? new Foo4() : new Foo4(s);
	}
}

class Foo5 extends Foo {
	private String message;
	
	public Foo5(String s) {
		message = s;
	}
	
	public Foo5() {
		message = "foo5: no data";
	}
	
	String run() {
		return message;
	}
}


class Foo {
	private String message;
	
	public Foo(String s) {
		message = s;
	}
	
	public Foo() {
		message = "foo: no data";
	}
	
	String run() {
		return message;
	}
}

class Foo2 extends Foo {
	private String message;
	
	public Foo2(String s) {
		message = s;
	}
	
	public Foo2() {
		message = "foo2: no data";
	}
	
	String run() {
		return message;
	}
}

class Foo3 extends Foo {
	private String message;
	
	public Foo3(String s) {
		message = s;
	}
	
	public Foo3() {
		message = "foo3: no data";
	}
	
	String run() {
		return message;
	}
}

class Foo4 extends Foo2 {
	private String message;
	
	public Foo4(String s) {
		message = s;
	}
	
	public Foo4() {
		message = "foo4: no data";
	}
	
	String run() {
		return message;
	}
}

class Data {
	private Data() {}
	public Integer applyData() {
		return new Integer(4);
	}
}
