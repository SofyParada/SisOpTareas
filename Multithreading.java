import java.util.concurrent.ForkJoinPool;
import java.util.concurrent.RecursiveTask;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class  Multithreading {
    public static void main(String[] args) {
        String Tesoro = "ubicacion-tesoro.txt";

        try (BufferedReader br = new BufferedReader(new FileReader(Tesoro))) {
            String linea;
            int i = 0;
            while ((linea = br.readLine()) != null && i < 3) {
                if(i == 0){
                    int matriz = Integer.parseInt(linea);;
                }
                else if(i == 2){
                    int Largo = Integer.parseInt(linea);
                }
                else{
                    
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

}
