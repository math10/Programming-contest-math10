void Stirling_numbers_of_the_second_kind(){
    forab(i,1,1000){
        stirling_numbers[i][1] = 1;
        forab(j,2,i){
            stirling_numbers[i][j] = (stirling_numbers[i-1][j-1] + (j*stirling_numbers[i-1][j]));
        }
    }
}
