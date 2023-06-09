package Lab3;
public class Threads extends Thread{
    private int largo;
    private int tesoro;
    private int[][] matriz;
    private int[][] matriz1;
    private int cuadrante;
    private int iteracion;
    private int posx;
    private int posy;
    private Object lock;

    public Threads() {
        this.largo = 0;
        this.tesoro = 0;
        this.matriz = new int[0][0];
        this.matriz1 = new int[0][0];
        this.cuadrante = 0;
        this.iteracion = -1;
        this.posx = 0;
        this.posy = 0;
        this.lock = new Object();
    }

    public void EjecutarThread(){
        System.out.println("Comienza ejecucion de threads");
        this.start();

        // Iniciar los hilos

        try {
            synchronized (lock) {
                lock.wait();
            }
            System.out.println("Termina ejecucion de threads");
            

        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        // Imprimir mensaje de finalización
    }



    public void run() {
        int newlargo = largo/2;
        int offsetx = 0;
        int offsety = 0;
        if (largo%2 == 0 ){
            for(int i = 0;i<4;i++){
                int[][] newmatriz = new int[largo/2][largo/2];
                switch(i){
                    case 0: //Primer cuadrante (Arriba izquierda)
                    cuadrante = 1;
                    offsetx = 0;
                    offsety = 0;
                    for(int n=0 ;n<newlargo ;n++){
                        for(int m=0 ;m<newlargo ;m++){
                            newmatriz[n][m] = matriz[n][m];
                            
                        }
                    }
                    break;
                    
                    case 1: //Segundo cuadrante (Arriba derecha)
                    cuadrante = 2;
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
                    cuadrante = 3;
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
                    cuadrante = 4;
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
                Threads thread = new Threads();
                thread.setLargo(largo/2);
                thread.setTesoro(tesoro);
                thread.setMatriz(newmatriz);
                thread.setMatriz1(matriz1);
                thread.setCuadrante(cuadrante);
                thread.setIteracion(iteracion);
                thread.setPosx(posx + offsetx);
                thread.setPosy(posy + offsety);
                thread.setLock(lock);
                thread.start();
            }


        }
        else{
            for(int n=0 ;n<largo ;n++){
                for(int m=0 ;m<largo ;m++){
                    int found = matriz[n][m];
                    if (found == 1){
                        int posXTesoro = posx + n + 1; // Actualizar la coordenada X del tesoro
                        int posYTesoro = posy + m + 1; // Actualizar la coordenada Y del tesoro
                        System.out.println("El tesoro se encuentra en la coordenada: "+posXTesoro+","+posYTesoro);
                        synchronized (lock) {
                            lock.notifyAll();
                        }
                        this.setIteracion(iteracion);
                        return;
                    }
                }
            }
        }
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

    public void setCuadrante(int x){
        cuadrante = x;
    }

    public void setIteracion(int x){
        iteracion = x;
    }
    public int getIteracion(){
        return iteracion;
    }

    public void setPosx(int x){
        posx = x;
    }

    public void setPosy(int x){
        posy = x;
    }

    public int getCuadrante(){
        return cuadrante;
    }

    public void setMatriz(int[][] x){
        matriz = x;
    }

    public int[][] getMatriz(){
        return matriz;
    }
    public void setMatriz1(int[][] x){
        matriz1 = x;
    }

    public int[][] getMatriz1(){
        return matriz1;
    }
    
    public void setLock(Object x) {
        this.lock = x;
    }
    
}
