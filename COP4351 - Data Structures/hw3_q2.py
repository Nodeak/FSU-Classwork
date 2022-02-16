def kth_largest(arr1, arr2, k):
    print("\n\ns1 = ", arr1)
    print("s2 = ", arr2)
    if arr1 is None and arr2 is not None:
        return arr2[k]
    elif arr1 is not None and arr2 is None:
        return arr1[k]
    
    m1 = len(arr1) // 2
    m2 = len(arr2) // 2
    print("m1 + m2 = ", m1 + m2)
    if m1 + m2 < k:
        print("First")
        print("Comparing {} <= {}".format(arr1[m1], arr2[m2]))
        if (arr1[m1] <= arr2[m2]):
            return kth_largest(arr1[m1:], arr2, k - m1 - 1)
        else:
            return kth_largest(arr1, arr2[m2:], k - m2 - 1)
    else:
        print("Second.")
        print("Comparing {} <= {}".format(arr1[m1], arr2[m2]))
        if (arr1[m1] <= arr2[m2]):
            return kth_largest(arr1, arr2[:m2], k)
        else:
            return kth_largest(arr1[:m1], arr2, k)


def main():
    arr1 = [2,3,7,10,15,16]
    arr2 = [1,4,6,9]
    print(kth_largest(arr1, arr2, 3))

main()