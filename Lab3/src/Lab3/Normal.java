package Lab3;
public class Normal{
    private int largo;
    private int tesoro;
    private int[][] matriz;

    public Normal() {
        this.largo = 0;
        this.tesoro = 0;
        this.matriz = new int[0][0];
    }

    public void BuscarTesoro() {
        //Implementar busqueda de tesoro normal, sin uso de forks ni threads
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
