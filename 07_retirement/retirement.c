#include <stdio.h>
#include <stdlib.h>

struct _retire_info{
  int months;
  double contribution;
  double rate_of_return;
};

typedef struct _retire_info retire_info;

double get_balance(double balance, retire_info info){
  balance += balance*info.rate_of_return;
  balance += info.contribution;
  return balance;
}

void print_info(double balance, int months){
  printf("Age %3d  month %2d you have $%.2lf\n", months/12, months%12, balance);
  
}

void retirement(int startAge, double initial, retire_info working, retire_info retired){
  double balance = initial;

  int i = 0;
  int months = startAge - 1;
  
  for(i=0; i< working.months; i++){
    months ++;
    print_info(balance, months);
    balance = get_balance(balance, working);
  }

  for(i=0; i< retired.months; i++){
    months++;
    print_info(balance, months);
    balance = get_balance(balance, retired);
  }
  
}


int main(){
  retire_info working;
  retire_info retired;

  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 0.045/12;

  retired.months = 384;
  retired.contribution = -4000;
  retired.rate_of_return = 0.01/12;

  retirement(327, 21345, working, retired);

  return 0;
}
