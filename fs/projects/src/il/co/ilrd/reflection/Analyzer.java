package il.co.ilrd.reflection;

import java.lang.reflect.*;

public class Analyzer {

	public static void main(String[] args) throws NoSuchMethodException, SecurityException, IllegalAccessException,
			IllegalArgumentException, InvocationTargetException, NoSuchFieldException {
		ObjectAnalyzer obj = new ObjectAnalyzer();
		Class<? extends ObjectAnalyzer> cls = obj.getClass();
		
		System.out.println("1) The name of class is " + cls.getName());
		System.out.println("2) The Super Class is:" + cls.getSuperclass());
		System.out.print("3) The Interfaces is :");
		
		for (Class<?> printer: cls.getInterfaces()) {
			System.out.print(printer + ", ");
		}	
		System.out.println();

		Constructor<? extends ObjectAnalyzer> constructor = cls.getConstructor();
		System.out.println("4) The name of constructor is " + constructor.getName());

		System.out.println("5) The public methods of class are : ");

		Method[] methods = cls.getMethods();

		for (Method method : methods) {
			System.out.println(method.getName());			
		}

		Method methodcall1 = cls.getDeclaredMethod("method2", int.class);
		methodcall1.invoke(obj, 19);
		
		Field field = cls.getDeclaredField("field");

		field.setAccessible(true);
		field.set(obj, "LOL");

		Method methodcall2 = cls.getDeclaredMethod("method1");
		methodcall2.invoke(obj);
		
		Method methodcall3 = cls.getDeclaredMethod("method3");
		methodcall3.setAccessible(true);
		methodcall3.invoke(obj);
	}
}
