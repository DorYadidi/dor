package il.co.ilrd.exams;

public class Matrix {
	public static int matrix (int[][] arr, int N) {
		int result = 0;
		
		for (int i = 0; i < N; ++i) {
			
			for (int j = 0; j <= i; ++j) {
				if (i == j) {
					if (arr[i][j] != 1) {
						return result;
					}
					int temp_i = i - 1;
					while (temp_i >= 0) {
						if (arr[temp_i][j] != 0) {
							return result;
						}
						
						-- temp_i;
					}
				} else {
					if (arr[i][j] != 0) {
						return result;
					}
				}
			}
			
			++result;
		}
		return result;
	}
	
	public static boolean isPolindrom(int num) {
		int sum = 0;
		int last = 0;
		int temp = num;
		
		while (num > 0) {
			last = num % 10;
			sum = (sum * 10) + last;
			num = num / 10;
		}
		
		return sum == temp;
	}
	
	public static void main(String[] args) {
		int[][] arr = new int[3][3];
		arr[0][0] = 1;
		arr[0][1] = 0;
		arr[0][2] = 0;
		arr[1][0] = 0;
		arr[1][1] = 1;
		arr[1][2] = 0;
		arr[2][2] = 0;
		arr[2][1] = 0;
		arr[2][2] = 1;
		
		System.out.println(matrix(arr, 3));
		
		System.out.println(isPolindrom(1212));
		System.out.println(isPolindrom(1221));
	}
}
