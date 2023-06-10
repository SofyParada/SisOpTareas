package Lab3;
public class Normal{
    private int largo;
    private int tesoro;
    private int[][] matriz;

    public Normal(int largo, int tesoro, int[][] matriz) {
        this.largo = largo;
        this.tesoro = tesoro;
        this.matriz = matriz;
    }

    public void BuscarTesoro() {
        //Implementar busqueda de tesoro normal, sin uso de forks ni threads
        for(int i = 0; i < matriz.length; i++ ){
            for(int j = 0; j < matriz[i].length; j++){
                if(matriz[i][j] == 1){
                    System.out.println("El tesoro se encuentra en la coordenada: ["+(i+1)+','+(j+1)+']');
                    break;
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

    public void setMatriz(int[][] x){
        matriz = x;
    }

    public int[][] getMatriz(){
        return matriz;
    }    
    
}