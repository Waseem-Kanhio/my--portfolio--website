import java.util.ListIterator;
import java.util.Scanner;

public class SumFloat {
    public static void Sumfloat (float ...Numbers) {
        float sumfloat = 0;
        for (int i = 0; i < Numbers.length; i++){
            sumfloat+=Numbers[i];
        }
        System.out.println("Sum of float Number is : " + sumfloat);
    }
    public static void main(String[] args) {
        System.out.print("How Many Numbers that you want to add : ");
        Scanner Numb = new Scanner(System.in);
        int Limit = Numb.nextInt();
        float[] arraysumfloat = new float[Limit];
        System.out.print("Enter Numbers : ");
        Scanner get = new Scanner(System.in);
        
        for (int i = 0 ; i < Limit; i++) {
            arraysumfloat[i] =get.nextFloat();
        }
        Sumfloat(arraysumfloat);
    }
    
}
