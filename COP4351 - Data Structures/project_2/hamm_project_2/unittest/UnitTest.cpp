// Component to be Tested
#include "../upsample_algos.cpp"
#include "gtest/gtest.h"

// Tests upsampling a 3x3 to 6x6 array
TEST(algorithm, nearestNeighbor){
    int input[] = {1,2,3,4,5,6,7,8,9};
    int old_size = 3;
    int new_size = 6;

    // Hand calculated output
    int expected_output[] = {1,1,2,2,3,3,1,1,2,2,3,3,4,4,5,5,6,6,4,4,5,5,6,6,7,7,8,8,9,9,7,7,8,8,9,9};
    int* temp = nearestNeighbor(old_size, new_size, input);
  for(int i = 0; i < 36; i++){
    EXPECT_EQ(expected_output[i],temp[i]);
  }
}

TEST(algorithm, bilinear){
    int input[] = {1,2,3,4,5,6,7,8,9};
    int old_size = 3;
    int new_size = 6;

    // Hand calculated output
    int expected_output[] = {1,1,1,2,2,2,2,2,2,3,3,3,3,3,3,4,4,4,4,4,4,5,5,5,5,5,5,6,6,6,6,6,6,7,7,7};
    int* temp = bilinear(old_size, old_size, new_size, new_size, input);
  for(int i = 0; i < 36; i++){
  //  std::cout << temp[i] << ", ";
    EXPECT_EQ(expected_output[i],temp[i]);
  }
}

TEST(test, l1_metric){
    int upsampled[] = {1,2,3,4,5,6};
    int original[] = {2,3,4,5,6,7};
    EXPECT_EQ(6, l1_metric(upsampled, original, 6));
}

int main(int ac, char* av[])
{
  testing::InitGoogleTest(&ac, av);
  return RUN_ALL_TESTS();
}