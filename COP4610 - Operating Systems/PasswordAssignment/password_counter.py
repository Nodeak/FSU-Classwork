"""
Author: Kaedon Hamm
Date: April 14, 2020

Notes:
    Although it should've been a lot easier, Python gave me trouble because a lot of the hashable data structures are not sortable
    without some complex and "non-pythonic" way of transfering the data to Lists or of some sort.

    If anyone sees this and knows how to improve on this please let me know.
"""


import operator         # Used to sort (operator.attrgetter())
import sys              # Used for command line args


# Simple main function to handle command line arguments
def __main__():
    if len(sys.argv) > 1:
        if sys.argv[1] == '--top':
            top_passwords()
        elif sys.argv[1] == '--digit':
            perc_digits()
        elif sys.argv[1] == '--dict':
            perc_dict()
    else:
        print("Use the following arguments:\n\t--top: Most used passwords\n\t--digit: Percent only using digits\n\t--dict: Percent in dictionary")


# Finds the Most Used Passwords and their Count
def top_passwords():

    # Class for each word to be stored
    class Pass:
        def __init__(self, word, count):
            self.word = word
            self.count = count

    pwd_dict = {}                                   # Dictionary (Hash Map in C++) for Passwords
    pwd_list = []                                   # List to hold Pass objects

    # with open() as f: is an easy way to read from a file and store the contents in an string. One and Done.
    # the encoding was necessary as it was giving my byte errors or something for some reason.
    with open("10-million-passwords.txt", encoding = "ISO-8859-1") as f:
        lines = f.readlines()

    # Loop through each line in 'lines', stored as 'word'
    for word in lines:
        if not pwd_dict.get(word):                                  # Checks Dictionary for entry with current line
            pwd_dict[word] = 1                                          # Creates new entry with value 1
        else:                                                       # If key exists...
            pwd_dict[word] = pwd_dict.get(word) + 1                     # Increment value (counter) by 1

    # Store each Key:Value pair in new List. Reasoning at top.
    for password, count in pwd_dict.items():
        list_insert = Pass(password, count)                         # Creates new Pass object to store in List
        pwd_list.append(list_insert)

    # sort function found online
    #       sorted(<List>, key=<optional, tells what to sort by>, reverse=<optional, makes it decending order>)
    sort_list = sorted(pwd_list, key=operator.attrgetter('count'), reverse=True)

    # Same as above except 'w' as a paramter for "Write"
    #   Easier than clogging up my terminal
    with open("output", "w") as f:
        for x in sort_list:                                         # for each entry in sort_list, represented as x
            f.write("{} : {}".format(x.count, x.word))              # {} is where the variable in .format() is placed, respectively


# Find percentage of passwords that are only digits
def perc_digits():
    count = 0
    with open("10-million-passwords.txt", encoding = "ISO-8859-1") as f:
        lines = f.readlines()

    for word in lines:
        if word.replace('\n','',1).isdigit():                       # Replaces all \n in the String with ''
            count += 1
    perc = (count / 10000000) * 100
    print("Count: {}".format(count))                                
    print("Percent (only #): {}".format(perc))


# Find percentage of passwords that are in the dictionary
def perc_dict():
    dict_list = set()                                               # Creates an empty Set, used for it's easy entry search, used below
    counter = 0                                                     #   Sets contain unordered and hashable objects, can be removed and added

    with open("wordlist.10000.txt", encoding = "ISO-8859-1") as f:
        lines = f.readlines()
    for dict_word in lines: 
        dict_list.add(dict_word.replace('\n','',1))                 # add() addes object to Set

    with open("10-million-passwords.txt", encoding = "ISO-8859-1") as g:
        lines = g.readlines()
    for word in lines:
        if word.replace('\n','',1) in dict_list:                    # The search function for Sets. Format: if [Object] in [List]:
            counter += 1
    perc = (counter / 10000000) * 100
    print("Count: {}".format(counter))    
    print("In Dictionary: {}".format(perc))            


# Calls main
__main__()