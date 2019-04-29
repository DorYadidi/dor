package il.co.ilrd.reflection;

import java.lang.reflect.*;

public class ObjectAnalyzer {
 
    private String field; 
   
    public ObjectAnalyzer() {
    	field = "This Is Constructor"; 
    } 
   
    public void method1() { 
        System.out.println("The string is " + field); 
    } 
   
    public void method2(int n)  { 
        System.out.println("The number is " + n); 
    } 
   
	private void method3() { 
        System.out.println("Private method invoked"); 
    }
}
