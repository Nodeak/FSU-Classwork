# Kaedon Hamm
# COP3353
# Assigment 5
# 11/3/2017
#!/bin/bash

touch output.txt

#Question 1
cp ~gaitrosd/ufiles/* .

#Question 2
chmod 700 grades
echo "================== Grades test 1 ==================" >> output.txt
grades < t1 >> output.txt
echo "================== Grades test 2 ==================" >> output.txt
grades < t2 >> output.txt

#Question 3
chmod 644 file1
chmod 644 file2

#Question 4
echo "================= diff test 1 =================" >> output.txt
diff file1 file2 >> output.txt
echo "================= diff test 2 =================" >> output.txt
diff -b file1 file2 >> output.txt
echo "================= diff test 3 =================" >> output.txt
diff -b -i file1 file2 >> output.txt

#Question 5
echo "================= grep test 1 =================" >> output.txt
grep -n -i the file1 >> output.txt
echo "================= grep test 2 =================" >> output.txt
grep -n ^The file1 >> output.txt
echo "================= grep test 3 =================" >> output.txt
grep -n -w who file1 >> output.txt

#Question 6
ps -f -u root >> output.txt

#Question 7
echo "================= Directory Listing =================" >> output.txt
ls -l >> output.txt

#Question 8
mkdir archive
tar -czvf a5.tar.gz file1 file2 grades t1 t2
mv a5.tar.gz archive


exit 0
