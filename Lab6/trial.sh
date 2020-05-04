#!/bin/sh


# echo "Read first value"
# read a
# echo "Read second value"
# read b
# echo "elements before swapping are $a , $b "
# temp=$a
# a=$b
# b=$temp
# # a=$((a+b))
# # b=$((a-b))
# # a=$((a-b))
# echo "elements after swapping are $a , $b"

echo "Enter Principal amount : "
read p
echo "Enter number of years : "
read t
echo "Enter rate of interest : "
read r
si=$(((p*t*r)/100))
echo "Simple Interest : $si"