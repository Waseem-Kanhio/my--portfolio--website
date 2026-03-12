import java.util.Scanner;
public class Sum {
    public static void sum (int ...Numbers) {
        int sum = 0;
        for (int i = 0; i < Numbers.length; i ++) {
            
            sum = sum +Numbers[i];
        }
        System.out.println("Sum is : " + sum);
    }
    public static void main(String[] args) {
        System.out.print("How many numbers that you add : ");
        Scanner input = new Scanner(System.in);
        int Count = input.nextInt();
        
        System.out.print("Enter numbers : ");
        Scanner getumber = new Scanner(System.in);
        int [] arraysum = new int[Count];
        for (int i = 0; i < Count; i++){
            if (getumber.nextInt() < Count){
                System.out.println("Number Exceed...");
                    break;
            }
            arraysum[i] = getumber.nextInt();
        }
        sum(arraysum);
    }
}
