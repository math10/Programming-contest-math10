
int64 nCr[1010][1010];
void make_nCr(){
     nCr[0][0] = 1;
        For(i,1000) {
                nCr[i][0] = 1;
                For(j,i) {
                        nCr[i][j] = (nCr[i-1][j-1] + nCr[i-1][j]);
                }
        }
}
