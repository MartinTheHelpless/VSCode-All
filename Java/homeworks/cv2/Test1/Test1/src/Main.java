import java.util.Random;

public class Main {
    public static void main(String[] args) {

        Descriptable[] array = new Descriptable[30];

        Random random = new Random();
        random.nextDouble();

        for (int i = 0; i < array.length; i+=3){
            array[i] = new Cat("Cat " + random.nextDouble(1,1000), random.nextInt(50));
            array[i + 1] = new Canidae("RGB-" + random.nextInt(100000, 899999), random.nextInt(1, 15));
            array[i + 2] = new DomesticDog("Steve", "RGB-" + random.nextInt(100000, 899999), random.nextInt(1, 15));
        }

        int count = 3;

        for (int i = 0; i < array.length && count > 0; i++){
            if (array[i].getClass() == Cat.class && count == 3){
                System.out.print("Array position: " + i + " -- ");
                System.out.println(array[i].getDescription());
            }else if (array[i].getClass() == Canidae.class && count == 2){
                System.out.print("Array position: " + i + " -- ");
                System.out.println(array[i].getDescription());
            }else if (array[i].getClass() == DomesticDog.class && count ==1){
                System.out.print("Array position: " + i + " -- ");
                System.out.println(array[i].getDescription());
            }

            if (i == array.length - 1) {
                count--;
                i = 0;
                System.out.println(" ");
            }


        }

    }
}