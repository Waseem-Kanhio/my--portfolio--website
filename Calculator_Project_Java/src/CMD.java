public class CMD {
    public static void main(String[] args) {
        int Sum = 0;
        for(int i =0; i < args.length; i++){
            int Number = Integer.parseInt(args[i]);
            Sum = Sum + Number;
        }
        System.out.println("Sum : " + Sum);
          String name = "Waseem Abbas";
    int intname = Integer.parseInt(name);
    System.out.println(intname);
    }
}
