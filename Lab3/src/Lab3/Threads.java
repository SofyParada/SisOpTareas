package Lab3;
public class Threads extends Thread{
    private int largo;
    private int tesoro;
    private int[][] matriz;

    public Threads() {
        this.largo = 0;
        this.tesoro = 0;
        this.matriz = new int[0][0];
    }

    public void EjecutarThread(){

        this.start();

        // Iniciar los hilos

        // Esperar a que los hilos terminen su ejecución
        try {
            this.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        // Imprimir mensaje de finalización
        System.out.println("Todos los hilos han terminado su ejecución.");
    }



    public void run() {
        System.out.println("Hilo iniciado.");
        int newlargo = largo/2;
        System.out.println("El largo de mi matriz es:"+largo);
        if (largo%2 == 0 ){
            System.out.println("Es divisible");
            for(int i = 0;i<4;i++){
                int[][] newmatriz = new int[largo/2][largo/2];
                switch(i){
                    case 0: //Primer cuadrante (Arriba izquierda)
                    for(int n=0 ;n<newlargo ;n++){
                        for(int m=0 ;m<newlargo ;m++){ 
                            newmatriz[n][m] = matriz[n][m];
                            
                        }
                    }
                    break;
                    
                    case 1: //Segundo cuadrante (Arriba derecha)
                    for(int n=0 ;n<newlargo ;n++){
                        int j = 0;
                        for(int m=newlargo ;m<largo ;m++){
                            newmatriz[n][j] = matriz[n][m];
                            j++;
                        }
                    }
                    break;

                    case 2: //Tercer cuadrante  (Abajo izquierda)
                    int j = -1;
                    for(int n=newlargo ;n<largo ;n++){
                        j++;
                        for(int m=0 ;m<newlargo ;m++){
                            newmatriz[j][m] = matriz[n][m];
                        }
                    }
                    break;

                    case 3: //Cuarto cuadrante (Abajo derecha)
                    j = -1;
                    for(int n=newlargo ;n<largo ;n++){
                        int k = 0;
                        j++;
                        for(int m=newlargo ;m<largo ;m++){
                            newmatriz[j][k] = matriz[n][m];
                            k++;
                        }
                    }
                    break;
                }
                Threads thread = new Threads();
                thread.setLargo(largo/2);
                thread.setTesoro(tesoro);
                thread.setMatriz(newmatriz);
                thread.EjecutarThread();
            }


        }
        else{
            System.out.println("No es divisible");
        }
        System.out.println("Hilo terminado.");
    }


    //Setter Getters
    public void setLargo(int x){
        largo = x;
    }

    public int getLargo(){
        return largo;
    }

    public void setTesoro(int x){
        tesoro = x;
    }

    public int getTesoro(){
        return tesoro;
    }

    public void setMatriz(int[][] x){
        matriz = x;
    }

    public int[][] getMatriz(){
        return matriz;
    }    
    
}
