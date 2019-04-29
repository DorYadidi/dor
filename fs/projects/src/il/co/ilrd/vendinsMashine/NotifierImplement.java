package il.co.ilrd.vendinsMashine;

public class NotifierImplement implements Notifier {
	@Override
	public void write(String str) {
		System.out.println(str);
	}
}
