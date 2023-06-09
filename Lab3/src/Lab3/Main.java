package Lab3;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.concurrent.ForkJoinPool;

public class Main {

    public static void main(String[] args) {
        try {
            File file = new File("ubicacion-tesoro.txt");
            Scanner scanner = new Scanner(file);
            int N = 0;
            int T = 0;
            int[][] matriz = new int[0][0];
            while (scanner.hasNextLine()) {
                String data = scanner.nextLine();
                N = Integer.parseInt(data);
                System.out.println(N);

                data = scanner.nextLine();
                T = Integer.parseInt(data);
                System.out.println(T);

                data = scanner.nextLine();
                String M = data;
                int fila = 0;
                int columna = 0;
                int[][] newmatriz = new int[N][N];
                boolean flag = false;
                
                for(int j = 0; j < M.length(); j++){
                    char caracter = M.charAt(j);
                    if(caracter == '['){
                        flag = true;
                    }
                    if(caracter == ']'){
                        flag = false;
                        fila++;
                    }
                    if(flag == true){
                        if(caracter == 'x'){
                            newmatriz[fila][columna] = 1;
                            columna++;
                        }
                        if(caracter == '0'){
                            newmatriz[fila][columna] = 0;
                            columna++;
                        }
                        if (columna == N){
                            columna = 0;
                        }
                    }
                    
                }
                matriz = newmatriz;
                 
                System.out.println("Termina de crearse la matriz");
            }
            
            //Ejecucion Thread!!
            Threads thread = new Threads();
            thread.setLargo(N);
            thread.setTesoro(T);
            thread.setMatriz(matriz);
            thread.EjecutarThread();
            //Ejecucion Forks!!
            System.out.println("\n");
            
            System.out.println("Comienza ejecucion de forks");

            ForkJoinPool fork = ForkJoinPool.commonPool();
            Forks search = new Forks(matriz, T, N, 0, 0);
            fork.invoke(search);
            //Ejecucion normal!!

             
            
            scanner.close();
        }
        catch(FileNotFoundException e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }
    }
 
}
