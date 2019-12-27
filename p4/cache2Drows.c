int arr2D[3000][500];

int main(){
    for (int row = 0; row < 3000; row++){
        for (int col = 0; col < 500; col++){
            arr2D[row][col] = row + col;
        }
    }
}
