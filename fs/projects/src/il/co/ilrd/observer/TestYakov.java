package il.co.ilrd.observer;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

class TestYakov {

	David david;
	Ari ari;
	Ima ima;
	
	@BeforeEach
	void setup(){
		david = new David();
		ari = new Ari();
		ima = new Ima();
		
		david.getDispatcher().register(ari.getCallback());
		david.getDispatcher().register(ima.getCallback());	
	}
	
	@Test
	void testBasicFunctionality() {

		assertNotEquals(ari.says(), "waaaaaaa!");
		assertNotEquals(ima.says(), "go to bed David!");
		
		david.setSays("no Ari!");
		
		assertEquals(ari.says(), "waaaaaaa!");
		assertEquals(ima.says(), "go to bed David!");
	}
	
	@Test
	void testUnregister() {
		assertNotEquals(ari.says(), "oh!");
		assertNotEquals(ima.says(), "bye!");
		
		david.getDispatcher().unregister(ari.getCallback());
		ima.getCallback().unregisterCallback();
		
		assertEquals(ari.says(), "oh!");
		assertEquals(ima.says(), "bye!");
		
		david.setSays("no Ari!");
		
		assertNotEquals(ari.says(), "waaaaaaa!");
		assertNotEquals(ima.says(), "go to bed David!");
		assertEquals(ari.says(), "oh!");
		assertEquals(ima.says(), "bye!");
	}
	
	@Test
	void testTerminate() {
		assertNotEquals(ari.says(), "oh!");
		assertNotEquals(ima.says(), "bye!");
		
		david.getDispatcher().terminate();
		
		assertEquals(ari.says(), "oh!");
		assertEquals(ima.says(), "bye!");
		
		david.setSays("no Ari!");
		
		assertNotEquals(ari.says(), "waaaaaaa!");
		assertNotEquals(ima.says(), "go to bed David!");
		assertEquals(ari.says(), "oh!");
		assertEquals(ima.says(), "bye!");
	}
	
	@Test
	void testChangeUpdateTerminate() {
		assertNotEquals(ari.says(), "bye bye!");
		assertNotEquals(ari.says(), "go away!");
		
		ari.getCallback().setUpdate((String s) -> {if (s.equals("no Ari!")) {
			ari.setSays("go away!");
		}});
		ari.getCallback().setTerminate(() -> ari.setSays("bye bye!"));
		
		david.setSays("no Ari!");
		assertEquals(ari.says(), "go away!");
		
		david.getDispatcher().unregister(ari.getCallback());
		assertEquals(ari.says(), "bye bye!");
	}
	
}

class David {
	private String says = "";
	private Dispatcher<String> dispatcher = new Dispatcher<>();
	
	public String says() {
		return says;
	}
	
	public void setSays(String s) {
		says = s;
		dispatcher.notifyObservers(s);
	}

	public Dispatcher<String> getDispatcher() {
		return dispatcher;
	}
}

class Ari {
	private String says = "";
	
	private Callback<String> callback = new Callback<>(
			(String s) -> {if (s.equals("no Ari!")) {
				says = "waaaaaaa!";
			}},
			() -> says = "oh!");

	public String says() {
		return says;
	}
	
	public void setSays(String s) {
		says = s;
	}

	public Callback<String> getCallback() {
		return callback;
	}
}

class Ima {
	private String says = "";
	
	private Callback<String> callback = new Callback<>(
			(String s) -> {if (s.equals("no Ari!")) {
				says = "go to bed David!";
			}},
			() -> says = "bye!");

	public String says() {
		return says;
	}
	
	public void setSays(String s) {
		says = s;
	}

	public Callback<String> getCallback() {
		return callback;
	}
}