package il.co.ilrd.observer;

public class TestClass {
	
	public static void main(String[] args) {
		Subject mariv = new Subject();
		ObserverDor dor = new ObserverDor();
		ObserverTomer tomer = new ObserverTomer();
		ObserverChen chen = new ObserverChen();
		
		mariv.register(dor.getCallBack());
		mariv.register(tomer.getCallBack());
		mariv.register(chen.getCallBack());
		
		mariv.run();
		System.out.println();
		mariv.terminate();
		
		mariv.run();
		
		System.out.println();
		mariv.register(dor.getCallBack());
		mariv.register(tomer.getCallBack());
		mariv.register(chen.getCallBack());
		
		dor.getCallBack().unregisterCallback();
		System.out.println();

		mariv.run();
		
		System.out.println();
		tomer.getCallBack().unregisterCallback();
		System.out.println();
		mariv.run();
		System.out.println();
		chen.getCallBack().unregisterCallback();
	}
}
