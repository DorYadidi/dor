package il.co.ilrd.ClassInfo;


public class ClassInfo {
	public static class class_info {

		public static void main(String[] args) throws ClassNotFoundException {
		
			Class<?> c = Class.forName(args[0]);
			
			System.out.println(c.getModifiers());
			System.out.println(c.getCanonicalName());
			System.out.println(c.getName());
			System.out.println(c.getSimpleName());
			System.out.println(c.getTypeName());
			System.out.println(c.getAnnotatedSuperclass());
			System.out.println(c.getAnnotations());
			System.out.println(c.isAnnotation());
			System.out.println(c.toString());
			System.out.println(c.getPackage());
			System.out.println(c.getSuperclass());
			System.out.println(c.getClasses());
			System.out.println(c.getClassLoader());
			System.out.println(c.getEnclosingMethod());
			System.out.println(c.getFields());
			System.out.println(c.getProtectionDomain());
			System.out.println(c.getSigners());
			System.out.println(c.getTypeParameters());
		}
	}
}
