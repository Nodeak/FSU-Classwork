# Algorithm is based upon 3 possible paths when looking at a sub array
#   1. Max subarray is the left half  (recursive)
#   2. Max subarray is the right half (recursive)
#   3. Max subarray is somewhere inbetween (requires more analysis)
# This program runs these options on each subarray created and 
#  utilizes the max found of those 3 options.
#
#   **This program might take longer than O(nlogn) because of 
#       extra functions to make output more readable.**
#   However, base algorithm should only take O(nlogn)

def main():
    arr = [31,-41,59,26,-53,58,97,-93,-23,84]
    print("Current array: ", arr)

    # Stores multiple return values
    max_sum, max_arr = max_subarray(arr, 0, len(arr)-1)
    print("\nMax contiguous sub-vector: {}\nSum of sub-vector: {}".format(max_arr, max_sum))


def max_subarray(arr, left, right):
    # If only one element in array
    if (left == right):
        return arr[left], arr[left]

    # flag for middle element
    middle = (left + right) // 2    # rounds to int

    # Checking above stated cases
    left_sum, left_arr = max_subarray(arr, left, middle)                # recursive
    right_sum, right_arr = max_subarray(arr, middle + 1, right)         # recurisve
    inbetween_sum, inbetween_arr = max_inbetween(arr, left, middle, right)

    # Python's comparison value to find max of numbers
    max_sum =  max(left_sum, right_sum, inbetween_sum)

    if (max_sum == left_sum):
        return left_sum, left_arr
    elif(max_sum == right_sum):
        return right_sum, right_arr
    else:
        return inbetween_sum, inbetween_arr



# This is where a definitive number/subarray is chosen
# Where recursion ends and comparisons begin.
def max_inbetween(arr, left, middle, right):
    print("\n\nFull Array:", arr)
    print("Left = {}\tMiddle = {}\tRight = {}".format(arr[left], arr[middle], arr[right]))
    sub_sum = 0
    left_sum = -99999999        # arbitrary number

    # Python's for loop.
    # "middle" = start point
    # "left - 1" = end point
    # "-1" = go backwards
    print("\tL Sub array: ", arr[left:middle+1])
    for i in range(middle, left - 1, -1):
        print("\t\tSum: {} = {} + {}".format(sub_sum + arr[i], sub_sum, arr[i]))
        sub_sum = sub_sum + arr[i]
        if (sub_sum > left_sum):
            left_sum = sub_sum
            max_midleft_ele = middle
            max_left_ele = i


    # Now do the same to the right side, inside to out
    sub_sum = 0
    right_sum = -99999999       # arbitrary number
    print("\tR Sub array:", arr[middle + 1:right + 1])
    for i in range(middle + 1, right + 1):
        print("\t\tSum: {} = {} + {}".format(sub_sum + arr[i], sub_sum, arr[i]))
        sub_sum = sub_sum +  arr[i]
        if (sub_sum > right_sum):
            right_sum = sub_sum
            max_midright_ele = middle + 1
            max_right_ele = i
    
    # Printing middle sub array for easier output
    print("\tR+L Sub array:", arr[max_left_ele:max_right_ele + 1])
    print("\t\tSum: {} = {} + {}".format(left_sum + right_sum, left_sum, right_sum))

    # Return the max 
    # By comparing the two sides from the inside out,
    #   the middle number acts as a connection point b/w
    #   the two comparisons of the left and right side.
    #   That is why we put a left_sum + right_sum in there
    max_sum = max(left_sum + right_sum, left_sum, right_sum)


    # Returns maximum sum along with corresponding sub_array
    if (max_sum == left_sum + right_sum):
        print("-- Max sub array so far: ", arr[max_left_ele:max_right_ele + 1])
        print("-- Sum of sub array: ", max_sum)
        return max_sum, arr[max_left_ele:max_right_ele + 1]
    elif(max_sum == left_sum):
        print("-- Max sub array so far: ", arr[max_left_ele:max_midleft_ele + 1])
        print("-- Sum of sub array: ", max_sum)
        return max_sum, arr[max_left_ele:max_midleft_ele + 1]
    else:
        print("-- Max sub array so far: ", arr[max_midright_ele:max_right_ele + 1])
        print("-- Sum of sub array: ", max_sum)
        return max_sum, arr[max_midright_ele:max_right_ele + 1]

main()