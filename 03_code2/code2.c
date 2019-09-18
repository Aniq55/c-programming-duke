
int printTriangle(int size) {
  //start with starCount being 0
  int starCount = 0;
  //count from 0 (inclusive) to size (exclusive), for each number i that you count
  for(int i=0; i<size; i++)
  {
    for(int j=0; j<=i; j++)
    {
      printf("*");
      starCount++;
    }
    printf("\n");;
  }
  return starCount;
}


int main(void) {
  int numStars;
  printf("Here is a triangle with height 4\n");
  numStars = printTriangle(4);
  printf("That triangle had %d total stars\n", numStars);
  //now print "Here is a triangle with height 7\n"
  printf("Here is a triangle with height 7\n");
  //then call printTriangle, passing in 7, and assign the result to numStars
  numStars = printTriangle(7);
  //finally, print "That triangle had %d total stars\n", such that the %d 
  //prints the value of numStars
  printf("That triangle had %d total stars\n", numStars);

  return 0;
}



