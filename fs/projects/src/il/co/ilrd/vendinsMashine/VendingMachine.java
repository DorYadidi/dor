package il.co.ilrd.vendinsMashine;

import java.util.ArrayList;

public class VendingMachine {

	private StateVendingMachine stateVM;
	private NotifierImplement printMsg;
	private ArrayList<Product> arrProducts;
	private int timerFlag;
	private Thread threadTimer;
	private Product myProdct;

	enum StateVendingMachine {

		START {

			@Override
			protected void trunOn(VendingMachine vm) {
				vm.threadTimer.start();
				vm.stateVM = WAITING_FOR_SELECTION;
			}

			@Override
			protected void select(VendingMachine vm, String productName) {
			}

			@Override
			protected void inputMomey(VendingMachine vm, double money) {
			}

			@Override
			protected void cancel(VendingMachine vm) {
			}
		},

		WAITING_FOR_SELECTION {
			@Override
			protected void select(VendingMachine vm, String productName) {
				for (Product current : vm.arrProducts) {
					if (productName.equals(current.getName())) {
						vm.myProdct = current;
						vm.timerFlag = 10;
						vm.stateVM = WATING_FOR_MONEY;
						return;
					}
				}

				vm.stateVM = WAITING_FOR_SELECTION;
			}

			@Override
			protected void inputMomey(VendingMachine vm, double money) {
			}

			@Override
			protected void cancel(VendingMachine vm) {
			}
		},

		WATING_FOR_MONEY {
			@Override
			protected void select(VendingMachine vm, String productName) {
			}

			@Override
			protected void inputMomey(VendingMachine vm, double money) {
				if (vm.myProdct.getPrice() <= money) {
					vm.printMsg.write(vm.myProdct + ", Your change: " + (money - vm.myProdct.getPrice()));
				} else {
					vm.printMsg.write("No money, Your change: " + (money));
				}

				vm.stateVM = WAITING_FOR_SELECTION;
			}

			@Override
			protected void cancel(VendingMachine vm) {
				vm.stateVM = WAITING_FOR_SELECTION;
			}

			@Override
			protected void timeOut(VendingMachine vm) {
				if (vm.timerFlag == 0) {
					vm.printMsg.write("TimeOut: Cancel - make new selection");
					vm.stateVM = WAITING_FOR_SELECTION;
				}

				--vm.timerFlag;
			}
		};

		protected void turnOff(VendingMachine vm) {
			vm.stateVM = START;
		}

		protected void timeOut(VendingMachine vm) {
		}

		protected void trunOn(VendingMachine vm) {
		}

		protected abstract void select(VendingMachine vm, String productName);

		protected abstract void inputMomey(VendingMachine vm, double money);

		protected abstract void cancel(VendingMachine vm);
	}

	public VendingMachine(ArrayList<Product> productList, NotifierImplement note) {
		stateVM = StateVendingMachine.START;
		arrProducts = productList;
		printMsg = note;
	}

	public void trunOn() {
		threadTimer = new Thread(() -> {
			while (stateVM != StateVendingMachine.START) {
				try {
					Thread.sleep(1000);
				} catch (InterruptedException e) {
					e.printStackTrace();
				}

				stateVM.timeOut(this);
			}
		});
		stateVM.trunOn(this);
	}

	public void select(String name) {
		stateVM.select(this, name);
	}

	public void inputMoney(double money) {
		stateVM.inputMomey(this, money);
	}

	public void cansel() {
		stateVM.cancel(this);
	}

	public void turnOff() {
		stateVM.turnOff(this);
	}
}
