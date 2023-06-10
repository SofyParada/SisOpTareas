package Lab3;
import java.util.concurrent.RecursiveAction;


public class Forks extends RecursiveAction {
    private int[][] matriz;
    private int tesoro;
    private int largo;
    private int posx = 0;
    private int posy = 0;
    private Object lock = new Object();


    public Forks(int[][] matriz, int tesoro, int largo,int posx, int posy,Object lock) {
        this.matriz = matriz;
        this.tesoro = tesoro;
        this.largo = largo;
        this.posx = posx;
        this.posy = posx;
        this.lock = lock;
    }

    protected void compute() {
        int newlargo = largo/2;
        int offsetx = 0;
        int offsety = 0;
        if (largo%2 == 0 && largo > tesoro) {
            for(int i = 0;i<4;i++){
                int[][] newmatriz = new int[largo/2][largo/2];
                switch(i){
                    case 0: //Primer cuadrante (Arriba izquierda)
                    offsetx = 0;
                    offsety = 0;
                    for(int n=0 ;n<newlargo ;n++){
                        for(int m=0 ;m<newlargo ;m++){
                            newmatriz[n][m] = matriz[n][m];
                            
                        }
                    }
                    break;
                    
                    case 1: //Segundo cuadrante (Arriba derecha)
                    offsetx = 0;
                    offsety = newlargo;
                    for(int n=0 ;n<newlargo ;n++){
                        int j = 0;
                        for(int m=newlargo ;m<largo ;m++){
                            newmatriz[n][j] = matriz[n][m];
                            j++;
                        }
                    }
                    break;

                    case 2: //Tercer cuadrante  (Abajo izquierda)
                    offsetx = newlargo;
                    offsety = 0;
                    int j = -1;
                    for(int n=newlargo ;n<largo ;n++){
                        j++;
                        for(int m=0 ;m<newlargo ;m++){
                            newmatriz[j][m] = matriz[n][m];
                        }
                    }
                    break;

                    case 3: //Cuarto cuadrante (Abajo derecha)
                    offsetx = newlargo;
                    offsety = newlargo;
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
                Forks fork = new Forks(newmatriz, tesoro, newlargo, posx + offsetx, posy + offsety, lock);
                fork.fork();
            }

        }
        else {
            if (largo == tesoro){
                for(int n=0 ;n<largo ;n++){
                    for(int m=0 ;m<largo ;m++){
                        int found = matriz[n][m];
                        if (found == 1){
                            int posXTesoro = posx + n + 1; // Actualizar la coordenada X del tesoro
                            int posYTesoro = (posy + m + 1)-tesoro; // Actualizar la coordenada Y del tesoro
                            System.out.println("El tesoro se encuentra en la coordenada: ["+posXTesoro+","+posYTesoro+"]");
                            System.out.println("Termina ejecucion de forks");
                            synchronized (lock) {
                                lock.notifyAll();
                            }
                            return;
                        }
                        
                    }
                }
            }
        } 
    }

}
