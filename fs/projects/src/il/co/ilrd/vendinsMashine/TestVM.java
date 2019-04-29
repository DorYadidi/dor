package il.co.ilrd.vendinsMashine;

import java.util.ArrayList;
import java.util.Scanner;
import org.junit.jupiter.api.Test;

class TestVM implements Cloneable{
	private Scanner sc;

	@Test
	void test() {

		ArrayList<Product> productArrayList = new ArrayList<Product>();

		Product pro1 = new Product("Soko", 3.5);
		Product pro2 = new Product("Click", 4.5);
		Product pro3 = new Product("Skarzi", 2.5);
		Product pro4 = new Product("XL", 6.0);
		Product pro5 = new Product("Bisli", 6.0);
		Product pro6 = new Product("Bamba", 3.0);
		Product pro7 = new Product("Water", 2.0);
		NotifierImplement printMsg = new NotifierImplement();

		productArrayList.add(pro1);
		productArrayList.add(pro2);
		productArrayList.add(pro3);
		productArrayList.add(pro4);
		productArrayList.add(pro5);
		productArrayList.add(pro6);
		productArrayList.add(pro7);

		VendingMachine vm = new VendingMachine(productArrayList, printMsg);

		while (true) {
			vm.trunOn();
			
			System.out.println("Select a product:");
			sc = new Scanner(System.in);
			String name = sc.nextLine();
			vm.select(name);
			
			System.out.println("Input Money:");
			double money = sc.nextDouble();
			vm.inputMoney(money);
		}

	}

}
